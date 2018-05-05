#ifndef _JITD_H_SHIELD
#define _JITD_H_SHIELD

#include <iostream>
#include <memory>
#include <atomic>
#import <queue>


#include "data.hpp"
#include "cog.hpp"
#include "iterator.hpp"
#include "transform.hpp"
#include "policy.hpp"


template<class Tuple, class Policy>
class JITD {
  
  CogHandle<Tuple>     root;
  Policy               policy;
  
  public:
    JITD() : 
      root(new CogHandleBase<Tuple>(CogPtr<Tuple>(new ArrayCog<Tuple>(
        Buffer<Tuple>(new std::vector<Tuple>()))))),
      policy(Policy()) 
      { policy.init(root); }
    
    CogHandle<Tuple> getRoot()
    {
      return std::atomic_load(root);
    }
    
    Iterator<Tuple> iterator()
    {
      // Root changes with each version, so we need to sync the pointer.
      CogHandle<Tuple> r = std::atomic_load(&root);
      
      // And grab an iterator on whatever falls out.
      return r->iterator();
    }
    
    void init(Buffer<Tuple> records)
    {
      root->put(CogPtr<Tuple>(new ArrayCog<Tuple>(records)));
      policy.init(root);
    }

    void reinitPolicy()
    {
      policy.init(root);
    }


    void insert(Buffer<Tuple> records)
    {
      // Create a template for the new root structure
      ConcatCog<Tuple> *newRootCog = new ConcatCog<Tuple>(
        nullptr,
        CogHandle<Tuple>(new CogHandleBase<Tuple>(CogPtr<Tuple>(
          new ArrayCog<Tuple>(records))))
      );
      // newRootCog->lhs is a placeholder for the current root object
      
      // Define a new root handle to swap in
      CogHandle<Tuple> newRoot = 
        CogHandle<Tuple>(new CogHandleBase<Tuple>(CogPtr<Tuple>(newRootCog)));
      
      // As one atomic operation, perform:
      //   newRootCog->lhs = root
      //   root = newRoot
      swapInNewRoot(newRoot, newRootCog->lhs);
    }
    
    // remove() exactly mirrors insert.
    void remove(Buffer<Tuple> records)
    {
      DeleteCog<Tuple> *newRootCog = new DeleteCog<Tuple>(
        nullptr,
        CogHandle<Tuple>(new CogHandleBase<Tuple>(CogPtr<Tuple>(
          new ArrayCog<Tuple>(records))))
      );
      CogHandle<Tuple> newRoot = 
        CogHandle<Tuple>(new CogHandleBase<Tuple>(CogPtr<Tuple>(newRootCog)));
      swapInNewRoot(newRoot, newRootCog->source);
    }
    
    void printDebug()
    {
      CogHandle<Tuple> r = std::atomic_load(&root);
      std::cout << "gROOT [" << r->size() << " elements]" << std::endl;
      r->printDebug(1);
    }

    Policy *getPolicy()
    {
      return &policy;
    }
    
    int size()
    {
      return std::atomic_load(&root)->size();
    }

  private: 
    
    // Replace root with newRoot.  placeholder is set to the value of root
    // at time of insertion.  Placeholder may be iterated through several root
    // values until there are no more conflicts.
    inline void swapInNewRoot(
      CogHandle<Tuple> &newRoot, CogHandle<Tuple> &placeholder
    ) {
      bool succeeded = false;
      while(!succeeded){
        placeholder = root;
        succeeded = std::atomic_compare_exchange_strong(
          &root,        // This value gets atomically replaced...
          &placeholder, // ... if this is currently its value
          newRoot       // This value replaces it.
        );
      }
    }
};

#endif //_JITD_H_SHIELD