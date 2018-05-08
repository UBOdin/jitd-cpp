template <class Tuple>
class ConcatCog : public Cog<Tuple>
{
  public:
    ConcatCog (CogHandle<Tuple> lhs, CogHandle<Tuple> rhs) :
      Cog<Tuple>(COG_CONCAT), lhs(lhs), rhs(rhs) {}
  
    Iterator<Tuple> iterator()
    {
      return Iterator<Tuple>(new MergeIterator<Tuple>(lhs, rhs));
    }
    int size(){ return lhs->size() + rhs->size(); }
    void apply_to_children(std::function<void(CogHandle<Tuple>)> fn) 
    {
      fn(lhs);
      fn(rhs);
    }
    
    void printDebug(int depth)
    {
      Cog<Tuple>::printPrefix(depth);
      std::cout << "Concat" << std::endl;
      lhs->printDebug(depth+1);
      rhs->printDebug(depth+1);
    }
    
    CogHandle<Tuple> lhs;
    CogHandle<Tuple> rhs;
};