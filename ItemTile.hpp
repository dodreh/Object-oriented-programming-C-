//---------------------------------------------------------------------------------------------------------------------
// ItemTile.hpp
//
// ItemTile determines subclass of Tile on which item stands.
//
// Author: Milan Mirosav, 11731475
//---------------------------------------------------------------------------------------------------------------------
//

#ifndef OOP1SS21_A2_131_ITEMTILE_HPP
#define OOP1SS21_A2_131_ITEMTILE_HPP

#include "Tile.hpp"
#include "Item.hpp"

class ItemTile : public Tile
{
public:
  //-------------------------------------------------------------------------------------------------------------------
  /// Constructor definition
  ///
  /// @param type The enum class TileType of the Tile.
  /// @param rotation The enum class Rotation of the Tile.
  //
  ItemTile(TileType type, Rotation rotation, Item* item);

  //-------------------------------------------------------------------------------------------------------------------
  /// Destructor definition
  ///
  ~ItemTile() = default;

  //-------------------------------------------------------------------------------------------------------------------
  /// Copy constructor
  ///
  //
  ItemTile(const ItemTile &copy);

  //-------------------------------------------------------------------------------------------------------------------
  /// Assignment operator
  ///
  //
  ItemTile& operator= (const ItemTile &Item_tile);

  //-------------------------------------------------------------------------------------------------------------------
  /// Get the string, which represents an item tile. (with \n)
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

  //-------------------------------------------------------------------------------------------------------------------
  /// collectItem, set collected to true if player collected it from tile, and vice versa.
  /// Because if it is collected it's gonna not be printed on the board.
  //
  void setCollected(bool set);

  //-------------------------------------------------------------------------------------------------------------------
  /// Returns collected_.
  //
  bool getCollected() const;

  //-------------------------------------------------------------------------------------------------------------------
  /// Get item from current tile.
  ///
  /// @return item_.
  //
  Item* getItem() const;
private:
  //-------------------------------------------------------------------------------------------------------------------
  /// Get the vector of strings, which represents a normal tile. (without \n)
  ///
  /// @return A pointer to the Treasure class
  //
  std::vector<std::string>* getTileStringVector() override;
  //-------------------------------------------------------------------------------------------------------------------
  /// Get the vector of strings, which represents a item tile. (without \n) when no treasure is on it!
  ///
  /// @return A vector of tile strings.
  //
  std::vector<std::string>* noItemTileStringVector();
  //-------------------------------------------------------------------------------------------------------------------
  /// Get the vector of strings, which represents an item tile. (without \n) when an item is on it!
  ///
  /// @return A vector of tile strings.
  //
  std::vector<std::string>* itemTileStringVector();
  //-------------------------------------------------------------------------------------------------------------------
  /// Shows the tile in a string!
  //
  std::string tile_string_;
  //-------------------------------------------------------------------------------------------------------------------
  /// Indicates item.
  //
  Item* item_;
  //-------------------------------------------------------------------------------------------------------------------
  /// Indicates if item is collected or not. Default value is false.
  //
  bool collected_ = false;
};


#endif //OOP1SS21_A2_131_ITEMTILE_HPP
