
#include <iostream>
#include <sstream>
#include <memory>
#include <string>
#include <stack>
#include <cstdlib>
#include <algorithm>
#include <sys/time.h>

#include "cog.hpp"
#include "iterator.hpp"
#include "test.hpp"
#include "policy.hpp"

using namespace std;

RecordBuffer build_buffer(int len, int max)
{
  int i;
  RecordBuffer buff(new std::vector<Record>(len));
  for(i = 0; i < len; i++){
    (*buff)[i].key = rand() % max;
    (*buff)[i].value = (Value)0xDEADBEEF;
  }
  return buff;
}

RecordBuffer load_buffer(istream &input)
{
  RecordBuffer ret(new vector<Record>());
  Record r;
  r.value = (Value)0xDEADBEEF;
  while(!input.eof()){
    input >> r.key;
    ret->push_back(r);
  }
  return ret;
}

RecordCogHandle array_for_buffer(RecordBuffer buff)
{
  return CogHandle<Record>(new CogHandleBase<Record>(CogPtr<Record>(
    new ArrayCog<Record>(buff, buff->begin(), buff->end()))));
}


RecordCogHandle build_random_array(int len, int max)
{
  return array_for_buffer(build_buffer(len, max));
}

RecordCogHandle build_random_sorted_array(int len, int max)
{
  RecordBuffer buff = build_buffer(len, max);
  sort(buff->begin(), buff->end());
  return CogHandle<Record>(new CogHandleBase<Record>(CogPtr<Record>(
          new SortedArrayCog<Record>(buff, buff->begin(), buff->end()))));
}

void cog_test(istream &input)
{
  stack<CogHandle<Record> > stack;
  string line;
  
  while(getline(input, line)){
    istringstream toks(line);
    string op;
    
    toks >> op;
    
    ///////////////// COG LOADERS /////////////////
    if(string("array") == op){
      string fill;
      toks >> fill;
      
      if(string("random") == fill) {
        int len, max;
        toks >> len >> max;
        stack.push(build_random_array(len,max));        
      } else if(string("explicit") == fill) {
        stack.push(array_for_buffer(load_buffer(toks)));
      } else {
        cerr << "Invalid ArrayCog Fill Mode: " << fill << endl;
        exit(-1);
      }
      
    } else if(string("concat") == op) {
      CogHandle<Record> a = stack.top(); stack.pop();
      CogHandle<Record> b = stack.top(); stack.pop();
      
      stack.push(CogHandle<Record>(new CogHandleBase<Record>(CogPtr<Record>(
                    new ConcatCog<Record>(a, b)))));
      
    } else if(string("btree") == op) {
      Record sep;
      toks >> sep.key;
      sep.value = NULL;
      
      CogHandle<Record> b = stack.top(); stack.pop();
      CogHandle<Record> a = stack.top(); stack.pop();

      stack.push(CogHandle<Record>(new CogHandleBase<Record>(CogPtr<Record>(
                    new BTreeCog<Record>(a, b, sep)))));
    
    ///////////////// SIMPLE QUERIES /////////////////
    } else if(string("size") == op) {
      cout << "Size: " << stack.top()->size() << " records" << endl; 
    } else if(string("dump") == op) {
      cout << "gROOT" << endl;
      stack.top()->printDebug(1);
    } else if(string("scan") == op) {
      CogHandle<Record> root = stack.top();
      Iterator<Record> iter = root->iterator();
      int row = 1;
      cout << "---------------" << endl;
      while(!iter->atEnd()){
        cout << row << " -> " << iter->get()->key << endl;
        iter->next();
        row++;
      }
      cout << "---------------" << endl;
    } else if(string("time_scan") == op) {
      CogHandle<Record> root = stack.top();
      timeval start, end;
      gettimeofday(&start, NULL);
      Iterator<Record> iter = root->iterator();
      int row = 1;
      while(!iter->atEnd()){ iter->next(); row++; }
      gettimeofday(&end, NULL);
      float totalTime = 
        (end.tv_sec - start.tv_sec) * 1000000.0 +
        (end.tv_usec - start.tv_usec);
      cout << "---------------" << endl;
      cout << "Records Scanned: " << (row-1) << endl;
      cout << "Time Taken: " << totalTime << " us" << endl;
      if(row > 1){
        cout << "Time/Record: " << totalTime/(row-1) << " us" << endl;
      }
      cout << "---------------" << endl;
      
    ///////////////// OOOPS /////////////////
    } else {
      cerr << "Invalid Test Operation: " << op << endl;
      exit(-1);
    }
  }
}