template<class Tuple>
  ScoreFunctionReturn<Tuple> CrackArrayBigFirst(int threshold, CogPtr<Tuple> cog){ 
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
      //std::cout <<"Decided to crack" << std::endl;
      return TRANSFORM_WITH(size, randomSplitArray<Tuple>);
    } else {
      // std::cerr << "    ^--- Decided on Sort\n";
      //std::cout <<"Size < Threshold cant crack"<< std::endl;
      //return TRANSFORM_WITH(size, sortArray<Tuple>);
      return NO_TRANSFORMS;
    }

  }