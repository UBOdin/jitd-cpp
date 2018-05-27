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
    bool getKey(Tuple key, BufferElement<Tuple> &result)
    {
     
      //std::cout<<"In BTree getKey";
      if(key < sep)
      {
        //std::cout<<"In LHS :the sep value is "<< sep <<std::endl;
        return lhs->getKey(key,result);
      }
      else
      {
         //std::cout<<"In RHS :the sep value is "<< sep <<std::endl;
        return rhs->getKey(key,result);
      }

    }
    const Tuple sep;
    const CogHandle<Tuple> lhs;
    const CogHandle<Tuple> rhs;
  
};