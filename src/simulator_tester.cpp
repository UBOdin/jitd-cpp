#include <iostream>
#include <sstream>
#include <map>
#include <sys/time.h>
#include <tgmath.h>
#include "jitd.hpp"
#include "test.hpp"
#include "data.hpp"
#include "cog.hpp"
#include "iterator.hpp"
#include "transform.hpp"
#include "policy.hpp"
using namespace std;
//template<class Tuple, class Policy>
void sm_test(istream &input)
{
	//cout << "In simulator class finally" << endl;
	string line;
	RecordCogHandle data_array;
    RecordCogHandle data_array_sorted;
    int len, max;
	while(getline(input, line))
	{
		istringstream toks(line);
    	string op;
    	CASE_1("--") 
    	{
      		// comment, ignore
      
    		///////////////// MUTATOR OPERATIONS /////////////////
    	}
    	CASE("init")
    	{
    		//cout << "In INIT" <<endl;
    		RecordBuffer data = buffer_cmd(toks);
    		data_array = array_for_buffer(data);
    		//cout << "Created an Array of the data" << endl;
    	}
        CASE("init-sorted")//needed only for measure scan for sorted
        {
            string fill;
            toks >> fill;
            //cout <<"In init-sorted"<<endl;
            if(string("random") == fill) 
            {
                
                toks >> len >> max;
                //std::cout << "length:"<<len <<"Max:"<<max<<std::endl;
                data_array_sorted = build_random_sorted_array(len,max);        
            }
        }
    	CASE("MEASURE_SORT_TIME")
    	{
    		timeval start_sort, end_sort;
    		//cout<<"measuring one sort time"<<endl;
    		CogPtr<Record> data_to_sort = data_array->get();
    		gettimeofday(&start_sort, NULL);
    		sortArray(data_to_sort);
    		gettimeofday(&end_sort, NULL);
    		cout << "Time for single sort : " << total_time(start_sort, end_sort) << " us" << endl;

    	}
    	CASE("MEASURE_CRACK_TIME")
    	{
    		timeval start_crack, end_crack;
    		//cout<<"measuring one crack time"<<endl;
    		CogPtr<Record> data_to_crack = data_array->get();
    		gettimeofday(&start_crack, NULL);
    		randomSplitArray(data_to_crack);
    		gettimeofday(&end_crack, NULL);
    		cout << "Time for single crack : " << total_time(start_crack, end_crack) << " us" << endl;
    	}
        CASE("MEASURE_SORTED_SCAN_TIME")
        {
            //cout <<"measure scan time"<<endl;
            timeval start_s_scan, end_s_scan;
            Record target;
            target.value = NULL;
            target.key = rand() % max;
            bool keyFound = false;
            BufferElement<Record> result;
            //cout <<"Key searched for " << target.key<<endl; 
            gettimeofday(&start_s_scan, NULL);   
            keyFound = data_array_sorted->getKey(target,result);
            gettimeofday(&end_s_scan, NULL);
            cout << "Time for 1 scan in a sorted array : " << total_time(start_s_scan, end_s_scan) << " us" << endl;
            
        }
        CASE("MEASURE_UNSORTED_SCAN_TIME")
        {
            timeval start_us_scan, end_us_scan;
            Record target;
            target.value = NULL;
            target.key = rand() % max;
            bool keyFound = false;
            BufferElement<Record> result;
            //cout <<"Key searched for " << target.key<<endl; 
            gettimeofday(&start_us_scan, NULL);   
            keyFound = data_array->getKey(target,result);
            gettimeofday(&end_us_scan, NULL);
            cout << "Time for 1 scan in an unsorted array : " << total_time(start_us_scan, end_us_scan) << " us" << endl;
        }
	}
	
}