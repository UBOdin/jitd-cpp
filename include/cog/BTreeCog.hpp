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
      //return Iterator<Tuple>(new SeqIterator<Tuple>(lhs, sep, rhs));
      return Iterator<Tuple>(new FastIterator<Tuple>(lhs, sep, rhs));
      //return Iterator<Tuple>(new FastIterator<Tuple>(this));
    }

    int size(){ return lhs->size() + rhs->size(); }
    int lsize(){return lhs->size();}
    int rsize(){return rhs->size();}
    bool lhs_leaf()
    {
      
      if(lhs->type() == COG_SORTED_ARRAY || lhs->type() == COG_ARRAY )
      {
        return true;
      }
      else
      {
        return false;
      }
      //return lhs;
    }

    bool rhs_leaf()
    {
      if(rhs->type() == COG_SORTED_ARRAY || rhs->type() == COG_ARRAY )
      {
        return true;
      }
      else
      {
        return false;
      }
      //return rhs;
    }
    std::shared_ptr<CogHandleBase<Tuple> > lhs_ptr() 
    {
      return lhs;
    }
    std::shared_ptr<CogHandleBase<Tuple> > lhs_most() 
    {
      
      return lhs->lhs_most();
    }
    std::shared_ptr<CogHandleBase<Tuple> > rhs_ptr() 
    {
      return rhs;
    }
    std::shared_ptr<CogHandleBase<Tuple> > rhs_most() 
    {
      if(rhs->type() == COG_ARRAY || rhs->type() == COG_SORTED_ARRAY)
      {
        //std::cout<<"child is leaf"<<std::endl;
        return rhs;
      }
      else
      {
        return rhs->rhs_most();
      }
      
    }
    Tuple getSepVal(){return sep;}
    void apply_to_children(std::function<void(CogHandle<Tuple>)> fn) 
    {
      //std::cout<<"in apply to children"<<std::endl;
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
    // inline void swapInNewCog(CogHandle<Tuple> &newRoot, CogHandle<Tuple> &placeholder) 
    // {
    //   bool succeeded = false;
    //   while(!succeeded){
    //     placeholder = root;
    //     succeeded = std::atomic_compare_exchange_strong(
    //       &root,        // This value gets atomically replaced...
    //       &placeholder, // ... if this is currently its value
    //       newRoot       // This value replaces it.
    //     );
    //   }
    // }
    // void cog_insert_pos(CogHandle<Tuple> insert_val)
    // {
    //   std::cout<<"BTREE INSERT"<<std::endl;
    //   std::cout<<insert_val->type();
    //   Buffer<Tuple> buff = insert_val->getBuffer();
    //   Tuple insert_value = buff->begin()->key;
    //   std::cout<<"insert value is "<< insert_value.key << std::endl;
    //   CogHandle<Tuple> ret;
    //   if(insert_value < sep)
    //   {
    //     if(lhs_leaf())
    //     {
    //       std::cout<<"lhs of btree is a leaf"<< sep <<std::endl;
    //       CogPtr<Tuple> new_cog = (CogPtr<Tuple>(new ConcatCog<Tuple>(lhs,insert_val)));
    //       lhs->put(new_cog);
  

    //     }
    //     else
    //     {
    //       std::cout<<"lhs of btree is a not leaf"<<std::endl;
    //       lhs->cog_insert_pos(insert_val);
    //       std::cout<<"blah...blah"<<std::endl;
    //     }

    //   }
    //   else
    //   {
    //     if(rhs_leaf())
    //     {
    //       std::cout<<"rhs of btree is a leaf"<<std::endl;
    //     }
    //     else
    //     {
    //       std::cout<<"rhs of btree is a not leaf"<<std::endl;
    //       rhs->cog_insert_pos(insert_val);
    //     }
    //   }
    // }
    bool desc_key(Record key)
    {
     
      //std::cout<<"In BTree getKey";
        if(!(key < sep)) 
        {
          //std::cout<<"In RHS :the sep value is "<< sep <<std::endl;
          return rhs->desc_key(key);
        }     
        else
        {
          return false;
        }
      

    }
    const Tuple sep;
    const CogHandle<Tuple> lhs;
    const CogHandle<Tuple> rhs;
  
};