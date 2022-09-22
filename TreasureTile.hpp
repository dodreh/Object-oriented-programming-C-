//---------------------------------------------------------------------------------------------------------------------
// TreasureTile.hpp
//
// TreasureTile subclass of Tile that represents a gear map with a treasure.
//
// Author: Boris Smiljanic 01531652
//         Milan Mirosav 11731475
//         Markus Dopelreiter 01535331
//---------------------------------------------------------------------------------------------------------------------
//

#ifndef TREASURETILE_HPP
#define TREASURETILE_HPP

#include "Tile.hpp"
#include <string>

class TreasureTile : public Tile
{
public:
  //-------------------------------------------------------------------------------------------------------------------
  /// Constructor definition
  ///
  /// @param type The enum class TileType of the Tile.
  /// @param rotation The enum class Rotation of the Tile.
  /// @param treasure A pointer to the Treasure class.
  //
  TreasureTile(TileType type, Rotation rotation, Treasure* treasure);

  //-------------------------------------------------------------------------------------------------------------------
  /// Destructor definition
  //
  ~TreasureTile() = default;

  //-------------------------------------------------------------------------------------------------------------------
  /// Copy constructor
  ///
  //
  TreasureTile(const TreasureTile &copy);

  //-------------------------------------------------------------------------------------------------------------------
  /// Assignment operator
  ///
  ///
  TreasureTile& operator= (const TreasureTile &treasure_tile);

  //-------------------------------------------------------------------------------------------------------------------
  /// Get the pointer, which point to the Treasure class
  ///
  /// @return A pointer to the Treasure class
  //
  Treasure* getTreasure() const override;

  //-------------------------------------------------------------------------------------------------------------------
  /// Get the string, which represents a treasure tile. (with \n)
  ///
  /// @return A string for illustration treasure tile.
  //
  std::string* getTileString() override;

  //-------------------------------------------------------------------------------------------------------------------
  /// Get the vector of strings, which represents a treasure tile. (without \n)
  ///
  /// @return A vector of tile strings.
  //
  std::vector<std::string>* getTileStringVector() override;

  //-------------------------------------------------------------------------------------------------------------------
  /// Collect the treasure.
  //
  void collectTreasure() override;

  //-------------------------------------------------------------------------------------------------------------------
  /// Get the vector of strings, which represents a treasure tile. (without \n) when no treasure is on it!
  ///
  /// @return A vector of tile strings.
  //
  std::vector<std::string>* noTreasureTileStringVector();

  //-------------------------------------------------------------------------------------------------------------------
  /// Get the vector of strings, which represents a treasure tile. (without \n) when a treasure is on it!
  ///
  /// @return A vector of tile strings.
  //
  std::vector<std::string>* treasureTileStringVector();

  //-------------------------------------------------------------------------------------------------------------------
  /// Get the playerColor as string.
  ///
  /// @return playercolor as string.
  //
  std::string getPlayerColor() const override { return "False"; };

private:
  //-------------------------------------------------------------------------------------------------------------------
  /// Refers to the Treasure
  //
  Treasure* treasure_;

  //-------------------------------------------------------------------------------------------------------------------
  /// Shows whether the treasure has been collected
  //
  bool collected_;

  //-------------------------------------------------------------------------------------------------------------------
  /// Shows the tile in a string!
  //
  std::string tile_string_;
};
#endif // TREASURETILE_HPP