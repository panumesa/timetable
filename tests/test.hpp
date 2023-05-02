/**
 * @file tests/test.hpp
 * @author Mikhail Lozhnikov
 *
 * Заголовочный файл для объявлений основных тестовых функций.
 */

#ifndef TESTS_TEST_HPP_
#define TESTS_TEST_HPP_

#include <httplib.h>
#include <nlohmann/json.hpp>
#include <set>
#include <unordered_set>
#include "generator.h"
const int num = 14;
/**
 * @brief Набор тестов для класса timetable::Timetable.
 */
void TestTimetable();

/* Сюда нужно добавить объявления тестовых функций. */

void Test_get_keywords();

/* Конец вставки. */

#endif  // TESTS_TEST_HPP_
