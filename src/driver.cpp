#include <iostream>
#include <fstream>
#include <istream>
#include <unistd.h>
#include <string.h>

#include "jitd.hpp"
#include "test.hpp"
#define SEED_MAX RAND_MAX
using namespace std;

typedef enum {
  COG_TEST, JITD_TEST, MAP_TEST, SIM_TEST
} TestMode;

double total_time(timeval &start, timeval &end)
{
  return (end.tv_sec - start.tv_sec) * 1000000.0 +
         (end.tv_usec - start.tv_usec); 
}
RecordBuffer buffer_cmd(istream &toks)
{
  string fill;
  toks >> fill;

  if(string("random") == fill) {
    int len, max;
    toks >> len >> max;
    std::cout << "length:"<<len <<"Max:"<<max<<std::endl;
    return build_buffer(len,max);        

  } else if(string("explicit") == fill) {
    return load_buffer(toks);
  
  } else if(string("file") == fill) {
    ifstream f;
    string filename;
    toks >> filename;
    f.open(filename);
    return load_buffer(f);        
    
  } else {
    cerr << "Invalid Fill Mode: " << fill << endl;
    exit(-1);
  }
}
RecordBuffer buffer_singleton(long max_insert_val)
{
  
  return build_singleton(max_insert_val);
}
RecordBufferSet buffer_cmd_set(istream &toks)
{
  string fill;
  toks >> fill;
  std::cout<<"filling the set"<<std::endl;
  if(string("random") == fill) {
    int len, max;
    toks >> len >> max;
    //std::cout << "length:"<<len <<"Max:"<<max<<std::endl;
    return build_bufferSet(len,max);        

   } 
    //else if(string("explicit") == fill) {
  //   return load_buffer(toks);
  
  // } else if(string("file") == fill) {
  //   ifstream f;
  //   string filename;
  //   toks >> filename;
  //   f.open(filename);
  //   return load_buffer(f);        
    
  //}
   else {
    cerr << "Invalid Fill Mode: " << fill << endl;
    exit(-1);
  }
}
int main(int argc, char **argv)
{
  istream *src;
  TestMode mode = JITD_TEST;
  int i, t = 0;
  bool interactive;
  JITD<Record, UniversalPolicy<Record>> jitd;
  
  srand(SEED_MAX);
  cout <<"using rand max"<<SEED_MAX<<endl;
//  sleep(1);
  for(i = 1; i < argc; i++){
    ifstream srcF;
    if((strlen(argv[i]) > 1) && (argv[i][0] == '-')){
      string flag(argv[i]);
      if(string("-c") == flag){ mode = COG_TEST; }
      else if(string("-j") == flag){ mode = JITD_TEST; }
      else if(string("-m") == flag){ mode = MAP_TEST; }
      else if(string("-s") == flag){ mode = SIM_TEST; }
      else {
        cerr << "Invalid command line switch: " << flag << endl;
        exit(-1);
      }
    } else {
      if(string("-") == string(argv[i])){
        src = &cin;
        interactive = true;
      } else {
        srcF.open(argv[i], std::ios_base::in);
        src = &srcF;
        interactive = false;
      }
      switch(mode){
        case COG_TEST:
          cog_test(*src);
          break;
        case JITD_TEST:
          t = jitd_test(jitd, *src, interactive, 0);
          cout << "JITD ran all operations for a Total Time[" << argv[i] << "]: " << t << " s" << endl;
          break;
        case MAP_TEST:
          ds_test(*src);
        case SIM_TEST:
          sm_test(*src);  
      }
    }
  }
//  sleep(60);
}
