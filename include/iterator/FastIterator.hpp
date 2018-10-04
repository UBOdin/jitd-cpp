template <class Tuple> 
class FastIterator : public IteratorBase<Tuple> {
CogHandle<Tuple> lhs, rhs;
Iterator<Tuple> lhsIter, rhsIter;
std::stack<CogHandle<Tuple>> nodeStack;
CogHandle<Tuple> node;
Iterator<Tuple> iter; 
const Tuple sep;

  
  public: 
    FastIterator(CogHandle<Tuple> lhs, 
      Tuple sep, 
      CogHandle<Tuple> rhs):sep(sep), lhs(lhs), rhs(rhs)
      {

        //std::cout<<"In fast iterator constructor with sep,lhs,rhs"<< "sep val "<<this->sep<<std::endl;
 
      }
      
    void initroot(const Tuple &k1)
    {
      //std::cout<<"In init root"<<std::endl;
      if(k1 < sep)
        {
          // node = rhs;
          // std::cout<<"node->type rhs" << node->type()<<std::endl;
          node = lhs;
          //std::cout<<"LHS node->type" << node->type()<<std::endl;
          nodeStack.push(rhs);
          //std::cout<<"after initroot stack size "<<nodeStack.size()<<std::endl;
        } 
        else
        {
          node = rhs;
          //std::cout<<"RHS node->type" << node->type()<<std::endl;
          //std::cout<<"node->type rhs" << node->type()<<std::endl;
          // node = lhs;
          // std::cout<<"node->type lhs" << node->type()<<std::endl;
          // nodeStack.push(rhs);
        }
    }
    
    // void rangeseek(const Tuple &k1,const Tuple &k2)
    // {
      
    //   initroot(k1);
      

    //   while(node != NULL)
    //   {

    //     if(node->type() == COG_BTREE)
    //     {
    //       std::cout<<"BtreeCog with sep value " <<node->getSepVal()<<std::endl;
    //       if((k1 < node->getSepVal()))
    //       {
    //         std::cout<<"in if"<<std::endl;
    //         nodeStack.push(node->rhs_ptr());
    //         node = node->lhs_ptr();
    //         //std::cout<<"Node lhs sep "<< node->getSepVal()<<std::endl;
            
    //       } 
    //       else
    //       {
            
    //         std::cout<<"in else";
    //         node = node->rhs_ptr();
    //         //std::cout<<"Node lhs sep "<< node->getSepVal()<<std::endl;
    //       }
    //     }

    //     else if(node->type() == COG_SORTED_ARRAY)
    //     {
    //       std::cout<<"Node is sorted array"<<std::endl;
    //       //Buffer<Tuple> sortBuffer = sort(lhs->getBuffer()->begin(),lhs->getBuffer()->end);
    //       buffiter = node->iterator();
    //       std::cout<<"initialized iterator"<<std::endl;
    //       if(!buffiter->isEmpty())
    //       {
    //         std::cout<<"empty buffer before seek"<<std::endl;
    //         buffiter->seek(k1);
    //         std::cout<<"called seek"<<std::endl;
    //         while((!buffiter->atEnd()) && *buffiter->get() < k2)
    //         {
    //           std::cout<<"buffer not at end"<<std::endl;
            
    //           std::cout<< *buffiter->get()<<",";
    //           buffiter->next();
    //           std::cout<<"here"<<std::endl;
    //         }
    //       }
          
    //       if(!nodeStack.empty())
    //       {
    //         std::cout<<"node stack not empty"<<std::endl;
    //         node = nodeStack.top();
    //         nodeStack.pop();
    //       }
    //       else
    //       {
    //         std::cout<<"node stack is empty"<<std::endl;
    //         node = NULL;
    //         std::cout<<"after node is null"<<std::endl;
    //       }


    //     }
        
    //     else if(node->type() == COG_ARRAY )
    //     {
    //       std::cout<<"Node is array"<<std::endl;
    //       //Buffer<Tuple> sortBuffer = sort(lhs->getBuffer()->begin(),lhs->getBuffer()->end);
    //       buffiter = node->iterator();
    //       if(!buffiter->isEmpty())
    //       {
    //         //std::cout<<"empty buffer before seek"<<std::endl;
    //         buffiter->seek(k1);
    //         while((!buffiter->atEnd()) && *buffiter->get() < k2)
    //         {
          
    //           //std::cout<<"buffer not at end"<<std::endl;
    //           std::cout<< *buffiter->get()<<",";
    //           buffiter->next();
    //           //std::cout<<"here"<<std::endl;

    //         }
    //       }
          
    //       if(!nodeStack.empty())
    //       {
    //         node = nodeStack.top();
    //         nodeStack.pop();
    //       }
    //       else
    //       {
    //         node = NULL;
    //       }
    //     }
        

    //   }
    //   //return buffiter;
    // }

    BufferElement<Tuple> get()
    {
      //std::cout<<"in fast iterator get"<<std::endl;
      if(iter.get()==NULL && node == NULL)
      {
        //std::cout<<"iter not init in FI"<<std::endl;
          
            if(lhs->size() == 0)
            {
              
              iter = rhs->iterator();
            }
            else
            {
              
              iter = lhs->iterator();
            }
           
      }
      return iter->get();
      
    }
    void initNode()
    {
      //std::cout<<"in initNode node type is"<<node->type()<<std::endl;
      while(node!=NULL)
      {
        if(node->type() == COG_SORTED_ARRAY && iter->atEnd() )
        {
          //std::cout<<"init buffiter SA"<<std::endl;
          
          //if((node->iterator())->isEmpty())
          if((node->iterator())->atEnd())
          {
            node = nodeStack.top();
            nodeStack.pop();
          }
          else
          {
            iter = node->iterator();
            return;
          }
          
        }
        else if(node->type() == COG_ARRAY && iter->atEnd() )
        {
          //std::cout<<"init buffiter Array"<<std::endl;
          //if((node->iterator())->isEmpty())
          if((node->iterator())->atEnd())
          {
            node = nodeStack.top();
            nodeStack.pop();
          }
          else
          {
            iter = node->iterator();
            return;
          }
        }
        else if(node->type() == COG_BTREE)
        {
          //std::cout<<"init Btree stack with sep "<<node->getSepVal()<<std::endl;
          nodeStack.push(node->rhs_ptr());
          //std::cout<<"pushed rhs"<<std::endl;
          node = node->lhs_ptr();  
        }
      }
      
      
    }
    void next()
    {
      //std::cout<<"in fast iter next"<<std::endl;
      
        //std::cout<<"node stack not empty"<<std::endl;
      if(node != NULL || !nodeStack.empty())
      {
        if(node->type() == COG_SORTED_ARRAY)
        {
            //std::cout<<"found sorted array in next"<<std::endl;
          
            // if(iter->atEnd())
            // {
            //   node = 
            // }
            //iter = node->iterator();

            iter->next();
            //std::cout<<"value of iter after SA next"<<*iter->get()<<std::endl;

        }
        else if(node->type() == COG_ARRAY)
        {
          //std::cout<<"found array in next"<<std::endl;
          
          
          //std::cout<< *buffiter->get()<<",";
            iter->next();

        }
        //std::cout<<"here"<<std::endl;
        else if(node->type() == COG_BTREE)
        {
          //std::cout<<"found Btree cog in next with sep val"<<node->getSepVal()<<std::endl;
          nodeStack.push(node->rhs_ptr());
          node = node->lhs_ptr();
          

        }
        if(!nodeStack.empty() && iter->atEnd())
        {
          //std::cout<<"node stack not empty and iter at end"<<std::endl;
          node = nodeStack.top();
          nodeStack.pop();
          //std::cout<<"type of node "<<node->type()<<std::endl;
          initNode();
        } 
      }

    }  
    void seek(const Tuple &k)
    {
      //std::cout<<"in fast iter seek"<<std::endl;
      initroot(k);
      while(node!=NULL)
      {
        if(node->type() == COG_BTREE)
        {
          //std::cout<<"BtreeCog with sep value " <<node->getSepVal()<<std::endl;
          if(k < node->getSepVal())
          {
            //std::cout<<"in if"<<std::endl;
            nodeStack.push(node->rhs_ptr());
            //std::cout<<"pushed node"<<std::endl;
            node = node->lhs_ptr();
            //std::cout<<"Node lhs sep "<< node->getSepVal()<<std::endl;
            //std::cout<<"stack size "<<nodeStack.size()<<std::endl;
            
          } 
          else
          {
            
            //std::cout<<"in else";
            node = node->rhs_ptr();
            //std::cout<<"Node lhs sep "<< node->getSepVal()<<std::endl;
          }
        }
        else if(node->type() == COG_SORTED_ARRAY)
        {
          //std::cout<<"Node is sorted array"<<std::endl;
          iter = node->iterator();
          
          if(iter->atEnd() && !nodeStack.empty())
          {
              //std::cout<<"empty buffer node reassigned with sibling"<<std::endl;
              node = nodeStack.top();
              nodeStack.pop();
              //std::cout<<"stack size "<<nodeStack.size()<<std::endl;
          }
          else
          {
            iter->seek(k);
            if(iter->atEnd() && !nodeStack.empty())
            {
              node = nodeStack.top();
              nodeStack.pop();
              //std::cout<<"stack size "<<nodeStack.size()<<std::endl;
            }
            else
            {
              return;
            }
            
          } 
          
        }
        else if(node->type() == COG_ARRAY)
        {
          //std::cout<<"Node is array"<<std::endl;
          iter = node->iterator();
          if(iter->atEnd() && !nodeStack.empty())
          {
              //std::cout<<"Seeked but didnt find key"<<std::endl;
              //std::cout<<"empty buffer node reassigned with sibling"<<std::endl;
              node = nodeStack.top();
              nodeStack.pop();
          }
          else
          {
            iter->seek(k);
            if(iter->atEnd() && !nodeStack.empty())
            {
              //std::cout<<"Seeked but didnt find key"<<std::endl;
              node = nodeStack.top();
              nodeStack.pop();
              //std::cout<<"stack size "<<nodeStack.size()<<std::endl;
            }
            else
            {
              return;
            }
          } 
        }
        // else if(node->type() == COG_CONCAT)
        // {
        //   std::cout<<"Node is concat"<<std::endl;
        //   // if(!iter->isEmpty() || iter.get() == NULL)
        //   // {
        //     iter = node->iterator();
        //     iter->seek(k);
            
        //   //}
        // }
       }  
    }
    
    // bool isEmpty()
    // {
    //   if(iter.get() == NULL)
    //   {
    //     return true;
    //   }
    //   else
    //   {
    //     return iter->isEmpty();
    //   }
    // }
    bool atEnd()
    {
      //std::cout<<"fast iter atEnd"<<std::endl;
      if(iter.get()==NULL && node == NULL)
      {
        //std::cout<<"no iter in fast iter"<<",";
          
            if(lhs->size() == 0)
            {
              //std::cout<<"in rhs node"<<std::endl;
              iter = rhs->iterator();
            }
            else
            {
              //std::cout<<"in lhs node"<<std::endl;
              iter = lhs->iterator();
            }
            return iter->atEnd();
           
      }
      else if(nodeStack.empty() && iter->atEnd())
      {
        //std::cout<<"node stack E, buffiter E"<<std::endl;
        return true;
      }
      else if(!nodeStack.empty() && iter->atEnd())
      {
        //std::cout<<"node stack NE, buffiter E"<<std::endl;
        return false;
      }
      else if(!nodeStack.empty() && !iter->atEnd())
      {
        //std::cout<<"node stack NE, buffiter NE"<<std::endl;
        return false;
      }
      else
      {
        //std::cout<<"else of atEnd"<<std::endl;
        return false;
      }
    }
    
    // BufferElement<Tuple> get()
    // {
    //   initNeeded();
    //   return lhsDone ? rhsIter->get() : lhsIter->get();
    //}
};