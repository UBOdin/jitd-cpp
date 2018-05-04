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
    
    Buffer<Tuple> buffer;
    BufferElement<Tuple> start;
    BufferElement<Tuple> end;
};