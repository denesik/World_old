// ============================================================================
// ==                   Copyright (c) 2015, Smirnov Denis                    ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#include "Game.h"
#include <stdlib.h>
#include <time.h>
#include "Log.h"
#include <boost/log/sources/severity_logger.hpp>

int main()
{
  srand(static_cast<unsigned int>(time(0)));

  LogInit();

  Game game;
  return game.Run();
}

