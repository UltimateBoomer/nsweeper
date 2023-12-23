#include "game.h"
#include "regularboard.h"
#include "termcontroller.h"
#include "termdisplay.h"

using namespace nsweeper;

int main(int argc, char *argv[]) {
  Game game{std::cin, std::cout};
  game.run();
}
