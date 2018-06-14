
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
// struct MergeAction {

//     MergeAction(CogHandle<Tuple> target, Transform<Tuple> effect, Score score) : 
//       target(target), effect(effect), score(score) {}
//     CogHandle<Tuple> target;
//     Transform<Tuple> effect;
//     Score score;

//     inline const bool operator>(const MergeAction<Tuple> &other){ return score > other.score; }
    
//   };

// template<class Tuple>
// inline bool operator>(const MergeAction<Tuple> &a, const MergeAction<Tuple> &b){ return a.score > b.score; }


template <class Tuple> class UniversalPolicy {
  
  std::priority_queue<Action<Tuple>> todos;
  //std::priority_queue<MergeAction<Tuple>> mergePQ;

  ScoreFunction<Tuple> score;

  public:

    UniversalPolicy() : todos(), score(NoOpScoreFunction<Tuple>)
    {}

    void init(CogHandle<Tuple> root){
      while(!todos.empty()){ todos.pop(); }
      //while(!mergePQ.empty()){ mergePQ.pop(); }
      enqueueCog(root);
      //enqueueCogMerge(root);
    }

    void setScoreFunction(ScoreFunction<Tuple> newFn) { score = newFn; }

    inline bool act(std::string policy_name){
      //std::cout<<"Universal Policy"<<std::endl;
      if(policy_name == "crack" || policy_name == "sort" || policy_name == "divide" || policy_name == "merge")
      {
        if(todos.empty()){ std::cout<<"Todos empty"<<std::endl;return false; }
        Action<Tuple> next = todos.top(); 
        //CogType val = (next.target->type());
        //std::cout<<"the PQ elem Target: " << val << "; Score: " << next.score <<std::endl;
        todos.pop();
        CogPtr<Tuple> target = next.target->get();
        CogPtr<Tuple> replacement = target;
        if(next.effect(replacement)){
          target->apply_to_children(std::bind(&UniversalPolicy::dequeueCog, this, std::placeholders::_1));
          next.target->put(replacement);
          enqueueCog(next.target);

        }
        return true;
      }
      // if(policy_name == "sort")
      // {
      //   if(todos.empty()){ std::cout<<"Todos sort empty"<<std::endl;return false; }
      //   Action<Tuple> next = todos.top(); 
      //   //CogType val = (next.target->type());
      //   //std::cout<<"the PQ elem Target: " << val << "; Score: " << next.score <<std::endl;
      //   todos.pop();
      //   CogPtr<Tuple> target = next.target->get();
      //   CogPtr<Tuple> replacement = target;
      //   if(next.effect(replacement)){
      //     target->apply_to_children(std::bind(&UniversalPolicy::dequeueCog, this, std::placeholders::_1));
      //     next.target->put(replacement);
      //     enqueueCog(next.target);

      //   }
      //   return true;
      // }
      // if(policy_name == "merge")
      // {
      //   //std::cout << "merging...." << std::endl;
      //   if(todos.empty()){ std::cout<<"Todos merge empty"<<std::endl;return false; }
      //   Action<Tuple> next = todos.top(); 
      //   todos.pop();
      //   CogPtr<Tuple> target = next.target->get();
      //   CogPtr<Tuple> replacement = target;
      //   if(next.effect(replacement)){
      //     target->apply_to_children(std::bind(&UniversalPolicy::dequeueCog, this, std::placeholders::_1));
      //     next.target->put(replacement);
      //     enqueueCog(next.target);

      //   }
      //   return true;
      // }

      else
      {
        std::cout <<"No valid atomic policy"<<std::endl;
        return false;
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
      //std::cout << "In enqueue cog emplace The target is  " << target <<"The transform is "<< op->second.get() <<"The score is " << op->first << std::endl;
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
