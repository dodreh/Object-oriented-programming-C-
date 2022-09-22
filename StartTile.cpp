//---------------------------------------------------------------------------------------------------------------------
// StartTile.cpp
//
// StartTile subclass of Tile that represents a gait map.
//
// Author: Boris Smiljanic, 01531652
//         Milan Mirosav, 11731475
//         Markus Doppelreiter, 01535331
//---------------------------------------------------------------------------------------------------------------------
//

#include "StartTile.hpp"

//---------------------------------------------------------------------------------------------------------------------
StartTile::StartTile(TileType type, Rotation rotation, std::string player_color) :
    Tile{type, rotation}, player_color_(player_color)
{
}

//---------------------------------------------------------------------------------------------------------------------
StartTile::StartTile(const StartTile &copy) : Tile(dynamic_cast<const Tile&>(copy))
{
  player_color_ = copy.player_color_;
  tile_string_ = copy.tile_string_;
}

//---------------------------------------------------------------------------------------------------------------------
StartTile& StartTile::operator= (const StartTile &start_tile)
{
  dynamic_cast<Tile&>(*this) = dynamic_cast<const Tile&>(start_tile);
  player_color_ = start_tile.player_color_;
  tile_string_ = start_tile.tile_string_;

  return *this;
}

//---------------------------------------------------------------------------------------------------------------------
std::string StartTile::getPlayerColor() const
{
  return player_color_;
}

//---------------------------------------------------------------------------------------------------------------------
std::vector<std::string>* StartTile::getTileStringVector()
{
  std::vector<std::string>* str_vector = Tile::getBasicTileStringVector();
  std::string clip_on = "(";
  std::string clip_off = ")";
  std::string start_description;
  std::string player_description = "P";
  start_description = clip_on + getPlayerColor() + clip_off;
  // create the true player string
  for (auto iterator : Tile::getPlayer())
  {
    player_description += iterator->getColorString();
  }

  // All StartTile classes must be from TileType "L"
  if (Tile::getType() == TileType::L)
  {
    // Upper-right and Lower-right curve
    if (Tile::getRotation() == Rotation::DEG0 || Tile::getRotation() == Rotation::DEG270)
    {
      size_t pos = str_vector->at(2).find(" ") + 1;
      str_vector->at(2).replace(pos, start_description.size(), start_description);

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
      size_t pos = str_vector->at(2).find(" ") + 3;
      str_vector->at(2).replace(pos, start_description.size(), start_description);

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
std::string* StartTile::getTileString()
{
  tile_string_.clear();
  std::vector<std::string>* str_vector = getTileStringVector();

  for (auto str : *str_vector)
  {
    tile_string_ += str + "\n";
  }
  return &tile_string_;
}