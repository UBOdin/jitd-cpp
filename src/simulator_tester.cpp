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
CogPtr<Record> cog_desc;
void split(CogPtr<Record> &cog)
{
    if(cog->type == COG_ARRAY || cog->type == COG_SORTED_ARRAY)
    {
    ArrayCog<Record> *arr = (ArrayCog<Record> *)cog.get();
    BufferElement<Record> pivot = arr->midElement();
    //std::cout<<"the rand elem is"<<pivot->key<<std::endl;
    std::pair<Buffer<Record>,Buffer<Record>> splits = arr->split(*pivot);
    //std::pair<Buffer<Record>,Buffer<Record>> splits = arr->splitPos(pivot);
    Buffer<Record> lhs = splits.first;
    Buffer<Record> rhs = splits.second;
    std::sort(lhs->begin(),lhs->end());
    std::sort(rhs->begin(),rhs->end());
    CogPtr<Record> lhsC = CogPtr<Record>(new SortedArrayCog<Record>(lhs,lhs->begin(),lhs->end()));
            
    CogPtr<Record> rhsC = CogPtr<Record>(new SortedArrayCog<Record>(rhs,rhs->begin(),rhs->end()));
            
    CogHandle<Record> lhsH(new CogHandleBase<Record>(lhsC));
    CogHandle<Record> rhsH(new CogHandleBase<Record>(rhsC));
    cog = CogPtr<Record>(new BTreeCog<Record>(lhsH, rhsH, *pivot));
    }
}
// void splitBtree(CogHandleBase<Record> &cog)
// {
//     if(cog.type() == COG_ARRAY || cog.type() == COG_SORTED_ARRAY)
//     {
//         std::cout<<"A/SA"<<std::endl;
//     ArrayCog<Record> *arr = (ArrayCog<Record> *)cog.get();
//     BufferElement<Record> pivot = arr->randElement();
//     std::cout<<"the rand elem is"<<pivot->key<<std::endl;
//     std::pair<Buffer<Record>,Buffer<Record>> splits = arr->split(*pivot);
//     //std::pair<Buffer<Record>,Buffer<Record>> splits = arr->splitPos(pivot);
//     Buffer<Record> lhs = splits.first;
//     Buffer<Record> rhs = splits.second;
//     std::sort(lhs->begin(),lhs->end());
//     std::sort(rhs->begin(),rhs->end());
//     CogPtr<Record> lhsC = CogPtr<Record>(new SortedArrayCog<Record>(lhs,lhs->begin(),lhs->end()));
            
//     CogPtr<Record> rhsC = CogPtr<Record>(new SortedArrayCog<Record>(rhs,rhs->begin(),rhs->end()));
            
//     CogHandle<Record> lhsH(new CogHandleBase<Record>(lhsC));
//     CogHandle<Record> rhsH(new CogHandleBase<Record>(rhsC));
//     cog = CogPtr<Record>(new BTreeCog<Record>(lhsH, rhsH, *pivot));
//     }
//     if(cog->type == COG_BTREE)
//     {
//         std::cout<<"BT"<<std::endl;
//     }
//     //return cog;
// }
//template<class Record, class Policy>
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
        CASE("MEASURE_MERGE_TIME")
        {
            std::cout<<"in measure merge time"<<std::endl;
            timeval start_merge, end_merge;
            CogPtr<Record> cog = data_array->get();
            
            if(cog->type == COG_ARRAY) {
            //std::cout <<"Array Cog Found ready to split" <<std::endl;
            ArrayCog<Record> *arr = (ArrayCog<Record> *)cog.get();
            BufferElement<Record> pivot = arr->randElement();
            //std::cout<<"the mid elem is"<<pivot->key<<std::endl;
            std::pair<Buffer<Record>,Buffer<Record>> splits = arr->split(*pivot);
            //std::pair<Buffer<Record>,Buffer<Record>> splits = arr->splitPos(pivot);
            Buffer<Record> lhs = splits.first;
            Buffer<Record> rhs = splits.second;
            std::sort(lhs->begin(),lhs->end());
            std::sort(rhs->begin(),rhs->end());
            CogPtr<Record> lhsC = CogPtr<Record>(new SortedArrayCog<Record>(lhs,lhs->begin(),lhs->end()));
            
            CogPtr<Record> rhsC = CogPtr<Record>(new SortedArrayCog<Record>(rhs,rhs->begin(),rhs->end()));
            
            CogHandle<Record> lhsH(new CogHandleBase<Record>(lhsC));
            CogHandle<Record> rhsH(new CogHandleBase<Record>(rhsC));
            cog = CogPtr<Record>(new BTreeCog<Record>(lhsH, rhsH, *pivot));
            if(cog->type == COG_BTREE)
            {
                //std::cout<<"Btree found to merge"<<std::endl;
                gettimeofday(&start_merge, NULL);
                mergeArray(cog);
                gettimeofday(&end_merge, NULL);

            } 
            cout << "Time for single merge : " << total_time(start_merge, end_merge) << " us" << endl; 
            }
        }
        CASE("MEASURE_SORTED_SCAN_TIME")
        {
            //cout <<"measure scan time"<<endl;
            timeval start_s_scan, end_s_scan;
            Record target;
            target.value = NULL;
            
            bool keyFound = false;
            BufferElement<Record> result;
            int scan_cnt = 1000000;
            //cout <<"Key searched for " << target.key<<endl; 

            gettimeofday(&start_s_scan, NULL);  
            for(int i=0;i<scan_cnt;i++)
            { 
                target.key = rand() % max;
                keyFound = data_array_sorted->getKey(target,result);
            }    
            gettimeofday(&end_s_scan, NULL);
            cout << "This is the scan time for doing 1000000 scans : "<<total_time(start_s_scan, end_s_scan)<<",";
            
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
        CASE("MEASURE_DESCENT_TIME")
        {
            int height_of_split;
            toks >> height_of_split;
            timeval start_us_scan, end_us_scan;
            cog_desc = data_array->get();
            split(cog_desc);
            BufferElement<Record> result;
            //cog_desc->printDebug();
            CogPtr<Record> rhstosplit = cog_desc->rhs_most()->get();
            //std::cout<<"type of rhs->most" <<rhstosplit->type<<std::endl;
            for(int i=1;i<height_of_split;i++)
            {
                if(rhstosplit->type == COG_ARRAY || rhstosplit->type == COG_SORTED_ARRAY)
                {
                split(rhstosplit);
                cog_desc->rhs_most()->put(rhstosplit);
                rhstosplit = cog_desc->rhs_most()->get();
                }
                else
                {
                    std::cout<<"Not a leaf"<<std::endl;
                }
            }
            //cog_desc->printDebug();
            gettimeofday(&start_us_scan, NULL);
            cog_desc->desc_key(max);
            gettimeofday(&end_us_scan, NULL);
            cout << "Time for "<<height_of_split<<" Descends is :" << total_time(start_us_scan, end_us_scan) << " us" << endl;    
        }
	}
	
}