
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
  ScoreFunction<Tuple> score;

  public:

    UniversalPolicy() : todos(), score(NoOpScoreFunction<Tuple>), min_score(LLONG_MAX), cogToMerge(), oldCogHandle()
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
    inline bool merge_act(CogHandle<Tuple> root)
    {
      min_score = LLONG_MAX;
      CogPtr<Tuple> target = root->get();
      //std::cout<<"in merge act root sep "<< target->getSepVal()<<","<<target->type<<std::endl;
      if(target->type == COG_SORTED_ARRAY){return false;}
      if(target->lhs_leaf() && target->rhs_leaf()){mergeArray(target);root->put(target);return true;}
        //std::cout<<"in if "<<std::endl;
        target->apply_to_children(std::bind(&UniversalPolicy::scoreCog, this, std::placeholders::_1));
        
        mergeArray(cogToMerge);
        
        oldCogHandle->put(cogToMerge);


        return true;
    }
    inline void scoreCog (CogHandle<Tuple> Target)
    {
      CogPtr<Tuple> cog = Target->get(); 
      long long int score = 0;
      
      if(cog->lhs_leaf() && cog->rhs_leaf())
      {

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
        
          std::cout << "Target: " << todos.top().target 
                  // << "; Effect: " << todos.top().effect 
                  << "; Score: " << todos.top().score << std::endl;
        
      }
    }
    




  private:

};
