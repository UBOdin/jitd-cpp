template <class Tuple> 
class SeqIterator : public IteratorBase<Tuple> {
  CogHandle<Tuple> lhs, rhs;
  Iterator<Tuple> lhsIter, rhsIter;
  bool lhsDone, rhsDone;
  const Tuple sep;
  
  public: 
    SeqIterator(
      CogHandle<Tuple> lhs, 
      Tuple sep, 
      CogHandle<Tuple> rhs
    ) :
      sep(sep), lhs(lhs), rhs(rhs), 
      lhsDone(lhs->size() < 1), rhsDone(rhs->size() < 1) {}
    
    inline void initNeeded()
    { 
      if(!lhsDone) {
        if(lhsIter.get() == NULL) { 
          lhsIter = lhs->iterator();
          lhsDone = lhsIter->atEnd();
        }
      }
      if(lhsDone)  {
        if(rhsIter.get() == NULL) { 
          rhsIter = rhs->iterator();
          rhsDone = rhsIter->atEnd();
        }
      }
    }

    void next()
    {
      initNeeded();
      if(!lhsDone)     { lhsIter->next(); lhsDone = lhsIter->atEnd(); }
      else if(!rhsDone){ rhsIter->next(); rhsDone = rhsIter->atEnd(); }
    }

    void seek(const Tuple &k)
    {
      if(!(k < sep)) { lhsDone = true; }
      // check key first... may not need to init LHS.
      initNeeded();
      if(!lhsDone)     { lhsIter->seek(k); lhsDone = lhsIter->atEnd(); }
      else if(!rhsDone){ rhsIter->seek(k); rhsDone = rhsIter->atEnd(); }
    }

    bool atEnd()
    {
      return lhsDone && rhsDone;
    }
    
    BufferElement<Tuple> get()
    {
      initNeeded();
      return lhsDone ? rhsIter->get() : lhsIter->get();
    }
};