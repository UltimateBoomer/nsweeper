#include "gamesetting.h"
#include "interactivegame/interactivegame.h"
#include <clocale>
#include <ncpp/NotCurses.hh>

using namespace nsweeper;

int main(int argc, char *argv[]) {
  setlocale(LC_CTYPE, "");
  GameSetting s = settings[0].first;

  for (int i = 1; i < argc; ++i) {
    std::string str = argv[i];
    if (str == "-s" || str == "--settings") {
      str = argv[++i];
      size_t n = std::stoll(str);
      if (n < settings.size()) {
        s = settings[n].first;
      }
    }
  }

  ncpp::NotCurses nc;
  InteractiveGame game{s, nc};
  /* game.run(); */
}
