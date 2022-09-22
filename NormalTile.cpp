//---------------------------------------------------------------------------------------------------------------------
// NormalTile.cpp
//
// NormalTile subclass of Tile that represents a Tile without anything.
//
// Author: Boris Smiljanic 01531652
//         Milan Mirosav 11731475
//         Markus Dopelreiter 01535331
//---------------------------------------------------------------------------------------------------------------------
//

#include "NormalTile.hpp"

//---------------------------------------------------------------------------------------------------------------------
NormalTile::NormalTile(TileType type, Rotation rotation) : Tile{type, rotation} {}

//---------------------------------------------------------------------------------------------------------------------
NormalTile::NormalTile(const NormalTile &copy) : Tile(dynamic_cast<const Tile&>(copy))
{
  tile_string_ = copy.tile_string_;
}

//---------------------------------------------------------------------------------------------------------------------
NormalTile& NormalTile::operator= (const NormalTile &normal_tile)
{
  dynamic_cast<Tile&>(*this) = dynamic_cast<const Tile&>(normal_tile);
  tile_string_ = normal_tile.tile_string_;

  return *this;
}

//---------------------------------------------------------------------------------------------------------------------
std::vector<std::string>* NormalTile::getTileStringVector()
{
  std::vector<std::string>* str_vector = Tile::getBasicTileStringVector();

  std::string player_description = "P";
  // create the true player string
  for (auto iterator : Tile::getPlayer())
  {
    player_description += iterator->getColorString();
  }

  // TileType "L"
  if (Tile::getType() == TileType::L)
  {
    // Upper-right and Lower-right curve
    if (Tile::getRotation() == Rotation::DEG0 || Tile::getRotation() == Rotation::DEG270)
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
    // Upper-left and Lower-left curve
    if (Tile::getRotation() == Rotation::DEG90 || Tile::getRotation() == Rotation::DEG180)
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
  }
  // TileType "I"
  if (Tile::getType() == TileType::I)
  {
    // straight corridor vertical
    if (Tile::getRotation() == Rotation::DEG0 || Tile::getRotation() == Rotation::DEG180)
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
    // straight corridor horizontal
    if (Tile::getRotation() == Rotation::DEG90 || Tile::getRotation() == Rotation::DEG270)
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
  }
  return str_vector;
}

//---------------------------------------------------------------------------------------------------------------------
std::string* NormalTile::getTileString()
{
  tile_string_.clear();
  std::vector<std::string>* str_vector = getTileStringVector();
  for (auto str : *str_vector)
  {
    tile_string_ += str + "\n";
  }
  return &tile_string_;
}