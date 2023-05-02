//
// Created by Клим on 25.04.2023.
//

#ifndef TIMETABLE_GET_KEYWORDS_HPP
#define TIMETABLE_GET_KEYWORDS_HPP
#include <nlohmann/json.hpp>
#include "timetable.hpp"
using nlohmann::json;
int get_keywords(const nlohmann::json& input, nlohmann::json* output);
#endif //TIMETABLE_GET_KEYWORDS_HPP
