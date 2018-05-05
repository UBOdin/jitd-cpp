
#include <iostream>
#include <sstream>
#include <map>
#include <sys/time.h>

#include "jitd.hpp"
#include "test.hpp"

using namespace std;

void ds_test(istream &input) 
{
  string line;
  shared_ptr<map<Key,Value>> ds(new map<Key,Value>());

  while(getline(input, line)){
    istringstream toks(line);
    string op;

    CASE_1("--") {
      // skip, comment
    } CASE("init") {
      RecordBuffer data = buffer_cmd(toks);
      vector<pair<Key, Value>> map_data;

      for(BufferElement<Record> curr = data->begin(); curr != data->end(); ++curr){
        map_data.push_back(std::make_pair(curr->key, curr->value));
      }

      timeval start, end;      
      gettimeofday(&start, NULL);
      for(vector<pair<Key,Value>>::iterator curr = map_data.begin(); curr != map_data.end(); curr++){
        ds->insert(*curr);
      }
      // for(BufferElement<Record> curr = data->begin(); curr != data->end(); ++curr){
      //   ds->emplace(curr->key, curr->value);
      // }
      gettimeofday(&end, NULL);
      cout << "Load Map: " << total_time(start, end) << " us" << endl;

    } else {
      cout << "Skipping irrelevant operation: " << line << endl;
    }

  }
}
