#ifndef _COG_H_SHIELD
#define _COG_H_SHIELD

#include <memory>
#include <atomic>
#include <iostream>
#include <algorithm>
#include <cassert>
#include <experimental/optional>
#include "data.hpp"

//
// CogPtr/CogHandle
// 
// A CogPtr<Tuple> is a concrete *representation* of the bag, although 
// it may be potentially defined in terms of one or more CogHandle objects.  
//
// A CogHandle<Tuple> is an abstract representation of a bag of Tuple objects.  
// CogHandles are *mostly* functional.  The bag of represented Tuples will 
// never change.  However, the *representation* of this bag is allowed to 
// fluctuate.  ->get() is always guaranteed to return an *equivalent* CogPtr,
// but not necesarilly the same one each time.
//
// Cogs kept in memory should be stored as CogHandles.  Cogs being directly
// acted upon should be stored as CogPtrs.  
//
// The templated Tuple object must implement:
//   operator<()
//   operator>()
//   operator==()



///////////// Forward Refs /////////////

template <class Tuple> 
  class IteratorBase;

template <class Tuple>
  using Iterator = std::shared_ptr<IteratorBase<Tuple> >;
  

template <class Tuple> 
  class RewritePolicyBase;
template <class Tuple>
  using RewritePolicy = std::shared_ptr<RewritePolicyBase<Tuple> >;


///////////// Global Cog Content /////////////

typedef enum {
  COG_CONCAT,
  COG_BTREE,
  COG_DELETE,
  COG_ARRAY,
  COG_SORTED_ARRAY
} CogType;

template <class Tuple> class CogHandleBase;

template <class Tuple>
class Cog {
  
  public:
    Cog(CogType type): type(type) {}
  
    virtual Iterator<Tuple> iterator()
    { 
      std::cerr << type << std::endl;
      assert(0);
    }
    
    virtual bool lhs_leaf()
    {
      std::cerr << type << std::endl;
      assert(0);
    }
    virtual bool rhs_leaf()
    {
      std::cerr << type << std::endl;
      assert(0);
    }
    virtual std::shared_ptr<CogHandleBase<Tuple> > lhs_ptr()
    {
      std::cerr << type << std::endl;
      assert(0);
    }
    virtual std::shared_ptr<CogHandleBase<Tuple> > rhs_most()
    {
      std::cerr << type << std::endl;
      assert(0);
    }
    virtual std::shared_ptr<CogHandleBase<Tuple> > rhs_ptr()
    {
      std::cerr << type << std::endl;
      assert(0);
    }
    virtual int size()
    {
      std::cerr << type << std::endl;
      assert(0);
    }
     virtual int lsize()
    {
      std::cerr << type << std::endl;
      assert(0);
    }
      virtual int rsize()
    {
      std::cerr << type << std::endl;
      assert(0);
    } 
    virtual Buffer<Tuple> getBuffer()
    {
      std::cerr << type << std::endl;
      assert(0);
    } 
    virtual void apply_to_children(std::function<void(std::shared_ptr<CogHandleBase<Tuple>>)> fn)
    { 
      std::cerr << type << std::endl;
      assert(0);
    }
    void printDebug() { printDebug(0); }
    void printPrefix(int depth){ while(depth > 0){ std::cout << "  "; depth--; } }
    virtual void printDebug(int depth) {
      printPrefix(depth);
      std::cout << "???" << std::endl;
    }
    virtual bool getKey(Record key, BufferElement<Tuple> &result)
    {
      std::cerr << type << std::endl;
      assert(0);
    }
    virtual bool desc_key(Record key)
    {
      std::cerr << type << std::endl;
      assert(0);
    }
    virtual Tuple getSepVal()
    {
      std::cerr << type << std::endl;
      assert(0);
    }
    CogType type;
};

template <class Tuple>
  using CogPtr = std::shared_ptr< Cog<Tuple> >;  

#define makeHandle(s) CogHandle<Tuple>(new CogHandleBase<Tuple>(CogPtr<Tuple>(s)))

template <class Tuple>
class CogHandleBase {
  CogPtr<Tuple> ref;
  
  public:
    CogHandleBase(CogPtr<Tuple> init) : ref(init) {}
    
    // Obtain a snapshot of the pointer.
    inline CogPtr<Tuple> get()
    {
      return atomic_load(&ref);
    }
    // Precondition: `nref` MUST BE equivalent to `ref`.
    inline void put(CogPtr<Tuple> nref)
    { 
      atomic_store(&ref, nref); 
    }

    void apply_to_children(std::function<void(std::shared_ptr<CogHandleBase<Tuple>>)> fn)
    {
      get().apply_to_children(fn);
    }
    
    inline Iterator<Tuple> iterator()            { return get()->iterator(); }
    inline int             size()                { return get()->size(); }
    inline int             lsize()               { return get()->lsize(); }
    inline int             rsize()               { return get()->rsize(); }
    inline CogType         type()                { return get()->type; }
    inline void            printDebug()          { get()->printDebug(); }
    inline void            printDebug(int depth) { get()->printDebug(depth); }
    inline bool            getKey(Record key, BufferElement<Tuple> &result) {return get()->getKey(key,result);} 
    inline bool            desc_key(Record key) {return get()->desc_key(key);} 
    inline Buffer<Tuple>   getBuffer() {return get()->getBuffer();}
    inline bool            lhs_leaf() {return get()->lhs_leaf();} 
    inline bool            rhs_leaf() {return get()->rhs_leaf();}
    inline std::shared_ptr<CogHandleBase<Tuple> > rhs_most(){return get()->rhs_most();}
    inline Tuple           getSepVal() {return get()->getSepVal();}
    inline std::shared_ptr<CogHandleBase<Tuple> > lhs_ptr() {return get()->lhs_ptr();}
    inline std::shared_ptr<CogHandleBase<Tuple> > rhs_ptr() {return get()->rhs_ptr();}
};

template <class Tuple>
  using CogHandle = std::shared_ptr<CogHandleBase<Tuple> >;



#include "iterator.hpp"
///////////// Cog-Specific Class Headers /////////////

// ConcatCog
//
// Represents a Bag Union of two CogHandles
#include "cog/ConcatCog.hpp"

// BTreeCog
// 
// Represents a partition of two CogHandles.  For a value sep, guarantees
// that all of the left-hand-side Tuples are lower than sep, and the 
// right-hand-side Tuples are greater than or equal to sep.
#include "cog/BTreeCog.hpp"

// DeleteCog
// 
// Represents Bag Difference of two CogHandles.  Given source and delete 
// handles, tuples in the delete handle remove tuples from the source handle
// on a one-for-one basis.  Assumes that the delete handle represents a subset
// of the source handle.
#include "cog/DeleteCog.hpp"

// SortedArrayCog
//
// Wraps a Buffer<Tuple> that is guaranteed to be sorted.
#include "cog/SortedArrayCog.hpp"

// ArrayCog
//
// Wraps an arbitrary Buffer<Tuple>
#include "cog/ArrayCog.hpp"

#endif //_COG_H_SHIELD