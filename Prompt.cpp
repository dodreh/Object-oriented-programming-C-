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

#include "Prompt.hpp"
//---------------------------------------------------------------------------------------------------------------------
Prompt::Prompt() {}

//---------------------------------------------------------------------------------------------------------------------
Prompt& Prompt::getInstance()
{
  static Prompt prompt;
  return prompt;
}

//---------------------------------------------------------------------------------------------------------------------
void Prompt::run()
{
  Game& game = Game::getInstance();

  players_ = game.getPlayers();
  current_player_cnt_ = 0; // goes throw the players_ vector
  next_player_ = false;

  while (1)
  {
    try
    {
      promptCall();
    }
    // Exception handling!
    catch (const Error& e)
    {
      if (e == Error::Exit)
      {
        throw Error::Exit;
      }
      if (e == Error::ImpossibleMove)
      {
        std::cout << "Impossible move!" << std::endl;
      }
      if (e == Error::InvCommand)
      {
        std::cout << "Invalid command: \"" << player_input_.at(0) << "\"" << std::endl;
      }
      if (e == Error::InvalidPosition)
      {
        std::cout << "Invalid Position!" << std::endl;
      }
      if (e == Error::InvParameter1)
      {
        std::cout << "Invalid parameter: \"" << player_input_.at(1) << "\"" << std::endl;
      }
      if (e == Error::InvParameter2)
      {
        std::cout << "Invalid parameter: \"" << player_input_.at(2) << "\"" << std::endl;
      }
      if (e == Error::NoArguments)
      {
        std::cout << "This command does not take any arguments!" << std::endl;
      }
      if (e == Error::WrongNrArg)
      {
        std::cout << "Wrong number of arguments" << std::endl;
      }
      if (e == Error::NotAllowed)
      {
        std::cout << "\"" << read_input_ << "\" is currently not allowed" << std::endl;
      }
      if (e == Error::NotAllowedGo)
      {
        std::cout << "\"" << player_input_.at(0) << "\" is currently not allowed" << std::endl;
      }
      if (e == Error::CannotMove)
      {
        std::cout << "You can't move because you are tied up" << std::endl;
      }
      if (e == Error::NoItemCollected)
      {
        std::cout << "No item collected" << std::endl;
      }
    }
  }
}

//--------------------------------------------------------------------------------------------------------------------
void Prompt::promptCall()
{
  if (finished_)
  {
    current_player_ = getCurrentPlayer();
    current_player_str_ = getCurrentPlayerStr();
    current_tile_ = getCurrentTile();
    finished_ = false;
  }

  std::cout << current_player_str_ << " > ";
  // reads the input from the iostream
  getline(std::cin, read_input_);
  // check if eof
  if (std::cin.eof())
  {
    throw Error::Exit;
  }


  formatInput();
  checkInput();
  // checks the Gamefiedl ON/OFF
  checkGamefieldOnOff();
}

//---------------------------------------------------------------------------------------------------------------------
void Prompt::checkGamefieldOnOff()
{
  Board& board = Board::getInstance();
  if (gamefield_on == true && player_input_.at(0).empty() == false && gamefield_setted_ == false &&
      moved_gamefield == true)
  {
    board.printBoard();
    // if the treasure is shown
    if (showtreasure_)
    {
      printTreasure();
    }
  }
  // reset bools
  gamefield_setted_ = false;
  moved_gamefield = false;
}

//---------------------------------------------------------------------------------------------------------------------
void Prompt::checkInput()
{
  //// if current player is blocked input command "finish"
  /*if (current_player_->getBlocked())
    inputFinish();*/

  first_param = false;
  size_t first_input = 0;
  // Input gamefield/g - on/off
  if (player_input_.at(first_input) == "gamefield" || player_input_.at(first_input) == "g")
  {
    inputGamefield();
    first_param = true;
  }
  // Input showfreetile/sft
  if (player_input_.at(first_input) == "showfreetile" || player_input_.at(first_input) == "sft")
  {
    inputShowFreeTile();
    first_param = true;
  }
  // Input showtreasure/st
  if (player_input_.at(first_input) == "showtreasure" || player_input_.at(first_input) == "st")
  {
    inputShowTreasure();
    first_param = true;
  }
  // Input hidetreasure/ht
  if (player_input_.at(first_input) == "hidetreasure" || player_input_.at(first_input) == "ht")
  {
    inputHideTreasure();
    first_param = true;
  }
  // Input rotate
  if (player_input_.at(first_input) == "rotate")
  {
    if (!inserted_)
      inputRotate();
    else
      throw Error::NotAllowedGo;
    first_param = true;
  }
  // Input insert
  if (player_input_.at(first_input) == "insert" || player_input_.at(first_input) == "i")
  {
    if (!inserted_)
      inputInsert();
    else
      throw Error::NotAllowed;
    first_param = true;
  }
  // Inputs for move player
  if (player_input_.at(first_input) == "go" || player_input_.at(first_input) == "w" ||
      player_input_.at(first_input) == "s" || player_input_.at(first_input) == "d" ||
      player_input_.at(first_input) == "a" || player_input_.at(first_input) == "\x1b[A" ||
      player_input_.at(first_input) == "\x1b[B" || player_input_.at(first_input) == "\x1b[C" ||
      player_input_.at(first_input) == "\x1b[D")
  {
    if (inserted_)
      movePlayer();
    else
    {
      if (player_input_.at(first_input) == "go")
        throw Error::NotAllowedGo;
      else
        throw Error::NotAllowed;
    }
    first_param = true;
  }
  // Input quit/exit
  if (player_input_.at(first_input) == "quit" || player_input_.at(first_input) == "exit")
  {
    if (player_input_.size() != 1)
      throw Error::NoArguments;
    throw Error::Exit;
  }
  // Input finish/f
  if (player_input_.at(first_input) == "finish" || player_input_.at(first_input) == "f")
  {
    if (inserted_)
      inputFinish();
    else
      throw Error::NotAllowed;
    first_param = true;
  }

  if (player_input_.at(first_input) == "item")
  {
    if (current_player_->getItem() != nullptr)
    {
      if (current_player_->getItem()->getItemName() == "ROP")
      {
        inputRope();
        first_param = true;
      }
      if (current_player_->getItem()->getItemName() == "BRI")
      {
        inputBricks();
        first_param = true;
      }
      if (current_player_->getItem()->getItemName() == "LAD")
      {
        inputLadder();
        first_param = true;
      }
      if (current_player_->getItem()->getItemName() == "DYN")
      {
        inputDynamite();
        first_param = true;
      }
    }
    else
      throw Error::NoItemCollected;
  }


  ////////////////
  if (player_input_.at(first_input) == "block" || player_input_.at(first_input) == "b")
  {
    std::cout << "I am heree!!   \n";
    if (inserted_)
    {
      inputBlock();
      first_param = true;
    }
  }

  if (first_param == false && player_input_.at(first_input) != "")
  {
    throw Error::InvCommand;
  }

}

//---------------------------------------------------------------------------------------------------------------------
void Prompt::inputFinish()
{

  if (player_input_.size() != 1)
    throw Error::NoArguments;

  Game& game = Game::getInstance();
  Tile* current_tile = getCurrentTile();
  std::vector<Treasure*> temp_covered_stack = current_player_->getCoveredStack();
  int max_found_treasure = game.getTreasure().size() / game.getNrOfPlayers();
  // checks if the current player stands on the right treasure
  if (current_tile->getType() == TileType::T && !temp_covered_stack.empty())
  {
    Treasure* temp_treasure = temp_covered_stack.back();
    if (current_tile->getTreasure() == temp_treasure)
    {
      temp_covered_stack.pop_back();
      current_player_->setCoveredStack(temp_covered_stack);
      current_player_->increaseNrOfFoundTreasures();
      current_tile->collectTreasure();
    }
  }
  // check if the current player stands on the item
  if ((current_tile->getType() == TileType::X || current_tile->getType() == TileType::O) &&
       !current_player_->isItemCollected())
  {
    current_player_->collectItem(dynamic_cast<ItemTile*>(current_tile)->getItem());
    current_player_->setItemCollected(true);
    dynamic_cast<ItemTile*>(current_tile)->setCollected(true);
  }

  // If current player is tied set rope_ to false  (untied it)
  if (current_player_->isTied())
  {
    current_player_->setRope(false);
  }

  // check if the current player has collected all treasures an stand on start tile
  if (current_player_->getNrFoundTreasures() == max_found_treasure &&
      current_player_->getColorString() == current_tile->getPlayerColor())
  {
    std::cout << "The Player " << getCurrentPlayerStr() << " has won the game!\n";
    throw Error::Exit;
  }
  Board& board = Board::getInstance();
  board.printBoard(); // because allways output in finish
  next_player_ = true;
  showtreasure_ = false;
  finished_ = true;
  inserted_ = false;
}

//---------------------------------------------------------------------------------------------------------------------
void Prompt::inputShowFreeTile()
{
  Board& board = Board::getInstance();
  if (player_input_.size() == 1)
    board.printFreeTile();
  else
    throw Error::NoArguments;
}
//---------------------------------------------------------------------------------------------------------------------
void Prompt::inputRotate()
{
  size_t secound_input = 1;
  if (player_input_.size() != 2)
    throw Error::WrongNrArg;
  Game& game = Game::getInstance();
  board_tiles_ = game.getBoardTiles();
  bool rotate = false; // to make the query possible
  // checks if the second input is valid
  if (player_input_.at(secound_input) == "left" || player_input_.at(secound_input) == "l" ||
      player_input_.at(secound_input) == "right" || player_input_.at(secound_input) == "r")
  {
    if (player_input_.at(secound_input) == "left" || player_input_.at(secound_input) == "l")
    {
      // because the free tile is on back().back()
      if (board_tiles_->back().back()->getRotation() == Rotation::DEG0 && rotate == false)
      {
        board_tiles_->back().back()->setRotation(Rotation::DEG90);
        rotate = true;
      }
      if (board_tiles_->back().back()->getRotation() == Rotation::DEG90 && rotate == false)
      {
        board_tiles_->back().back()->setRotation(Rotation::DEG180);
        rotate = true;
      }
      if (board_tiles_->back().back()->getRotation() == Rotation::DEG180 && rotate == false)
      {
        board_tiles_->back().back()->setRotation(Rotation::DEG270);
        rotate = true;
      }
      if (board_tiles_->back().back()->getRotation() == Rotation::DEG270 && rotate == false)
      {
        board_tiles_->back().back()->setRotation(Rotation::DEG0);
        rotate = true;
      }
    }
    if (player_input_.at(secound_input) == "right" || player_input_.at(secound_input) == "r")
    {
      if (board_tiles_->back().back()->getRotation() == Rotation::DEG0 && rotate == false)
      {
        board_tiles_->back().back()->setRotation(Rotation::DEG270);
        rotate = true;
      }
      if (board_tiles_->back().back()->getRotation() == Rotation::DEG270 && rotate == false)
      {
        board_tiles_->back().back()->setRotation(Rotation::DEG180);
        rotate = true;
      }
      if (board_tiles_->back().back()->getRotation() == Rotation::DEG180 && rotate == false)
      {
        board_tiles_->back().back()->setRotation(Rotation::DEG90);
        rotate = true;
      }
      if (board_tiles_->back().back()->getRotation() == Rotation::DEG90 && rotate == false)
      {
        board_tiles_->back().back()->setRotation(Rotation::DEG0);
        rotate = true;
      }
    }
  }
  else
  {
    throw Error::InvParameter1;
  }
}

//---------------------------------------------------------------------------------------------------------------------
void Prompt::checkAllowedInsert()
{
  size_t secound_input = 1;
  size_t thired_input = 2;
  // check, if the input is correct, else throw exception
  // there we check if the move is allowed (last move/ current move)
  if (player_input_.size() > 2 && player_input_.at(thired_input).size() == 1 && player_input_.at(thired_input) > "0" &&
      player_input_.at(thired_input) < "8")
  {
    size_t current_pos = stoi(player_input_.at(thired_input));
    if (last_insert_str_ == "top" || last_insert_str_ == "t")
    {
      if (player_input_.at(secound_input) == "bottom" || player_input_.at(secound_input) == "b")
      {
        if (current_pos == last_insert_pos_)
          throw Error::NotAllowed;
      }
    }
    if (last_insert_str_ == "bottom" || last_insert_str_ == "b")
    {
      if (player_input_.at(secound_input) == "top" || player_input_.at(secound_input) == "t")
      {
        if (current_pos == last_insert_pos_)
          throw Error::NotAllowed;
      }
    }
    if (last_insert_str_ == "right" || last_insert_str_ == "r")
    {
      if (player_input_.at(secound_input) == "left" || player_input_.at(secound_input) == "l")
      {
        if (current_pos == last_insert_pos_)
          throw Error::NotAllowed;
      }
    }
    if (last_insert_str_ == "left" || last_insert_str_ == "l")
    {
      if (player_input_.at(secound_input) == "right" || player_input_.at(secound_input) == "r")
      {
        if (current_pos == last_insert_pos_)
          throw Error::NotAllowed;
      }
    }
  }
  else
  {
    throw Error::InvParameter2;
  }
}

//---------------------------------------------------------------------------------------------------------------------
void Prompt::inputInsert()
{
  if (player_input_.size() != 3)
    throw Error::WrongNrArg;
  size_t secound_input = 1;
  size_t thired_input = 2;
  checkAllowedInsert();
  // check the second input, else throw exception
  if (player_input_.at(secound_input) == "top" || player_input_.at(secound_input) == "t" ||
      player_input_.at(secound_input) == "bottom" || player_input_.at(secound_input) == "b" ||
      player_input_.at(secound_input) == "right" || player_input_.at(secound_input) == "r" ||
      player_input_.at(secound_input) == "left" || player_input_.at(secound_input) == "l")
  {
    if (player_input_.at(secound_input) == "top" || player_input_.at(secound_input) == "t")
    {
      inputInsertTopParam();
    }
    if (player_input_.at(secound_input) == "bottom" || player_input_.at(secound_input) == "b")
    {
      inputInsertBottomParam();
    }
    if (player_input_.at(secound_input) == "right" || player_input_.at(secound_input) == "r")
    {
      inputInsertRightParam();
    }
    if (player_input_.at(secound_input) == "left" || player_input_.at(secound_input) == "l")
    {
      inputInsertLeftParam();
    }
  }
  else
  {
    throw Error::InvParameter1;
  }
  last_insert_str_ = player_input_.at(secound_input);
  last_insert_pos_ = stoi(player_input_.at(thired_input));
  inserted_ = true;
}

//---------------------------------------------------------------------------------------------------------------------
void Prompt::inputInsertTopParam()
{
  Board& board = Board::getInstance();
  Game& game = Game::getInstance();
  size_t thired_input = 2;
  board_tiles_ = game.getBoardTiles();
  // the input(third) should be in rang between 1 and 7
  if (player_input_.size() > 2 && player_input_.at(thired_input).size() == 1 && player_input_.at(thired_input) > "0" &&
      player_input_.at(thired_input) < "8")
  {
    size_t insert_number = stoi(player_input_.at(thired_input)); // than make a size_t
    // the number must be a movable tile that means (2/4/6)
    if (insert_number == 2 || insert_number == 4 || insert_number == 6)
    {
      // now go throw the board_tiles an change it
      for (size_t row_cnt = 0; row_cnt < board_tiles_->size() - 1; row_cnt++)
      {
        std::swap(board_tiles_->at(row_cnt).at(insert_number - 1), board_tiles_->back().back());
      }
      checkIfPlayersOnTile(0, insert_number - 1);
      game.setCoordinates(); // don't forget the coordinates
      board.printBoard();    // because allways output by insert
      if (showtreasure_)
      {
        printTreasure();
      }
    }
    else
    {
      throw Error::InvalidPosition;
    }
  }
  else
  {
    throw Error::InvParameter2;
  }
}

//---------------------------------------------------------------------------------------------------------------------
void Prompt::inputInsertBottomParam()
{
  // commants take a closer loke by inputInsertTopParam()
  Board& board = Board::getInstance();
  Game& game = Game::getInstance();
  size_t thired_input = 2;
  size_t row_cnt;
  board_tiles_ = game.getBoardTiles();
  if (player_input_.size() > 2 && player_input_.at(thired_input).size() == 1 && player_input_.at(thired_input) > "0" &&
      player_input_.at(thired_input) < "9")
  {
    size_t insert_number = stoi(player_input_.at(thired_input));
    if (insert_number == 2 || insert_number == 4 || insert_number == 6)
    {
      for (row_cnt = board_tiles_->size() - 2; row_cnt > 0; row_cnt--)
      {
        std::swap(board_tiles_->at(row_cnt).at(insert_number - 1), board_tiles_->back().back());
      }
      // first row chang
      std::swap(board_tiles_->at(row_cnt).at(insert_number - 1), board_tiles_->back().back());
      checkIfPlayersOnTile(board_tiles_->size() - 2, insert_number - 1);
      game.setCoordinates();
      board.printBoard();
      if (showtreasure_)
      {
        printTreasure();
      }
    }
    else
    {
      throw Error::InvalidPosition;
    }
  }
  else
  {
    throw Error::InvParameter2;
  }
}

//---------------------------------------------------------------------------------------------------------------------
void Prompt::inputInsertRightParam()
{
  // commants take a closer loke by inputInsertTopParam()
  Board& board = Board::getInstance();
  Game& game = Game::getInstance();
  size_t thired_input = 2;
  size_t column_cnt;
  board_tiles_ = game.getBoardTiles();
  if (player_input_.size() > 2 && player_input_.at(thired_input).size() == 1 && player_input_.at(thired_input) > "0" &&
      player_input_.at(thired_input) < "9")
  {
    size_t insert_number = stoi(player_input_.at(thired_input));
    if (insert_number == 2 || insert_number == 4 || insert_number == 6)
    {
      for (column_cnt = board_tiles_->front().size() - 1; column_cnt > 0; column_cnt--)
      {
        std::swap(board_tiles_->at(insert_number - 1).at(column_cnt), board_tiles_->back().back());
      }
      std::swap(board_tiles_->at(insert_number - 1).at(column_cnt), board_tiles_->back().back());
      checkIfPlayersOnTile(insert_number - 1, board_tiles_->front().size() - 1);
      game.setCoordinates();
      board.printBoard();
      if (showtreasure_)
      {
        printTreasure();
      }
    }
    else
    {
      throw Error::InvalidPosition;
    }
  }
  else
  {
    throw Error::InvParameter2;
  }
}

//---------------------------------------------------------------------------------------------------------------------
void Prompt::inputInsertLeftParam()
{
  // commants take a closer loke by inputInsertTopParam()
  Board& board = Board::getInstance();
  Game& game = Game::getInstance();
  size_t thired_input = 2;
  board_tiles_ = game.getBoardTiles();
  if (player_input_.size() > 2 && player_input_.at(thired_input).size() == 1 && player_input_.at(thired_input) > "0" &&
      player_input_.at(thired_input) < "9")
  {
    size_t insert_number = stoi(player_input_.at(thired_input));
    if (insert_number == 2 || insert_number == 4 || insert_number == 6)
    {
      for (size_t column_cnt = 0; column_cnt < board_tiles_->size() - 1; column_cnt++)
      {
        std::swap(board_tiles_->at(insert_number - 1).at(column_cnt), board_tiles_->back().back());
      }
      checkIfPlayersOnTile(insert_number - 1, 0);
      game.setCoordinates();
      board.printBoard();
      if (showtreasure_)
      {
        printTreasure();
      }
    }
    else
    {
      throw Error::InvalidPosition;
    }
  }
  else
  {
    throw Error::InvParameter2;
  }
}

//---------------------------------------------------------------------------------------------------------------------
void Prompt::checkIfPlayersOnTile(size_t row, size_t column)
{
  // after put the right one out check if there are player(s)
  // back().back() because thats the free tile
  if (!board_tiles_->back().back()->getPlayer().empty())
  {
    // put the player(s) on the insert tile
    for (auto player : board_tiles_->back().back()->getPlayer())
    {
      board_tiles_->at(row).at(column)->setPlayer(player);
      board_tiles_->back().back()->deletePlayer();
    }
  }
}

//---------------------------------------------------------------------------------------------------------------------
void Prompt::inputShowTreasure()
{
  if (player_input_.size() != 1)
    throw Error::NoArguments;

  Game& game = Game::getInstance();
  Board& board = Board::getInstance();

  int max_found_treasure = game.getTreasure().size() / game.getNrOfPlayers();
  std::vector<Treasure*> temp_covered_stack = current_player_->getCoveredStack();
  // check if there are treasueres avaliable or if the player is finished!
  if (current_player_->getNrFoundTreasures() == max_found_treasure)
  {
    if (gamefield_on == true)
    {
      board.printBoard();
    }
    printTreasure();
  }
  else
  {
    if (gamefield_on == true)
    {
      board.printBoard();
    }
    printTreasure();
  }
  showtreasure_ = true;
}

//---------------------------------------------------------------------------------------------------------------------
void Prompt::printTreasure()
{
  Game& game = Game::getInstance();
  int max_found_treasure = game.getTreasure().size() / game.getNrOfPlayers();
  // if all treasures are found make if! If not all founded make else!
  if (current_player_->getNrFoundTreasures() == max_found_treasure)
  {
    std::cout << "All Treasures found, return to your startfield to win!" << std::endl;
  }
  else
  {
    std::vector<Treasure*> temp_covered_stack = current_player_->getCoveredStack();
    Treasure* temp_treasure = temp_covered_stack.back();
    if (temp_treasure->getTreasureId() > 9)
    {
      std::cout << "Current Treasure: " << temp_treasure->getName() << " Nr.: " << temp_treasure->getTreasureId()
                << '\n';
    }
    else
    {
      std::cout << "Current Treasure: " << temp_treasure->getName() << " Nr.: 0" << temp_treasure->getTreasureId()
                << '\n';
    }
  }
}
//---------------------------------------------------------------------------------------------------------------------
void Prompt::inputHideTreasure()
{
  if (player_input_.size() != 1)
  {
    throw Error::NoArguments;
  }

  std::cout << "\x1b[2J"; // << std::endl;
  Board& board = Board::getInstance();
  board.printBoard(); // because allways output by hide treasure
  showtreasure_ = false;
}

//---------------------------------------------------------------------------------------------------------------------
void Prompt::inputGamefield()
{
  size_t secound_input = 1;
  Board& board = Board::getInstance();
  if (player_input_.size() > 2)
    throw Error::WrongNrArg;
  // check if just gamefield without parameter
  if (player_input_.size() == 1)
  {
    board.printBoard();
    if (showtreasure_) // if showtreasuer is set
    {
      printTreasure();
    }
    gamefield_setted_ = true;
  }
  // check if gamefield with parameter
  if (player_input_.size() == 2 &&
      (player_input_.at(secound_input) == "on" || player_input_.at(secound_input) == "off"))
  {
    if (player_input_.at(secound_input) == "on")
    {
      // set the true bools for checkGamefieldOnOff()
      gamefield_on = true;
      gamefield_setted_ = true;
    }
    if (player_input_.at(secound_input) == "off")
    {
      // set the true bools for checkGamefieldOnOff()
      gamefield_on = false;
      gamefield_setted_ = true;
    }
  }
  else
  {
    if (player_input_.size() == 2)
      throw Error::InvParameter1;
  }
}

//---------------------------------------------------------------------------------------------------------------------
Player* Prompt::getCurrentPlayer()
{
  size_t nr_of_players = players_.size();
  // if called finish next_player_ become true
  if (next_player_)
  {
    next_player_ = false;
    // create a loop of the player count interval (vector)
    if (current_player_cnt_ == nr_of_players - 1)
    {
      current_player_cnt_ = 0;
      //// checking if current player is blocked
      if (players_.at(current_player_cnt_)->getBlocked())
      {
        std::cout << "I am in currentPlayer " << std::endl;
        players_.at(current_player_cnt_)->setBlocked(false);
        current_player_cnt_++;
        return players_.at(current_player_cnt_);
      }
      return players_.at(current_player_cnt_);
    }
    else
    {
      std::cout << "I am in currentPlayer else " << std::endl;
      current_player_cnt_++;
      if (players_.at(current_player_cnt_)->getBlocked())
      {
        std::cout << "Somethingggg!!!! " << std::endl;
        players_.at(current_player_cnt_)->setBlocked(false);
        current_player_cnt_++;
        return players_.at(current_player_cnt_);
      }
      return players_.at(current_player_cnt_);
    }
  }
  else
  {
    return players_.at(current_player_cnt_);
  }
}

//---------------------------------------------------------------------------------------------------------------------
std::string Prompt::getCurrentPlayerStr()
{
  PlayerColor current_player_color = current_player_->getColor();
  if (current_player_color == PlayerColor::R)
  {
    return "RED";
  }
  if (current_player_color == PlayerColor::Y)
  {
    return "YELLOW";
  }
  if (current_player_color == PlayerColor::G)
  {
    return "GREEN";
  }
  else
  {
    return "BLUE";
  }
}

//---------------------------------------------------------------------------------------------------------------------
void Prompt::formatInput()
{
  std::string st_buffer;
  player_input_.clear();

  clearWhitespaceToOne(); // now read_input_ hast just one whitespace between
  // read input into an vector of strings
  for (size_t letter = 0; letter < read_input_.length(); letter++)
  {
    // use the whitespace for separation the string
    if (read_input_.at(letter) != ' ')
    {
      // push it in a temp string
      st_buffer.push_back(read_input_.at(letter));
    }
    else
    {
      // than push the string in a vector
      player_input_.push_back(st_buffer);
      st_buffer.clear();
    }
  }
  player_input_.push_back(st_buffer);
  arrowOutput();
}

//---------------------------------------------------------------------------------------------------------------------
void Prompt::arrowOutput()
{
  // for the Exception only
  int first_input = 0;
  if (player_input_.at(first_input) == "\x1b[A")
  {
    read_input_.clear();
    read_input_ = "arrow up";
  }
  if (player_input_.at(first_input) == "\x1b[B")
  {
    read_input_.clear();
    read_input_ = "arrow down";
  }
  if (player_input_.at(first_input) == "\x1b[C")
  {
    read_input_.clear();
    read_input_ = "arrow right";
  }
  if (player_input_.at(first_input) == "\x1b[D")
  {
    read_input_.clear();
    read_input_ = "arrow left";
  }
}

//---------------------------------------------------------------------------------------------------------------------
void Prompt::clearWhitespaceToOne()
{
  std::string cleared_input;
  std::string temp_str;

  for (char letter : read_input_)
  {
    if (letter != ' ')
    {
      cleared_input.push_back(letter);
    }
    // just insert ONE whitespace!
    if (temp_str.length() > 0 && temp_str.back() != ' ' && letter == ' ')
    {
      cleared_input.push_back(letter);
    }
    temp_str.push_back(letter);
  }
  // check if the last input was a whitespace!
  if (cleared_input.back() == ' ')
  {
    cleared_input.pop_back();
  }
  read_input_ = cleared_input;
}
//---------------------------------------------------------------------------------------------------------------------
void Prompt::movePlayer()
{
  if (player_input_.size() > 3)
    throw Error::WrongNrArg;


  size_t first_input = 0;

  // if player is tied he can't move
  if (current_player_->isTied())
    throw Error::CannotMove;

  // go UP
  if (player_input_.at(first_input) == "w" || player_input_.at(first_input) == "\x1b[A")
  {
    if (player_input_.size() > 1)
      throw Error::NoArguments;
    goUp();
  }
  // go Down
  if (player_input_.at(first_input) == "s" || player_input_.at(first_input) == "\x1b[B")
  {
    if (player_input_.size() > 1)
      throw Error::NoArguments;
    goDown();
  }
  // go Right
  if (player_input_.at(first_input) == "d" || player_input_.at(first_input) == "\x1b[C")
  {
    if (player_input_.size() > 1)
      throw Error::NoArguments;
    goRight();
  }
  // go Left
  if (player_input_.at(first_input) == "a" || player_input_.at(first_input) == "\x1b[D")
  {
    if (player_input_.size() > 1)
      throw Error::NoArguments;
    goLeft();
  }
  if (player_input_.at(first_input) == "go" && player_input_.size() == 1)
    throw Error::WrongNrArg;
  // if the move command is "go"
  if (player_input_.at(first_input) == "go")
  {
    goMovement();
  }
  moved_gamefield = true;
  current_player_->activateLadder(false);
}

//---------------------------------------------------------------------------------------------------------------------
void Prompt::goMovement()
{
  size_t second_input = 1;
  // checks the first parameter
  if (player_input_.size() > 1 &&
      (player_input_.at(second_input) == "up" || player_input_.at(second_input) == "down" ||
       player_input_.at(second_input) == "right" || player_input_.at(second_input) == "left"))
  {
    // if just one parameter
    if (player_input_.size() == 2)
    {
      if (player_input_.at(second_input) == "up")
        goUp();
      if (player_input_.at(second_input) == "down")
        goDown();
      if (player_input_.at(second_input) == "right")
        goRight();
      if (player_input_.at(second_input) == "left")
        goLeft();
    }
    else // if two parameter
    {
      size_t steps;
      if (player_input_.at(2) > "0" && player_input_.at(2) < "7")
        steps = stoi(player_input_.at(2));
      else
        throw Error::InvParameter2;
      if (player_input_.at(second_input) == "up")
      {
        checkGoUpPossible();
        for (size_t cnt = 0; cnt < steps; cnt++)
          goUp();
      }
      if (player_input_.at(second_input) == "down")
      {
        checkGoDownPossible();
        for (size_t cnt = 0; cnt < steps; cnt++)
          goDown();
      }
      if (player_input_.at(second_input) == "right")
      {
        checkGoRightPossible();
        for (size_t cnt = 0; cnt < steps; cnt++)
          goRight();
      }
      if (player_input_.at(second_input) == "left")
      {
        checkGoLeftPossible();
        for (size_t cnt = 0; cnt < steps; cnt++)
          goLeft();
      }
    }
  }
  else
  {
    throw Error::InvParameter1;
  }
}

//---------------------------------------------------------------------------------------------------------------------
void Prompt::checkGoUpPossible()
{
  // check the player input for stoi!
  if (player_input_.at(2) > "0" && player_input_.at(2) < "7")
  {

    Game& game = Game::getInstance();
    board_tiles_ = game.getBoardTiles();
    size_t steps = stoi(player_input_.at(2));
    bool temp_ladder = current_player_->isLadderActivated();
    // how many steps the will go in the direction
    for (size_t step = 0; step < steps; step++)
    {
      Open current_tile_open_to = current_tile_->getOpenTo();
      Coordinates current_tile_coordinates = current_tile_->getPosition();
      // if the direction is free! (current tile)
      if ((current_tile_open_to.up_ == true || temp_ladder) && current_tile_coordinates.row_ != 1)
      {
        Tile* next_tile = board_tiles_->at(current_tile_coordinates.row_ - 2).at(current_tile_coordinates.column_ - 1);
        Open next_tile_open_to = next_tile->getOpenTo();
        // if the direction is free! (next tile)
        if (next_tile_open_to.down_ == true || temp_ladder)
        {
          current_tile_ = next_tile; // because the move is possible
        }
        else
        {
          current_tile_ = getCurrentTile();
          throw Error::ImpossibleMove;
        }
      }
      else
      {
        current_tile_ = getCurrentTile();
        throw Error::ImpossibleMove;
      }
    }
  }
  else
  {
    current_tile_ = getCurrentTile();
    throw Error::ImpossibleMove;
  }
  current_tile_ = getCurrentTile(); // if possible go pack to begin and start the right method goUp!
}

//---------------------------------------------------------------------------------------------------------------------
void Prompt::goUp()
{
  Open current_tile_open_to = current_tile_->getOpenTo();
  Coordinates current_tile_coordinates = current_tile_->getPosition();

  Game& game = Game::getInstance();
  board_tiles_ = game.getBoardTiles();
  bool temp_ladder = current_player_->isLadderActivated();
  // if the direction is free! (current tile)
  if ((current_tile_open_to.up_ == true || temp_ladder) && current_tile_coordinates.row_ != 1) // it's not first row
  {
    Tile* next_tile = board_tiles_->at(current_tile_coordinates.row_ - 2).at(current_tile_coordinates.column_ - 1);
    Open next_tile_open_to = next_tile->getOpenTo();
    // if the direction is free! (next tile)
    if (next_tile_open_to.down_ == true || temp_ladder)
    {
      current_tile_->erasePlayer(current_player_); // delete the player from the tile
      next_tile->setPlayer(current_player_);       // create the new player on the next tile
      current_tile_ = next_tile;
    }
    else
    {
      throw Error::ImpossibleMove;
    }
  }
  else
  {
    throw Error::ImpossibleMove;
  }
}

//---------------------------------------------------------------------------------------------------------------------
void Prompt::checkGoDownPossible()
{
  // to understand the code take a closer loke to the Up direction (good doc)
  if (player_input_.at(2) > "0" && player_input_.at(2) < "7")
  {

    Game& game = Game::getInstance();
    board_tiles_ = game.getBoardTiles();
    size_t steps = stoi(player_input_.at(2));
    bool temp_ladder = current_player_->isLadderActivated();

    for (size_t step = 0; step < steps; step++)
    {
      Open current_tile_open_to = current_tile_->getOpenTo();
      Coordinates current_tile_coordinates = current_tile_->getPosition();
      if ((current_tile_open_to.down_ == true || temp_ladder) &&
           current_tile_coordinates.row_ != board_tiles_->size() - 1)
      {
        Tile* next_tile = board_tiles_->at(current_tile_coordinates.row_).at(current_tile_coordinates.column_ - 1);
        Open next_tile_open_to = next_tile->getOpenTo();
        if (next_tile_open_to.up_ == true || temp_ladder)
        {
          current_tile_ = next_tile;
        }
        else
        {
          current_tile_ = getCurrentTile();
          throw Error::ImpossibleMove;
        }
      }
      else
      {
        current_tile_ = getCurrentTile();
        throw Error::ImpossibleMove;
      }
    }
  }
  else
  {
    current_tile_ = getCurrentTile();
    throw Error::ImpossibleMove;
  }
  current_tile_ = getCurrentTile();
}

//---------------------------------------------------------------------------------------------------------------------
void Prompt::goDown()
{
  // to understand the code take a closer loke to the Up direction (good doc)
  Open current_tile_open_to = current_tile_->getOpenTo();
  Coordinates current_tile_coordinates = current_tile_->getPosition();

  Game& game = Game::getInstance();
  board_tiles_ = game.getBoardTiles();
  bool temp_ladder = current_player_->isLadderActivated();

  if ((current_tile_open_to.down_ == true || temp_ladder) &&
      current_tile_coordinates.row_ != board_tiles_->size() - 1) // it's not last row
  {
    Tile* next_tile = board_tiles_->at(current_tile_coordinates.row_).at(current_tile_coordinates.column_ - 1);
    Open next_tile_open_to = next_tile->getOpenTo();
    if (next_tile_open_to.up_ == true || temp_ladder)
    {
      current_tile_->erasePlayer(current_player_);
      next_tile->setPlayer(current_player_);
      current_tile_ = next_tile;
    }
    else
    {
      throw Error::ImpossibleMove;
    }
  }
  else
  {
    throw Error::ImpossibleMove;
  }
}

//---------------------------------------------------------------------------------------------------------------------
void Prompt::checkGoLeftPossible()
{
  // to understand the code take a closer look to the Up direction (good doc)
  if (player_input_.at(2) > "0" && player_input_.at(2) < "7")
  {

    Game& game = Game::getInstance();
    board_tiles_ = game.getBoardTiles();
    size_t steps = stoi(player_input_.at(2));
    bool temp_ladder = current_player_->isLadderActivated();

    for (size_t step = 0; step < steps; step++)
    {
      Open current_tile_open_to = current_tile_->getOpenTo();
      Coordinates current_tile_coordinates = current_tile_->getPosition();
      if ((current_tile_open_to.left_ == true || temp_ladder) && current_tile_coordinates.column_ != 1)
      {
        Tile* next_tile = board_tiles_->at(current_tile_coordinates.row_ - 1).at(current_tile_coordinates.column_ - 2);
        Open next_tile_open_to = next_tile->getOpenTo();
        if (next_tile_open_to.right_ == true || temp_ladder)
        {
          current_tile_ = next_tile;
        }
        else
        {
          current_tile_ = getCurrentTile();
          throw Error::ImpossibleMove;
        }
      }
      else
      {
        current_tile_ = getCurrentTile();
        throw Error::ImpossibleMove;
      }
    }
  }
  else
  {
    current_tile_ = getCurrentTile();
    throw Error::ImpossibleMove;
  }
  current_tile_ = getCurrentTile();
}

//---------------------------------------------------------------------------------------------------------------------
void Prompt::goLeft()
{
  // to understand the code take a closer loke to the Up direction (good doc)
  Open current_tile_open_to = current_tile_->getOpenTo();
  Coordinates current_tile_coordinates = current_tile_->getPosition();

  Game& game = Game::getInstance();
  board_tiles_ = game.getBoardTiles();
  bool temp_ladder = current_player_->isLadderActivated();

  if ((current_tile_open_to.left_ == true || temp_ladder) &&
       current_tile_coordinates.column_ != 1) // it's not the most left column
  {
    Tile* next_tile = board_tiles_->at(current_tile_coordinates.row_ - 1).at(current_tile_coordinates.column_ - 2);
    Open next_tile_open_to = next_tile->getOpenTo();
    if (next_tile_open_to.right_ == true || temp_ladder)
    {
      current_tile_->erasePlayer(current_player_);
      next_tile->setPlayer(current_player_);
      current_tile_ = next_tile;
    }
    else
    {
      throw Error::ImpossibleMove;
    }
  }
  else
  {
    throw Error::ImpossibleMove;
  }
}

//---------------------------------------------------------------------------------------------------------------------
void Prompt::checkGoRightPossible()
{
  // to understand the code take a closer loke to the Up direction (good doc)
  if (player_input_.at(2) > "0" && player_input_.at(2) < "7")
  {

    Game& game = Game::getInstance();
    board_tiles_ = game.getBoardTiles();
    size_t steps = stoi(player_input_.at(2));
    bool temp_ladder = current_player_->isLadderActivated();

    for (size_t step = 0; step < steps; step++)
    {
      Open current_tile_open_to = current_tile_->getOpenTo();
      Coordinates current_tile_coordinates = current_tile_->getPosition();
      if ((current_tile_open_to.right_ == true || temp_ladder) && current_tile_coordinates.column_ != 7)
      {
        Tile* next_tile = board_tiles_->at(current_tile_coordinates.row_ - 1).at(current_tile_coordinates.column_);
        Open next_tile_open_to = next_tile->getOpenTo();
        if (next_tile_open_to.left_ == true || temp_ladder)
        {
          current_tile_ = next_tile;
        }
        else
        {
          current_tile_ = getCurrentTile();
          throw Error::ImpossibleMove;
        }
      }
      else
      {
        current_tile_ = getCurrentTile();
        throw Error::ImpossibleMove;
      }
    }
  }
  else
  {
    current_tile_ = getCurrentTile();
    throw Error::ImpossibleMove;
  }
  current_tile_ = getCurrentTile();
}

//---------------------------------------------------------------------------------------------------------------------
void Prompt::goRight()
{
  // to understand the code take a closer loke to the Up direction (good doc)
  Open current_tile_open_to = current_tile_->getOpenTo();
  Coordinates current_tile_coordinates = current_tile_->getPosition();

  Game& game = Game::getInstance();
  board_tiles_ = game.getBoardTiles();
  bool temp_ladder = current_player_->isLadderActivated();

  if ((current_tile_open_to.right_ == true || temp_ladder) && current_tile_coordinates.column_ != 7) // it's not the most right column
  {
    Tile* next_tile = board_tiles_->at(current_tile_coordinates.row_ - 1).at(current_tile_coordinates.column_);
    Open next_tile_open_to = next_tile->getOpenTo();
    if (next_tile_open_to.left_ == true || temp_ladder)
    {
      current_tile_->erasePlayer(current_player_);
      next_tile->setPlayer(current_player_);
      current_tile_ = next_tile;
    }
    else
    {
      throw Error::ImpossibleMove;
    }
  }
  else
  {
    throw Error::ImpossibleMove;
  }
}
//---------------------------------------------------------------------------------------------------------------------
Tile* Prompt::getCurrentTile()
{
  Game& game = Game::getInstance();
  board_tiles_ = game.getBoardTiles();
  Tile* temp_tile = nullptr; // should help
  // go throw the board tile
  for (size_t row = 0; row < board_tiles_->size() - 1; row++)
  {
    for (auto tile : board_tiles_->at(row))
    {
      auto temp_players = tile->getPlayer();
      // than go trhow the players on tile
      for (auto player : temp_players)
      {
        // if the right player is founded return the tile
        if (player == current_player_)
        {
          temp_tile = tile;
          break;
        }
      }
    }
  }
  return temp_tile;
}

//-------------------------------------------------------------------------------------
void Prompt::inputRope()
{
  Game& game = Game::getInstance();
  board_tiles_ = game.getBoardTiles();

  std::vector<Player*> temp_players =  current_tile_->getPlayer();
  // check if temp_players is empty because it is possible that there are
  // no players inside the temp_players
  if (!temp_players.empty())
  {
    for (std::vector<Player*>::iterator it = temp_players.begin(); it != temp_players.end(); it++)
    {
      if (*it != current_player_)
      {
        (*it)->setRope(true);
        std::cout << "Player " << (*it)->getColorString() << " tied up." << std::endl;
      }
    }
    current_player_->setItemUsed(true);
    current_player_->setItemCollected(false);
  }
  else
  {
    std::cout << "No player to tie up here." << std::endl;
  }
}

//-------------------------------------------------------------------------------------
void Prompt::inputDynamite()
{
  //Game& game = Game::getInstance();
  //board_tiles_ = game.getBoardTiles();
}

//-------------------------------------------------------------------------------------
void Prompt::inputLadder()
{
  Game& game = Game::getInstance();
  board_tiles_ = game.getBoardTiles();

  current_player_->activateLadder(true);
  std::cout << "You can go in all directions, with your next move. Choose wisely!" << std::endl;

  // After the item ladder is used we must assure that the same item can be collected in the future.
  for (int row = 0; row < 7; row++)
  {
    for (int col = 0; col < 7; col++)
    {
      if (board_tiles_->at(row).at(col)->getType() == TileType::X ||
          board_tiles_->at(row).at(col)->getType() == TileType::O)
      {
        //dynamic_cast<ItemTile*>(current_tile)->getItem()
        if (dynamic_cast<ItemTile*>(board_tiles_->at(row).at(col))->getItem() == current_player_->getItem())
          dynamic_cast<ItemTile*>(board_tiles_->at(row).at(col))->setCollected(false);
      }
    }
  }
  // At the end we set collected_ to false, because with that we allow player to collect item again.
  // Because one player can have only one item in storage (reserve).
  current_player_->setItemCollected(false);
}

//-------------------------------------------------------------------------------------
void Prompt::inputBricks()
{
  //Game& game = Game::getInstance();
  //board_tiles_ = game.getBoardTiles();
}

void Prompt::inputBlock()
{
  //Game& game = Game::getInstance();
  //board_tiles_ = game.getBoardTiles();

  //std::vector<Player*> temp_players =  current_tile_->getPlayer();
  //std::vector<Player*> players =
  bool flag = false;

  for (std::vector<Player*>::iterator it = players_.begin(); it != players_.end(); it++)
  {

    if (flag)
    {
      if ((*it)->getColor() == PlayerColor::Y)
       std::cout << "Yellow" <<std::endl;
      (*it)->setBlocked(true);
      break;
    }

    if (!current_player_->getBlockUsed())
    {
      if (*it == current_player_)
      {
        current_player_->setBlockUsed(true);
        flag = true;
      }
    }
  }
}