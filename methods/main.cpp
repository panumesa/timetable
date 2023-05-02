/**
 * @file methods/main.cpp
 * @author Mikhail Lozhnikov
 *
 * Файл с функией main() для серверной части программы.
 */

#include <httplib.h>
#include <iostream>
#include <nlohmann/json.hpp>
#include "methods.hpp"



int main(int argc, char* argv[]) {
  // Порт по-умолчанию.
  int port = 8080;

  if (argc >= 2) {
    // Меняем порт по умолчанию, если предоставлен соответствующий
    // аргумент командной строки.
    if (std::sscanf(argv[1], "%d", &port) != 1)
      return -1;
  }

  std::cerr << "Listening on port " << port << "..." << std::endl;

  httplib::Server svr;
  timetable::Timetable<timetable::PublicEvent<double>> aa;
  // Обработчик для GET запроса по адресу /stop. Этот обработчик
  // останавливает сервер.
  svr.Get("/stop", [&](const httplib::Request&, httplib::Response&) {
    svr.stop();
  });
  svr.Post("/add_event", [&](const httplib::Request& req, httplib::Response& resp){
    std::string copy = req.body;
    nlohmann::json j = nlohmann::json::parse(copy);
    timetable::PublicEvent<double> abc(j);
    aa.AddEvent(abc);
    resp.status = 200;
    resp.body = std::to_string(abc.id);
  });
//  svr.Get("/get_event", )

  /* Сюда нужно вставить обработчик post запроса для алгоритма. */

  svr.Post("/get_keywords", [&](const httplib::Request& req, httplib::Response& resp){
    nlohmann::json result;
    timetable::get_keywords(aa, nlohmann::json::parse(req.body), result);
    resp.body = result["body"].dump();
  });

  /* Конец вставки. */

  // Эта функция запускает сервер на указанном порту. Программа не завершится
  // до тех пор, пока сервер не будет остановлен.
  svr.listen("0.0.0.0", port);

  return 0;
}
