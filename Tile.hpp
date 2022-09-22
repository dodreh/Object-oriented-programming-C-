//---------------------------------------------------------------------------------------------------------------------
// Tile.hpp
//
// Tile is the base classe of tile.
//
// Author: Boris Smiljanic 01531652
//         Milan Mirosav 11731475
//         Markus Dopelreiter 01535331
//---------------------------------------------------------------------------------------------------------------------
//

#ifndef TILE_HPP
#define TILE_HPP

#include "Player.hpp"
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

///--------------------------------------------------------------------------------------------------------------------
// TileType Enum Class
// Enum class for 6 types of tiles.
//
enum class TileType
{
  T,
  L,
  I,
  O,
  U,
  X
};

///--------------------------------------------------------------------------------------------------------------------
// Rotation Enum Class
// Enum class for 4 rotation positions of tiles.
//
enum class Rotation
{
  DEG0 = 0,
  DEG90 = 1,
  DEG180 = 2,
  DEG270 = 3
};

///--------------------------------------------------------------------------------------------------------------------
// Coordinates struct
// Coordinates will handle the position from the tiles.
//
struct Coordinates
{
  size_t row_;
  size_t column_;
};

///--------------------------------------------------------------------------------------------------------------------
/// Open struct
/// Open will show in which direction the tile is open.
//
struct Open
{
  bool up_ = true;
  bool down_ = true;
  bool right_ = true;
  bool left_ = true;
};

class Tile
{
public:
  //-------------------------------------------------------------------------------------------------------------------
  /// Constructor definition
  ///
  /// @param type The enum class TileType of the Tile.
  /// @param rotation The enum class Rotation of the Tile.
  //
  Tile(TileType type, Rotation rotation);

  //-------------------------------------------------------------------------------------------------------------------
  /// Destructor definition
  //
  virtual ~Tile();

  //-------------------------------------------------------------------------------------------------------------------
  /// Copy constructor
  ///
  //
  Tile(const Tile& copy);

  //-------------------------------------------------------------------------------------------------------------------
  /// Assignment operator
  ///
  //
  Tile& operator= (const Tile &tile);

  //-------------------------------------------------------------------------------------------------------------------
  /// Get the rotation value of the tile in degree.
  ///
  /// @return Integer in degree of rotation.
  //
  int getRotationValue() const;

  //-------------------------------------------------------------------------------------------------------------------
  /// Get the type in a string from the tile.
  ///
  /// @return string of the TileType.
  //
  std::string getTileTypeString() const;

  //-------------------------------------------------------------------------------------------------------------------
  /// Get the enum TileType from the tile.
  ///
  /// @return enum of TileType.
  //
  TileType getType() const;

  //-------------------------------------------------------------------------------------------------------------------
  /// Get the enum Rotation from the tile.
  ///
  /// @return enum of Rotation.
  //
  Rotation getRotation() const;

  //-------------------------------------------------------------------------------------------------------------------
  /// Get vector of pointers to players, which are on the tile.
  ///
  /// @return vevtor of pointers (referenz to players).
  //
  std::vector<Player*> getPlayer() const;

  //-------------------------------------------------------------------------------------------------------------------
  /// Get the the position (Coordinates)
  ///
  /// @return (Coordinates) position
  //
  Coordinates getPosition() const { return position_; };

  //-------------------------------------------------------------------------------------------------------------------
  /// Get the basic string vector, which is the base of all subclasses.
  ///
  /// @return vector of basic strings.
  //
  std::vector<std::string>* getBasicTileStringVector();

  //-------------------------------------------------------------------------------------------------------------------
  /// getTileString is deleted in the base class (virtual).
  //
  virtual std::string* getTileString() = 0;

  //-------------------------------------------------------------------------------------------------------------------
  /// getTileStringVector is deleted in the base class (virtual).
  //
  virtual std::vector<std::string>* getTileStringVector() = 0;

  //-------------------------------------------------------------------------------------------------------------------
  /// Set the rotation of a tile.
  ///
  /// @param rotation the enum class Rotation.
  //
  void setRotation(Rotation rotation);

  //-------------------------------------------------------------------------------------------------------------------
  /// Set a player on a tile.
  ///
  /// @param player pointer of the player.
  //
  void setPlayer(Player* player);

  //-------------------------------------------------------------------------------------------------------------------
  /// delete the last player on the vector.
  //
  void deletePlayer();

  //-------------------------------------------------------------------------------------------------------------------
  /// Set the position of the tile on the board.
  ///
  /// @param Coordinates position.
  //
  void setPosition(Coordinates position);
  //-------------------------------------------------------------------------------------------------------------------
  /// Gets open_to_ which shows us in which direction the tile is open.
  ///
  /// @return open_to_ of the current tile.
  //
  Open getOpenTo();
  //-------------------------------------------------------------------------------------------------------------------
  /// Erase the player from players_. Set new vector of players_ with new length.
  ///
  /// @param Pointer to the player (on the tile) which we want to erase.
  //
  void erasePlayer(Player* player);

  //-------------------------------------------------------------------------------------------------------------------
  /// getTreasure is deleted in the base class (virtual).
  //
  virtual Treasure* getTreasure() const = 0;

  //-------------------------------------------------------------------------------------------------------------------
  /// collectTreasure is deleted in the base class (virtual).
  //
  virtual void collectTreasure() = 0;

  //-------------------------------------------------------------------------------------------------------------------
  /// getPlayerColor is deleted in the base class (virtual).
  //
  virtual std::string getPlayerColor() const = 0;

  //-------------------------------------------------------------------------------------------------------------------
  /// This Methode orders the Players in the players_ vector
  //
  void orderPlayers();

private:
  //-------------------------------------------------------------------------------------------------------------------
  /// Get the basic string vector, if the enum TileType is I.
  ///
  /// @return vector of basic strings (Type I).
  //
  std::vector<std::string>* getBasicTileStringVectorTypI();

  //-------------------------------------------------------------------------------------------------------------------
  /// Get the basic string vector, if the enum TileType is T.
  ///
  /// @return vector of basic strings (Type T).
  //
  std::vector<std::string>* getBasicTileStringVectorTypT();

  //-------------------------------------------------------------------------------------------------------------------
  /// Get the basic string vector, if the enum TileType is L.
  ///
  /// @return vector of basic strings (Type L).
  //
  std::vector<std::string>* getBasicTileStringVectorTypL();

  //-------------------------------------------------------------------------------------------------------------------
  /// Get the basic string vector, if the enum TileType is X.
  ///
  /// @return vector of basic strings (Type X).
  //
  std::vector<std::string>* getBasicTileStringVectorTypX();

  //-------------------------------------------------------------------------------------------------------------------
  /// Get the basic string vector, if the enum TileType is O.
  ///
  /// @return vector of basic strings (Type O).
  //
  std::vector<std::string>* getBasicTileStringVectorTypO();

  //-------------------------------------------------------------------------------------------------------------------
  /// Set the open_to_ of the current tile.
  ///
  //
  void setOpenTo();

  //-------------------------------------------------------------------------------------------------------------------
  /// Shows the type of a tile.  Indicates for which.
  //
  TileType type_;

  //-------------------------------------------------------------------------------------------------------------------
  /// Shows the rotation of a tile.
  //
  Rotation rotation_;

  //-------------------------------------------------------------------------------------------------------------------
  /// Indicates the players in a vector.
  //
  std::vector<Player*> players_;

  //-------------------------------------------------------------------------------------------------------------------
  /// Shows the position of the tile.
  //
  Coordinates position_;
  //-------------------------------------------------------------------------------------------------------------------
  /// Shows in which direction the tile is open.
  //
  Open open_to_;

  //-------------------------------------------------------------------------------------------------------------------
  /// Shows the basic of all tiles in a vector.
  //
  std::vector<std::string> basic_tile_string_vector_;
};
#endif // TILE_HPP
