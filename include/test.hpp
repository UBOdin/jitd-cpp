#ifndef _TEST_H_SHIELD
#define _TEST_H_SHIELD

#include <istream>
#include "jitd.hpp"

typedef Buffer<Record> RecordBuffer;
typedef CogHandle<Record> RecordCogHandle;

RecordBuffer build_buffer(int len, int max);
RecordBuffer load_buffer(std::istream &input);
RecordCogHandle array_for_buffer(RecordBuffer buff);
RecordCogHandle build_random_array(int len, int max);
RecordCogHandle build_random_sorted_array(int len, int max);

#endif // _TEST_H_SHIELD