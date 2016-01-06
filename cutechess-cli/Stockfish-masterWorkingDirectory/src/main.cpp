/*
  Stockfish, a UCI chess playing engine derived from Glaurung 2.1
  Copyright (C) 2004-2008 Tord Romstad (Glaurung author)
  Copyright (C) 2008-2015 Marco Costalba, Joona Kiiski, Tord Romstad

  Stockfish is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  Stockfish is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <iostream>

#include "bitboard.h"
#include "evaluate.h"
#include "position.h"
#include "search.h"
#include "thread.h"
#include "types.h"
#include "tt.h"
#include "uci.h"
#include "syzygy/tbprobe.h"

Value
  VALUE_ZERO      = 0,
  VALUE_DRAW      = 0,
  VALUE_KNOWN_WIN = 10000,
  VALUE_MATE      = 32000,
  VALUE_INFINITE  = 32001,
  VALUE_NONE      = 32002,
  VALUE_MATE_IN_MAX_PLY  =  VALUE_MATE - 2 * MAX_PLY,
  VALUE_MATED_IN_MAX_PLY = -VALUE_MATE + 2 * MAX_PLY,
  PawnValueMg   = 198,   PawnValueEg   = 258,
  KnightValueMg = 817,   KnightValueEg = 846,
  BishopValueMg = 836,   BishopValueEg = 857,
  RookValueMg   = 1270,  RookValueEg   = 1281,
  QueenValueMg  = 2521,  QueenValueEg  = 2558,
  MidgameLimit  = 15581, EndgameLimit  = 3998;

int main(int argc, char* argv[]) {

  std::cout << engine_info() << std::endl;

  UCI::init(Options);
  PSQT::init();
  Bitboards::init();
  Position::init();
  Bitbases::init();
  Search::init();
  Eval::init();
  Pawns::init();
  Threads.init();
  Tablebases::init(Options["SyzygyPath"]);
  TT.resize(Options["Hash"]);

  char * pawnMg = getenv("PawnValueMg");
  if(pawnMg != NULL){
    PawnValueMg = std::stoi(pawnMg);
  }
  char * knightMg = getenv("KnightValueMg");
  if(knightMg != NULL){
    KnightValueMg = std::stoi(knightMg);
  }
  char * bishopMg = getenv("BishopValueMg");
  if(bishopMg != NULL){
    BishopValueMg = std::stoi(bishopMg);
  }
  char * rookMg = getenv("RookValueMg");
  if(pawnMg != NULL){
    RookValueMg = std::stoi(rookMg);
  }
  char * queenMg = getenv("QueenValueMg");
  if(pawnMg != NULL){
    QueenValueMg = std::stoi(queenMg);
  }
    
    
    /*FILE * output;
    output = fopen("output.txt", "w");
    fprintf(output, "%d\t%d\t%d\t%d\t%d\n", PawnValueMg, KnightValueMg, BishopValueMg, RookValueMg, QueenValueMg);
    fclose(output);*/
  

  UCI::loop(argc, argv);

  Threads.exit();
  return 0;
}
