template<class Tuple>
  ScoreFunctionReturn<Tuple> MergeArraySmallFirst(int threshold, CogPtr<Tuple> cog){ 
    if(cog->type != COG_BTREE){ 
    
      return NO_TRANSFORMS; 
    }
    
      int min_score;
      //std::cout << "Cog is a BTree" << std::endl;
      //cog->printDebug(3);
      //int size = cog->size();
      
      int lhs_size = cog->lsize();
      int rhs_size = cog->rsize();
      //std::cout << "Lhs size " << lhs_size << "Rhs size" << rhs_size <<std::endl;
      min_score = std::abs(lhs_size - rhs_size);
      return TRANSFORM_WITH((-min_score),mergeArray<Tuple>);
  }