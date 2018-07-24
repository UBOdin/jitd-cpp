
#include <iostream>
#include <sstream>
#include <fstream>
#include <memory>
#include <string>
#include <stack>
#include <cstdlib>
#include <algorithm>
#include <thread>
#include <random>
#include <sys/time.h>
#include <queue>
#include <experimental/optional>
#include "jitd.hpp"
#include "test.hpp"

using namespace std;


void run_update_thread(
  JITD<Record,JITD_TEST_POLICY> *jitd, 
  Key max_key,
  int size, 
  long int low_mark, 
  long int high_mark, 
  int seed, 
  int per_op_sleep_ms,
  int runtime_ms
){
  timeval global_start, start, end;
  long int del_step = 0;
  mt19937 ins_rand(seed);
  mt19937 del_rand(seed);
  int i;
  long int tot_cnt = 0;
  long int delta_mark = high_mark - low_mark;
    
  gettimeofday(&global_start, NULL);
  cout << "Start Updates [" << low_mark << "--" << high_mark << "] by " << size
       << "; every " << per_op_sleep_ms << " ms for " << runtime_ms << "ms" << endl;
  do {
    
    gettimeofday(&start, NULL);
    if((rand() % delta_mark) > (tot_cnt - low_mark)){
      // insert
      RecordBuffer buff = RecordBuffer(new vector<Record>);
      for(i = 0; i < size; i++){
        buff->emplace_back(ins_rand() % max_key);
      }
      jitd->insert(buff);
      tot_cnt += size;
      
    } else {
      // delete
      RecordBuffer buff = RecordBuffer(new vector<Record>);
      for(i = 0; i < size; i++){
        buff->emplace_back(del_rand() % max_key);
      }
      jitd->remove(buff);
      tot_cnt -= size;
      
    }
    
    gettimeofday(&end, NULL);
    this_thread::sleep_for(chrono::milliseconds(
      per_op_sleep_ms - int(total_time(start, end) / 1000)
    ));
  } while(total_time(global_start, end) < 1000 * runtime_ms);
  cout << "End Updates" << endl;
  
  
}

void run_test_thread(JITD<Record, JITD_TEST_POLICY> *jitd, string file, int per_op_sleep_ms)
{
  ifstream in(file);
  timeval start, end;
  gettimeofday(&start, NULL);
  cout << "Start[" << file << "]" << endl;
  int t = jitd_test(*jitd, in, false, per_op_sleep_ms);
  gettimeofday(&end, NULL);
  cout << "Time[" << file << "]: " << t << " s" << endl;
}

int jitd_test(
  JITD<Record, JITD_TEST_POLICY> &jitd, 
  istream &input, 
  bool interactive, 
  int per_op_sleep_ms
) {
  string line;
  vector<std::thread> threads;
  string policy_name;
  timeval global_start, global_end;
  gettimeofday(&global_start, NULL);
  
  if(interactive) { cout << "jitd> "; cout.flush(); }
  while(getline(input, line)){
    istringstream toks(line);
    string op;
    
    CASE_1("--") {
      // comment, ignore
      
    ///////////////// MUTATOR OPERATIONS /////////////////
    } CASE("init") {
      timeval start, end;
      RecordBuffer data = buffer_cmd(toks);
      gettimeofday(&start, NULL);
      jitd.init(data);
      gettimeofday(&end, NULL);
      cout << "Init JITD: " << total_time(start, end) << " us" << endl;
    } CASE("insert") {
      timeval start, end;
      RecordBuffer data = buffer_cmd(toks);
      gettimeofday(&start, NULL);
      jitd.insert(data);
      gettimeofday(&end, NULL);
      cout << "Insert into JITD: " << total_time(start, end) << " us" << endl;
    } CASE("remove") {
      timeval start, end;
      RecordBuffer data = buffer_cmd(toks);
      gettimeofday(&start, NULL);
      jitd.remove(data);
      gettimeofday(&end, NULL);
      cout << "Delete from JITD: " << total_time(start, end) << " us" << endl;

    ///////////////// POLICY OPERATIONS /////////////////    
    } CASE("policy_set") {
      
      CASE_1("cracksort"){
        //policy_name = "cracksort";
        int threshold;
        toks >> threshold;
        cout << "Switching to Crack/Sort Policy with Threshold of " << threshold << endl;
        //cout << &jitd.getPolicy();
        jitd.getPolicy()->setScoreFunction(
          std::bind(CrackOrSortArraysBigFirst<Record>, threshold, std::placeholders::_1)
        );
        jitd.reinitPolicy();
      } 
      CASE("crack")
      {
        //policy_name = "crack";
        int threshold;
        toks >> threshold;
        cout << "Switching to Crack-Only Policy with Threshold of " << threshold << endl;
        jitd.getPolicy()->setScoreFunction(
          std::bind(CrackArrayBigFirst<Record>, threshold, std::placeholders::_1)
        );
        jitd.reinitPolicy();

      }
      CASE("sort")
      {
        //policy_name = "sort";
        int threshold;
        toks >> threshold;
        cout << "Switching to Sort-Only Policy with Threshold of " << threshold << endl;
        jitd.getPolicy()->setScoreFunction(
          std::bind(SortArrayBigFirst<Record>, threshold, std::placeholders::_1)
        );
        jitd.reinitPolicy();

      }
      CASE("merge")
      {
        //policy_name = "merge";
        int threshold;
        toks >> threshold;
        cout << "Switching to Merge-Only Policy with Threshold of " << threshold << endl;
        // jitd.getPolicy()->setScoreFunction(
        //   std::bind(ScoreFunctionMerge<Record>, threshold, std::placeholders::_1)
        // );
        jitd.reinitPolicy();

      }
      CASE("divide")
      {
        //policy_name = "divide";
        int threshold;
        toks >> threshold;
        cout << "Switching to Divide-Only Policy with Threshold of " << threshold << endl;
        jitd.getPolicy()->setScoreFunction(
          std::bind(DivideArray<Record>, threshold, std::placeholders::_1)
        );
        jitd.reinitPolicy();

      }
      else {
        cerr << "Invalid Policy " << op << endl;
        exit(-1);
      }

    } 
    CASE("merge_act_until_done")
    { 
        //cout << "in merge act until done"<<endl;
        bool more_work_to_do = true;
        unsigned long steps_taken = 0;
        timeval start, end;
        JITD_TEST_POLICY *policy = jitd.getPolicy();
        int target_steps = 12;
        gettimeofday(&start, NULL);
        while(more_work_to_do)
        {
          steps_taken++;
            
          more_work_to_do = policy->merge_act(jitd.getMergeRoot());
        }
        gettimeofday(&end, NULL);
        cout << "policy_act_until_done " << steps_taken << " Actions: " << total_time(start, end) << " us" << endl;
    }
    CASE("merge_act_for") {
      long target_steps;
      double used_microseconds = 0;
      timeval start, end;
      JITD_TEST_POLICY *policy = jitd.getPolicy();

      toks >> target_steps;
      //cout << "in merge act for target steps "<< target_steps <<endl;
      for(int x = 0; x < target_steps; x++){
        gettimeofday(&start, NULL);
        policy->merge_act(jitd.getMergeRoot());
        gettimeofday(&end, NULL);
        used_microseconds += total_time(start, end);
      }
      cout << "Policy_act_for_ " << target_steps << " Actions: " << used_microseconds << " us" << endl;
    }
    CASE("policy_act_once") {
      timeval start, end;
      jitd.getPolicy()->describeNext();
      JITD_TEST_POLICY *policy = jitd.getPolicy();
      gettimeofday(&start, NULL);
      policy->act();
      gettimeofday(&end, NULL);
      cout << "Policy Action: " << total_time(start, end) << " us" << endl;

    } CASE("policy_act_for") {
      long target_steps;
      double used_microseconds = 0;
      timeval start, end;
      JITD_TEST_POLICY *policy = jitd.getPolicy();

      toks >> target_steps;

      for(int x = 0; x < target_steps; x++){
        gettimeofday(&start, NULL);
        policy->act();
        gettimeofday(&end, NULL);
        used_microseconds += total_time(start, end);
      }

      cout << "Policy_act_for_ " << target_steps << " Actions: " << used_microseconds << " us" << endl;

    } CASE("policy_act_until_done") {
      bool more_work_to_do = true;
      unsigned long steps_taken = 0;
      timeval start, end;
      JITD_TEST_POLICY *policy = jitd.getPolicy();

      gettimeofday(&start, NULL);
      while(more_work_to_do){
        steps_taken++;
        more_work_to_do = policy->act();
      }
      gettimeofday(&end, NULL);
      cout << "policy_act_until_done " << steps_taken << " Actions: " << total_time(start, end) << " us" << endl;


    ///////////////// ACCESS OPERATIONS /////////////////    
    } CASE("scan") {
      Iterator<Record> iter = jitd.iterator();
      timeval start, end;
      int idx = 0;
      
      while(!toks.eof() && !iter->atEnd()){
        CASE_1("flush") { // no argument
          int startidx = idx;
          gettimeofday(&start, NULL);
          while(!iter->atEnd()){ iter->next(); idx++; }
          gettimeofday(&end, NULL);
          cout << "Records Flushed: " << (idx - startidx) << endl;
          cout << "Flush Time: " << total_time(start, end) << " us" << endl;
        } CASE("full") { // no argument
          while(!iter->atEnd()){ 
            cout << idx << " -> " << iter->get()->key << endl;
            iter->next(); 
            idx++; 
          }
        } CASE("step") { // no argument
          cout << idx << " -> " << iter->get()->key << endl;
          idx++;
          iter->next();
        } CASE("next") { // [CNT]
          int cnt;
          for(toks >> cnt; (cnt > 0) && !iter->atEnd(); cnt--){
            cout << idx << " -> " << iter->get()->key << endl;
            idx++;
            iter->next();
          }
        } CASE("quiet_next") { // [CNT]
          int cnt, startidx = idx;
          for(toks >> cnt; (cnt > 0) && !iter->atEnd(); cnt--){ 
            idx++;
            iter->next();
          }
        } CASE("seek") { // [TARGET]
          Record target;
          toks >> target.key;
          target.value = NULL;
          gettimeofday(&start, NULL);
          iter->seek(target);
          gettimeofday(&end, NULL);
          cout << "Seek Time: " << total_time(start, end) << " us" << endl;
        } CASE("quiet_seek") { // [TARGET]
          Record target;
          toks >> target.key;
          target.value = NULL;
          iter->seek(target);
        }
      }
     } //CASE("random_scan_old") {
    //   long int key;
    //   int scan_cnt, max_scan_val;
    //   //cout << "Found random scan" << endl;
    //   toks >> scan_cnt >> max_scan_val;
    //   //cout << " Scan cnt and max scan val are:" << scan_cnt <<","<< max_scan_val << endl;
    //   timeval start_scan, end_scan;
    //   Record target;
    //   target.value = NULL;
    //   gettimeofday(&start_scan, NULL);
    //   while(scan_cnt != 0)
    //   {
    //     //cout << "inside while loop" << endl;
    //     Iterator<Record> iter = jitd.iterator();
    //     target.key = rand() % max_scan_val; 
    //     iter->seek(target);
    //     --scan_cnt;
    //   }
    //   gettimeofday(&end_scan, NULL);
    //   cout << "Scan JITD time in Random Mode: " << total_time(start_scan, end_scan) << " us" << endl;

    //   // int time_in_ms, max_key, key_cnt;
    //   // long int scan_count = 0;
    //   // timeval start, end;
    //   // Record target;
    //   // target.value = NULL;
    //   // toks >> time_in_ms >> max_key >> key_cnt;
    //   // gettimeofday(&start, NULL);
    //   // gettimeofday(&end, NULL);
      
    //   // cout << "Scanning for " << time_in_ms << " s in [0,"
    //   //      << max_key << ") -> " << key_cnt << " keys/read" << endl;
    //   // while(total_time(start, end) < time_in_ms*1000){
    //   //   Iterator<Record> iter = jitd.iterator();
    //   //   target.key = rand() % max_key;
    //   //   iter->seek(target);
    //   //   for(; key_cnt > 0; key_cnt--) { iter->next(); }
    //   //   scan_count++;
        
    //   //   gettimeofday(&end, NULL);
    //   // }
    //   // cout << "Random Scan: " << scan_count << " scans over "
    //   //      << total_time(start, end)/(1000*1000) << " s" << endl 
    //   //      << "Rate: " 
    //   //        << ((1000*1000*scan_count) / total_time(start, end))
    //   //        << " scans/sec" << endl;
    
    // } 
    CASE("random_scan")
    {
      cout << "Switching to random point scan"<<endl;
      long int key;
      int scan_cnt, max_scan_val;
      toks >> scan_cnt >> max_scan_val;
      //cout<<"scancnt is"<< scan_cnt;
      Record target;
      target.value = NULL;
      timeval start_scan, end_scan;
      gettimeofday(&start_scan, NULL); 
      while(scan_cnt != 0)
      {
        //cout << "inside while loop" << endl;
        
        target.key = rand() % max_scan_val; 
        //cout << "the key being scanned for : " << target.key << endl;
        jitd.get(target);
        --scan_cnt;
      }
      gettimeofday(&end_scan, NULL);
      cout << "Scan JITD time in Random Mode: " << total_time(start_scan, end_scan) << " us" << endl;

    }
    CASE("scan_heavy_hitter")
    {
      //cout << "in heavy hitter block" << endl;
      int scan_cnt, max_scan_val, per_data, per_time;
      Record target;
      target.value = NULL;
      toks >> scan_cnt >> max_scan_val >> per_data >> per_time;
      //cout << scan_cnt << ","<< max_scan_val << "," << per_data << "," <<per_time << endl;
      int key_range = floor((per_data/100.0)*max_scan_val);
      int scan_cnt_within_range = floor((per_time/100.0)*scan_cnt);
      timeval start_scan, end_scan;
      gettimeofday(&start_scan, NULL);
      while(scan_cnt !=0)
      {
        if((rand()%100)< per_time && scan_cnt_within_range != 0)
        {
         
            target.key = rand() % key_range;
            jitd.get(target);
            --scan_cnt_within_range;
            --scan_cnt;
        }
        else
        {
            
            target.key = rand() % max_scan_val;
            jitd.get(target);
            --scan_cnt;
        }
      }
      gettimeofday(&end_scan, NULL);
      cout << "Scan JITD time in Heavy Hitter Mode: " << total_time(start_scan, end_scan) << " us" << endl;
    }
    CASE("spawn") {
      string file;
      toks >> file;
      threads.emplace_back(run_test_thread, &jitd, file, 0);

    } CASE("spawn_slow") {
      int delay_ms;
      string file;
      toks >> delay_ms >> file;
      threads.emplace_back(run_test_thread, &jitd, file, delay_ms);
    
    } CASE("spawn_updates") {
      Key max_key;
      int size;
      long int low_mark;
      long int high_mark;
      int seed = 42;
      int per_op_sleep_ms;
      int runtime_ms;
      
      toks >> max_key >> size >> low_mark >> high_mark >> per_op_sleep_ms >> runtime_ms;
      
      threads.emplace_back(run_update_thread, &jitd, max_key, size, low_mark, high_mark, seed, per_op_sleep_ms, runtime_ms);

    } CASE("run") {
      string file;
      toks >> file;
      run_test_thread(&jitd, file, per_op_sleep_ms);

    } CASE("time") {
      timeval end; 
      gettimeofday(&end, NULL);
      cout << "Time now: " << total_time(global_start, end)/(1000*1000) << endl;
    
    } CASE("sleep") {
      int ms;
      toks >> ms;
      this_thread::sleep_for(chrono::milliseconds(ms));
      
    } CASE("size") {
      cout << jitd.size() << " records" << endl;
    } CASE("dump") {
      jitd.printDebug();
      
    ///////////////// OOOPS /////////////////
    } else {
      cerr << "Invalid Test Operation: " << op << endl;
      exit(-1);
    }
    if(interactive) { cout << "jitd> "; cout.flush(); }
    if(per_op_sleep_ms > 0){ 
      this_thread::sleep_for(chrono::milliseconds(per_op_sleep_ms));
    }
  }
  gettimeofday(&global_end, NULL);
  
  vector<thread>::iterator th;
  for(th = threads.begin(); th < threads.end(); ++th){
    th->join();
  }
  return total_time(global_start, global_end) / (1000*1000);
}