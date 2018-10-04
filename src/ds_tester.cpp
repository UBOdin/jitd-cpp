
#include <iostream>
#include <sstream>
#include <map>
#include <unordered_map>
#include <sys/time.h>
#include <tgmath.h>
#include "jitd.hpp"
#include "test.hpp"
#include "btree.h"
#include <iterator>
//#include "btree_container.h"
#include "btree_map.h"
using namespace std;
void ds_test(istream &input) 
{
  string line;
  shared_ptr<map<Key,Value>> ds_map(new map<Key,Value>());
  shared_ptr<unordered_map<Key,Value>> ds_unorderedmap(new unordered_map<Key,Value>());
  typedef btree::btree_map<Key,Value> ds_btree_map;
  // typedef btree::btree_iterator<node_type, reference, pointer> iterator;
  shared_ptr<ds_btree_map> ds_btree(new ds_btree_map);

  while(getline(input, line)){
    istringstream toks(line);
    string op;

    CASE_1("--") {
      // skip, comment
    } CASE("init_btree"){
      std:cout<<"loading Btree...."<<std::endl;
      RecordBufferSet data = buffer_cmd_set(toks);
      vector<pair<Key, Value>> map_data;

      for(BufferSetElement<Record> curr = data->begin(); curr != data->end(); ++curr){
        map_data.push_back(std::make_pair(curr->key, curr->value));
      }

      timeval start_load, end_load;      
      gettimeofday(&start_load, NULL);
      for(vector<pair<Key,Value>>::iterator curr = map_data.begin(); curr != map_data.end(); curr++){
        ds_btree->insert(*curr);
        //std::cout<<"value being inserted"<<curr->first<<std::endl;
      }
      gettimeofday(&end_load, NULL);
      // for(auto it = ds->begin();it != ds->end(); ++it)
      // {
      //    cout << it->first << "," << it->second << endl;

      // }
      cout << "Loaded Btree: " << total_time(start_load, end_load) << " us" << endl;

    } 
    CASE("init_orderedmap") {
      std::cout<<"Loading map...."<<std::endl;
      RecordBufferSet data = buffer_cmd_set(toks);
      vector<pair<Key, Value>> map_data;

      for(BufferSetElement<Record> curr = data->begin(); curr != data->end(); ++curr){
        map_data.push_back(std::make_pair(curr->key, curr->value));
      }

      timeval start_load, end_load;      
      gettimeofday(&start_load, NULL);
      for(vector<pair<Key,Value>>::iterator curr = map_data.begin(); curr != map_data.end(); curr++){
        ds_map->insert(*curr);
        //std::cout<<"value being inserted"<<curr->first<<std::endl;
      }
      // for(BufferElement<Record> curr = data->begin(); curr != data->end(); ++curr){
      //   ds->emplace(curr->key, curr->value);
      // }
      gettimeofday(&end_load, NULL);
      // for(auto it = ds->begin();it != ds->end(); ++it)
      // {
      //    cout << it->first << "," << it->second << endl;

      // }
      cout << "Loaded Map: " << total_time(start_load, end_load) << " us" << endl;

    } CASE("init_unorderedmap") {
    
    std::cout<<"Loading unordered map..."<<std::endl;
      RecordBufferSet data = buffer_cmd_set(toks);
      vector<pair<Key, Value>> map_data;

      for(BufferSetElement<Record> curr = data->begin(); curr != data->end(); ++curr){
        map_data.push_back(std::make_pair(curr->key, curr->value));
      }

      timeval start_load, end_load;      
      gettimeofday(&start_load, NULL);
      for(vector<pair<Key,Value>>::iterator curr = map_data.begin(); curr != map_data.end(); curr++){
        ds_unorderedmap->insert(*curr);
        //std::cout<<"value being inserted"<<curr->first<<"size is "<<ds_unorderedmap->size()<<std::endl;
      }
      // for(BufferElement<Record> curr = data->begin(); curr != data->end(); ++curr){
      //   ds->emplace(curr->key, curr->value);
      // }
      gettimeofday(&end_load, NULL);
      // for(auto it = ds->begin();it != ds->end(); ++it)
      // {
      //    cout << it->first << "," << it->second << endl;

      // }
      cout << "Loaded UnorderedMap: " << total_time(start_load, end_load) << " us" << endl;

    }
    CASE("random_scan_btree") { /* Uniform */
        //cout << "Random detected" << endl ;
        long int key;
        int scan_cnt, max_scan_val;

        toks >> scan_cnt >> max_scan_val;
        //cout << scan_cnt << max_scan_val << endl;
        timeval start_scan, end_scan;  
        std::cout<<"Scanning...."<<std::endl;    
        gettimeofday(&start_scan, NULL);
        while(scan_cnt != 0)
        {
          key = rand() % max_scan_val;
          // cout << "while loop number : " << scan_cnt << endl;
          //cout<< "searching for key : " << key << endl;
          //ds_btree->find(key);
          ds_btree->find(key);
          --scan_cnt;

        }
        gettimeofday(&end_scan, NULL);
        cout << "Scan Btree time in Random Mode: " << total_time(start_scan, end_scan) << " us" << endl;
        //cout << "Broke while loop as scan_cnt is 0" <<endl;

      }
    CASE("range_scan_btree")
    {

      long int lower,upper,num1,num2,noofscans;
      long int k1,k2;
      double running_time=0;
      double time_taken;
      toks >> lower;
      toks >> upper;
      toks >> noofscans;
      std::cout<<"Scanning...."<<std::endl;
      timeval start_scan, end_scan; 
      for(int i=0;i<=noofscans;i++)
      {
      num1 = (rand()%(upper - lower +1))+lower;
      num2 = (rand()%(upper - lower +1))+lower;
      // k1.value = NULL;
      // k2.value = NULL;
      
      if(num1 < num2)
      {
        k1 = num1;
        k2 = num2;
      }
      else
      {
        k1 = num2;
        k2 = num1;
      }
      //k1 = 0; k2=8;
      std::cout<<"the key range is ["<< k1 <<","<<k2 <<"]"<<std::endl;
      gettimeofday(&start_scan, NULL);
      btree::btree_map<Key,Value>::iterator pos = ds_btree->lower_bound(k1);
      while(!(pos->first > k2) && pos != ds_btree->end())
      {
        ++pos;
        //std::cout<<"the iterator is at"<<pos->first<<std::endl;
      }
      gettimeofday(&end_scan, NULL);
      time_taken = total_time(start_scan, end_scan);
      cout << "Scan Btree time in Range Mode for range scan "<< i <<"is : " << time_taken << " us" <<std::endl;
      }
      running_time += time_taken;
      cout<<"Time taken for "<<noofscans<<" btree scans is : "<<running_time<<" us"<<std::endl;
    }
    CASE("random_scan_orderedmap") { /* Uniform */
        //cout << "Random detected" << endl ;
        long int key;
        int scan_cnt, max_scan_val;
        std::cout<<"Scanning....";
        toks >> scan_cnt >> max_scan_val;
        //cout << scan_cnt << max_scan_val << endl;
        timeval start_scan, end_scan;      
        gettimeofday(&start_scan, NULL);
        while(scan_cnt != 0)
        {
          key = rand() % max_scan_val;
          // cout << "while loop number : " << scan_cnt << endl;
          //cout<< "searching for key : " << key << endl;
          //ds_map->find(key);
          ds_map->find(key);
          --scan_cnt;

        }
        gettimeofday(&end_scan, NULL);
        cout << "Scan Map time in Random Mode: " << total_time(start_scan, end_scan) << " us" <<std::endl;
        //cout << "Broke while loop as scan_cnt is 0" <<endl;

      }
      CASE("range_scan_orderedmap")
    {
      long int lower,upper,num1,num2,noofscans;
      long int k1,k2;
      double running_time=0;
      double time_taken;
      timeval start_scan, end_scan;
      toks >> lower;
      toks >> upper;
      toks >> noofscans;
      std::cout<<"Scanning...."<<std::endl;
      for(int i=0;i<=noofscans;i++)
      {
      num1 = (rand()%(upper - lower +1))+lower;
      num2 = (rand()%(upper - lower +1))+lower;
      // k1.value = NULL;
      // k2.value = NULL;
      if(num1 < num2)
      {
        k1 = num1;
        k2 = num2;
      }
      else
      {
        k1 = num2;
        k2 = num1;
      }
      std::cout<<"the key range is ["<< k1 <<","<<k2 <<"]"<<std::endl;
      gettimeofday(&start_scan, NULL);
      map<Key,Value>::iterator pos = ds_map->lower_bound(k1);
      while(!(pos->first > k2) && !(pos == ds_map->end()))
      {
        pos++;
        //std::cout<<"the iterator is at"<<pos->first<<std::endl;
      }
      gettimeofday(&end_scan, NULL);
      time_taken = total_time(start_scan, end_scan);
      cout << "Scan ordered map time in Range Mode for range scan "<< i <<"is : " << time_taken << " us" <<std::endl;
      }
      running_time += time_taken;
      cout<<"Time taken for "<<noofscans<<" orderedmap scans is : " <<running_time<<" us"<<std::endl;
    }
      
      CASE("random_scan_unorderedmap") { /* Uniform */
        //cout << "Random detected" << endl ;
        long int key;
        int scan_cnt, max_scan_val;

        toks >> scan_cnt >> max_scan_val;
        //cout << scan_cnt << max_scan_val << endl;
        timeval start_scan, end_scan;  
        std::cout<<"Scanning...."<<std::endl;    
        gettimeofday(&start_scan, NULL);
        while(scan_cnt != 0)
        {
          key = rand() % max_scan_val;
          // cout << "while loop number : " << scan_cnt << endl;
          //cout<< "searching for key : " << key << endl;
          ds_unorderedmap->find(key);
          --scan_cnt;

        }
        gettimeofday(&end_scan, NULL);
        cout << "Scan UnorderedMap time in Random Mode: " << total_time(start_scan, end_scan) << " us" << endl;
        //cout << "Broke while loop as scan_cnt is 0" <<endl;

      }
      CASE("scan_heavy_hitter_btreemap") { /* Heavy Hitters */

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
            ds_btree->find(rand() % key_range);
            --scan_cnt_within_range;  
            --scan_cnt;
          }
          else
          {
            //out_of_range_key = rand() % max_scan_val;
            //cout << "while loop number : " << scan_cnt_outof_range << endl;
            //cout<< "searching for non heavy hitter key : " << out_of_range_key << endl;
            ds_btree->find(rand() % max_scan_val);
              --scan_cnt;
          }
        }
      
        gettimeofday(&end_scan, NULL);
        cout << "Scan Btree time in Heavy Hitter Mode: " << total_time(start_scan, end_scan) << " us" << endl;

      }
       CASE("scan_heavy_hitter_orderedmap") { /* Heavy Hitters */

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
            ds_map->find(rand() % key_range);
            --scan_cnt_within_range;  
            --scan_cnt;
          }
          else
          {
            //out_of_range_key = rand() % max_scan_val;
            //cout << "while loop number : " << scan_cnt_outof_range << endl;
            //cout<< "searching for non heavy hitter key : " << out_of_range_key << endl;
            ds_map->find(rand() % max_scan_val);
              --scan_cnt;
          }
        }
      
        gettimeofday(&end_scan, NULL);
        cout << "Scan Map time in Heavy Hitter Mode: " << total_time(start_scan, end_scan) << " us" << endl;

      }
       CASE("scan_heavy_hitter_unorderedmap") { /* Heavy Hitters */

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
            ds_unorderedmap->find(rand() % key_range);
            --scan_cnt_within_range;  
            --scan_cnt;
          }
          else
          {
            //out_of_range_key = rand() % max_scan_val;
            //cout << "while loop number : " << scan_cnt_outof_range << endl;
            //cout<< "searching for non heavy hitter key : " << out_of_range_key << endl;
            ds_unorderedmap->find(rand() % max_scan_val);
              --scan_cnt;
          }
        }
      
        gettimeofday(&end_scan, NULL);
        cout << "Scan UnorderedMap time in Heavy Hitter Mode: " << total_time(start_scan, end_scan) << " us" << endl;

      }

     
    else {
      cout << "Skipping irrelevant operation: " << line << endl;
    }

  }
}
