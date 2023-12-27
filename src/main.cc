#include "gamesetting.h"
#include "interactivegame.h"
#include "regularboard.h"
#include <clocale>
#include <ncpp/NotCurses.hh>

using namespace nsweeper;

int main(int argc, char *argv[]) {
  setlocale(LC_CTYPE, "");
  ncpp::NotCurses nc;
  InteractiveGame game{settings[0].first, nc};
  /* game.run(); */
}
