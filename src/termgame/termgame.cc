#include "termgame/termgame.h"
#include "board/boardstate.h"
#include "board/pressresult.h"
#include "board/regularboard.h"
#include "gamesetting.h"
#include "termgame/termcontroller.h"
#include "termgame/termdisplay.h"
#include "visitor.h"
#include <array>
#include <bits/chrono.h>
#include <chrono>
#include <format>
#include <memory>
#include <sstream>
#include <variant>

namespace nsweeper {
/* TermGame::TermGame(GameSetting s, std::istream &is, std::ostream &os) */
/*     : board{std::make_unique<RegularBoard>(s.dim)}, */
/*       display{std::make_unique<TermDisplay>(board, os)}, */
/*       controller{std::make_unique<TermController>(board, is, os)}, is{is}, */
/*       os{os} {} */
/**/
/* struct PosReader { */
/*   std::istream &is; */
/**/
/*   template <typename BoardType> */
/*   BoardType::Pos operator()(const BoardType &board); */
/* }; */
/**/
/* template <> */
/* RegularBoard::Pos */
/* PosReader::operator()<RegularBoard>(const RegularBoard &board) { */
/*   size_t x, y; */
/*   is >> x >> y; */
/*   return {x, y}; */
/* } */
/**/
/* template <typename BoardType> */
/* void distribute(BoardType &&board, size_t n, unsigned int seed) { */
/*   std::mt19937_64 rng{seed}; */
/*   size_t size = board.size(); */
/*   std::vector<size_t> nums(size); */
/*   std::iota(nums.begin(), nums.end(), 0); */
/*   std::shuffle(nums.begin(), nums.end(), rng); */
/*   board.clear(); */
/*   size_t i = 0; */
/*   for (auto it = nums.begin(); i < n && it != nums.end(); ++i, ++it) { */
/*     board.setMine(true, *it); */
/*   } */
/* } */
/**/
/* void TermGame::run() { */
/*   os << "Welcome to NSweeper!" << std::endl; */
/*   os << "Select type of game: " << std::endl; */
/*   for (auto it = settings.begin(); it != settings.end(); ++it) { */
/*     os << std::format("{}: {} ({}x{}, {} mines)", */
/*                       std::distance(settings.begin(), it), it->second, */
/*                       it->first.dim.x, it->first.dim.y, it->first.numMines)
 */
/*        << std::endl; */
/*   } */
/*   std::string mode; */
/*   GameSetting s; */
/*   while (is) { */
/*     os << "> "; */
/*     is >> mode; */
/**/
/*     size_t num; */
/*     if (std::istringstream{mode} >> num) { */
/*       if (num < settings.size()) { */
/*         s = settings[num].first; */
/*         break; */
/*       } */
/*     } */
/*   } */
/**/
/*   auto seed = std::random_device{}(); */
/*   os << "Seed: " << seed << std::endl; */
/*   board.emplace<RegularBoard>(s.dim.x, s.dim.y); */
/* } */
/**/
/* void TermGame::setup() { */
/*   std::string cmd; */
/*   bool cont = true; */
/*   while (cont) { */
/*     try { */
/*       os << "SETUP > "; */
/*       is >> cmd; */
/**/
/*       if (cmd == "s" || cmd == "set") { */
/*         auto pos = std::visit(PosReader{is}, board); */
/*         std::visit([&](auto &&board) { board.setMine(true, pos); }, board);
 */
/*       } else if (cmd == "u" || cmd == "unset") { */
/*         auto pos = std::visit(PosReader{is}, board); */
/*         std::visit([&](auto &&board) { board.setMine(false, pos); }, board);
 */
/*       } else if (cmd == "r" || cmd == "random") { */
/*         size_t n; */
/*         is >> n; */
/*         auto seed = std::random_device{}(); */
/*         os << "Seed: " << seed << std::endl; */
/*         std::visit([&](auto &&board) { distribute(board, n, seed); }, board);
 */
/*       } else if (cmd == "rs" || cmd == "random_seed") { */
/*         size_t n; */
/*         unsigned int seed; */
/*         is >> n >> seed; */
/*         std::visit([&](auto &&board) { distribute(board, n, seed); }, board);
 */
/*       } else if (cmd == "d" || cmd == "done") { */
/*         cont = false; */
/*       } */
/*     } catch (std::iostream::failure &) { */
/*       os << "Exiting" << std::endl; */
/*       cont = false; */
/*     } */
/*   } */
/* } */
/**/
/* void TermGame::runLoop() { */
/*   auto t1 = std::chrono::high_resolution_clock::now(); */
/*   std::string cmd; */
/*   while (is) { */
/*     display->notify(); */
/*     controller->makeMove(); */
/*     auto state = std::visit([](auto &&b) { return b.getState(); }, board); */
/**/
/*     if (!std::holds_alternative<std::monostate>(state)) { */
/*       break; */
/*     } */
/*   } */
/*   auto t2 = std::chrono::high_resolution_clock::now(); */
/*   std::visit( */
/*       Visitor{[&](GameWon &&) { */
/*                 display->notify(); */
/*                 os << "You won!" << std::endl; */
/*                 os << std::format( */
/*                           "Time: {}", */
/*                           std::chrono::duration_cast<std::chrono::seconds>(t2
 * - */
/*                                                                            t1))
 */
/*                    << std::endl; */
/*               }, */
/*               [&](GameLost &&) { */
/*                 display->notify(); */
/*                 os << "You Lost!" << std::endl; */
/*               }, */
/*               [&](auto &&) {}}, */
/*       std::visit([](auto &&b) { return b.getState(); }, board)); */
/* } */
} // namespace nsweeper
