#ifndef HELPER_FUNCS_H
#define HELPER_FUNCS_H
#include <format>
#include <fstream>
#include <string>
#include <vector>

#include "baseGUI.h"

inline std::string get_time() {
   // Epoch was 01 Jan 1970
   auto seconds_since_epoch =
      chrono::system_clock::now().time_since_epoch().count() /
      1'000'000'000;

   auto seconds_into_today = seconds_since_epoch % (3600 * 24);
   auto hours = seconds_into_today / 3600;
   // Very basic conversion to my timezone - WIP
   hours += 1;
   auto minutes = (seconds_into_today % 3600) / 60;

   return std::format("{}:{}", hours, minutes);
}

inline std::vector<std::string> get_weather() {
   const std::string output_file = "./pics/weather.txt";

   int code = system(std::format(
      "curl -sf wttr.in/London | head -n 7 | ansi2txt | iconv -f utf8 -t ascii//TRANSLIT > {}",
      output_file).c_str());
   if (code != 0) {
      throw runtime_error(std::format("Weather call failed with code: {}", code));
   }

   std::ifstream ifs(output_file);
   if (!ifs.is_open()) {
      throw runtime_error("could not open weather file");
   }

   std::stringstream ss{};
   std::string weather_line{};
   std::vector<std::string> lines{};

   while (getline(ifs, weather_line)) {
      if (weather_line.size() == 0) continue;
      if (weather_line.starts_with("Weather report: London")) continue;

      std::string l = weather_line.substr(0, 16) + weather_line.substr(16, 14) + '\n';

      for (auto& ch : l) {
         if (ch <= 31) ch = ' ';
      }

      lines.push_back(l);
   }

   return lines;
}

#endif //HELPER_FUNCS_H
