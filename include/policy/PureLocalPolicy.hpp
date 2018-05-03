
typedef int Score;

template <class Tuple>
  using ScoreFunction = 
    std::function<
      std::experimental::optional<
        std::pair<
          Score,
          Transform<Tuple>
        >
      >(CogPtr<Tuple>)
    >;

template <class Tuple>
struct Action {
    CogHandle<Tuple> target;
    Transform<Tuple> effect;
    Score score;

    inline bool operator<(const Action<Tuple> &other){ return score < other.score; }
  };

template<class Tuple>
inline bool operator<(const Action<Tuple> &a, const Action<Tuple> &b){ return a.score < b.score; }


template <class Tuple> class PureLocalPolicy {
  
  std::priority_queue<Action<Tuple>> todos;
  ScoreFunction<Tuple> score;

  public:

    PureLocalPolicy(CogHandle<Tuple> root)
    {
      enqueue_cog
    }

    inline bool act(){
      if(todos.empty()){ return false; }
      Action<Tuple> next = todos.pop();
      CogPtr<Tuple> target = next.target->get();
      CogPtr<Tuple> replacement = target;
      if(next.effect(replacement)){
        target->apply_to_children(this->dequeue_cog);
        next.target->put(replacement);
        enqueue_cog(next.target);
      }
      return true;
    }

    inline void dequeue_cog(CogHandle<Tuple> target)
    {
      std::cerr << "dequeue cog unimplemented\n";
      exit(-1);
    }

    inline void enqueue_cog(CogHandle<Tuple> target)
    {
      CogPtr<Tuple> cog = target.get();
      std::experimental::optional<std::pair<Score,Transform<Tuple>>> op = score(cog);
      if(op){
        todos.emplace(
          target,
          op->second(),
          op->first()
        );        
      }
      cog->apply_to_children(this->enqueue_cog);
    }




  private:

};