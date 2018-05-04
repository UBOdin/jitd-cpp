
#include "cog.hpp"

///////////// Atomic Transform Implementations /////////////


template <class Tuple>
  bool randomSplitArray(CogPtr<Tuple> &cog)
    {
      if(cog->type == COG_ARRAY) {
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
      return false;
    }

template <class Tuple>
  bool sortArray(CogPtr<Tuple> &cog)
    {
      if(cog->type == COG_ARRAY){
        ArrayCog<Tuple> *arr = (ArrayCog<Tuple> *)cog.get();
        Buffer<Tuple> sorted = arr->sortedBuffer();
        cog = CogPtr<Tuple>(new SortedArrayCog<Tuple>(
          sorted, sorted->begin(), sorted->end()
        ));
        return true;
      }
      return false;
    }
