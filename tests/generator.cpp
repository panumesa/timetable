//

//
#include "generator.h"
size_t decider(int max,unsigned int seed){
    std::srand(seed);
    size_t a = static_cast<size_t>(std::rand() % max);
    return  (a > 0) ? a : 1;
}

std::string generator(int id, const std::string& description, const std::vector<std::string>& keywords){
    nlohmann::json res;
    res["id"] = id;
    timetable::Date x{};
    res["date"] = x.to_json();
    timetable::Time y{};
    res["time"] = y.to_json();
    timetable::Location<double> z{};
    res["location"] = z.to_json();
    res["title"] = "koeficient";
    res["description"] = description;
    res["keywords"] = keywords;
    return res.dump();
}
std::string generator_q(const vector<string>& qu){
    nlohmann::json res;
    res["keywords"] = qu;
    return res.dump();
}
vec_vecstr___str Generate_Events(size_t num_of_events){
    vec_vecstr___str u; u.resize(num_of_events);
    for (size_t i = 0; i < num_of_events; ++i) {
        u[i].second = to_string(i);
        size_t m = decider(static_cast<int>(n_of_kwds + 1),static_cast<unsigned int>(i));
        for (size_t j = 0; j < m; ++j) {
            u[i].first.push_back(keywords_pool[j]);
        }
    }
    return u;
}
vector<string> Gen_query(){
    size_t m = decider(static_cast<int>(n_of_kwds),static_cast<unsigned int>(nm));
    vector<string> qu; qu.resize(m);
    for (size_t i = 0; i < m; ++i) {
        qu[i] = keywords_pool[n_of_kwds - 1 - i];
    }
    return qu;
}
set<string> Gen_expected(const vec_vecstr___str& events, const vector<string>& query){
    set<string> exp;
    for (size_t i = 0; i < events.size(); ++i) {
        exp.insert(events[i].second);
        for (size_t j = 0; j < query.size(); ++j) {
            if(std::find(events[i].first.begin(), events[i].first.end(), query[j]) == events[i].first.end())
            {
                exp.extract(events[i].second);
            }
        }
    }
    return exp;
}