#include "termcontroller.h"
#include "boardvisitor.h"
#include "pressresult.h"
#include "regularboard.h"
#include "visitor.h"
#include <functional>
#include <istream>
#include <variant>

namespace nsweeper {

/* TermController::TermController(Board *board, std::istream &is, std::ostream
 * &os) */
/*     : Controller{board}, is{is}, os{os} {} */
/**/
/* struct PressVisitor : public BoardVisitor { */
/*   std::istream &is; */
/**/
/*   PressVisitor(std::istream &is) : is{is} {} */
/**/
/*   void operator()(RegularBoard &board) { */
/*     int x, y; */
/*     is >> x >> y; */
/*     board.press(x, y); */
/*   } */
/* }; */
/**/
/* struct FlagVisitor : public BoardVisitor { */
/*   std::istream &is; */
/**/
/*   FlagVisitor(std::istream &is) : is{is} {} */
/**/
/*   void operator()(RegularBoard &board) { */
/*     int x, y; */
/*     is >> x >> y; */
/*     board.flag(x, y); */
/*   } */
/* }; */
/**/
/* void TermController::makeMove() { */
/*   std::string cmd; */
/*   os << "> "; */
/*   is >> cmd; */
/**/
/*   if (cmd == "p" || cmd == "press") { */
/*     getBoard()->accept(PressVisitor{is}); */
/*   } else if (cmd == "f" || cmd == "flag") { */
/*     getBoard()->accept(FlagVisitor{is}); */
/*   } */
/* } */

} // namespace nsweeper
