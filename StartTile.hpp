//---------------------------------------------------------------------------------------------------------------------
// StartTile.hpp
//
// StartTile subclass of Tile that represents a gait map.
//
// Author: Boris Smiljanic 01531652
//         Milan Mirosav 11731475
//         Markus Dopelreiter 01535331
//---------------------------------------------------------------------------------------------------------------------
//

#ifndef STARTTILE_HPP
#define STARTTILE_HPP

#include "Tile.hpp"

class StartTile : public Tile
{
public:
  //-------------------------------------------------------------------------------------------------------------------
  /// Constructor definition
  ///
  /// @param type The enum class TileType of the Tile.
  /// @param rotation The enum class Rotation of the Tile.
  /// @param player_color The string abbreviation (R/Y/G/B)
  //
  StartTile(TileType type, Rotation rotation, std::string player_color);

  //-------------------------------------------------------------------------------------------------------------------
  /// Destructor definition
  //
  ~StartTile() = default;

  //-------------------------------------------------------------------------------------------------------------------
  /// Copy constructor
  ///
  //
  StartTile(const StartTile &copy);

  //-------------------------------------------------------------------------------------------------------------------
  /// Assignment operator
  ///
  ///
  StartTile& operator= (const StartTile &start_tile);

  //-------------------------------------------------------------------------------------------------------------------
  /// Get abbreviation of the string, which players color is on the start tile.
  ///
  /// @return The string abbreviation (R/Y/G/B)
  //
  std::string getPlayerColor() const override;

  //-------------------------------------------------------------------------------------------------------------------
  /// Get the string, which represents a start tile. (with \n)
  ///
  /// @return A string for illustration start tile.
  //
  std::string* getTileString() override;

  //-------------------------------------------------------------------------------------------------------------------
  /// Get the vector of strings, which represents a start tile. (without \n)
  ///
  /// @return A vector of tile strings.
  //
  std::vector<std::string>* getTileStringVector() override;

  //-------------------------------------------------------------------------------------------------------------------
  /// Get Treasure, but unused because ther is no Treasure.
  ///
  /// @return Treasure pointer.
  //
  Treasure* getTreasure() const override { return nullptr; };

  //-------------------------------------------------------------------------------------------------------------------
  /// Collect Treasure, but unused because ther is no Treasure.
  //
  void collectTreasure() override{};

private:
  //-------------------------------------------------------------------------------------------------------------------
  // Indicates for which player the gear card is used as a starting field
  //
  std::string player_color_;

  //-------------------------------------------------------------------------------------------------------------------
  /// Shows the tile in a string!
  //
  std::string tile_string_;
};
#endif // STARTTILE_HPP