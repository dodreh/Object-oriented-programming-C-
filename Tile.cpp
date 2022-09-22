//---------------------------------------------------------------------------------------------------------------------
// Tile.cpp
//
// Tile is the base class of tile.
//
// Author: Boris Smiljanic, 01531652
//         Milan Mirosav, 11731475
//         Markus Doppelreiter, 01535331
//---------------------------------------------------------------------------------------------------------------------
//

#include "Tile.hpp"

//---------------------------------------------------------------------------------------------------------------------
Tile::Tile(TileType type, Rotation rotation) : type_(type), rotation_(rotation) {}

//---------------------------------------------------------------------------------------------------------------------
Tile::~Tile() {}


Tile::Tile(const Tile& copy) : type_(copy.type_), rotation_(copy.rotation_),
                               players_(copy.players_), position_(copy.position_),
                               open_to_(copy.open_to_), basic_tile_string_vector_(copy.basic_tile_string_vector_)
{
}

//---------------------------------------------------------------------------------------------------------------------
Tile& Tile::operator= (const Tile &tile)
{
  type_ = tile.type_;
  rotation_ = tile.rotation_;
  players_ = tile.players_;
  position_ = tile.position_;
  open_to_ = tile.open_to_;
  basic_tile_string_vector_ = tile.basic_tile_string_vector_;

  return *this;
}
//---------------------------------------------------------------------------------------------------------------------
int Tile::getRotationValue() const
{
  if (rotation_ == Rotation::DEG0)
    return 0;
  if (rotation_ == Rotation::DEG90)
    return 90;
  if (rotation_ == Rotation::DEG180)
    return 180;
  return 270;
}

//---------------------------------------------------------------------------------------------------------------------
std::string Tile::getTileTypeString() const
{
  if (type_ == TileType::T)
    return "T";
  if (type_ == TileType::L)
    return "L";
  if (type_ == TileType::I)
    return "I";
  if (type_ == TileType::O)
    return "O";
  if (type_ == TileType::U)
    return "U";
  return "X";
}

//---------------------------------------------------------------------------------------------------------------------
TileType Tile::getType() const
{
  return type_;
}

//---------------------------------------------------------------------------------------------------------------------
Rotation Tile::getRotation() const
{
  return rotation_;
}

//---------------------------------------------------------------------------------------------------------------------
std::vector<Player*> Tile::getPlayer() const
{
  return players_;
}

//---------------------------------------------------------------------------------------------------------------------
void Tile::setRotation(Rotation rotation)
{
  rotation_ = rotation;
}

//---------------------------------------------------------------------------------------------------------------------
void Tile::setPlayer(Player* player)
{
  players_.push_back(player);
  orderPlayers();
}

//---------------------------------------------------------------------------------------------------------------------
void Tile::orderPlayers()
{
  std::vector<Player*> temp_vector;
  if (players_.size() != 1)
  {
    std::sort(players_.begin(), players_.end());
  }
}

//---------------------------------------------------------------------------------------------------------------------
void Tile::deletePlayer()
{
  players_.pop_back();
}

//---------------------------------------------------------------------------------------------------------------------
void Tile::setPosition(Coordinates position)
{
  position_ = position;
}
//---------------------------------------------------------------------------------------------------------------------
std::vector<std::string>* Tile::getBasicTileStringVectorTypI()
{
  basic_tile_string_vector_.clear();
  // definition of the shown corritor
  std::string full = "█████████";
  std::string left = "██       ";
  std::string right = "       ██";
  std::string empty = "         ";
  std::string left_and_right = "██     ██";

  // straight corridor horizontal
  if (Tile::getRotation() == Rotation::DEG90 || Tile::getRotation() == Rotation::DEG270)
  {
    basic_tile_string_vector_.push_back(full);
    basic_tile_string_vector_.push_back(empty);
    basic_tile_string_vector_.push_back(empty);
    basic_tile_string_vector_.push_back(empty);
    basic_tile_string_vector_.push_back(full);
    return &basic_tile_string_vector_;
  }
  // straight corridor vertical
  /*if(Tile::getRotation() == Rotation::DEG0 ||
    Tile::getRotation() == Rotation::DEG180)*/
  basic_tile_string_vector_.push_back(left_and_right);
  basic_tile_string_vector_.push_back(left_and_right);
  basic_tile_string_vector_.push_back(left_and_right);
  basic_tile_string_vector_.push_back(left_and_right);
  basic_tile_string_vector_.push_back(left_and_right);
  return &basic_tile_string_vector_;
}

//---------------------------------------------------------------------------------------------------------------------
std::vector<std::string>* Tile::getBasicTileStringVectorTypT()
{
  basic_tile_string_vector_.clear();
  // definition of the shown corritor
  std::string full = "█████████";
  std::string left = "██       ";
  std::string right = "       ██";
  std::string empty = "         ";
  std::string left_and_right = "██     ██";

  // branch to the right
  if (Tile::getRotation() == Rotation::DEG90)
  {
    basic_tile_string_vector_.push_back(left_and_right);
    basic_tile_string_vector_.push_back(left);
    basic_tile_string_vector_.push_back(left);
    basic_tile_string_vector_.push_back(left);
    basic_tile_string_vector_.push_back(left_and_right);
    return &basic_tile_string_vector_;
  }
  // branch up
  if (Tile::getRotation() == Rotation::DEG180)
  {
    basic_tile_string_vector_.push_back(left_and_right);
    basic_tile_string_vector_.push_back(empty);
    basic_tile_string_vector_.push_back(empty);
    basic_tile_string_vector_.push_back(empty);
    basic_tile_string_vector_.push_back(full);
    return &basic_tile_string_vector_;
  }
  // branch to the left
  if (Tile::getRotation() == Rotation::DEG270)
  {
    basic_tile_string_vector_.push_back(left_and_right);
    basic_tile_string_vector_.push_back(right);
    basic_tile_string_vector_.push_back(right);
    basic_tile_string_vector_.push_back(right);
    basic_tile_string_vector_.push_back(left_and_right);
    return &basic_tile_string_vector_;
  }
  // branch down
  /*if(Tile::getRotation() == Rotation::DEG0)*/
  basic_tile_string_vector_.push_back(full);
  basic_tile_string_vector_.push_back(empty);
  basic_tile_string_vector_.push_back(empty);
  basic_tile_string_vector_.push_back(empty);
  basic_tile_string_vector_.push_back(left_and_right);
  return &basic_tile_string_vector_;
}

//---------------------------------------------------------------------------------------------------------------------
std::vector<std::string>* Tile::getBasicTileStringVectorTypL()
{
  basic_tile_string_vector_.clear();
  // definition of the shown corritor
  std::string full = "█████████";
  std::string left = "██       ";
  std::string right = "       ██";
  std::string empty = "         ";
  std::string left_and_right = "██     ██";

  // Upper-right curve
  if (Tile::getRotation() == Rotation::DEG0)
  {
    basic_tile_string_vector_.push_back(left_and_right);
    basic_tile_string_vector_.push_back(left);
    basic_tile_string_vector_.push_back(left);
    basic_tile_string_vector_.push_back(left);
    basic_tile_string_vector_.push_back(full);
    return &basic_tile_string_vector_;
  }
  // Upper-left curve
  if (Tile::getRotation() == Rotation::DEG90)
  {
    basic_tile_string_vector_.push_back(left_and_right);
    basic_tile_string_vector_.push_back(right);
    basic_tile_string_vector_.push_back(right);
    basic_tile_string_vector_.push_back(right);
    basic_tile_string_vector_.push_back(full);
    return &basic_tile_string_vector_;
  }
  // Lower-left curve
  if (Tile::getRotation() == Rotation::DEG180)
  {
    basic_tile_string_vector_.push_back(full);
    basic_tile_string_vector_.push_back(right);
    basic_tile_string_vector_.push_back(right);
    basic_tile_string_vector_.push_back(right);
    basic_tile_string_vector_.push_back(left_and_right);
    return &basic_tile_string_vector_;
  }
  // Lower-right curve
  /*if(Tile::getRotation() == Rotation::DEG270)*/
  basic_tile_string_vector_.push_back(full);
  basic_tile_string_vector_.push_back(left);
  basic_tile_string_vector_.push_back(left);
  basic_tile_string_vector_.push_back(left);
  basic_tile_string_vector_.push_back(left_and_right);
  return &basic_tile_string_vector_;
}
//---------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------
std::vector<std::string>* Tile::getBasicTileStringVectorTypX()
{
  basic_tile_string_vector_.clear();
  // Three empty lines embraced with two left_and_right lines.
  std::string left_and_right = "██     ██";
  std::string empty = "         ";

  basic_tile_string_vector_.push_back(left_and_right);
  basic_tile_string_vector_.push_back(empty);
  basic_tile_string_vector_.push_back(empty);
  basic_tile_string_vector_.push_back(empty);
  basic_tile_string_vector_.push_back(left_and_right);
  return &basic_tile_string_vector_;
}

//---------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------
  std::vector<std::string>* Tile::getBasicTileStringVectorTypO()
  {
    basic_tile_string_vector_.clear();
    // Three left_and_right lines embraced with two full lines.
    std::string full = "█████████";
    std::string left_and_right = "██     ██";

    basic_tile_string_vector_.push_back(full);
    basic_tile_string_vector_.push_back(left_and_right);
    basic_tile_string_vector_.push_back(left_and_right);
    basic_tile_string_vector_.push_back(left_and_right);
    basic_tile_string_vector_.push_back(full);
    return &basic_tile_string_vector_;
  }
//---------------------------------------------------------------------------------------------------------------------
std::vector<std::string>* Tile::getBasicTileStringVector()
{
  if (Tile::getType() == TileType::I)
  {
    return getBasicTileStringVectorTypI();
  }
  if (Tile::getType() == TileType::T)
  {
    return getBasicTileStringVectorTypT();
  }
  if (Tile::getType() == TileType::L)
  {
    return getBasicTileStringVectorTypL();
  }
  if (Tile::getType() == TileType::X)
  {
    return getBasicTileStringVectorTypX();
  }
  if (Tile::getType() == TileType::O)
  {
    return getBasicTileStringVectorTypO();
  }
  // returns ah empty vector
  basic_tile_string_vector_.clear();
  return &basic_tile_string_vector_;
}
//---------------------------------------------------------------------------------------------------------------------
void Tile::setOpenTo()
{
  if (Tile::getType() == TileType::I)
  {
    if ((Tile::getRotation() == Rotation::DEG0) || (Tile::getRotation() == Rotation::DEG180))
    {
      open_to_.right_ = false;
      open_to_.left_ = false;
      open_to_.up_ = true;
      open_to_.down_ = true;
    }
    else
    {
      open_to_.right_ = true;
      open_to_.left_ = true;
      open_to_.up_ = false;
      open_to_.down_ = false;
    }
  }
  if (Tile::getType() == TileType::T)
  {
    if (Tile::getRotation() == Rotation::DEG0)
    {
      open_to_.up_ = false;
      open_to_.down_ = true;
      open_to_.left_ = true;
      open_to_.right_ = true;
    }
    if (Tile::getRotation() == Rotation::DEG90)
    {
      open_to_.left_ = false;
      open_to_.down_ = true;
      open_to_.right_ = true;
      open_to_.up_ = true;
    }
    if (Tile::getRotation() == Rotation::DEG180)
    {
      open_to_.down_ = false;
      open_to_.left_ = true;
      open_to_.right_ = true;
      open_to_.up_ = true;
    }
    if (Tile::getRotation() == Rotation::DEG270)
    {
      open_to_.right_ = false;
      open_to_.down_ = true;
      open_to_.left_ = true;
      open_to_.up_ = true;
    }
  }
  if (Tile::getType() == TileType::L)
  {
    if (Tile::getRotation() == Rotation::DEG0)
    {
      open_to_.down_ = false;
      open_to_.left_ = false;
      open_to_.up_ = true;
      open_to_.right_ = true;
    }
    if (Tile::getRotation() == Rotation::DEG90)
    {
      open_to_.down_ = false;
      open_to_.right_ = false;
      open_to_.up_ = true;
      open_to_.left_ = true;
    }
    if (Tile::getRotation() == Rotation::DEG180)
    {
      open_to_.up_ = false;
      open_to_.right_ = false;
      open_to_.down_ = true;
      open_to_.left_ = true;
    }
    if (Tile::getRotation() == Rotation::DEG270)
    {
      open_to_.up_ = false;
      open_to_.left_ = false;
      open_to_.down_ = true;
      open_to_.right_ = true;
    }
  }
}
//---------------------------------------------------------------------------------------------------------------------
Open Tile::getOpenTo()
{
  setOpenTo();
  return open_to_;
}
//---------------------------------------------------------------------------------------------------------------------
void Tile::erasePlayer(Player* player)
{
  for (size_t it = 0; it < players_.size(); it++)
  {
    if (players_.at(it) == player)
      players_.erase(players_.begin() + it);
  }
}