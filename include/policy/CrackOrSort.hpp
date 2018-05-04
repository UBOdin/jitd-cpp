

template<class Tuple>
  ScoreFunctionReturn<Tuple> CrackOrSortArraysBigFirst(int threshold, CogPtr<Tuple> cog){ 
    if(cog->type != COG_ARRAY){ return NO_TRANSFORMS; }
    
    int size = cog->size();

    if(size > threshold){
      return TRANSFORM_WITH(size, randomSplitArray<Tuple>);
    } else {
      return TRANSFORM_WITH(size, sortArray<Tuple>);
    }

  }
