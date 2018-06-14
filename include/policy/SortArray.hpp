template<class Tuple>
  ScoreFunctionReturn<Tuple> SortArrayBigFirst(int threshold, CogPtr<Tuple> cog){ 
    //std::cout<<"In crack Sort"<<std::endl;
    if(cog->type != COG_ARRAY){ 
      // std::cerr << "Crack or Sort: Not an Array\n";
      return NO_TRANSFORMS; 
    }
    
    int size = cog->size();
    // std::cerr << "Crack or Sort: Size " << size << " / " << threshold << std::endl;
    //cog->printDebug(3);


    if(size > threshold){
      // std::cerr << "    ^--- Decided on Crack\n";
      //std::cout <<"In sort but size > threshold" << size << threshold << std::endl;
      //return TRANSFORM_WITH(size, randomSplitArray<Tuple>);
      return NO_TRANSFORMS;
    } else {
      // std::cerr << "    ^--- Decided on Sort\n";
      //std::cout <<"Size < Threshold decided to sort"<< std::endl;
      return TRANSFORM_WITH(size, sortArray<Tuple>);
      //return NO_TRANSFORMS;
    }

  }