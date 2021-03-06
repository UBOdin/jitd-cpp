// LHS < k <= RHS
template <class Tuple>
class BTreeCog : public Cog<Tuple>
{
  public:
    BTreeCog (
      CogHandle<Tuple> lhs, 
      CogHandle<Tuple> rhs, 
      Tuple sep
    ) : 
      Cog<Tuple>(COG_BTREE), lhs(lhs), sep(sep), rhs(rhs) {}
  
    Iterator<Tuple> iterator()
    {
      return Iterator<Tuple>(new SeqIterator<Tuple>(lhs, sep, rhs));
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
      std::cout << "BTree[" << sep << "]" << std::endl;
      lhs->printDebug(depth+1);
      rhs->printDebug(depth+1);
    }
    const Tuple sep;
    const CogHandle<Tuple> lhs;
    const CogHandle<Tuple> rhs;
  
};