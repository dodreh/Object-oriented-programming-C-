//---------------------------------------------------------------------------------------------------------------------
// Game.hpp
//
// Game class that represents the game logic.
//
// Author: Boris Smiljanic, 01531652
//         Milan Mirosav, 11731475
//         Markus Doppelreiter, 01535331
//---------------------------------------------------------------------------------------------------------------------
//

#ifndef GAME_HPP
#define GAME_HPP

#include "NormalTile.hpp"
#include "Player.hpp"
#include "Random.hpp"
#include "StartTile.hpp"
#include "Tile.hpp"
#include "TreasureTile.hpp"
#include "Item.hpp"
#include "ItemTile.hpp"

#include <fstream>
#include <iostream>
#include <map>

///--------------------------------------------------------------------------------------------------------------------
// Error Enum Class
// Enum class for Error exceptions.
//
enum class Error
{
  Exit,
  WrongArg,
  Memory,
  InvCommand,
  NotAllowed,
  InvParameter1,
  InvParameter2,
  ImpossibleMove,
  InvalidPosition,
  NoArguments,
  WrongNrArg,
  NotAllowedGo,
  CannotMove,
  NoItemCollected
};

class Game
{
public:
  //-------------------------------------------------------------------------------------------------------------------
  /// Returns an instance of the Game class (Singleton pattern).
  //
  static Game& getInstance();

  //-------------------------------------------------------------------------------------------------------------------
  /// Deleted copy constructor.
  //
  Game(const Game& copy) = delete;

  //-------------------------------------------------------------------------------------------------------------------
  /// Deleting assignment operator
  ///
  //
  Game& operator= (const Game &game) = delete;

  //-------------------------------------------------------------------------------------------------------------------
  /// Get the number of created players.
  ///
  /// @return integer number of players.
  //
  size_t getNrOfPlayers() const;

  //-------------------------------------------------------------------------------------------------------------------
  /// This methode starts the game.
  //
  void startGame();

  //-------------------------------------------------------------------------------------------------------------------
  /// This methode run the game.
  //
  void runGame();

  //-------------------------------------------------------------------------------------------------------------------
  /// Getter Methode to get the Treasure.
  ///
  /// @return vector of Treasure Pointer.
  //
  std::vector<Treasure*> getTreasure() const;

  //-------------------------------------------------------------------------------------------------------------------
  /// Getter Methode to get the FixTiles.
  ///
  /// @return vector of Tile Pointer.
  //
  std::vector<Tile*> getFixTiles() const;

  //-------------------------------------------------------------------------------------------------------------------
  /// Getter Methode to get the MovableTiles.
  ///
  /// @return vector of Tile Pointer.
  //
  std::vector<Tile*> getMovableTiles() const;

  //-------------------------------------------------------------------------------------------------------------------
  /// Getter Methode to get the Players.
  ///
  /// @return vector of Player Pointer.
  //
  std::vector<Player*> getPlayers() const;

  //-------------------------------------------------------------------------------------------------------------------
  /// Getter Methode to get the BoardTile.
  ///
  /// @return vector of Tile Pointer.
  //
  std::vector<std::vector<Tile*>>* getBoardTiles();

  //-------------------------------------------------------------------------------------------------------------------
  /// Set the coordinates by the given board_tile_.
  //
  void setCoordinates();

  //-------------------------------------------------------------------------------------------------------------------
  /// Set the bonus_ member variable if the program is called with -bonus argument.
  //
  void setBonus(bool bonus);

private:
  //-------------------------------------------------------------------------------------------------------------------
  /// This methode creates the player in the heap and you will get back how many
  /// player are in the game!
  //
  void createPlayer();

  //-------------------------------------------------------------------------------------------------------------------
  /// Reads the treasure from the "Treasures.txt" file and then creates the
  /// treasure objects which can then be used via the return vector.
  //
  void readTreasure();

  //-------------------------------------------------------------------------------------------------------------------
  /// Creates items and stores them into the vector items_.
  //
  void readItem();

  //-------------------------------------------------------------------------------------------------------------------
  /// Delete all created Treasures objects.
  //
  void assignCoveredStack(size_t nr_of_players);

  //-------------------------------------------------------------------------------------------------------------------
  /// Reads the tile form the "FixTile.txt" file and then creates the
  /// tile objects which can then be used via the return vector.
  //
  void createFixTile();

  //-------------------------------------------------------------------------------------------------------------------
  /// Reads the tile form the "MovableTile.txt" file and then creates the
  /// tile objects which can then be used via the return vector.
  //
  void createMovableTile();

  //-------------------------------------------------------------------------------------------------------------------
  /// Shuffles the movable tiles.
  //
  void shuffleMovableTiles();

  //-------------------------------------------------------------------------------------------------------------------
  /// Shuffles the orientation from the movable tiles.
  //
  void shuffleOrientation();

  //-------------------------------------------------------------------------------------------------------------------
  /// Set the board_tile_ vector an give the tiles the right coordinates.
  //
  void setBoardTilesWithCoordinates();


  //-------------------------------------------------------------------------------------------------------------------
  /// Put the player to the start tile.
  //
  void putPlayerOnStartTile();

  //-------------------------------------------------------------------------------------------------------------------
  /// Delete all created Treasures objects.
  //
  void deleteTreasure();

  //-------------------------------------------------------------------------------------------------------------------
  /// Delete all created Playeer objects.
  //
  void deletePlayer();

  //-------------------------------------------------------------------------------------------------------------------
  /// Delete all created tile objects.
  //
  void deleteAllTile();

  //-------------------------------------------------------------------------------------------------------------------
  /// Delete all created item objects.
  //
  void deleteAllItem();

  //-------------------------------------------------------------------------------------------------------------------
  /// Indicates a vector of all created treasures.
  //
  std::vector<Treasure*> treasures_;

  //-------------------------------------------------------------------------------------------------------------------
  /// Indicates a vector of all created fix tiles.
  //
  std::vector<Tile*> fix_tiles_;

  //-------------------------------------------------------------------------------------------------------------------
  /// Indicates a vector of all created movable tiles.
  //
  std::vector<Tile*> movable_tiles_;

  //-------------------------------------------------------------------------------------------------------------------
  /// Indicates a vector of vector of all tiles on the board.
  //
  std::vector<std::vector<Tile*>> board_tiles_;

  //-------------------------------------------------------------------------------------------------------------------
  /// Indicates a vector of all created treasures.
  //
  std::vector<Player*> players_;
  // std::vector<std::vector<Tile*>> board_output_;

  //-------------------------------------------------------------------------------------------------------------------
  /// Shows the number of created players.
  //
  size_t nr_of_players_;

  //-------------------------------------------------------------------------------------------------------------------
  /// Vector of created items.
  //
  std::vector<Item*> items_;

  //-------------------------------------------------------------------------------------------------------------------
  /// Shows if the program is called with -bonus argument or not. Initially set to false.
  //
  bool bonus_ = false;

  //-------------------------------------------------------------------------------------------------------------------
  /// Private constructor. Access only possible in the class.
  //
  Game();

  //-------------------------------------------------------------------------------------------------------------------
  /// Private destructor Acess only possible in the class
  //
  ~Game();
};
#endif // GAME_HPP
