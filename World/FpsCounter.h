// ============================================================================
// ==                   Copyright (c) 2015, Smirnov Denis                    ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#ifndef FPSCounter_h__
#define FPSCounter_h__

#include <list>

class FpsCounter
{
private:
  std::list<double> fpsStack;
  double currentTime;
  double lastTime;

  double fpsTime;

public:
  FpsCounter(void);
  ~FpsCounter(void);

  void Update();

  size_t GetCount();

};


#endif // FPSCounter_h__