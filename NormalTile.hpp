//---------------------------------------------------------------------------------------------------------------------
// NormalTile.hpp
//
// NormalTile subclass of Tile that represents a Tile without anything.
//
// Author: Boris Smiljanic 01531652
//         Milan Mirosav 11731475
//         Markus Dopelreiter 01535331
//---------------------------------------------------------------------------------------------------------------------
//

#ifndef NORMALTILE_HPP
#define NORMALTILE_HPP

#include "Tile.hpp"

class NormalTile : public Tile
{
public:
  //-------------------------------------------------------------------------------------------------------------------
  /// Constructor definition
  ///
  /// @param type The enum class TileType of the Tile.
  /// @param rotation The enum class Rotation of the Tile.
  //
  NormalTile(TileType type, Rotation rotation);

  //-------------------------------------------------------------------------------------------------------------------
  /// Destructor definition
  //
  ~NormalTile() = default;

  //-------------------------------------------------------------------------------------------------------------------
  /// Copy constructor
  ///
  //
  NormalTile(const NormalTile &copy);

  //-------------------------------------------------------------------------------------------------------------------
  /// Assignment operator
  ///
  ///
  NormalTile& operator= (const NormalTile &start_tile);

  //-------------------------------------------------------------------------------------------------------------------
  /// Get the string, which represents a normal tile. (with \n)
  ///
  /// @return A vector of tile strings.
  //
  std::string* getTileString() override;

  //-------------------------------------------------------------------------------------------------------------------
  /// Get Treasure, but unused because there is no Treasure.
  ///
  /// @return Treasure pointer.
  //
  Treasure* getTreasure() const override { return nullptr; };

  //-------------------------------------------------------------------------------------------------------------------
  /// collectTreasure, but unused because there is no Treasure.
  //
  void collectTreasure() override{};

  //-------------------------------------------------------------------------------------------------------------------
  /// Get PlayerColor, but unused because there is no Player.
  ///
  /// @return PlayerColor string.
  //
  std::string getPlayerColor() const override { return "False"; };

private:
  //-------------------------------------------------------------------------------------------------------------------
  /// Get the vector of strings, which represents a normal tile. (without \n)
  ///
  /// @return A pointer to the Treasure class
  //
  std::vector<std::string>* getTileStringVector() override;
  //-------------------------------------------------------------------------------------------------------------------
  /// Shows the tile in a string!
  //
  std::string tile_string_;
};
#endif // NORMALTILE_HPP