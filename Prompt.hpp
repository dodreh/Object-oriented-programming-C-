//---------------------------------------------------------------------------------------------------------------------
// Prompt.hpp
//
// Prompt is the class to handle the prompt input etc.
//
// Author: Boris Smiljanic 01531652
//         Milan Mirosav 11731475
//         Markus Dopelreiter 01535331
//---------------------------------------------------------------------------------------------------------------------
//

#ifndef PROMPT_HPP
#define PROMPT_HPP

#include "Board.hpp"
#include "Game.hpp"
#include "Player.hpp"

class Prompt
{
public:
  //-------------------------------------------------------------------------------------------------------------------
  /// Returns an instance of the Prompt class (Singleton pattern).
  //
  static Prompt& getInstance();

  //-------------------------------------------------------------------------------------------------------------------
  /// Deleted copy constructor.
  //
  Prompt(const Prompt& copy) = delete;

  //-------------------------------------------------------------------------------------------------------------------
  /// Deleting assignment operator
  ///
  //
  Prompt& operator= (const Prompt &prompt) = delete;

  //-------------------------------------------------------------------------------------------------------------------
  /// This method runs the prompt.
  //
  void run();


private:
  //-------------------------------------------------------------------------------------------------------------------
  /// Private constructor. Access only possible in the class.
  //
  Prompt();

  //-------------------------------------------------------------------------------------------------------------------
  /// Private destructor. Access only possible in the class
  //
  ~Prompt() = default;

  //-------------------------------------------------------------------------------------------------------------------
  /// Prompt call is the hole prompt where exceptions where catched!
  //
  void promptCall();

  //-------------------------------------------------------------------------------------------------------------------
  /// Format the player input from the prompt and gives it to the player_input_ vector of strings,
  /// where the string elements are the commands/parameters!
  //
  void formatInput();

  //-------------------------------------------------------------------------------------------------------------------
  /// Clears the whitespaces (front/between/back) from the read_input_.
  //
  void clearWhitespaceToOne();

  //-------------------------------------------------------------------------------------------------------------------
  /// Main method which handles the input cases (input commands).
  //
  void checkInput();

  //-------------------------------------------------------------------------------------------------------------------
  ///
  ///
  //
  void checkGamefieldOnOff();

  //-------------------------------------------------------------------------------------------------------------------
  /// Handels the algorithm if gamefield is called.
  //
  void inputGamefield();

  //-------------------------------------------------------------------------------------------------------------------
  /// Handels the algorithm if showtreasure is called.
  //
  void inputShowTreasure();

  //-------------------------------------------------------------------------------------------------------------------
  /// Handels the algorithm if hidetreasure is called.
  //
  void inputHideTreasure();

  //-------------------------------------------------------------------------------------------------------------------
  /// Handels the algorithm if rotate is called.
  //
  void inputRotate();

  //-------------------------------------------------------------------------------------------------------------------
  /// Handels the algorithm if insert is called.
  //
  void inputInsert();

  //-------------------------------------------------------------------------------------------------------------------
  /// Handels the algorithm if showfreetile is called.
  //
  void inputShowFreeTile();

  //-------------------------------------------------------------------------------------------------------------------
  /// Handels the algorithm if finish is called.
  //
  void inputFinish();

  //-------------------------------------------------------------------------------------------------------------------
  /// Handels the algorithm if the insert is on the top.
  //
  void inputInsertTopParam();

  //-------------------------------------------------------------------------------------------------------------------
  /// Handels the algorithm if the insert is on the bottom.
  //
  void inputInsertBottomParam();

  //-------------------------------------------------------------------------------------------------------------------
  /// Handels the algorithm if the insert is on the right.
  //
  void inputInsertRightParam();

  //-------------------------------------------------------------------------------------------------------------------
  /// Handels the algorithm if the insert is on the left.
  //
  void inputInsertLeftParam();

  //-------------------------------------------------------------------------------------------------------------------
  /// Handels the algorithm if move is called.
  //
  void movePlayer();

  //-------------------------------------------------------------------------------------------------------------------
  /// Handels the algorithm if the move is go up.
  //
  void goUp();

  //-------------------------------------------------------------------------------------------------------------------
  /// Handels the algorithm if the move is go down.
  //
  void goDown();

  //-------------------------------------------------------------------------------------------------------------------
  /// Handels the algorithm if the move is go right.
  //
  void goRight();

  //-------------------------------------------------------------------------------------------------------------------
  /// Handels the algorithm if the move is go down.
  //
  void goLeft();

  //-------------------------------------------------------------------------------------------------------------------
  /// Handles the algorithm if the move command is "go".
  //
  void goMovement();

  //-------------------------------------------------------------------------------------------------------------------
  /// Checks when the move command is "go" and with third parameter, if the movement is possible.
  /// that's for the direction go up.
  //
  void checkGoUpPossible();

  //-------------------------------------------------------------------------------------------------------------------
  /// Checks when the move command is "go" and with third parameter, if the movement is possible.
  /// that's for the direction go down.
  //
  void checkGoDownPossible();

  //-------------------------------------------------------------------------------------------------------------------
  /// Checks when the move command is "go" and with third parameter, if the movement is possible.
  /// that's for the direction go right.
  //
  void checkGoRightPossible();

  //-------------------------------------------------------------------------------------------------------------------
  /// Checks when the move command is "go" and with third parameter, if the movement is possible.
  /// that's for the direction go left.
  //
  void checkGoLeftPossible();

  //-------------------------------------------------------------------------------------------------------------------
  /// check if there are/is player(s) on the outputed tile. If there, put the player on the inserted tile!
  //
  void checkIfPlayersOnTile(size_t row, size_t column);

  //-------------------------------------------------------------------------------------------------------------------
  /// Prints the treasure in the method inputShowTreasure.
  //
  void printTreasure();

  //-------------------------------------------------------------------------------------------------------------------
  /// Handles the exception if the input is a arrow and calls an exception.
  //
  void arrowOutput();

  //-------------------------------------------------------------------------------------------------------------------
  /// Handles the exception if the insert is allowed.
  //
  void checkAllowedInsert();

  //-------------------------------------------------------------------------------------------------------------------
  /// Goes throw the board_tile_ vector and player_ vector and returns the current Tile.
  ///
  /// @return current tile pointer
  //
  Tile* getCurrentTile();

  //-------------------------------------------------------------------------------------------------------------------
  /// check witch player is current and returns the associated string.
  ///
  /// @return (string) from current player (RED/YELLOW/GREEN/BLUE)
  //
  std::string getCurrentPlayerStr();

  //-------------------------------------------------------------------------------------------------------------------
  /// Goes throw the player_ vector and returns the current player.
  ///
  /// @return current player pointer
  //
  Player* getCurrentPlayer();

  //-------------------------------------------------------------------------------------------------------------------
  /// Handles the algorithm if the command item (rope) is used/called.
  ///
  //
  void inputRope();

  //-------------------------------------------------------------------------------------------------------------------
  /// Handles the algorithm if the command item (dynamite) is used/called.
  ///
  //
  void inputDynamite();

  //-------------------------------------------------------------------------------------------------------------------
  /// Handles the algorithm if the command item (bricks) is used/called.
  ///
  //
  void inputBricks();

  //-------------------------------------------------------------------------------------------------------------------
  /// Handles the algorithm if the command item (ladder) is used/called.
  ///
  //
  void inputLadder();

  void inputBlock();
  //-------------------------------------------------------------------------------------------------------------------
  /// MEMBER VARIABLES
  //-------------------------------------------------------------------------------------------------------------------
  /// Shows the player input in th prompt.
  //
  std::string read_input_;

  //-------------------------------------------------------------------------------------------------------------------
  /// Shows the player input in vector string forme in th prompt.
  //
  std::vector<std::string> player_input_;

  //-------------------------------------------------------------------------------------------------------------------
  /// Shows the active players in the vector prompt.
  //
  std::vector<Player*> players_;

  //-------------------------------------------------------------------------------------------------------------------
  /// Shows the current player in the prompt.
  //
  Player* current_player_;

  //-------------------------------------------------------------------------------------------------------------------
  /// Shows the current tile in the prompt.
  //
  Tile* current_tile_;

  //-------------------------------------------------------------------------------------------------------------------
  /// Shows the current player string in the prompt.
  //
  std::string current_player_str_;

  //-------------------------------------------------------------------------------------------------------------------
  /// Shows the current player counter for the next player iterator.
  //
  size_t current_player_cnt_;

  //-------------------------------------------------------------------------------------------------------------------
  /// Shows the referenz to the board tile vector of vector tile.
  //
  std::vector<std::vector<Tile*>>* board_tiles_;

  //-------------------------------------------------------------------------------------------------------------------
  /// Says if next player is true.
  //
  bool next_player_;

  //-------------------------------------------------------------------------------------------------------------------
  /// Says if gamefield is setted.
  //
  bool gamefield_setted_ = false;

  //-------------------------------------------------------------------------------------------------------------------
  /// Says if gamefield is on.
  //
  bool gamefield_on = true;

  //-------------------------------------------------------------------------------------------------------------------
  /// Says if moved gamefield is calld an resetet in the check gamefiled method.
  //
  bool moved_gamefield = false;

  //-------------------------------------------------------------------------------------------------------------------
  /// Says if showtreasure is activated.
  //
  bool showtreasure_ = false;

  //-------------------------------------------------------------------------------------------------------------------
  /// If the first_param is valide it gets true.
  //
  bool first_param = false;

  //-------------------------------------------------------------------------------------------------------------------
  /// Say if inserted is call (gamelogic).
  //
  bool inserted_ = false;

  //-------------------------------------------------------------------------------------------------------------------
  /// Say if finish is call (gamelogic).
  //
  bool finished_ = true;

  //-------------------------------------------------------------------------------------------------------------------
  /// Shows the last insert input (first parameter).
  //
  std::string last_insert_str_;

  //-------------------------------------------------------------------------------------------------------------------
  /// Shows the last insert input (second parameter).
  //
  size_t last_insert_pos_ = 0;
};

#endif // PROMPT_HPP