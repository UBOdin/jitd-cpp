
#include <iostream>
#include <sstream>
#include <map>
#include <sys/time.h>
#include <tgmath.h>
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

      timeval start_load, end_load;      
      gettimeofday(&start_load, NULL);
      for(vector<pair<Key,Value>>::iterator curr = map_data.begin(); curr != map_data.end(); curr++){
        ds->insert(*curr);
      }
      // for(BufferElement<Record> curr = data->begin(); curr != data->end(); ++curr){
      //   ds->emplace(curr->key, curr->value);
      // }
      gettimeofday(&end_load, NULL);
      // for(auto it = ds->begin();it != ds->end(); ++it)
      // {
      //    cout << it->first << "," << it->second << endl;

      // }
      cout << "Load Map: " << total_time(start_load, end_load) << " us" << endl;

    } CASE("random_scan") { /* Uniform */
        //cout << "Random detected" << endl ;
        long int key;
        int scan_cnt, max_scan_val;

        toks >> scan_cnt >> max_scan_val;
        //cout << scan_cnt << max_scan_val << endl;
        timeval start_scan, end_scan;      
        gettimeofday(&start_scan, NULL);
        while(scan_cnt != 0)
        {
          // key = rand() % max_scan_val;
          // cout << "while loop number : " << scan_cnt << endl;
          //cout<< "searching for key : " << key << endl;
          ds->lower_bound(rand() % max_scan_val);
          --scan_cnt;

        }
        gettimeofday(&end_scan, NULL);
        cout << "Scan Map time in Random Mode: " << total_time(start_scan, end_scan) << " us" << endl;
        //cout << "Broke while loop as scan_cnt is 0" <<endl;

      } CASE("scan_heavy_hitter") { /* Heavy Hitters */

        long int range_key,out_of_range_key,key_to_scan;
        //cout << "Scanning with probability" << endl;
        int scan_cnt, max_scan_val,per_data,per_time;
        toks >> scan_cnt >> max_scan_val >> per_data >> per_time;
        //cout << scan_cnt << ","<< max_scan_val << "," << per_data << "," <<per_time << endl;
       
        int key_range = floor((per_data/100.0)*max_scan_val); //DOUBT: key range is 3 but values needed is 0-2. rand%3 can give 3 also?
        int scan_cnt_within_range = floor((per_time/100.0)*scan_cnt);
        // int scan_cnt_outof_range = scan_cnt - scan_cnt_within_range;
        //cout << "key range :" << key_range <<", scan_cnt_within_range :" << scan_cnt_within_range << ", scan_cnt_outof_range :" << scan_cnt_outof_range << endl;
      

        /* Scanning within Heavy Hitter range */
        timeval start_scan, end_scan;      
        gettimeofday(&start_scan, NULL);
        while(scan_cnt !=0)
        {
          //cout << "Entering while scan count is : " << scan_cnt << endl;
          if((rand()%100)< per_time && scan_cnt_within_range != 0)
          {
            //range_key = rand() % key_range;
            //cout << "while loop number : " << scan_cnt_within_range << endl;
            //cout<< "searching for heavy hitter key : " << range_key << endl;
            ds->lower_bound(rand() % key_range);
            --scan_cnt_within_range;  
            --scan_cnt;
          }
          else
          {
            //out_of_range_key = rand() % max_scan_val;
            //cout << "while loop number : " << scan_cnt_outof_range << endl;
            //cout<< "searching for non heavy hitter key : " << out_of_range_key << endl;
            ds->lower_bound(rand() % max_scan_val);
              --scan_cnt;
          }
        }
      
        gettimeofday(&end_scan, NULL);
        cout << "Scan Map time in Heavy Hitter Mode: " << total_time(start_scan, end_scan) << " us" << endl;

      }

     
    else {
      cout << "Skipping irrelevant operation: " << line << endl;
    }

  }
}
