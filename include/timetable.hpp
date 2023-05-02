/**
 * @file include/timetable.hpp
 * @author Mikhail Lozhnikov
 *
 * Определение класса расписания.
 */

#ifndef INCLUDE_TIMETABLE_HPP_
#define INCLUDE_TIMETABLE_HPP_

#include <unordered_map>
#include <unordered_set>
#include <map>
#include <vector>
#include <string>
#include <tuple>
#include <stdexcept>
#include <utility>
#include <cstdint>
#include <nlohmann/json.hpp>
namespace timetable {

/**
 * Дата события.
 */
struct Date {
  //! Год.
  uint16_t year;
  //! Месяц.
  uint8_t month;
  //! День.
  uint8_t day;
  Date() = default;
  Date(const nlohmann::json& j)
    : year(j["year"]), month(j["month"]), day(j["day"])
  {

  }
  /**
   * @brief Оператор сравнения "меньше" для двух дат.
   *
   * @param other Вторая дата.
   * @return Возвращает true, если текущая дата меньше второй даты
   * и false в противном случае.
   */
  bool operator<(const Date& other) const {
    return std::make_tuple(year, month, day) <
      std::make_tuple(other.year, other.month, other.day);
  }
  nlohmann::json to_json(){
      nlohmann::json tmp;
      tmp["day"] = this->day;
      tmp["month"] = this->month;
      tmp["year"] = this->year;
      return tmp;
  }
};

/**
 * Время начала события.
 */
struct Time {
  //! Часы.
  uint8_t hours;
  //! Минуты.
  uint8_t minutes;
  //! Секунды.
  uint8_t seconds;

  /**
   * @brief Оператор сравнения "меньше" для двух временных точек.
   *
   * @param other Вторая временная точка.
   * @return Возвращает true, если текущее время меньше второй временной точки
   * и false в противном случае.
   */
  Time() = default;
  Time(const nlohmann::json& j): hours(j["hours"]), minutes(j["minutes"]), seconds(j["seconds"]){

  }
  bool operator<(const Time& other) const {
    return std::make_tuple(hours, minutes, seconds) <
      std::make_tuple(other.hours, other.minutes, other.seconds);
  }
    nlohmann::json to_json(){
      nlohmann::json tmp;
      tmp["hours"] = this->hours;
      tmp["minutes"] = this->minutes;
      tmp["seconds"] = this->seconds;
      return tmp;
    }
};

/**
 * @brief Место события.
 * @tparam T Тип данных для широты и долготы.
 */
template <typename T>
struct Location {
  //! Широта.
  T latitude;
  //! Долгота.
  T longitude;
  Location() = default;
  Location(const nlohmann::json& j): latitude(j["latitude"].get<T>()), longitude(j["longitude"].get<T>()){

  }
    nlohmann::json to_json(){
      nlohmann::json tmp;
      tmp["latitude"] = this->latitude;
      tmp["longitude"] = this->longitude;
      return tmp;
    }
};

/**
 * Участник конференции.
 */
struct Participant {
  //! Имя.
  std::string name;
  //! Должность.
  std::string position;
  //! Возраст.
  unsigned age;
};

/**
 * @brief Открытое событие.
 * @tparam Real Тип данных для широты и долготы.
 */
template <typename Real>
struct PublicEvent {
  //! Уникальный идентификационный номер события.
  size_t id;

  //! Дата события.
  Date date;
  //! Время начала события.
  Time time;
  //! Место события.
  Location<Real> location;

  //! Название события.
  std::string title;
  //! Краткое описание события.
  std::string description;
  //! Список ключевых слов.
  std::vector<std::string> keywords;

  //! Список участников события. Для открытых событий список всегда пустой.
//  std::vector<Participant> Participants() const { return {}; }
  PublicEvent() = default;
  PublicEvent(const nlohmann::json& j):id(j["id"]) , date(j["date"]), time(j["time"]), location(j["location"]),title(j["title"]),
  description(j["description"]), keywords(j["keywords"])
  {

  }
};

/**
 * @brief Закрытое событие.
 * @tparam Real Тип данных для широты и долготы.
 */
template <typename Real>
struct PrivateEvent {
  //! Уникальный идентификационный номер события.
  size_t id;

  //! Дата события.
  Date date;
  //! Время начала события.
  Time time;
  //! Место события.
  Location<Real> location;

  //! Название события.
  std::string title;
  //! Краткое описание события.
  std::string description;
  //! Список ключевых слов.
  std::vector<std::string> keywords;

  //! Список участников события.
  std::vector<Participant> participants;

  PrivateEvent() = default;
  //! Получить список участников события.
  const std::vector<Participant>& Participants() const { return participants; }
  //! Модифицировать список участников события.
  std::vector<Participant>& Participants() { return participants; }
  PrivateEvent(const nlohmann::json& j):id(j["id"]) , date(j["date"]), time(j["time"]), location(j["location"]),title(j["title"]),
                                         description(j["description"]), keywords(j["keywords"]),participants(j["participants"]){
    }
};

template<typename Event>
class Timetable {
 public:
  /**
   * Конструктор по-умолчанию.
   */
  Timetable() = default;

  /**
   * @brief Добавить событие в расписание.
   *
   * @param event Добавляемое событие.
   *
   * Функция добавляет событие в расписание. Идентификационный номер
   * события должен быть уникальным.
   */
  void AddEvent(const Event& event) {
    if (idToEvent.find(event.id) != idToEvent.end())
      throw std::runtime_error("Event ids must differ!");

    idToEvent[event.id] = event;
    eventsByDateTime[std::make_pair(event.date, event.time)].insert(event.id);
  }

  /** Модифицировать словарь, задающий соответствие идентификационного номера
  событию. */
  std::unordered_map<std::size_t, Event>& IdToEvent() { return idToEvent; }
  //! Получить словарь, задающий соответствие идентификационного номера событию.
  const std::unordered_map<std::size_t, Event>& IdToEvent() const {
    return idToEvent;
  }

  /** Получить словарь идентификационных номеров событий, упорядоченных
  по дате и времени. */
  std::map<std::pair<Date, Time>, std::unordered_set<std::size_t>>&
      EventsByDateTime() {
    return eventsByDateTime;
  }

  /** Модифицировать словарь идентификационных номеров событий, упорядоченных
  по дате и времени. */
  const std::map<std::pair<Date, Time>, std::unordered_set<std::size_t>>&
      EventsByDateTime() const {
    return eventsByDateTime;
  }
 Timetable(const nlohmann::json& j){
//   idToEvent = j["idToEvent"].get<std::unordered_map<std::size_t, Event>>();
   const auto& events = j["idToEvent"];
   for(const auto& it : events){

   }
//   eventsByDateTime = j["eventsByDateTime"].get<std::map<std::pair<Date, Time>,std::unordered_set<std::size_t>>>();
  }
 private:
  //! Словарь, задающий соответствие идентификационного номера событию.
  std::unordered_map<std::size_t, Event> idToEvent;
  //! Словарь идентификационных номеров, упорядоченный по дате и времени.
  std::map<std::pair<Date, Time>,
           std::unordered_set<std::size_t>> eventsByDateTime;
};

}  // namespace timetable

#endif  // INCLUDE_TIMETABLE_HPP_
