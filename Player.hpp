//---------------------------------------------------------------------------------------------------------------------
// Player.hpp
//
// Player determines all players and their treasure stacks
//
// Author: Boris Smiljanic, 01531652
//         Milan Mirosav, 11731475
//         Markus Doppelreiter, 01535331
//---------------------------------------------------------------------------------------------------------------------
//

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Treasure.hpp"
#include <vector>
#include "Item.hpp"

///--------------------------------------------------------------------------------------------------------------------
// PlayerColor Enum Class
// Enum class for the player color.
//
enum class PlayerColor
{
  R,
  Y,
  G,
  B
};

class Player
{
public:
  //-------------------------------------------------------------------------------------------------------------------
  /// Constructor definition
  ///
  /// @param covered_stack is a vector of random treasures.
  //
  Player(PlayerColor color);

  //-------------------------------------------------------------------------------------------------------------------
  /// Destructor definition
  ///
  //
  ~Player();

  //-------------------------------------------------------------------------------------------------------------------
  /// Copy constructor
  ///
  //
  Player(const Player &player) = delete;

  //-------------------------------------------------------------------------------------------------------------------
  /// Overloading assignment operator
  ///
  //
  Player& operator= (const Player &player) = delete;

  //-------------------------------------------------------------------------------------------------------------------
  /// Get number of how many treasures are found.
  ///
  /// @return Integer of the number of treasures found.
  //
  int getNrFoundTreasures() const;

  //-------------------------------------------------------------------------------------------------------------------
  /// Get the vector which is filled with pointers that point to the class treasure.
  ///
  /// @return vector of treasure pointer (Treasure class).
  //
  std::vector<Treasure*> getCoveredStack() const;

  //-------------------------------------------------------------------------------------------------------------------
  /// Get the enum color of the player.
  ///
  /// @return enum class PlayerColor.
  //
  PlayerColor getColor() const;

  //-------------------------------------------------------------------------------------------------------------------
  /// Get the string color of the player.
  ///
  /// @return string with the color.(R/Y/G/B)
  //
  std::string getColorString() const;

  //-------------------------------------------------------------------------------------------------------------------
  /// Set the coverd stack.
  ///
  /// @param covered_stack vector with Treasure pointer.
  //
  void setCoveredStack(std::vector<Treasure*> covered_stack);

  //-------------------------------------------------------------------------------------------------------------------
  /// increase the number of found treasure value about 1.
  //
  void increaseNrOfFoundTreasures();

  //-------------------------------------------------------------------------------------------------------------------
  /// Get the item which is collected.
  ///
  /// @return Item* item_
  //
  Item* getItem() const;

  //-------------------------------------------------------------------------------------------------------------------
  /// Indicates if player is tied.
  ///
  /// @return bool rope_
  //
  bool isTied() const;

  //-------------------------------------------------------------------------------------------------------------------
  /// Set the item_collected_. If a player collects item we assign pointer of that item to member variable item_.
  /// Also when item is used we use this function to set item_ to nullptr.
  ///
  //
  void setItemCollected(bool set_item);

  //-------------------------------------------------------------------------------------------------------------------
  /// Set the item_used_.
  ///
  ///  @param set_item_used
  //
  void setItemUsed(bool set_item_used);

  //-------------------------------------------------------------------------------------------------------------------
  /// Shows if item is used or not.
  ///
  ///  @return bool item_used_
  //
  bool isItemUsed() const;

  //-------------------------------------------------------------------------------------------------------------------
  /// Set the sailed_.
  ///
  ///  @param set_rope.
  //
  void setRope(bool set_rope);

  //-------------------------------------------------------------------------------------------------------------------
  /// Collect the item_.
  ///
  ///  @param Item* item.
  //
  void collectItem(Item* item);

  //-------------------------------------------------------------------------------------------------------------------
  /// Shows if item_ is collected or not.
  ///
  ///  @return bool item_collected_.
  //
  bool isItemCollected() const;

  //-------------------------------------------------------------------------------------------------------------------
  /// Set the ladder_.
  ///
  ///  @param activate_ladder.
  //
  void activateLadder(bool activate_ladder);

  //-------------------------------------------------------------------------------------------------------------------
  /// Shows if item ladder is activated.
  ///
  ///  @return bool ladder_.
  //
  bool isLadderActivated() const;

  void setBlockUsed(bool bu);
  bool getBlockUsed();
  void setBlocked(bool block);
  bool getBlocked();
private:
  //-------------------------------------------------------------------------------------------------------------------
  /// Indicates the treasure in a vector.
  //
  std::vector<Treasure*> covered_stack_;

  //-------------------------------------------------------------------------------------------------------------------
  /// Shows the number of founded treasures.
  //
  int nr_found_treasures_ = 0;

  //-------------------------------------------------------------------------------------------------------------------
  /// Shows the color of the player!
  //
  const PlayerColor color_; // this member variable should be constant

  //-------------------------------------------------------------------------------------------------------------------
  /// Points to item, which is collected by player.
  //
  Item* item_ {nullptr};

  //-------------------------------------------------------------------------------------------------------------------
  /// Shows if the player has collected an item.
  //
  bool item_collected_ = false;

  //-------------------------------------------------------------------------------------------------------------------
  /// Shows if the player has used an item.
  //
  bool item_used_;

  //-------------------------------------------------------------------------------------------------------------------
  /// Shows if the player is tied and can't move one round.
  //
  bool rope_ = false;

  //-------------------------------------------------------------------------------------------------------------------
  /// Shows if ladder item is activated. If yes, player can move through walls.
  //
  bool ladder_;

  /// if block_used is true player cant play
  bool block_used_ = false;
  bool blocked_ = false;

};
#endif // PLAYER_HPP
