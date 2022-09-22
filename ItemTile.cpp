//---------------------------------------------------------------------------------------------------------------------
// ItemTile.cpp
//
// ItemTile determines subclass of Tile on which item stands.
//
// Author: Milan Mirosav, 11731475
//---------------------------------------------------------------------------------------------------------------------
//

#include "ItemTile.hpp"

//---------------------------------------------------------------------------------------------------------------------
ItemTile::ItemTile(TileType type, Rotation rotation, Item *item) : Tile{type, rotation}, item_(item) {}

//---------------------------------------------------------------------------------------------------------------------
ItemTile::ItemTile(const ItemTile &copy) : Tile(dynamic_cast<const Tile&>(copy))
{
  tile_string_ = copy.tile_string_;
  item_ = copy.item_;
  collected_ = copy.collected_;
}

//---------------------------------------------------------------------------------------------------------------------
ItemTile& ItemTile::operator= (const ItemTile &item_tile)
{
  dynamic_cast<Tile&>(*this) = dynamic_cast<const Tile&>(item_tile);
  tile_string_ = item_tile.tile_string_;
  item_ = item_tile.item_;
  collected_ = item_tile.collected_;

  return *this;
}
//---------------------------------------------------------------------------------------------------------------------
std::vector<std::string>* ItemTile::itemTileStringVector()
{
  std::vector<std::string>* str_vector = Tile::getBasicTileStringVector();
  //std::string treasure_description = "T";
  std::string item_description;
  std::string player_description = "P";
  // create the true player string
  for (auto iterator : Tile::getPlayer())
  {
    player_description += iterator->getColorString();
  }

  if (item_->getItemName() == "ROP")
    item_description = "ROP";
  if (item_->getItemName() == "DYN")
    item_description = "DYN";
  if (item_->getItemName() == "BRI")
    item_description = "BRI";
  if (item_->getItemName() == "LAD")
    item_description = "LAD";


  if (Tile::getType() == TileType::X && collected_ == false)
  {
      size_t pos = str_vector->at(2).find(" ") + 3;
      str_vector->at(2).replace(pos, item_description.size(), item_description);

      // Player representation on the tile
      if (!Tile::getPlayer().empty())
      {
        if (Tile::getPlayer().size() == 1 || Tile::getPlayer().size() == 2 || Tile::getPlayer().size() == 3)
        {
          size_t pos = str_vector->at(2).find(" ") + 3;
          str_vector->at(3).replace(pos, player_description.size(), player_description);
        }
        if (Tile::getPlayer().size() == 4)
        {
          size_t pos = str_vector->at(2).find(" ");
          str_vector->at(3).replace(pos, player_description.size(), player_description);
        }
      }
  }
  if (Tile::getType() == TileType::O && collected_ == false)
  {
    size_t pos = str_vector->at(2).find(" ") + 1;
    str_vector->at(2).replace(pos, item_description.size(), item_description);

    // Player representation on the tile
    if (!Tile::getPlayer().empty())
    {
      if (Tile::getPlayer().size() == 1 || Tile::getPlayer().size() == 2 || Tile::getPlayer().size() == 3)
      {
        size_t pos = str_vector->at(2).find(" ") + 1;
        str_vector->at(3).replace(pos, player_description.size(), player_description);
      }
      if (Tile::getPlayer().size() == 4)
      {
        size_t pos = str_vector->at(2).find(" ");
        str_vector->at(3).replace(pos, player_description.size(), player_description);
      }
    }
  }
  return str_vector;
}
//---------------------------------------------------------------------------------------------------------------------
std::vector<std::string>* ItemTile::noItemTileStringVector()
{
  std::vector<std::string>* str_vector = Tile::getBasicTileStringVector();
  std::string player_description = "P";
  // create the true player string
  for (auto iterator : Tile::getPlayer())
  {
    player_description += iterator->getColorString();
  }

  if (Tile::getType() == TileType::X && collected_ == true)
  {
    // Player representation on the tile
    if (!Tile::getPlayer().empty())
    {
      if (Tile::getPlayer().size() == 1 || Tile::getPlayer().size() == 2 || Tile::getPlayer().size() == 3)
      {
        size_t pos = str_vector->at(2).find(" ") + 3;
        str_vector->at(3).replace(pos, player_description.size(), player_description);
      }
      if (Tile::getPlayer().size() == 4)
      {
        size_t pos = str_vector->at(2).find(" ");
        str_vector->at(3).replace(pos, player_description.size(), player_description);
      }
    }
  }
  if (Tile::getType() == TileType::O && collected_ == true)
  {
    // Player representation on the tile
    if (!Tile::getPlayer().empty())
    {
      if (Tile::getPlayer().size() == 1 || Tile::getPlayer().size() == 2 || Tile::getPlayer().size() == 3)
      {
        size_t pos = str_vector->at(2).find(" ") + 1;
        str_vector->at(3).replace(pos, player_description.size(), player_description);
      }
      if (Tile::getPlayer().size() == 4)
      {
        size_t pos = str_vector->at(2).find(" ");
        str_vector->at(3).replace(pos, player_description.size(), player_description);
      }
    }
  }
  return str_vector;
}
//---------------------------------------------------------------------------------------------------------------------
std::vector<std::string>* ItemTile::getTileStringVector()
{
  // if no treasure
  if (collected_)
    return noItemTileStringVector();
    // if treasure
  else
    return itemTileStringVector();
}

//---------------------------------------------------------------------------------------------------------------------
std::string* ItemTile::getTileString()
{
  tile_string_.clear();
  std::vector<std::string>* str_vector = getTileStringVector();
  for (auto str : *str_vector)
  {
    tile_string_ += str + "\n";
  }
  return &tile_string_;
}

//---------------------------------------------------------------------------------------------------------------------
Item* ItemTile::getItem() const
{
  return item_;
}

//---------------------------------------------------------------------------------------------------------------------
void ItemTile::setCollected(bool set)
{
  collected_ = set;
}

//---------------------------------------------------------------------------------------------------------------------
bool ItemTile::getCollected() const
{
  return collected_;
}