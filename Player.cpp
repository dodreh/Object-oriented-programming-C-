//---------------------------------------------------------------------------------------------------------------------
// Player.cpp
//
// Player determines all players and their treasure stacks
//
// Author: Boris Smiljanic 01531652
//         Milan Mirosav 11731475
//         Markus Dopelreiter 01535331
//---------------------------------------------------------------------------------------------------------------------
//

#include "Player.hpp"

#include <iostream>

//---------------------------------------------------------------------------------------------------------------------
Player::Player(PlayerColor color) : color_(color) {}

//---------------------------------------------------------------------------------------------------------------------
Player::~Player() {}

//---------------------------------------------------------------------------------------------------------------------
int Player::getNrFoundTreasures() const
{
  return nr_found_treasures_;
}

//---------------------------------------------------------------------------------------------------------------------
std::vector<Treasure*> Player::getCoveredStack() const
{
  return covered_stack_;
}

//---------------------------------------------------------------------------------------------------------------------
PlayerColor Player::getColor() const
{
  return color_;
}

//---------------------------------------------------------------------------------------------------------------------
std::string Player::getColorString() const
{
  if (getColor() == PlayerColor::R)
  {
    return "R";
  }
  if (getColor() == PlayerColor::Y)
  {
    return "Y";
  }
  if (getColor() == PlayerColor::G)
  {
    return "G";
  }
  return "B";
}

//---------------------------------------------------------------------------------------------------------------------
void Player::setCoveredStack(std::vector<Treasure*> covered_stack)
{
  covered_stack_ = covered_stack;
}

//---------------------------------------------------------------------------------------------------------------------
void Player::increaseNrOfFoundTreasures()
{
  nr_found_treasures_++;
}

//---------------------------------------------------------------------------------------------------------------------
void Player::setItemCollected(bool set_item)
{
  item_collected_ = set_item;
}

//---------------------------------------------------------------------------------------------------------------------
void Player::collectItem(Item* item)
{
  item_ = item;
}

//---------------------------------------------------------------------------------------------------------------------
bool Player::isTied() const
{
  return rope_;
}

//---------------------------------------------------------------------------------------------------------------------
Item* Player::getItem() const
{
  return item_;
}

//---------------------------------------------------------------------------------------------------------------------
void Player::setItemUsed(bool set_item_used)
{
  item_used_ = set_item_used;
}

//---------------------------------------------------------------------------------------------------------------------
bool Player::isItemUsed() const
{
  return item_used_;
}

//---------------------------------------------------------------------------------------------------------------------
bool Player::isItemCollected() const
{
  return item_collected_;
}

//---------------------------------------------------------------------------------------------------------------------
void Player::setRope(bool set_rope)
{
  rope_ = set_rope;
}

//---------------------------------------------------------------------------------------------------------------------
void Player::activateLadder(bool set_ladder)
{
  ladder_ = set_ladder;
}

//---------------------------------------------------------------------------------------------------------------------
bool Player::isLadderActivated() const
{
  return ladder_;
}



void Player::setBlockUsed(bool bu)
{
  block_used_ = bu;
}

bool Player::getBlockUsed()
{
  return block_used_;
}


void Player::setBlocked(bool blocked)
{
  blocked_ = blocked;
}

bool Player::getBlocked()
{
  return blocked_;
}