

template<class Tuple>
  ScoreFunctionReturn<Tuple> CrackOrSortArraysBigFirst(int threshold, CogPtr<Tuple> cog){ 
    if(cog->type != COG_ARRAY){ 
      // std::cerr << "Crack or Sort: Not an Array\n";
      return NO_TRANSFORMS; 
    }
    
    int size = cog->size();
    // std::cerr << "Crack or Sort: Size " << size << " / " << threshold << std::endl;
    // cog->printDebug(3);


    if(size > threshold){
      // std::cerr << "    ^--- Decided on Crack\n";
      return TRANSFORM_WITH(size, randomSplitArray<Tuple>);
    } else {
      // std::cerr << "    ^--- Decided on Sort\n";
      return TRANSFORM_WITH(size, sortArray<Tuple>);
    }

  }
