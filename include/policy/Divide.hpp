template<class Tuple>
  ScoreFunctionReturn<Tuple> DivideArray(int threshold, CogPtr<Tuple> cog){ 
    //Divide is applicable only to array cog
    if(cog->type != COG_ARRAY){ 
      // std::cerr << "Crack or Sort: Not an Array\n";
      return NO_TRANSFORMS; 
    }
    
    int size = cog->size();
    // std::cerr << "Crack or Sort: Size " << size << " / " << threshold << std::endl;
    // cog->printDebug(3);


    if(size > threshold){
      // std::cerr << "    ^--- Decided on Divide\n";
      std::cout << "In Divide policy" << std::endl;
      return TRANSFORM_WITH(size, divideArray<Tuple>);
    } else {
      std::cout<<" size < threshold"<<std::endl;
      return NO_TRANSFORMS;
    }

  }
