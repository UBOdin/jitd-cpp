
#include "cog.hpp"

///////////// Atomic Transform Implementations /////////////

template <class Tuple>
  bool randomSplitArray(CogPtr<Tuple> &cog)
    {
      if(cog->type == COG_ARRAY) {
        ArrayCog<Tuple> *arr = cog.get();
        cog = arr->splitCog(arr->randElement());
        return true;
      }
      return false;
    }

template <class Tuple>
  bool sortArray(CogPtr<Tuple> &cog)
    {
      if(cog->type == COG_ARRAY){
        ArrayCog<Tuple> *arr = cog.get();
        return arr->splitCog(arr->sortedCog());
      }
      return cog;
    }
