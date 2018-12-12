template<class Tuple>
  ScoreFunctionReturn<Tuple> pushdownConcatOnce(int threshold, CogPtr<Tuple> cog){ 
    //Divide is applicable only to array cog
    int size = 0;
    //std::cout<<"in pushdown once"<<std::endl;
    if(cog->type != COG_CONCAT){ 
      // std::cerr << "Crack or Sort: Not an Array\n";
      return NO_TRANSFORMS; 
    }
    else
    {
      return TRANSFORM_WITH(size, pushDown<Tuple>);
    }


    // if(size > threshold){
    //   // std::cerr << "    ^--- Decided on Divide\n";
    //   //std::cout << "In Divide policy" << std::endl;
    //   return TRANSFORM_WITH(size, divideArray<Tuple>);
    // } else {
    //   //std::cout<<" size < threshold"<<std::endl;
    //   return NO_TRANSFORMS;
    // }

  }
