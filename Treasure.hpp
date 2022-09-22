//---------------------------------------------------------------------------------------------------------------------
// Treasure.hpp
//
// Treasure class that represents a treasure.
//
// Author: Boris Smiljanic 01531652
//         Milan Mirosav 11731475
//         Markus Dopelreiter 01535331
//---------------------------------------------------------------------------------------------------------------------
//

#ifndef TREASURE_HPP
#define TREASURE_HPP

#include <string>

class Treasure
{
public:
  //-------------------------------------------------------------------------------------------------------------------
  /// Constructor definition
  ///
  /// @param name A string with the name of the treasure
  /// @param treasure_id A integer of the treasure ID.
  //
  Treasure(std::string name, int treasure_id);

  //-------------------------------------------------------------------------------------------------------------------
  /// Destructor definition
  ///
  //
  ~Treasure();

  //-------------------------------------------------------------------------------------------------------------------
  /// Copy constructor
  ///
  //
  Treasure(const Treasure &copy);

  //-------------------------------------------------------------------------------------------------------------------
  /// Assignment operator
  ///
  //
  Treasure& operator= (const Treasure &treasure);

  //-------------------------------------------------------------------------------------------------------------------
  /// Get the name from the treasure in string.
  ///
  /// @return A string with the treasure name.
  //
  std::string getName();

  //-------------------------------------------------------------------------------------------------------------------
  /// Get the id from the treasure in integer.
  ///
  /// @return A integer with the treasure id.
  //
  int getTreasureId();

  //-------------------------------------------------------------------------------------------------------------------
  /// Get the information if th treasure is found allready or not.
  ///
  /// @return A bool, if found.
  //
  bool getFound();

  //-------------------------------------------------------------------------------------------------------------------
  /// Set the found value to true.
  //
  void setFound();

private:
  //-------------------------------------------------------------------------------------------------------------------
  /// Name of the treasure
  //
  std::string name_;

  //-------------------------------------------------------------------------------------------------------------------
  /// ID number of treasure
  //
  int treasure_id_;

  //-------------------------------------------------------------------------------------------------------------------
  /// Shows if card is found
  //
  bool found_;
};
#endif // TREASURE_HPP