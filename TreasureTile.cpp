//---------------------------------------------------------------------------------------------------------------------
// TreasureTile.cpp
//
// TreasureTile subclass of Tile that represents a gear map with a treasure.
//
// Author: Boris Smiljanic 01531652
//         Milan Mirosav 11731475
//         Markus Dopelreiter 01535331
//---------------------------------------------------------------------------------------------------------------------
//

#include "TreasureTile.hpp"
#include "Tile.hpp"
#include <stdio.h>
#include <string>

//---------------------------------------------------------------------------------------------------------------------
TreasureTile::TreasureTile(TileType type, Rotation rotation, Treasure* treasure) :
    Tile{type, rotation}, treasure_(treasure), collected_(false)
{
}

//---------------------------------------------------------------------------------------------------------------------
TreasureTile::TreasureTile(const TreasureTile &copy) : Tile(dynamic_cast<const Tile&>(copy))
{
  treasure_ = copy.treasure_;
  collected_ = copy.collected_;
  tile_string_ = copy.tile_string_;
}

//---------------------------------------------------------------------------------------------------------------------
TreasureTile& TreasureTile::operator= (const TreasureTile &treasure_tile)
{
  dynamic_cast<Tile&>(*this) = dynamic_cast<const Tile&>(treasure_tile);
  treasure_ = treasure_tile.treasure_;
  collected_ = treasure_tile.collected_;
  tile_string_ = treasure_tile.tile_string_;

  return *this;
}
//---------------------------------------------------------------------------------------------------------------------
Treasure* TreasureTile::getTreasure() const
{
  return treasure_;
}

//---------------------------------------------------------------------------------------------------------------------
void TreasureTile::collectTreasure()
{
  collected_ = true;
}

//---------------------------------------------------------------------------------------------------------------------
std::vector<std::string>* TreasureTile::treasureTileStringVector()
{
  std::vector<std::string>* str_vector = Tile::getBasicTileStringVector();
  std::string treasure_description = "T";
  std::string player_description = "P";
  // create the true player string
  for (auto iterator : Tile::getPlayer())
  {
    player_description += iterator->getColorString();
  }
  if (treasure_->getTreasureId() < 10)
  {
    treasure_description += "0";
  }
  treasure_description += std::to_string(treasure_->getTreasureId());

  // All TreasureTile classes must be from TileType "T"
  if (Tile::getType() == TileType::T && collected_ == false)
  {
    // branch to the right
    if (Tile::getRotation() == Rotation::DEG90)
    {
      size_t pos = str_vector->at(2).find(" ") + 1;
      str_vector->at(2).replace(pos, treasure_description.size(), treasure_description);

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
    // branch left/up/down
    if (Tile::getRotation() == Rotation::DEG0 || Tile::getRotation() == Rotation::DEG180 ||
        Tile::getRotation() == Rotation::DEG270)
    {
      size_t pos = str_vector->at(2).find(" ") + 3;
      str_vector->at(2).replace(pos, treasure_description.size(), treasure_description);

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
          size_t pos = str_vector->at(2).find(" ") + 2;
          str_vector->at(3).replace(pos, player_description.size(), player_description);
        }
      }
    }
  }
  return str_vector;
}

//---------------------------------------------------------------------------------------------------------------------
std::vector<std::string>* TreasureTile::noTreasureTileStringVector()
{
  std::vector<std::string>* str_vector = Tile::getBasicTileStringVector();
  std::string player_description = "P";
  // create the true player string
  for (auto iterator : Tile::getPlayer())
  {
    player_description += iterator->getColorString();
  }

  if (Tile::getRotation() == Rotation::DEG90)
  {
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
    return str_vector;
  }
  if (Tile::getRotation() == Rotation::DEG0 || Tile::getRotation() == Rotation::DEG180 ||
      Tile::getRotation() == Rotation::DEG270)
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
        size_t pos = str_vector->at(2).find(" ") + 2;
        str_vector->at(3).replace(pos, player_description.size(), player_description);
      }
    }
  }
  return str_vector;
}

//---------------------------------------------------------------------------------------------------------------------
std::vector<std::string>* TreasureTile::getTileStringVector()
{
  // if no treasure
  if (collected_ == true)
  {
    return noTreasureTileStringVector();
  }
  // if treasure
  else
  {
    return treasureTileStringVector();
  }
}

//---------------------------------------------------------------------------------------------------------------------
std::string* TreasureTile::getTileString()
{
  tile_string_.clear();
  std::vector<std::string>* str_vector = getTileStringVector();
  for (auto str : *str_vector)
  {
    tile_string_ += str + "\n";
  }
  return &tile_string_;
}
