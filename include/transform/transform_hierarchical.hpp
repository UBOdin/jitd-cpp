
#include "cog.hpp"

///////////// LHS/RHS Meta Templates /////////////


template <class Tuple>
  bool applyToLHS(Transform<Tuple> transform, CogPtr<Tuple> &cog)
    {
      switch(cog->type){
        case COG_BTREE: {
          BTreeCog<Tuple> *bt = (BTreeCog<Tuple> *)cog.get();
          CogPtr<Tuple> lhs = bt->lhs->get();
          if(transform(lhs)){
            bt->lhs->put(lhs);
            return true;
          }
        } break;
        case COG_CONCAT: {
          ConcatCog<Tuple> *concat = (ConcatCog<Tuple> *)cog.get();
          CogPtr<Tuple> lhs = concat->lhs->get();
          if(transform(lhs)){
            concat->lhs->put(lhs);
            return true;
          }
        } break;
      }
    }

template <class Tuple>
  bool applyToRHS(Transform<Tuple> transform, CogPtr<Tuple> &cog)
    {
      switch(cog->type){
        case COG_BTREE: {
          BTreeCog<Tuple> *bt = (BTreeCog<Tuple> *)cog.get();
          CogPtr<Tuple> rhs = bt->rhs->get();
          if(transform(rhs)){
            bt->rhs->put(rhs);
            return true;
          }
        } break;
        case COG_CONCAT: {
          ConcatCog<Tuple> *concat = (ConcatCog<Tuple> *)cog.get();
          CogPtr<Tuple> rhs = concat->rhs->get();
          if(transform(rhs)){
            concat->rhs->put(rhs);
            return true;
          }
        } break;
    }