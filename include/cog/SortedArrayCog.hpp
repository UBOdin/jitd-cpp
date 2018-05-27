template <class Tuple>
class SortedArrayCog : public Cog<Tuple>
{
  public:
    SortedArrayCog(
      Buffer<Tuple> buffer
    ) :
      Cog<Tuple>(COG_SORTED_ARRAY), buffer(buffer), 
      start(buffer->begin()), end(buffer->end()) {}
    SortedArrayCog(
      Buffer<Tuple> buffer, 
      BufferElement<Tuple> start, 
      BufferElement<Tuple> end
    ) :
      Cog<Tuple>(COG_SORTED_ARRAY), buffer(buffer), start(start), end(end) {}
  
    Buffer<Tuple> getBuffer(){ return buffer; }
    BufferElement<Tuple> getStart(){ return start; }
    BufferElement<Tuple> getEnd(){ return end; }
    inline BufferElement<Tuple> seek(Tuple t){ return lower_bound(start, end, t); }
    inline std::pair<CogPtr<Tuple>, CogPtr<Tuple> > splitCogs(const Tuple &t)
    {
      BufferElement<Tuple> mid = seek(t);
      CogPtr<Tuple> a((start < mid) ? new SortedArrayCog<Tuple>(buffer, start, mid) : NULL);
      CogPtr<Tuple> b((mid < end) ? new SortedArrayCog<Tuple>(buffer, mid, end) : NULL);
      std::pair<CogPtr<Tuple>, CogPtr<Tuple> > ret(a, b);
      return ret;
    }

    int size(){ return end-start; }
    void apply_to_children(std::function<void(CogHandle<Tuple>)> fn) {}

    Iterator<Tuple> iterator()
    {
      return Iterator<Tuple>(new BufferIterator<Tuple>(buffer, start, end));
    }

    void printDebug(int depth)
    {
      Cog<Tuple>::printPrefix(depth);
      std::cout << "SortedArray[" << (end-start) << " elements]" << std::endl;
    }
    bool getKey(Tuple key, BufferElement<Tuple> &result)
    {
      //std::cout<<"In SortedArray getKey()"<<std::endl;
      BufferElement<Tuple> temp = start;
      BufferElement<Tuple> curr = start;
      unsigned int d = 1;
      BufferElement<Tuple> high = curr;
      while((high < end) && (*high < key)){
        curr = high;
        high += d;
        d *= 2;
      }
      if(high > end){ high = end; }
      if(curr < high){
         temp = lower_bound(curr, high, key);
      }
      //return (temp->key == key.key) ? true : false;
      if(temp->key == key.key )
      {
        result = temp;
        //std::cout<<"the key is found" << result->key << std::endl;

        return true;
      }
      else
      {
        //std::cout<< "key no match"<<std::endl;
        return false;
      }
      
    }
    Buffer<Tuple> buffer;
    BufferElement<Tuple> start;
    BufferElement<Tuple> end;
};