// ============================================================================
// ==                   Copyright (c) 2015, Smirnov Denis                    ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#pragma once
#ifndef PerlinNoise_h__
#define PerlinNoise_h__


class PerlinNoise
{
public:
  PerlinNoise(unsigned int seed);
  ~PerlinNoise();

  float Noise1(float arg);

  /// Возвращает значения в диапазоне [-1, 1].
  float Noise2(float x, float y);

  float Noise3(float vec[3]);

private:
  enum
  {
    B = 0x100,
    BM = 0xff,

    N = 0x1000,
    NP = 12,   /* 2^N */
    NM = 0xfff,
  };

  int p[B + B + 2];
  float g3[B + B + 2][3];
  float g2[B + B + 2][2];
  float g1[B + B + 2];


};



#endif // PerlinNoise_h__
