
typedef int Score;

template<class Tuple>
  using ScoreFunctionReturn =
      std::experimental::optional<
        std::pair<
          Score,
          Transform<Tuple>
        >
      >;
#define NO_TRANSFORMS                   ScoreFunctionReturn<Tuple>()
#define TRANSFORM_WITH(score,function)  ScoreFunctionReturn<Tuple>(std::pair<Score, Transform<Tuple>>(score, function))


template<class Tuple>
  using ScoreFunction = std::function<ScoreFunctionReturn<Tuple>(CogPtr<Tuple>)>;

template <class Tuple>
struct Action {

    Action(CogHandle<Tuple> target, Transform<Tuple> effect, Score score) : 
      target(target), effect(effect), score(score) {}
    CogHandle<Tuple> target;
    Transform<Tuple> effect;
    Score score;

    inline const bool operator<(const Action<Tuple> &other){ return score < other.score; }
  };

template<class Tuple>
inline bool operator<(const Action<Tuple> &a, const Action<Tuple> &b){ return a.score < b.score; }

template<class Tuple>
  ScoreFunctionReturn<Tuple> NoOpScoreFunction(CogPtr<Tuple> cog){ 
    //std::cerr << "WARNING: USING NO OP SCORING FUNCTION\n";
    return ScoreFunctionReturn<Tuple>();
  }


template <class Tuple> class PureLocalPolicy {
  
  std::priority_queue<Action<Tuple>> todos;
  ScoreFunction<Tuple> score;

  public:

    PureLocalPolicy() : todos(), score(NoOpScoreFunction<Tuple>)
    {}

    void init(CogHandle<Tuple> root){
      while(!todos.empty()){ todos.pop(); }
      enqueueCog(root);
    }

    void setScoreFunction(ScoreFunction<Tuple> newFn) { score = newFn; }

    inline bool act(){
      if(todos.empty()){ return false; }
      Action<Tuple> next = todos.top(); todos.pop();
      CogPtr<Tuple> target = next.target->get();
      CogPtr<Tuple> replacement = target;
      if(next.effect(replacement)){
        target->apply_to_children(std::bind(&PureLocalPolicy::dequeueCog, this, std::placeholders::_1));
        next.target->put(replacement);
        enqueueCog(next.target);
      }
      return true;
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
      cog->apply_to_children(std::bind(&PureLocalPolicy::enqueueCog, this, std::placeholders::_1));
    }

    inline void describeNext()
    {
      if(todos.empty()){ std::cout << "[ No Op ]\n"; }
      else {
        std::cout << "Target: " << todos.top().target 
                  // << "; Effect: " << todos.top().effect 
                  << "; Score: " << todos.top().score << std::endl;
      }
    }




  private:

};