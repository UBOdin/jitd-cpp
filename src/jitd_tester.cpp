
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
#include <mutex>
#include "jitd.hpp"
#include "test.hpp"

using namespace std;
bool first_scan_isssued_flag = true;
timeval first_scan_isssued;
bool action_done = false;
// RecordBuffer scan_buff = RecordBuffer(new vector<Record>);
std::vector<Record> scan_buff;
std::vector<Record> range_scan_buff;
std::ostream&
print_one(std::ostream& os)
{
    return os;
}

template <class A0, class ...Args>
std::ostream&
print_one(std::ostream& os, const A0& a0, const Args& ...args)
{
    os << a0;
    return print_one(os, args...);
}

template <class ...Args>
std::ostream&
print(std::ostream& os, const Args& ...args)
{
    return print_one(os, args...);
}

std::mutex&
get_cout_mutex()
{
    static std::mutex m;
    return m;
}

template <class ...Args>
std::ostream&
print(const Args& ...args)
{
    std::lock_guard<std::mutex> _(get_cout_mutex());
    return print(std::cout, args...);
}

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
  if(!in)    
  {
    std::cerr << "While opening a file an error is encountered" << endl;
    assert(0);
    exit(-1);    
  }    
  // else    
  // {    
  //   cout << "File is successfully opened" << endl;    
  // }
  string line;
  timeval start, end;
  gettimeofday(&start, NULL);
  print("Starting Thread[",this_thread::get_id(),"]",file,'\n');
  //cout << "Starting thread "<<this_thread::get_id()<<"Running file "<<"[" << file << "]" << endl;
  int t = jitd_test(*jitd, in, false, per_op_sleep_ms);
  gettimeofday(&end, NULL);
  print("Thread[",this_thread::get_id(),file,"] Time taken:",t," s",'\n');
  //cout <<"Thread["<<this_thread::get_id()<<","<<file<<"]--"<<"Time" << ": " << t << " us" << endl;
}
// void run_scan_thread(JITD<Record, JITD_TEST_POLICY> *jitd, string file, int sleep_time)
// {
//   ifstream in(file);
//   if(!in)    
//   {
//     std::cerr << "While opening a file an error is encountered" << endl;
//     assert(0);
//     exit(-1);    
//   } 
//   string line;
//   timeval start, end;
//   gettimeofday(&start, NULL);
//   print("Starting scan Thread",this_thread::get_id(),file,'\n');
//   //cout << "Starting thread "<<this_thread::get_id()<<"Running file "<<"[" << file << "]" << endl;

//   int t = jitd_test(*jitd, in, false, sleep_time);
//   gettimeofday(&end, NULL);
//   print("Thread[",this_thread::get_id(),file,"] Time taken:",t,'\n');
//   //cout <<"Thread["<<this_thread::get_id()<<","<<file<<"]--"<<"Time" << ": " << t << " us" << endl;

// }

int jitd_test(
  JITD<Record, JITD_TEST_POLICY> &jitd, 
  istream &input, 
  bool interactive, 
  int per_op_sleep_ms
) {
  //std::cout<<"in jitd test"<<std::endl;
  string line;
  vector<std::thread> threads;
  string policy_name;
  timeval global_start, global_end;
  gettimeofday(&global_start, NULL);
  //std::cout<<"input is"<<input.rdbuf()<<std::endl;
  if(interactive) { cout << "jitd> "; cout.flush(); }
  while(getline(input, line)){
    //std::cout<<"line is:"<<line<<std::endl;
    istringstream toks(line);
    //toks(line);
    string op ;
    // std::cout<<"op is: "<<op<<std::endl;
    
    CASE_1("--") {
      // comment, ignore
      
    ///////////////// MUTATOR OPERATIONS /////////////////
    } CASE("init") {
      timeval start, end;
      long max_scan_val;
      RecordBuffer data = buffer_cmd(toks);
      gettimeofday(&start, NULL);
      jitd.init(data);
      gettimeofday(&end, NULL);
      cout << "Init JITD: " << total_time(start, end) << " us" << endl;
      //toks >> max_scan_val;
      // cout<<"Generating the scan vectors in range [0-1000000000] of size "<<scan_buff.size()<<std::endl;
      // for(int i=0;i<scan_buff.size();i++)
      // {

      //   scan_buff[i].key = rand()%1000000000;
      //   scan_buff[i].value = NULL;
      //   //cout<<"the key to scan is "<<scan_buff[i].key<<",";
        
      // }
      // for(int i=0;i<range_scan_buff.size();i++)
      // {

      //   range_scan_buff[i].key = rand()%1000000000;
      //   range_scan_buff[i].value = NULL;
      //   //cout<<"the key to scan is "<<scan_buff[i].key<<",";
        
      // }
    } CASE("gen_scan")
    {
      long noofscans,max_scan_val;
      toks >> noofscans >> max_scan_val;
      cout<<"In gen scan"<<endl;
      for(int i=0;i<noofscans;i++)
      {
        //cout<<i<<endl;
        scan_buff.emplace_back(rand()%max_scan_val);
        // scan_buff[i].key = rand()%1000000000;
        // scan_buff[i].value = NULL;
        //cout<<scan_buff[i].key<<",";
        
      }

    } 
    CASE("insert") {
      timeval start, end;
      RecordBuffer data = buffer_cmd(toks);
      //cout<<"size of insert "<<data->size()<<"/"<<data->begin()->key<<endl; 
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
      //std::cout<<"found policy set"<<std::endl;
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
        //std::cout<<"the threshold is"<<std::endl;
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
      CASE("pushdown-once")
      {
        int threshold;
        toks >> threshold;
        cout << "Switching to pushdown-once Policy with Threshold of " << threshold << endl;
        jitd.getPolicy()->setScoreFunction(
          std::bind(pushdownConcatOnce<Record>, threshold, std::placeholders::_1)
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
      cout << "Merge_act_for_ " << target_steps << " Actions: " << used_microseconds << " us" << endl;
    }
    CASE("pushdown_act_once") {
      timeval start, end;
      jitd.getPolicy()->describeNext();
      JITD_TEST_POLICY *policy = jitd.getPolicy();
      gettimeofday(&start, NULL);
      policy->pushdown_act_once(jitd.getRoot());
      gettimeofday(&end, NULL);
      cout << "Policy Action: " << total_time(start, end) << " us" << endl;

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

    }
    CASE("policy_act_for_time") {
      std::cout<<"in policy act for time"<<std::endl;
      long target_time;
      double used_microseconds = 0;
      bool more_work_to_do = false;
      timeval start, end;
      JITD_TEST_POLICY *policy = jitd.getPolicy();

      toks >> target_time;
      //double time_to_target = target_time * 2000000;
      while(used_microseconds < target_time){
        //cout<<"used_microseconds"<<used_microseconds<<std::endl;
        gettimeofday(&start, NULL);
        policy->act();
        gettimeofday(&end, NULL);
        //std::cout<<"more_work_to_do"<<more_work_to_do<<std::endl;
        used_microseconds += total_time(start, end);

      }

      cout << "Policy_act_for_ " << target_time << " Time: " << used_microseconds << " us" << endl;

    }
    CASE("policy_act_until_done") {
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
     } 
     CASE("insert-singleton")
    {
      cout<<"Switching to Singleton Inserts"<<endl;
      int num_inserts = 0;
      long max_insert_val = 0;
      toks >> num_inserts >> max_insert_val;
      for(int i=0;i<num_inserts;i++)
      {
        //cout<<"in insert"<<endl;
        RecordBuffer singleton_buff = buffer_singleton(max_insert_val);
        //jitd.get_insert_pos(singleton_buff);
        jitd.insert(singleton_buff);
      }
      

    }
    // CASE("pushdown")
    // {
    //   cout<<"in push down"<<endl;
    //   jitd.pushdown();
    // }
     CASE("range-scan")
     {
        cout<<"Switching to Range-scan using iterators for "<<range_scan_buff.size()<<" scans"<<std::endl;
        timeval start, end;
        int lower,upper,noOfRaneScans,num1,num2,time_taken;
        long running_rs_time = 0;
        Record k1,k2,min;
        // toks >> k1.key;
        // toks >> k2.key;
        toks >> lower;
        toks >> upper;
        //toks >> noOfRaneScans;
        k1.value = NULL;
        k2.value = NULL;
        min.key = -1;
        min.value = NULL;
        
        //Key Generation
        // for(int i=0;i<=noOfRaneScans;i++)
        // {
        //   num1 = (rand()%(upper - lower +1))+lower;
        //   //num2 = (rand()%(upper - lower +1))+lower;
        //   if(num1 < (upper-1000))
        //   {
        //     num2 = num1+1000;
            
        //   }
        //   else
        //   {
        //     num2 = upper;
        //   }
        //   k1.key = num1;
        //   k2.key = num2;
        gettimeofday(&start, NULL);
        for(int i = 0;i<scan_buff.size();i++)
        {
          k1.key = scan_buff[i].key;
          if(k1.key < (upper-1000))
          {
            
            k2.key = scan_buff[i].key+1000;
          }
          else
          {
            k2.key = upper;
          }
          
          
          std::cout<<"the key range is ["<< k1.key <<","<<k2.key<<"]"<<std::endl;
          
          
          Iterator<Record> fiter = jitd.iterator();
          fiter->seek(k1);
          //std::cout<<"the value seeked is "<<*fiter->get()<<std::endl;  
          // //fiter->rangeseek(start,end);
          while(( min < *fiter->get() && !(*fiter->get() > k2) && !fiter->atEnd()))
            { 
              //std::cout<<"iterator pointing at value before next <<"<<*fiter->get()<<">>"<<std::endl;
          //   //std::cout<<"main while loop"<<std::endl;
                fiter->next();
          //     // std::cout<<"iterator pointing at value after 1st next <<"<<*fiter->get()<<">>"<<std::endl;
          //     // fiter->next();
          //     // std::cout<<"iterator pointing at value after 2nd next <<"<<*fiter->get()<<">>"<<std::endl;  
           }
          // std::cout <<"RETURNED"<<std::endl;
           
          //time_taken = total_time(start, end);
          //running_rs_time = running_rs_time + time_taken;
          //cout << "Range scan "<<" Time: " << time_taken << " us" << endl;
          //  print("Range-Scan ",i,"Time :",time_taken," us",'\n');
        }
        gettimeofday(&end, NULL);
        time_taken = total_time(start, end);
        std::cout<<"The Total Time for range scans is "<<time_taken<<" us"<<std::endl;
     }
     CASE("thread-range-scan")
     {
        cout<<"Switching to thread Range-scan using iterators"<<std::endl;
        timeval start, end,abs_start,loop_start,sleeptime;
        int lower,upper,noOfRaneScans,num1,num2,time_taken;
        long running_rs_time = 0;
        double sleep_time=0;
        Record k1,k2,min;
        // toks >> k1.key;
        // toks >> k2.key;
        toks >> lower;
        toks >> upper;
        //toks >> noOfRaneScans;
        toks >> sleep_time;
        k1.value = NULL;
        k2.value = NULL;
        min.key = -1;
        min.value = NULL;
        int i=0;
        //Key Generation
        //for(int i=0;i<=scan_buff.size();i++)
        while(action_done == false)
        {
          gettimeofday(&loop_start, NULL);
          if(i == scan_buff.size())
          {
            i=0;
          }
          k1.key = scan_buff[i].key;
          if(k1.key < (upper-1))
          {
            
            k2.key = scan_buff[i].key+1000;
          }
          else
          {
            k2.key = upper;
          }
          std::cout<<"the key range is ["<< k1.key <<","<<k2.key<<"]"<<std::endl;
          Iterator<Record> fiter = jitd.iterator();
          gettimeofday(&start, NULL);
          fiter->seek(k1);
          //std::cout<<"the value seeked is "<<*fiter->get()<<std::endl;  
          // //fiter->rangeseek(start,end);
          while(( min < *fiter->get() && !(*fiter->get() > k2) && !fiter->atEnd()))
            { 
              //std::cout<<"iterator pointing at value before next <<"<<*fiter->get()<<">>"<<std::endl;
          //   //std::cout<<"main while loop"<<std::endl;
                fiter->next();
          //     // std::cout<<"iterator pointing at value after 1st next <<"<<*fiter->get()<<">>"<<std::endl;
          //     // fiter->next();
          //     // std::cout<<"iterator pointing at value after 2nd next <<"<<*fiter->get()<<">>"<<std::endl;  
           }
          // std::cout <<"RETURNED"<<std::endl;
          gettimeofday(&end, NULL);

          time_taken = total_time(start, end);
          running_rs_time = running_rs_time + time_taken;
          //cout << "Range scan "<< i <<" Time: " << time_taken << " us" << endl;
          print("Range-Scan Time :",time_taken," us",'\n');
          if(total_time(end,loop_start) <= 0)
          {
            this_thread::sleep_for(chrono::milliseconds(0));
          }
          else
          {
            double loop_time = total_time(end,loop_start);
            //print("SLEEP FOR DURATION",std::chrono::duration<double,std::micro>(sleep_time - loop_time),'\n');
            this_thread::sleep_for(std::chrono::duration<double,std::micro>(sleep_time - loop_time));
          }
          i++;
        }
        std::cout<<"The Total Time for all range scans is "<<running_rs_time<<" us"<<std::endl;

     }
     /** Scan time calculated for all scans at once and not running sum **/
    CASE("random_scan")
    {

      cout << "Switching to random point scan"<<endl;
      long int key;
      int scan_cnt, max_scan_val;
      //toks >> scan_cnt >> max_scan_val;
      //cout<<"scancnt is"<< scan_cnt<<"max scan val is"<<max_scan_val<<endl;
      Record target;
      target.value = NULL;
      timeval start_scan, end_scan;
      double running_scan_time = 0;
      double scan_time;
      //gettimeofday(&start_scan, NULL); 
      // while(scan_cnt != 0)
      // {
      //   //cout << "Scan number"<< scan_cnt << endl;
        
      //   target.key = rand() % max_scan_val; 
      //   //cout << "the key being scanned for : " << target.key << endl;
      //   jitd.get(target);
      //   --scan_cnt;
      // }
      long scan_buff_size = scan_buff.size();
      gettimeofday(&start_scan, NULL);
      for(int i=0;i<scan_buff_size;i++)
      {
        //target.key = rand() % max_scan_val;
        //gettimeofday(&start_scan, NULL);
        //jitd.get(target);
        //cout<<"scanning for element"<<scan_buff[i]<<endl;
        jitd.get(scan_buff[i]);
        //gettimeofday(&end_scan, NULL);
        //scan_time = total_time(start_scan, end_scan); 
        //running_scan_time = running_scan_time + scan_time;
      }
      gettimeofday(&end_scan, NULL);
      scan_time = total_time(start_scan, end_scan); 
      //gettimeofday(&end_scan, NULL);
       
      cout << scan_buff_size <<" Scans JITD time in Random Mode: " << scan_time << " us" << endl;

    }
    CASE("thread_random_scan")
    {
      cout << "Switching to thread random point scan"<<endl;
      long int key;
      int scan_cnt, max_scan_val;
      double sleep_time = 0.0;
      double running_time=0;
      toks >> sleep_time;
      //cout<<"scancnt is"<< scan_cnt;
      //cout<<"the sleep_time is "<< sleep_time<<std::endl;
      Record target;
      target.value = NULL;
      timeval start_scan, end_scan;
      int i=0;
      gettimeofday(&start_scan, NULL); 
      while(action_done == false)
      {
        if(i==scan_buff.size())
        {
          i=0;
        }
        
        jitd.get(scan_buff[i]);
        
        if(first_scan_isssued_flag == true)
        {
          first_scan_isssued = start_scan;
          first_scan_isssued_flag = false;
        }
        //print("first_scan_isssued time ",first_scan_isssued.tv_sec,first_scan_isssued.tv_usec);
        //long double time = total_time(first_scan_isssued,start_scan);
        //print("Scan issued at relative time: ",time," us",'\n');
        //double time_taken = total_time(start_scan, end_scan);
        //running_time += time_taken;
        //--scan_cnt;
        i++;
        //print("Time for random scan: ",time_taken," us",'\n');

        // if(time_taken <= 0)
        //   {
        //     this_thread::sleep_for(chrono::milliseconds(0));
        //   }
        //   else
        //   {
        //     this_thread::sleep_for(std::chrono::duration<double,std::micro>(sleep_time - time_taken));
        //   }
      }
      gettimeofday(&end_scan, NULL);
      double time_taken = total_time(start_scan, end_scan);
      //gettimeofday(&end_scan, NULL);
      //cout << "Scan JITD time in Random Mode: " << running_time << " us" << endl;
      print("Total random scan JITD time in thread Mode: ",time_taken," us",'\n');

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
      //print("spawnning threads",'\n');
      string file;
      toks >> file;
      //std::cout<<"file inputted is "<<file<<std::endl;
      threads.emplace_back(run_test_thread, &jitd, file, 0);

    } 
    CASE("spawn_slow") {
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
      std::cout<<"in run"<<std::endl;
      string file;
      toks >> file;
      //std::cout<<"file inputted is "<<file<<std::endl;
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
      std::cout<<"Indump"<<std::endl;
      jitd.printDebug();
      
      
    ///////////////// OOOPS /////////////////
    } CASE("done")
    {
      cout<<"policies complete"<<endl;
      action_done = true;
    }
     else {
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
    //std::cout<<"thread for joining "<< th->get_id()<<std::endl;
    th->join();
  }
  return total_time(global_start, global_end)/ (1000*1000);
}
