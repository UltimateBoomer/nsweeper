#include "termdisplay.h"
#include "boardvisitor.h"
#include "cellstate.h"
#include "display.h"
#include "gamestate.h"
#include "regularboard.h"
#include "textchar.h"
#include "visitor.h"
#include <array>
#include <format>
#include <variant>

namespace nsweeper {

/* TermDisplay::TermDisplay(const Board *board, std::ostream &os) */
/*     : Display{board}, os{os} {} */
/**/
/* struct PrintBoardVisitor : public ConstBoardVisitor { */
/*   std::ostream &os; */
/**/
/*   explicit PrintBoardVisitor(std::ostream &os) : os{os} {} */
/**/
/*   virtual void operator()(const RegularBoard &board) override { */
/*     auto [width, height] = board.getDim(); */
/*     os << "+" << std::string(width * 2, '-') << "+" << std::endl; */
/*     for (size_t y = 0; y < height; ++y) { */
/*       os << "|"; */
/*       for (size_t x = 0; x < width; ++x) { */
/*         auto &state = board.getCell(x, y).getState(); */
/*         std::visit(Visitor{[&](auto) { os << emptyChar; }, */
/*                            [&](CellFlagged) { os << flagChar; }, */
/*                            [&](CellRevealed v) { */
/*                              os << numDisplayTable[v.numAdjacentMines]; */
/*                            }}, */
/*                    state); */
/*       } */
/*       os << "|" << std::endl; */
/*     } */
/*     os << "+" << std::string(width * 2, '-') << "+" << std::endl; */
/*   } */
/* }; */
/**/
/* struct PrintRevealedBoardVisitor : public ConstBoardVisitor { */
/*   std::ostream &os; */
/**/
/*   explicit PrintRevealedBoardVisitor(std::ostream &os) : os{os} {} */
/**/
/*   virtual void operator()(const RegularBoard &board) override { */
/*     auto [width, height] = board.getDim(); */
/*     os << "+" << std::string(width * 2, '-') << "+" << std::endl; */
/*     for (size_t y = 0; y < height; ++y) { */
/*       os << "|"; */
/*       for (size_t x = 0; x < width; ++x) { */
/*         auto &cell = board.getCell(x, y); */
/*         auto &state = cell.getState(); */
/*         std::visit(Visitor{[&](auto) { */
/*                              os << (cell.hasMine() ? mineChar : emptyChar);
 */
/*                            }, */
/*                            [&](CellFlagged) { */
/*                              os << (cell.hasMine() ? mineChar : flagChar); */
/*                            }, */
/*                            [&](CellRevealed v) { */
/*                              os << numDisplayTable[v.numAdjacentMines]; */
/*                            }}, */
/*                    state); */
/*       } */
/*       os << "|" << std::endl; */
/*     } */
/*     os << "+" << std::string(width * 2, '-') << "+" << std::endl; */
/*   } */
/* }; */
/**/
/* void TermDisplay::notify() { */
/**/
/*   os << std::format("Mines: {}/{}", getBoard()->getNumFlagged(), */
/*                     getBoard()->getNumMines()) */
/*      << std::endl; */
/*   os << std::format("Board: {}/{}", getBoard()->getNumRevealed(), */
/*                     getBoard()->size()) */
/*      << std::endl; */
/**/
/*   if (!std::holds_alternative<std::monostate>(getBoard()->getState())) { */
/*     getBoard()->accept(PrintRevealedBoardVisitor{os}); */
/*   } else { */
/*     getBoard()->accept(PrintBoardVisitor{os}); */
/*   } */
/* } */

} // namespace nsweeper
