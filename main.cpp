//---------------------------------------------------------------------------------------------------------------------
// main.cpp
//
// Author: Boris Smiljanic 01531652
//         Milan Mirosav 11731475
//         Markus Dopelreiter 01535331
//---------------------------------------------------------------------------------------------------------------------
//

#include "Random.hpp"
#include "Game.hpp"
#include <iostream>
#include <stdio.h>
#include <string>
#include <cstring> //#include <string.h>     <ctring> is C++ library equivalent to string.h in C


//---------------------------------------------------------------------------------------------------------------------
///
/// The main program.
///
/// @param argc not used
/// @param argv not used
///
/// @return always zero
//
int main(int argc, __attribute__((unused)) const char **argv)
{
  if (argc > 2)
  {
    std::cout << "Wrong arguments!" << std::endl;
    return 2;
  }

  Game& game = Game::getInstance();

  if (argc == 2 && (strcmp(argv[1], "-bonus") == 0))
    game.setBonus(true);

  try
  {
    game.startGame();
    game.runGame();
  }
  catch(const Error &e)
  {
    if(e == Error::Exit)
    {
      return 0;
    }
  }
  return 0;
}

