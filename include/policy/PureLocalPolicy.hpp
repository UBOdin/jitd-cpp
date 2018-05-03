

typedef int Score;

template <class Tuple>
  using ScoreFunction = std::function<Score(CogPtr<Tuple>, Transform<Tuple> &)>;

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
  
  public:
    inline void init(CogHandle<Tuple> &root){

    }

    inline bool act(){
      if(todos.empty()){ return false; }
      Action<Tuple> next = todos.pop();
      CogPtr<Tuple> target = next.target->get();
      dequeue_descendents(target);
      next.effect(target);
      requeue_descendents(target);
      return true;
    }


  private:
    std::priority_queue<Action<Tuple>> todos;

};