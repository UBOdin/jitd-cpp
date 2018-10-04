template <class Tuple> 
class BufferIterator : public IteratorBase<Tuple> {
  Buffer<Tuple> buff;
  BufferElement<Tuple> curr, start, end;
  
  public: 

    // BufferIterator assumes that buff is sorted.
    BufferIterator(Buffer<Tuple> buff) : 
      buff(buff), start(buff->begin()), curr(buff->begin()), end(buff->end()) 
      {
        //std::cout<<"buffer iter init"<<std::endl;
        // if(buff->empty())
        // {
        //   std::cout<<"empty buffer in constructor"<<std::endl;
        // }
      }

    // BufferIterator assumes that buff is sorted.
    BufferIterator(
      Buffer<Tuple> buff, 
      BufferElement<Tuple> start, 
      BufferElement<Tuple> end
    ) : 
      buff(buff), start(start), curr(start), end(end) 
      {
        //std::cout<<"buffer iter init 2"<<std::endl;
        
      }

    void next()
    {
      //std::cout<<"next in BI"<<std::endl;
      if(buff->empty())
      {
        curr = end;
        return;
      }
      if(curr < end){ curr += 1; }
      
    }
    // bool isEmpty()
    // {
    //   if(buff->empty())
    //   {
    //     return true;
    //   }
    //   else
    //   {
    //     return false;
    //   }
    // }
    void seek(const Tuple &k)
    {
      //std::cout<<"in buffer iterator seek"<<std::endl;
      
      unsigned int d = 1;
      
      if(buff->empty())
      {
        //std::cout<<"empty buffer in bufferiter seek"<<std::endl;
        curr = end;
        return ;
      }
      BufferElement<Tuple> high = curr;
      while((high < end) && (*high < k)){
        curr = high;
        high += d;
        d *= 2;
      }
      if(high > end){ high = end; }
      if(curr < high){
         curr = lower_bound(curr, high, k);
         
      }
      //std::cout<<"curr is "<<*curr<<"end is "<<*end<<std::endl;
    }

    bool atEnd()
    {
      //std::cout<<"atEnd buffer iter"<<std::endl;
      if(buff->empty())
      {
         curr = end;
      }
      //std::cout<<"curr is "<<*curr<<"end is "<<*end<<std::endl;
      return curr == end;
    }

    BufferElement<Tuple> get()
    {
      if(buff->empty())
      {
        //std::cout<<"empty buffer";
        return end;
      }
      //std::cout<<"BI pointing at"<<*curr<<std::endl;
      else
      {
        return curr;
      }
      
    }
};