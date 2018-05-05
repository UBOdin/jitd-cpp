#ifndef _TEST_H_SHIELD
#define _TEST_H_SHIELD

#include <istream>
#include "jitd.hpp"

#ifndef JITD_TEST_POLICY
#define JITD_TEST_POLICY PureLocalPolicy<Record>
#endif
#define TEST_JITD 

typedef Buffer<Record> RecordBuffer;
typedef CogHandle<Record> RecordCogHandle;

RecordBuffer build_buffer(int len, int max);
RecordBuffer load_buffer(std::istream &input);
RecordCogHandle array_for_buffer(RecordBuffer buff);
RecordCogHandle build_random_array(int len, int max);
RecordCogHandle build_random_sorted_array(int len, int max);

/// Utility functions in driver.cpp

double total_time(timeval &start, timeval &end);
RecordBuffer buffer_cmd(std::istream &toks);

/// Utility Macros for Parsing command strings
/// Typical usage:
///
///   string line;
///   while(getline(input, line)){
///     istringstream toks(line);
///     string op;
///     
///     CASE_1('first_option') {
///       ...
///     } CASE('second_option') {
///       ...
///     } CASE('third_option') {
///       ...
///     } else {
///       /* handle invalid option in 'line' */
///     }
///   }

#define CASE_1(s) toks >> op; if(string(s) == op)
#define CASE(s) else if(string(s) == op)

/// Actual test harnesses 

int jitd_test(JITD<Record, JITD_TEST_POLICY> &jitd, std::istream &input, bool interactive, int per_op_sleep_ms);
void cog_test(std::istream &input);
void ds_test(std::istream &input);

#endif // _TEST_H_SHIELD