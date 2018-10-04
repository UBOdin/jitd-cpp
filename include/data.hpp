
#ifndef _DATA_HPP_SHIELD
#define _DATA_HPP_SHIELD

#include <memory>
#include <vector>
#include <functional>
#include <set>

template <class Tuple>
  using Buffer          = typename std::shared_ptr< std::vector<Tuple> >;
template <class Tuple>
  using BufferElement   = typename std::vector<Tuple>::const_iterator;
template <class Tuple>
  using BufferSet          = typename std::shared_ptr< std::set<Tuple> >;
template <class Tuple>
  using BufferSetElement   = typename std::set<Tuple>::const_iterator;

typedef long int Key;
typedef void *Value;

struct Record {
  Key   key;
  Value value;
  
  Record(Key key, Value _value) : key(key) { value = _value; }
  Record(Key key) : key(key) { value = (void *)0xdeadbeef; }
  Record() : key(0) { value = NULL; }
  
  inline bool operator>(const Record &other) const {
    return key > other.key;
  }
  inline bool operator<(const Record &other) const {
    return key < other.key;
  }
  inline bool operator==(const Record &other) const {
    return key == other.key;
    
  }
};

std::ostream &operator<<(std::ostream &o, const Record &r);

template <typename Tuple>
  inline std::pair<Buffer<Tuple>,Buffer<Tuple> > 
    splitBuffer(BufferElement<Tuple> curr, 
                BufferElement<Tuple> end, 
                const Tuple &pivot)
  {
    Buffer<Tuple> low (new std::vector<Tuple>);
    Buffer<Tuple> high(new std::vector<Tuple>);
    for(; curr < end; ++curr){
      if(*curr < pivot){ low ->push_back(*curr); }
      else             { high->push_back(*curr); }
    }
    return std::pair<Buffer<Tuple>,Buffer<Tuple> >(low, high);
  }
template <typename Tuple>
  inline std::pair<Buffer<Tuple>,Buffer<Tuple>> 
    splitBuffer(Buffer<Tuple> b, const Tuple &pivot)
  {
    return splitBuffer(b->begin(), b->end(), pivot);
  }


#endif // _DATA_HPP_SHIELD
