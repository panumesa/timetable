//
// Created by Клим on 25.04.2023.
//
#include "get_keywords.hpp"
#include "timetable.hpp"
#include <set>
namespace timetable {
  int get_keywords(const Timetable<PublicEvent<double>> &tt, const nlohmann::json &input, nlohmann::json &output) {
    std::set < std::string > kwds;
    for (const auto &it: input["keywords"])
      kwds.insert(it.get<std::string>());
    int count = 0;
    std::string ans;
    for (const auto &[id, Event]: tt.IdToEvent()) {
      std::set < std::string > tmp;
      for (const auto &it: Event.keywords) {
        tmp.insert(it);
      }
      bool is_subset = true;
      for (const auto &it: kwds) {
        if (tmp.find(it) == tmp.end())
          is_subset = false;
      }
      if (is_subset) {
        count++;
        ans = Event.description;
        output["body"] += ans;
      }
    }
    return 0;
  }
}