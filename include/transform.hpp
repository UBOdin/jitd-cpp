#ifndef _TRANSFORM_H_SHIELD
#define _TRANSFORM_H_SHIELD

///////////// Transform Templates /////////////

#include <functional>

// 
// Usage:
//   CogPtr<Tuple> cog
//   bool acted = transform(cog)
// Before:
//   'cog' should be any valid cog
// After:
//   If 'acted' is false, then no changes were made
//   If 'acted' is true, then 'cog' now contains the replacement value.
// 
// Example:
//   CogPtr<Tuple> cog = handle->get()
//   if(transform(cog)){
//     handle->put(cog)
//   }
//
template <class Tuple>
 using Transform = std::function<bool(CogPtr<Tuple>&)>;

// 
// Usage:
//   Transform<Tuple> transform
//   Transform<Tuple> composite = meta(transform)
// Before:
//   'transform' should be any Transform
// After:
//   'composite' will be the rewritten transform
// 
// Example:
//   Transform<Tuple> sort_lhs = hierarchicalLHS(sortArray)
//
template <class Tuple>
 using MetaTransform = std::function<bool(Transform<Tuple>, CogPtr<Tuple>&)>;


///////////// Transform Templates /////////////

template <class Tuple>
  Transform<Tuple> applyMeta(MetaTransform<Tuple> meta, Transform<Tuple> base)
  {
    return bind(meta, base, std::placeholders::_1);
  }

#include "transform/transform_atomic.hpp"
// #include "transform/transform_hierarchical.hpp"


#endif //_TRANSFORM_H_SHIELD