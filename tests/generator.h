

#ifndef TIMETABLE_GENERATOR_H
#define TIMETABLE_GENERATOR_H
#include <string>
#include <nlohmann/json.hpp>
#include <random>
#include <timetable.hpp>
#include <set>
#include <algorithm>
using namespace std;
const int nm = 10;
using vec_vecstr___str = vector<pair<vector<string>,string>>;
const std::vector<std::string> keywords_pool = {"university", "library", "openspace", "government"};
const size_t n_of_kwds = keywords_pool.size();
size_t decider(int max,unsigned int seed);
std::string generator(int id, const std::string& description, const std::vector<std::string>& keywords);
std::string generator_q(const vector<string>& qu);
vec_vecstr___str Generate_Events(size_t num_of_events);
vector<string> Gen_query();
set<string> Gen_expected(const vec_vecstr___str& events, const vector<string>& query);
#endif //TIMETABLE_GENERATOR_H
