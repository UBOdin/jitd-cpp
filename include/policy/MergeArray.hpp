template<class Tuple>
  ScoreFunctionReturn<Tuple> ScoreFunctionMerge(int threshold, CogPtr<Tuple> cog){ 
    if(cog->type != COG_BTREE){ 
    
      return NO_TRANSFORMS; 
    }
      int min_score = INT_MAX;
      bool is_lhs_leaf = cog->lhs_leaf();
      bool is_rhs_leaf = cog->rhs_leaf();
      int lhs_size = cog->lsize();
      int rhs_size = cog->rsize();
      if(is_lhs_leaf == true && is_rhs_leaf == true)
      {
       
        min_score = std::abs(lhs_size - rhs_size);
        //std::cout << "Min score " <<min_score <<std::endl;
        return TRANSFORM_WITH((min_score),mergeArray<Tuple>);
        
      }
      else
      {
        return NO_TRANSFORMS;
        
      }
    //return TRANSFORM_WITH((-min_score),mergeArray<Tuple>);
      
  }