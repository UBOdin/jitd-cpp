template <class Tuple> 
class MergeIterator : public IteratorBase<Tuple> {
  CogHandle<Tuple> lhs, rhs;
  Iterator<Tuple> lhsIter, rhsIter;
  bool lhsDone, rhsDone;
  bool lhsBest;
  
  public: 
    MergeIterator(
      CogHandle<Tuple> lhs, 
      CogHandle<Tuple> rhs
    )
    {
      //std::cout<<"initializing lhs iter"<<std::endl;
      lhsIter = lhs->iterator();
      lhsDone = lhsIter->atEnd();
      //std::cout<<"value of lhsDone is "<<lhsDone<<std::endl;
      //std::cout<<"initializing rhs iter"<<std::endl;
      rhsIter = rhs->iterator();
      rhsDone = rhsIter->atEnd();
      //std::cout<<"value of rhsDone is "<<rhsDone<<std::endl;
      updateBest();
    }
    
    inline void updateBest() 
    {
      if(lhsIter->atEnd())
      {
        //std::cout<<"lhs is empty so cannot compare lhsBest is default to false"<<std::endl;
        lhsBest = false;
      }
      else
      {

        lhsBest = ((!lhsDone) && (rhsDone || (*lhsIter->get() < *rhsIter->get())));
        // std::cout<<"lhsBest is set"<<std::endl;
        // std::cout << "Cmp: " << *lhsIter->get() << " ^^ " << *rhsIter->get() << std::endl;
        // std::cout<<"value of lhsBest in update best is "<<lhsBest<<std::endl;
      }
    }

    void next()
    {
      if(lhsDone && rhsDone) { return; }
      if(lhsBest) { lhsIter->next(); lhsDone = lhsIter->atEnd(); }
      else        { rhsIter->next(); rhsDone = rhsIter->atEnd(); }
      updateBest();
    }
    void seek(const Tuple &k)
    {
      //std::cout<<"merge iterator seek"<<std::endl;
      //std::cout<<"Merge seek lhs"<<std::endl;
      lhsIter->seek(k);  
      lhsDone = lhsIter->atEnd();
      // std::cout<<"value of lhs done is "<<lhsDone<<std::endl;
      //std::cout<<"Merge seek rhs"<<std::endl;
      rhsIter->seek(k);  
      rhsDone = rhsIter->atEnd();
      // std::cout<<"value of rhs done is "<<rhsDone<<std::endl;
      updateBest();
    }
    bool atEnd()
    {
      //std::cout<<"MI atEnd"<<std::endl;
      return lhsDone && rhsDone;
    }
    BufferElement<Tuple> get()
    {
      if(lhsBest) { return lhsIter->get(); }
      else        { return rhsIter->get(); }
    }
};