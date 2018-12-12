#include <climits>
// typedef int Score;

// template<class Tuple>
//   using ScoreFunctionReturn =
//       std::experimental::optional<
//         std::pair<
//           Score,
//           Transform<Tuple>
//         >
//       >;
// #define NO_TRANSFORMS                   ScoreFunctionReturn<Tuple>()
// #define TRANSFORM_WITH(score,function)  ScoreFunctionReturn<Tuple>(std::pair<Score, Transform<Tuple>>(score, function))


// template<class Tuple>
//   using ScoreFunction = std::function<ScoreFunctionReturn<Tuple>(CogPtr<Tuple>)>;

// template <class Tuple>
// struct Action {

//     Action(CogHandle<Tuple> target, Transform<Tuple> effect, Score score) : 
//       target(target), effect(effect), score(score) {}
//     CogHandle<Tuple> target;
//     Transform<Tuple> effect;
//     Score score;

//     inline const bool operator<(const Action<Tuple> &other){ return score < other.score; }
    
//   };

// template<class Tuple>
// inline bool operator<(const Action<Tuple> &a, const Action<Tuple> &b){ return a.score < b.score; }

// template<class Tuple>
//   ScoreFunctionReturn<Tuple> NoOpScoreFunction(CogPtr<Tuple> cog){ 
//     //std::cerr << "WARNING: USING NO OP SCORING FUNCTION\n";
//     return ScoreFunctionReturn<Tuple>();
//   }
// template <class Tuple>



template <class Tuple> class UniversalPolicy {
  
  std::priority_queue<Action<Tuple>> todos;
  CogPtr<Tuple> cogToMerge;
  long long int min_score;
  CogHandle<Tuple> oldCogHandle;
  CogHandle<Tuple> pushdownSwapHandle;
  ScoreFunction<Tuple> score;

  public:

    UniversalPolicy() : todos(), score(NoOpScoreFunction<Tuple>), min_score(LLONG_MAX), cogToMerge(), oldCogHandle(), pushdownSwapHandle()
    {}

    void init(CogHandle<Tuple> root){
      while(!todos.empty()){ todos.pop(); }
      enqueueCog(root);
      
    }

    void setScoreFunction(ScoreFunction<Tuple> newFn) { score = newFn; }

    inline bool act(){
      
        if(todos.empty()){ return false; }
        Action<Tuple> next = todos.top(); 
        todos.pop();
        CogPtr<Tuple> target = next.target->get();
        
        CogPtr<Tuple> replacement = target;
        if(next.effect(replacement)){
          //target->apply_to_children(std::bind(&UniversalPolicy::dequeueCog, this, std::placeholders::_1));
          next.target->put(replacement);
          enqueueCog(next.target);

        }
        return true;
      
    }
    inline bool pushdown_act_once(CogHandle<Tuple> root)
    {
      CogPtr<Tuple> target = root->get();
      pushdownSwapHandle = root;
      if(target->type == COG_CONCAT)
      {
        std::cout<<"concat cog found"<<std::endl;
        pushDown(target);
        root->put(target);
        return true;
      }
      else
      {
        return false;
      }
      
    }
    inline bool merge_act(CogHandle<Tuple> root)
    {
      min_score = LLONG_MAX;
      CogPtr<Tuple> target = root->get();
      //std::cout<<"in merge act"<<std::endl;
      //std::cout<<"in merge act root sep "<< target->getSepVal()<<","<<target->type<<std::endl;
      //std::cout<<"new impl"<<std::endl;
      if(target->type == COG_SORTED_ARRAY || target->type == COG_ARRAY){return false;}
      CogHandle<Tuple> lhsHandle = target->lhs_ptr();
      CogHandle<Tuple> rhsHandle = target->rhs_ptr();
      //std::cout<<"Cog Handle" << lhsHandle->type() << rhsHandle->type() <<std::endl;
      //if(target->lhs_leaf() && target->rhs_leaf()){mergeArray(target);root->put(target);return true;}
      if(lhsHandle->type() == COG_SORTED_ARRAY && rhsHandle->type() == COG_SORTED_ARRAY)
      {
        //std::cout<<"ROOT merge"<<std::endl;
        mergeArray(target);root->put(target);return true;
      }
      // if(lhsHandle->type() == COG_ARRAY && rhsHandle->type() == COG_ARRAY)
      // {
      //   //std::cout<<"ROOT merge"<<std::endl;
      //   mergeArray(target);root->put(target);return true;
      // }
      // if(lhsHandle->type() == COG_SORTED_ARRAY && rhsHandle->type() == COG_ARRAY)
      // {
      //   //std::cout<<"ROOT merge"<<std::endl;
      //   mergeArray(target);root->put(target);return true;
      // }
      // if(lhsHandle->type() == COG_ARRAY && rhsHandle->type() == COG_SORTED_ARRAY)
      // {
      //   //std::cout<<"ROOT merge"<<std::endl;
      //   mergeArray(target);root->put(target);return true;
      // }
      target->apply_to_children(std::bind(&UniversalPolicy::scoreCog, this, std::placeholders::_1));
        
      mergeArray(cogToMerge);
        
      oldCogHandle->put(cogToMerge);


      return true;
    }
    inline void scoreCog (CogHandle<Tuple> Target)
    {
      CogPtr<Tuple> cog = Target->get(); 
      if(cog->type == COG_BTREE || cog->type == COG_CONCAT)
      {
      //std::cout<<"The sep value is "<<cog->getSepVal()<<std::endl;
      long long int score = 0;
      CogHandle<Tuple> lhsCog = cog->lhs_ptr();

      //std::cout<<"Cog Handle lhs" << lhsCog->type()  <<std::endl;
      CogHandle<Tuple> rhsCog = cog->rhs_ptr();
      //std::cout<<"Cog Handle rhs" << rhsCog->type() <<std::endl;
      //std::cout<<"HERE"<<std::endl;
      
      //if(cog->lhs_leaf() && cog->rhs_leaf())
      if(lhsCog->type()==COG_SORTED_ARRAY && rhsCog->type()==COG_SORTED_ARRAY)
      {
        //std::cout<<"in if"<<std::endl;
        int lhs_size = cog->lsize();
        int rhs_size = cog->rsize();
        score = std::abs(lhs_size - rhs_size);
       
        if(score < min_score)
        {
          //std::cout<<"CTM Sep " << cog->getSepVal()<<std::endl;
            min_score = score;
            cogToMerge = cog;
            oldCogHandle = Target;
            
        }
      }
      else
      {
        cog->apply_to_children(std::bind(&UniversalPolicy::scoreCog, this, std::placeholders::_1));

      }
    }
      
    }
    inline void dequeueCog(CogHandle<Tuple> target)
    {
      std::cerr << "dequeue cog unimplemented\n";
      assert(0);
    }
  
    inline void enqueueCog(CogHandle<Tuple> target)
    {
      // std::cerr << "Enqueue " << target << std::endl;
      CogPtr<Tuple> cog = target->get();
      std::experimental::optional<std::pair<Score,Transform<Tuple>>> op = score(cog);
      if(op){
        todos.emplace(
          target,
          op->second,
          op->first
        );        
      }
      cog->apply_to_children(std::bind(&UniversalPolicy::enqueueCog, this, std::placeholders::_1));
    }

    
    inline void describeNext()
    {
      if(todos.empty()){ std::cout << "[ No Op ]\n"; }
      else 
      {
          //std::cout<<"todos not empty"<<std::endl<<todos.size();
          std::cout << "Target: " << todos.top().target 
                  // << "; Effect: " << todos.top().effect 
                  << "; Score: " << todos.top().score << std::endl;
        
      }
    }
    




  private:

};
