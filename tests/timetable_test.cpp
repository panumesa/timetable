/**
 * @file tests/timetable_test.cpp
 * @author Mikhail Lozhnikov
 *
 * Тесты для класса Edge.
 */

#include <limits>
#include <timetable.hpp>
#include "test_core.hpp"
#include "test.hpp"


using timetable::Date;
using timetable::Time;
using timetable::Participant;
using timetable::PublicEvent;
using timetable::PrivateEvent;
using timetable::Timetable;

template<typename T>
static void BuildTest();

/**
 * @brief Набор тестов для класса timetable::Timetable.
 */
void TestTimetable() {
  TestSuite suite("TestTimetable");

  RUN_TEST(suite, BuildTest<float>);
  RUN_TEST(suite, BuildTest<double>);
  RUN_TEST(suite, BuildTest<long double>);
}

/**
 * @brief Тест на компиляцию шаблона.
 *
 * @tparam T Тип данных, используемый для арифметики.
 */
template<typename T>
static void BuildTest() {
  {
    PublicEvent<T> event;
      event.id = 1,
      event.date.year = 2000, event.date.month = 1, event.date.day = 1,
      event.time.hours = 1, event.time.minutes = 1, event.time.seconds = 1,
      event.location.latitude = 100, event.location.longitude  = 100,
      event.title = "Conference",
      event.description = "Some description",
      event.keywords = {"Key1", "Key2", "Key3"};

    Timetable<PublicEvent<T>> tt;

    tt.AddEvent(event);

    REQUIRE_EQUAL(tt.IdToEvent().at(1).id, 1);
  }

  {
      PrivateEvent<T> event;
      event.id = 1,
      event.date.year = 2000, event.date.month = 1, event.date.day = 1,
      event.time.hours = 1, event.time.minutes = 1, event.time.seconds = 1,
      event.location.latitude = 100, event.location.longitude  = 100,
      event.title = "Conference",
      event.description = "Some description",
      event.keywords = {"Key1", "Key2", "Key3"};
      event.participants = {
        {.name = "John Smith", .position = "C++ developer", .age = 30}
      };
  Timetable<PrivateEvent<T>> tt;

    tt.AddEvent(event);

    REQUIRE_EQUAL(tt.IdToEvent().at(1).id, 1);
  }
}
