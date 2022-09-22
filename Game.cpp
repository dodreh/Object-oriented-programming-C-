//---------------------------------------------------------------------------------------------------------------------
// Game.cpp
//
// Game class that represents the game logic.
//
// Author: Boris Smiljanic 01531652
//         Milan Mirosav 11731475
//         Markus Dopelreiter 01535331
//---------------------------------------------------------------------------------------------------------------------
//

#include <algorithm>
#include <iostream>
#include <stdio.h>
#include <string>

#include "Board.hpp"
#include "Game.hpp"
#include "Prompt.hpp"
#include "Random.hpp"

//---------------------------------------------------------------------------------------------------------------------
Game::Game() {}

//---------------------------------------------------------------------------------------------------------------------
Game& Game::getInstance()
{
  static Game game;
  return game;
}

//---------------------------------------------------------------------------------------------------------------------
Game::~Game()
{
  deleteTreasure();
  deleteAllItem();
  deletePlayer();
  deleteAllTile();
}

//---------------------------------------------------------------------------------------------------------------------
size_t Game::getNrOfPlayers() const
{
  return nr_of_players_;
}

//---------------------------------------------------------------------------------------------------------------------
std::vector<Treasure*> Game::getTreasure() const
{
  return treasures_;
}

//---------------------------------------------------------------------------------------------------------------------
std::vector<Tile*> Game::getFixTiles() const
{
  return fix_tiles_;
}

//---------------------------------------------------------------------------------------------------------------------
std::vector<Tile*> Game::getMovableTiles() const
{
  return movable_tiles_;
}

//---------------------------------------------------------------------------------------------------------------------
std::vector<Player*> Game::getPlayers() const
{
  return players_;
}

//---------------------------------------------------------------------------------------------------------------------
std::vector<std::vector<Tile*>>* Game::getBoardTiles()
{
  return &board_tiles_;
}

//---------------------------------------------------------------------------------------------------------------------
void Game::runGame()
{
  Prompt& prompt = Prompt::getInstance();
  prompt.run();
}
//---------------------------------------------------------------------------------------------------------------------
void Game::deleteTreasure()
{
  for (auto iterator : treasures_)
  {
    delete iterator;
  }
}

//---------------------------------------------------------------------------------------------------------------------
void Game::deleteAllItem()
{
  for (auto iterator : items_)
  {
    delete iterator;
  }
}

//---------------------------------------------------------------------------------------------------------------------
void Game::readTreasure()
{
  treasures_.push_back(new Treasure("Totenkopf", 1));
  treasures_.push_back(new Treasure("Schwert", 2));
  treasures_.push_back(new Treasure("Goldsack", 3));
  treasures_.push_back(new Treasure("Schlüsselbund", 4));
  treasures_.push_back(new Treasure("Sombrero", 5));
  treasures_.push_back(new Treasure("Ritterhelm", 6));
  treasures_.push_back(new Treasure("Buch", 7));
  treasures_.push_back(new Treasure("Krone", 8));
  treasures_.push_back(new Treasure("Schatztruhe", 9));
  treasures_.push_back(new Treasure("Kerzenleuchte", 10));
  treasures_.push_back(new Treasure("Schatzkarte", 11));
  treasures_.push_back(new Treasure("Goldring", 12));
  treasures_.push_back(new Treasure("Eule", 13));
  treasures_.push_back(new Treasure("Hofnarr", 14));
  treasures_.push_back(new Treasure("Eidechse", 15));
  treasures_.push_back(new Treasure("Käfer", 16));
  treasures_.push_back(new Treasure("Flaschengeist", 17));
  treasures_.push_back(new Treasure("Kobold", 18));
  treasures_.push_back(new Treasure("Schlange", 19));
  treasures_.push_back(new Treasure("Geist", 20));
  treasures_.push_back(new Treasure("Fledermaus", 21));
  treasures_.push_back(new Treasure("Spinne", 22));
  treasures_.push_back(new Treasure("Ratte", 23));
  treasures_.push_back(new Treasure("Motte", 24));
}

//---------------------------------------------------------------------------------------------------------------------
void Game::readItem()
{
  items_.push_back(new Item("BRI"));
  items_.push_back(new Item("DYN"));
  items_.push_back(new Item("LAD"));
  items_.push_back(new Item("ROP"));
}

//---------------------------------------------------------------------------------------------------------------------
void Game::deleteAllTile()
{
  for (auto iterator : fix_tiles_)
  {
    delete iterator;
  }
  for (auto iterator : movable_tiles_)
  {
    delete iterator;
  }
}

//---------------------------------------------------------------------------------------------------------------------
void Game::createMovableTile()
{
  if (bonus_)
  {
    movable_tiles_.push_back(
      new ItemTile(TileType::X, Rotation::DEG0, items_.at(0)));
    movable_tiles_.push_back(
      new ItemTile(TileType::O, Rotation::DEG0, items_.at(1)));
    movable_tiles_.push_back(
      new ItemTile(TileType::X, Rotation::DEG0, items_.at(2)));
    movable_tiles_.push_back(
      new ItemTile(TileType::X, Rotation::DEG0, items_.at(3)));

    for (int to_nine = 0; to_nine < 9; to_nine++)
    {
      movable_tiles_.push_back(new NormalTile(TileType::L, Rotation::DEG0));
    }
    for (int to_nine = 0; to_nine < 9; to_nine++)
    {
      movable_tiles_.push_back(new NormalTile(TileType::I, Rotation::DEG0));
    }
    for (int treasure = 12; treasure < 24; treasure++)
    {
      movable_tiles_.push_back(new TreasureTile(TileType::T, Rotation::DEG0, treasures_.at(treasure)));
    }
  }
  else
  {
    for (int to_eleven = 0; to_eleven < 11; to_eleven++)
    {
      movable_tiles_.push_back(new NormalTile(TileType::L, Rotation::DEG0));
    }
    for (int to_eleven = 0; to_eleven < 11; to_eleven++)
    {
      movable_tiles_.push_back(new NormalTile(TileType::I, Rotation::DEG0));
    }
    for (int treasure = 12; treasure < 24; treasure++)
    {
      movable_tiles_.push_back(new TreasureTile(TileType::T, Rotation::DEG0, treasures_.at(treasure)));
    }
  }
}

//---------------------------------------------------------------------------------------------------------------------
void Game::createFixTile()
{
  // Fix Tile
  fix_tiles_.push_back(new StartTile(TileType::L, Rotation::DEG270, "R"));
  fix_tiles_.push_back(new TreasureTile(TileType::T, Rotation::DEG0, treasures_.at(0)));
  fix_tiles_.push_back(new TreasureTile(TileType::T, Rotation::DEG0, treasures_.at(1)));
  fix_tiles_.push_back(new StartTile(TileType::L, Rotation::DEG180, "Y"));
  fix_tiles_.push_back(new TreasureTile(TileType::T, Rotation::DEG90, treasures_.at(2)));
  fix_tiles_.push_back(new TreasureTile(TileType::T, Rotation::DEG90, treasures_.at(3)));
  fix_tiles_.push_back(new TreasureTile(TileType::T, Rotation::DEG0, treasures_.at(4)));
  fix_tiles_.push_back(new TreasureTile(TileType::T, Rotation::DEG270, treasures_.at(5)));
  fix_tiles_.push_back(new TreasureTile(TileType::T, Rotation::DEG90, treasures_.at(6)));
  fix_tiles_.push_back(new TreasureTile(TileType::T, Rotation::DEG180, treasures_.at(7)));
  fix_tiles_.push_back(new TreasureTile(TileType::T, Rotation::DEG270, treasures_.at(8)));
  fix_tiles_.push_back(new TreasureTile(TileType::T, Rotation::DEG270, treasures_.at(9)));
  fix_tiles_.push_back(new StartTile(TileType::L, Rotation::DEG0, "G"));
  fix_tiles_.push_back(new TreasureTile(TileType::T, Rotation::DEG180, treasures_.at(10)));
  fix_tiles_.push_back(new TreasureTile(TileType::T, Rotation::DEG180, treasures_.at(11)));
  fix_tiles_.push_back(new StartTile(TileType::L, Rotation::DEG90, "B"));
}

//---------------------------------------------------------------------------------------------------------------------
void Game::deletePlayer()
{
  for (auto iterator : players_)
  {
    delete iterator;
  }
}

//---------------------------------------------------------------------------------------------------------------------
void Game::createPlayer()
{
  std::cout << "Welcome to the Wild OOP Labyrinth!!!\n";
  nr_of_players_ = 2;
  std::string buffer;
  while (1)
  {
    std::cout << "Player Count (2-4): ";

    getline(std::cin, buffer);
    if (std::cin.eof())
    {
      throw Error::Exit;
    }
    // if(buffer.at(buffer.end()) == EOF)
    // delete alle white spaces!
    buffer.erase(remove(buffer.begin(), buffer.end(), ' '), buffer.end());
    if (!buffer.empty() && buffer.size() == 1 && buffer.front() >= '2' && buffer.front() <= '4')
    {
      nr_of_players_ = stoi(buffer);
      break;
    }
    std::cout << "Wrong Input only a Number from 2 to 4 is allowed!\n";
  }
  // create two players
  if (nr_of_players_ == 2)
  {
    players_.push_back(new Player(PlayerColor::R));
    players_.push_back(new Player(PlayerColor::Y));
  }
  // create three players
  if (nr_of_players_ == 3)
  {
    players_.push_back(new Player(PlayerColor::R));
    players_.push_back(new Player(PlayerColor::Y));
    players_.push_back(new Player(PlayerColor::G));
  }
  // create four players
  if (nr_of_players_ == 4)
  {
    players_.push_back(new Player(PlayerColor::R));
    players_.push_back(new Player(PlayerColor::Y));
    players_.push_back(new Player(PlayerColor::G));
    players_.push_back(new Player(PlayerColor::B));
  }
}

//---------------------------------------------------------------------------------------------------------------------
void Game::assignCoveredStack(size_t nr_of_players)
{
  std::vector<Treasure*> temp_created_treasures = treasures_;
  std::vector<Treasure*> first_player;
  std::vector<Treasure*> secound_player;
  std::vector<Treasure*> third_player;
  std::vector<Treasure*> fourth_player;
  size_t rand_number;

  // different cases, depending on the number of players
  if (nr_of_players == 2)
  {
    while (!temp_created_treasures.empty())
    {
      // first player
      rand_number = Oop::Random::getInstance().getRandomCard(temp_created_treasures.size());
      first_player.push_back(temp_created_treasures.at(rand_number - 1));
      temp_created_treasures.erase(temp_created_treasures.begin() + rand_number - 1);
      // secound player
      rand_number = Oop::Random::getInstance().getRandomCard(temp_created_treasures.size());
      secound_player.push_back(temp_created_treasures.at(rand_number - 1));
      temp_created_treasures.erase(temp_created_treasures.begin() + rand_number - 1);
    }
    players_.at(0)->setCoveredStack(first_player);
    players_.at(1)->setCoveredStack(secound_player);
  }
  if (nr_of_players == 3)
  {
    while (!temp_created_treasures.empty())
    {
      // first player
      rand_number = Oop::Random::getInstance().getRandomCard(temp_created_treasures.size());
      first_player.push_back(temp_created_treasures.at(rand_number - 1));
      temp_created_treasures.erase(temp_created_treasures.begin() + rand_number - 1);
      // secound player
      rand_number = Oop::Random::getInstance().getRandomCard(temp_created_treasures.size());
      secound_player.push_back(temp_created_treasures.at(rand_number - 1));
      temp_created_treasures.erase(temp_created_treasures.begin() + rand_number - 1);
      // third player
      rand_number = Oop::Random::getInstance().getRandomCard(temp_created_treasures.size());
      third_player.push_back(temp_created_treasures.at(rand_number - 1));
      temp_created_treasures.erase(temp_created_treasures.begin() + rand_number - 1);
    }
    players_.at(0)->setCoveredStack(first_player);
    players_.at(1)->setCoveredStack(secound_player);
    players_.at(2)->setCoveredStack(third_player);
  }
  if (nr_of_players_ == 4)
  {
    while (!temp_created_treasures.empty())
    {
      // first player
      rand_number = Oop::Random::getInstance().getRandomCard(temp_created_treasures.size());
      first_player.push_back(temp_created_treasures.at(rand_number - 1));
      temp_created_treasures.erase(temp_created_treasures.begin() + rand_number - 1);
      // secound player
      rand_number = Oop::Random::getInstance().getRandomCard(temp_created_treasures.size());
      secound_player.push_back(temp_created_treasures.at(rand_number - 1));
      temp_created_treasures.erase(temp_created_treasures.begin() + rand_number - 1);
      // third player
      rand_number = Oop::Random::getInstance().getRandomCard(temp_created_treasures.size());
      third_player.push_back(temp_created_treasures.at(rand_number - 1));
      temp_created_treasures.erase(temp_created_treasures.begin() + rand_number - 1);
      // fourth player
      rand_number = Oop::Random::getInstance().getRandomCard(temp_created_treasures.size());
      fourth_player.push_back(temp_created_treasures.at(rand_number - 1));
      temp_created_treasures.erase(temp_created_treasures.begin() + rand_number - 1);
    }
    players_.at(0)->setCoveredStack(first_player);
    players_.at(1)->setCoveredStack(secound_player);
    players_.at(2)->setCoveredStack(third_player);
    players_.at(3)->setCoveredStack(fourth_player);
  }
}

//---------------------------------------------------------------------------------------------------------------------
void Game::putPlayerOnStartTile()
{
  if (nr_of_players_ == 2)
  {
    fix_tiles_.at(0)->setPlayer(players_.at(0));
    fix_tiles_.at(3)->setPlayer(players_.at(1));
  }
  if (nr_of_players_ == 3)
  {
    fix_tiles_.at(0)->setPlayer(players_.at(0));
    fix_tiles_.at(3)->setPlayer(players_.at(1));
    fix_tiles_.at(12)->setPlayer(players_.at(2));
  }
  if (nr_of_players_ == 4)
  {
    fix_tiles_.at(0)->setPlayer(players_.at(0));
    fix_tiles_.at(3)->setPlayer(players_.at(1));
    fix_tiles_.at(12)->setPlayer(players_.at(2));
    fix_tiles_.at(15)->setPlayer(players_.at(3));
  }
}

//---------------------------------------------------------------------------------------------------------------------
void Game::shuffleMovableTiles()
{
  int number_of_movable_tiles = movable_tiles_.size();
  std::vector<Tile*> temp_movable_tiles;
  size_t number = movable_tiles_.size();
  // Because the last input in the vector shouldn't call the random class
  for (size_t cnt = 0; cnt < number - 1; cnt++)
  {
    int rand_number = Oop::Random::getInstance().getRandomCard(number_of_movable_tiles);
    Tile* temp_tile = movable_tiles_.at(rand_number - 1);
    temp_movable_tiles.push_back(temp_tile);
    movable_tiles_.erase(movable_tiles_.begin() + rand_number - 1);
    number_of_movable_tiles--;
  }
  // last input without random class
  Tile* temp_tile = movable_tiles_.front();
  temp_movable_tiles.push_back(temp_tile);
  movable_tiles_.erase(movable_tiles_.begin());

  movable_tiles_ = temp_movable_tiles;
}

//---------------------------------------------------------------------------------------------------------------------
void Game::shuffleOrientation()
{
  // size() - 1, because the last should have the  orientation value 0
  for (size_t i = 0; i < movable_tiles_.size() - 1; i++)
  {
    size_t rand_number = Oop::Random::getInstance().getRandomOrientation();
    Rotation rand = static_cast<Rotation>(rand_number);
    movable_tiles_.at(i)->setRotation(rand);
  }
}

//---------------------------------------------------------------------------------------------------------------------
void Game::setBoardTilesWithCoordinates()
{
  std::vector<Tile*> temp_board_vector;
  size_t max_board_row_cols = 7;
  bool cols_fix = true, rows_fix = true;
  int fix_counter = 0, mov_counter = 0;
  size_t board_row_nr;
  // goes through all board rows (7 times)
  for (board_row_nr = 0; board_row_nr < max_board_row_cols; board_row_nr++)
  {
    // if the board row is fix (1,3,5,7)
    if (rows_fix == true)
    {
      // goes through all board colums (7 times)
      for (size_t board_col_nr = 0; board_col_nr < max_board_row_cols; board_col_nr++)
      {
        // if the board colum is fix (1,3,5,7)
        if (cols_fix == true)
        {
          temp_board_vector.push_back(fix_tiles_.at(fix_counter));
          fix_tiles_.at(fix_counter)->setPosition({board_row_nr + 1, board_col_nr + 1});
          cols_fix = false;
          fix_counter++;
        }
        // if the board colum is movable (2,4,6)
        else
        {
          temp_board_vector.push_back(movable_tiles_.at(mov_counter));
          movable_tiles_.at(mov_counter)->setPosition({board_row_nr + 1, board_col_nr + 1});
          cols_fix = true;
          mov_counter++;
        }
      }
      board_tiles_.push_back(temp_board_vector);
      temp_board_vector.clear();
      cols_fix = true;
      rows_fix = false;
    }
    // if the board row is movable (2,4,6)
    else
    {

      // goes through all board colums (7 times)
      for (size_t board_col_nr = 0; board_col_nr < max_board_row_cols; board_col_nr++)
      {
        temp_board_vector.push_back(movable_tiles_.at(mov_counter));
        movable_tiles_.at(mov_counter)->setPosition({board_row_nr + 1, board_col_nr + 1});
        mov_counter++;
      }
      board_tiles_.push_back(temp_board_vector);
      temp_board_vector.clear();
      rows_fix = true;
      cols_fix = true;
    }
  }
  temp_board_vector.push_back(movable_tiles_.back());
  movable_tiles_.back()->setPosition({board_row_nr + 1, 1});
  board_tiles_.push_back(temp_board_vector);
}

//---------------------------------------------------------------------------------------------------------------------
void Game::setCoordinates()
{
  for (size_t row = 0; row < board_tiles_.size() - 1; row++)
  {
    for (size_t column = 0; column < board_tiles_.front().size(); column++)
    {
      board_tiles_.at(row).at(column)->setPosition({row + 1, column + 1});
    }
  }
  board_tiles_.back().back()->setPosition({board_tiles_.size(), 1});
}

//---------------------------------------------------------------------------------------------------------------------
void Game::startGame()
{
  createPlayer();

  readTreasure();
  readItem();
  createFixTile();
  createMovableTile();
  putPlayerOnStartTile();

  shuffleMovableTiles();
  shuffleOrientation();
  setBoardTilesWithCoordinates();

  Board& board = Board::getInstance();
  board.printBoard();
  assignCoveredStack(nr_of_players_);
}

//---------------------------------------------------------------------------------------------------------------------
void Game::setBonus(bool bonus)
{
  bonus_ = bonus;
}