//
#include "test.hpp"
using namespace std;
const std::string cont_type = "application/json";
void Test_get_keywords(){
    httplib::Client cli("127.0.0.1:8080");
    cli.Post("/add_event",generator(num + 1,"niveles1", {"ogord","pov","ulukbek"}),cont_type.c_str());
    cli.Post("/add_event",generator(num + 2,"niveles2", {"ogood","pov","ulukbek"}),cont_type.c_str());
    cli.Post("/add_event",generator(num + 3,"niveles3", {"ogorod","plov","ulukbek"}),cont_type.c_str());
    cli.Post("/add_event",generator(num + 4,"niveles4", {"ogorod","plov","ulukbek"}),cont_type.c_str());
    auto result = cli.Post("/get_keywords",R"({
    "keywords": [
        "ogorod",
        "plov"
    ]
})","application/json");
    std::cout << result->body << '\n';
    const std::unordered_set<std::string> expected = {"niveles3","niveles4"};
    if(!(expected == nlohmann::json::parse(result->body).get<std::unordered_set<std::string>>())){
        std::cout << "Test 1 failed \n";
        return;
    }
    vector<pair<vector<string>,string>> Events = Generate_Events(num);
    vector<string> query = Gen_query();
    set<string> expected2 = Gen_expected(Events, query);
    for (int i = 0; i < Events.size(); ++i) {
        cli.Post("/add_event", generator(i,Events[i].second,Events[i].first),cont_type.c_str());
    }
    auto res2 = cli.Post("/get_keywords", generator_q(query), cont_type.c_str());
    set<string> set_res2 = nlohmann::json::parse(res2->body).get<set<string>>();
//  if(expected2 )
    if(expected2 != set_res2){
        std::cout << "Test 2 failed \n";
        return;
    }
}

//
