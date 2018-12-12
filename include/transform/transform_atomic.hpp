
#include "cog.hpp"

///////////// Atomic Transform Implementations /////////////


template <class Tuple>
  bool randomSplitArray(CogPtr<Tuple> &cog)
    {
      if(cog->type == COG_ARRAY) {
        //std::cout <<"Array Cog Found ready to split" <<std::endl;
        ArrayCog<Tuple> *arr = (ArrayCog<Tuple> *)cog.get();
        BufferElement<Tuple> pivot = arr->randElement();
        std::pair<Buffer<Tuple>,Buffer<Tuple>> splits = arr->split(*pivot);
        CogPtr<Tuple> lhsC =
          CogPtr<Tuple>(
            new ArrayCog<Tuple>(
              splits.first, 
              splits.first->begin(), 
              splits.first->end()
            ));
        CogPtr<Tuple> rhsC =
          CogPtr<Tuple>(
            new ArrayCog<Tuple>(
              splits.second, 
              splits.second->begin(), 
              splits.second->end()
            ));


        CogHandle<Tuple> lhsH(new CogHandleBase<Tuple>(lhsC));
        CogHandle<Tuple> rhsH(new CogHandleBase<Tuple>(rhsC));

        cog = CogPtr<Tuple>(new BTreeCog<Tuple>(lhsH, rhsH, *pivot));
        return true;
      }
      else
      {return false;}
    }
template <class Tuple>
  bool divideArray(CogPtr<Tuple> &cog)
    {
      if(cog->type == COG_ARRAY) {
        //std::cout <<"Array Cog Found ready to Divide" <<std::endl;
        ArrayCog<Tuple> *arr = (ArrayCog<Tuple> *)cog.get();
        BufferElement<Tuple> pivot = arr->randElement();
        std::pair<Buffer<Tuple>,Buffer<Tuple>> splits = arr->split(*pivot);
        CogPtr<Tuple> lhsC =
          CogPtr<Tuple>(
            new ArrayCog<Tuple>(
              splits.first, 
              splits.first->begin(), 
              splits.first->end()
            ));
        CogPtr<Tuple> rhsC =
          CogPtr<Tuple>(
            new ArrayCog<Tuple>(
              splits.second, 
              splits.second->begin(), 
              splits.second->end()
            ));


        CogHandle<Tuple> lhsH(new CogHandleBase<Tuple>(lhsC));
        CogHandle<Tuple> rhsH(new CogHandleBase<Tuple>(rhsC));

        cog = CogPtr<Tuple>(new ConcatCog<Tuple>(lhsH, rhsH));
        return true;
      }
      else
      {return false;}
    }    
template <class Tuple>
  bool pushDown(CogPtr<Tuple> &cog)
    {
      BufferElement<Tuple> singleton;
      std::cout<<"atomic transform push down"<<std::endl;
      if(cog->type == COG_CONCAT)
      {
        std::cout<<"concat cog found"<<std::endl;
        CogHandle<Tuple> lhs = cog->lhs_ptr();
        CogHandle<Tuple> rhs = cog->rhs_ptr();
        Tuple sep = lhs->getSepVal();
        std::cout<<"lhs"<<lhs->type()<<sep.key;
        std::cout<<"rhs"<<rhs->type();
        if(rhs->type() == COG_ARRAY)
        {
          singleton = rhs->get()->getBuffer()->begin();
          std::cout<<"singleton"<<singleton->key<<std::endl;
        }
        if(lhs->type() == COG_BTREE)
        {
          std::cout<<"BTEE FOUND"<<std::endl;
          if(singleton->key < sep.key)
          {
            ConcatCog<Tuple> *newRootCog = new ConcatCog<Tuple>(lhs->lhs_ptr(),rhs);
            BTreeCog<Tuple> *newRoot = new BTreeCog<Tuple>(CogHandle<Tuple>(new CogHandleBase<Tuple>(CogPtr<Tuple>(newRootCog))),lhs->rhs_ptr(),sep);
            cog = CogPtr<Tuple>(newRoot);
          }
          else
          {
            ConcatCog<Tuple> *newRootCog = new ConcatCog<Tuple>(lhs->rhs_ptr(),rhs);
            BTreeCog<Tuple> *newRoot = new BTreeCog<Tuple>(lhs->lhs_ptr(),CogHandle<Tuple>(new CogHandleBase<Tuple>(CogPtr<Tuple>(newRootCog))),sep);
            cog = CogPtr<Tuple>(newRoot);
          }
        }
        
    //    ConcatCog<Tuple> *newRootCog = new ConcatCog<Tuple>(lhs->lhs_ptr(),rhs);
    //    BTreeCog<Tuple> *newRoot = new BTreeCog<Tuple>(CogHandle<Tuple>(new CogHandleBase<Tuple>(CogPtr<Tuple>(newRootCog))),lhs->rhs_ptr(),sep);
      }
      return false;
    }
template <class Tuple>
  bool sortArray(CogPtr<Tuple> &cog)
    {
      if(cog->type == COG_ARRAY){
        //std::cout <<"Array Cog Found ready to sort" <<std::endl;
        ArrayCog<Tuple> *arr = (ArrayCog<Tuple> *)cog.get();
        Buffer<Tuple> sorted = arr->sortedBuffer();
        cog = CogPtr<Tuple>(new SortedArrayCog<Tuple>(
          sorted, sorted->begin(), sorted->end()
        ));
        //std::cout<<"Sorting Complete" <<std::endl;
        return true;
      }
      else
      {return false;}
    }
template <class Tuple>
  bool mergeArray(CogPtr<Tuple> &cog)
    {
      //std::cout<<"cog to merge "<< cog;
      if(cog->type == COG_BTREE){
        //std::cout <<"Btree Cog Found here ready to merge" <<std::endl;
        BTreeCog<Tuple> *btree = (BTreeCog<Tuple> *)cog.get();
        CogPtr<Tuple> lhs_ptr = btree->lhs->get();
        CogPtr<Tuple> rhs_ptr = btree->rhs->get();
        // Tuple sep = btree->sep;
        // //std::cout<<"Btree["<<sep<<"]"<<std::endl;
        // // std::cout<< "lhs ptr is "<<lhs_ptr->type << std::endl;
        if(lhs_ptr->type == COG_SORTED_ARRAY && rhs_ptr->type == COG_SORTED_ARRAY  )
        {
          Buffer<Tuple> lhs_buff = lhs_ptr->getBuffer();
          Buffer<Tuple> rhs_buff = rhs_ptr->getBuffer();
          //std::cout << "Here... "<<std::endl;
          BufferElement<Tuple> lhs_start = lhs_buff->begin();
          BufferElement<Tuple> lhs_end = lhs_buff->end();
          BufferElement<Tuple> rhs_start = rhs_buff->begin();
          BufferElement<Tuple> rhs_end = rhs_buff->end();
          Buffer<Tuple> merged_array (new std::vector<Tuple>);
          for(;lhs_start<lhs_end;++lhs_start)
          {
            merged_array->push_back(*lhs_start);
          }
          for(;rhs_start<rhs_end;++rhs_start)
          {
            merged_array->push_back(*rhs_start);
          }
          BufferElement<Tuple> curr = merged_array->begin();
          // for(;curr<merged_array->end();++curr)
          // {
          //   std::cout<< *curr <<",";
          // }
          // std::cout << "Merge complete" <<std::endl;
          cog = CogPtr<Tuple>(new SortedArrayCog<Tuple>(merged_array,merged_array->begin(),merged_array->end()));
           return true;
         }
        else
        {
          return false;
        }
      }
      if(cog->type == COG_CONCAT){
        //std::cout <<"Btree Cog Found here ready to merge" <<std::endl;
        ConcatCog<Tuple> *concat = (ConcatCog<Tuple> *)cog.get();
        CogPtr<Tuple> lhs_ptr = concat->lhs->get();
        CogPtr<Tuple> rhs_ptr = concat->rhs->get();
        // Tuple sep = btree->sep;
        // //std::cout<<"Btree["<<sep<<"]"<<std::endl;
        // // std::cout<< "lhs ptr is "<<lhs_ptr->type << std::endl;
        if(lhs_ptr->type == COG_SORTED_ARRAY && rhs_ptr->type == COG_SORTED_ARRAY  )
        {
          Buffer<Tuple> lhs_buff = lhs_ptr->getBuffer();
          Buffer<Tuple> rhs_buff = rhs_ptr->getBuffer();
          //std::cout << "Here... "<<std::endl;
          BufferElement<Tuple> lhs_start = lhs_buff->begin();
          BufferElement<Tuple> lhs_end = lhs_buff->end();
          BufferElement<Tuple> rhs_start = rhs_buff->begin();
          BufferElement<Tuple> rhs_end = rhs_buff->end();
          Buffer<Tuple> merged_array (new std::vector<Tuple>);
          for(;lhs_start<lhs_end;++lhs_start)
          {
            merged_array->push_back(*lhs_start);
          }
          for(;rhs_start<rhs_end;++rhs_start)
          {
            merged_array->push_back(*rhs_start);
          }
          BufferElement<Tuple> curr = merged_array->begin();
          // for(;curr<merged_array->end();++curr)
          // {
          //   std::cout<< *curr <<",";
          // }
          // std::cout << "Merge complete" <<std::endl;
          cog = CogPtr<Tuple>(new SortedArrayCog<Tuple>(merged_array,merged_array->begin(),merged_array->end()));
           return true;
         }
        else
        {
          return false;
        }
      }
      else 
      {return false;}
    }
