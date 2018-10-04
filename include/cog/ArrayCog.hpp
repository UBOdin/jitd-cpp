template <class Tuple>
class ArrayCog : public Cog<Tuple>
{
  public:
    ArrayCog(
      Buffer<Tuple> buffer
    ) :
      Cog<Tuple>(COG_ARRAY), buffer(buffer), 
      start(buffer->begin()), end(buffer->end()) 
      {}
    ArrayCog(
      Buffer<Tuple> buffer, 
      BufferElement<Tuple> start, 
      BufferElement<Tuple> end
    ) :
      Cog<Tuple>(COG_ARRAY), buffer(buffer), start(start), end(end) {}
  
    Buffer<Tuple> getBuffer(){ return buffer; }
    Buffer<Tuple> sortedBuffer()
    {
      Buffer<Tuple> sorted(new std::vector<Tuple>(start, end));
      sort(sorted->begin(), sorted->end());
      return sorted;
    }

    std::pair<Buffer<Tuple>,Buffer<Tuple>> split(const Tuple &pivot)
    {
      return splitBuffer(start, end, pivot);
    }
    BufferElement<Tuple> randElement()
      { return (start+(rand() % (end-start))); }
    BufferElement<Tuple> getStart()
      { return start; }
    BufferElement<Tuple> getEnd()
      { return end; }

    int size(){ return end-start; }
    Iterator<Tuple> iterator()
    {
      return Iterator<Tuple>(new BufferIterator<Tuple>(sortedBuffer()));
    }
    int lsize(){ return 0; }
   
    int rsize(){ return 0; }
    
    bool lhs_leaf(){return false;}
    bool rhs_leaf(){return false;}
    std::shared_ptr<CogHandleBase<Tuple> > lhs_ptr() 
    {
      std::cerr << "no lhs pointer" << std::endl;
      assert(0);
      exit(-1);
    }
    std::shared_ptr<CogHandleBase<Tuple> > rhs_ptr() 
    {
      std::cerr << "no rhs pointer" << std::endl;
      assert(0);
      exit(-1);
    }
    Tuple getSepVal(){std::cerr <<"Array Cog no sep";assert(0);exit(-1);}
    void apply_to_children(std::function<void(CogHandle<Tuple>)> fn) {}

    void printDebug(int depth)
    {
      Cog<Tuple>::printPrefix(depth);
      std::cout << "Array[" << (end-start) << " elements] : { ";
      BufferElement<Tuple> curr = start;
      int i = 0;
      for(; (i < 6) && (curr != end); ++curr, ++i){
        std::cout << (i != 0 ? ", " : "") << curr->key;
      }
      if(curr != end) { std::cout << " ... "; }
      std::cout << " }\n";
    }
     bool getKey(Tuple key,BufferElement<Tuple> &result)
    {
      //std::cout<<"In Array getKey()"<<std::endl;
      BufferElement<Tuple> curr = start;
      bool keyFound = false;
      for(;curr!=end;++curr)
      {
        if(curr->key == key.key)
        {
          keyFound = true;
          //std::cout<<"the key is found" << curr->key << std::endl;
          result = curr;
          break;
        }
      }
      return keyFound; 
    }
    Buffer<Tuple> buffer;
    BufferElement<Tuple> start;
    BufferElement<Tuple> end;
};