//---------------------------------------------------------------------------------------------------------------------
// Board.cpp
//
// Board is the class whitch represent the terminal output.
//
// Author: Boris Smiljanic 01531652
//         Milan Mirosav 11731475
//         Markus Dopelreiter 01535331
//---------------------------------------------------------------------------------------------------------------------
//

#include "Board.hpp"
#include "Game.hpp"
#include "Random.hpp"

Board::Board() {}

Board& Board::getInstance()
{
  static Board board;
  return board;
}

//---------------------------------------------------------------------------------------------------------------------
Board::~Board() {}

//---------------------------------------------------------------------------------------------------------------------
void Board::printTileOnBoard()
{
  Game& game = Game::getInstance();
  board_tiles_ = game.getBoardTiles();
  int max_board_row_cols = board_tiles_->front().size();
  int max_tile_row = board_tiles_->front().front()->getTileStringVector()->size();
  bool rows_fix = true;

  // goes through all board rows (7 times)
  for (int board_row_nr = 0; board_row_nr < max_board_row_cols; board_row_nr++)
  {
    // if the board row is fix (1,3,5,7)
    if (rows_fix == true)
    {
      // goes through all tile rows (5 times)
      for (int tile_row_nr = 0; tile_row_nr < max_tile_row; tile_row_nr++)
      {
        // goes through all board colums (7 times)
        for (int board_col_nr = 0; board_col_nr < max_board_row_cols; board_col_nr++)
        {
          if (board_col_nr == 0)
          {
            if (tile_row_nr == 2)
            {
              std::cout << "   " << (board_row_nr + 1);
            }
            else
            {
              std::cout << "    ";
            }
          }
          std::cout << board_tiles_->at(board_row_nr).at(board_col_nr)->getTileStringVector()->at(tile_row_nr);
        }
        std::cout << std::endl;
      }
      rows_fix = false;
    }
    else
    {
      // goes through all tile rows (5 times)
      for (int tile_row_nr = 0; tile_row_nr < max_tile_row; tile_row_nr++)
      {
        // goes through all board colums (7 times)
        for (int board_col_nr = 0; board_col_nr < max_board_row_cols; board_col_nr++)
        {
          if (board_col_nr == 0)
          {
            if (tile_row_nr == 2)
            {
              std::cout << "-->" << (board_row_nr + 1);
            }
            else
            {
              std::cout << "    ";
            }
          }
          std::cout << board_tiles_->at(board_row_nr).at(board_col_nr)->getTileStringVector()->at(tile_row_nr);
          if (board_col_nr == max_board_row_cols - 1)
          {
            if (tile_row_nr == 2)
            {
              std::cout << "<--";
            }
          }
        }
        std::cout << std::endl;
      }
      rows_fix = true;
    }
  }
}

//---------------------------------------------------------------------------------------------------------------------
void Board::printBoard()
{
  Game& game = Game::getInstance();
  players_ = game.getPlayers();
  size_t max_found_treasure = game.getTreasure().size() / game.getNrOfPlayers();
  // prints the right header
  if (game.getNrOfPlayers() == 2)
  {
    if (players_.at(0)->getNrFoundTreasures() > 9)
    {
      std::cout << "Player Red(R)    |                 |                 |    Player Yellow(Y)" << std::endl;
      std::cout << "Treasure: " << players_.at(0)->getNrFoundTreasures() << "/" << max_found_treasure
                << "  V                 V                 V    Treasure: " << players_.at(1)->getNrFoundTreasures()
                << "/" << max_found_treasure << std::endl;
      std::cout << "        1        2        3        4        5        6        7    " << std::endl;
    }
    else
    {
      std::cout << "Player Red(R)    |                 |                 |    Player Yellow(Y)" << std::endl;
      std::cout << "Treasure: " << players_.at(0)->getNrFoundTreasures() << "/" << max_found_treasure
                << "   V                 V                 V    Treasure: " << players_.at(1)->getNrFoundTreasures()
                << "/" << max_found_treasure << std::endl;
      std::cout << "        1        2        3        4        5        6        7    " << std::endl;
    }
  }
  else
  {
    std::cout << "Player Red(R)    |                 |                 |    Player Yellow(Y)" << std::endl;
    std::cout << "Treasure: " << players_.at(0)->getNrFoundTreasures() << "/" << max_found_treasure
              << "    V                 V                 V    Treasure: " << players_.at(1)->getNrFoundTreasures()
              << "/" << max_found_treasure << std::endl;
    std::cout << "        1        2        3        4        5        6        7    " << std::endl;
  }

  // prints the tile with arrows
  printTileOnBoard();

  // prints the footer
  if (game.getNrOfPlayers() == 2)
  {
    std::cout << "                 Ʌ                 Ʌ                 Ʌ" << std::endl;
    std::cout << "                 |                 |                 |" << std::endl;
  }
  if (game.getNrOfPlayers() == 3)
  {
    std::cout << "Player Green(G)  Ʌ                 Ʌ                 Ʌ" << std::endl;
    std::cout << "Treasure: " << players_.at(2)->getNrFoundTreasures() << "/" << max_found_treasure
              << "    |                 |                 |" << std::endl;
  }
  if (game.getNrOfPlayers() == 4)
  {
    std::cout << "Player Green(G)  Ʌ                 Ʌ                 Ʌ    Player Blue(B)" << std::endl;
    std::cout << "Treasure: " << players_.at(2)->getNrFoundTreasures() << "/" << max_found_treasure
              << "    |                 |                 |    Treasure: "
              << game.getPlayers().at(3)->getNrFoundTreasures() << "/" << max_found_treasure << std::endl;
  }
}
//---------------------------------------------------------------------------------------------------------------------
void Board::printFreeTile()
{
  Game& game = Game::getInstance();
  board_tiles_ = game.getBoardTiles();
  std::cout << "Free tile:" << std::endl << *board_tiles_->back().back()->getTileString();
}