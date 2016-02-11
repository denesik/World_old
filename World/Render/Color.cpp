// ============================================================================
// ==                   Copyright (c) 2015, Smirnov Denis                    ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#include "Color.h"

Color::Color()
  : raw(0x00, 0x00, 0x00, 0xFF)
{

}

Color::Color(const glm::u8vec4 &color)
  : raw(color)
{

}

Color::Color(glm::u8 r, glm::u8 g, glm::u8 b, glm::u8 a)
  : raw(r, g, b, a)
{

}

glm::vec4 Color::Tof32Color() const
{
  return glm::vec4(static_cast<glm::f32>(raw.r) / 255.0f, 
                   static_cast<glm::f32>(raw.g) / 255.0f, 
                   static_cast<glm::f32>(raw.b) / 255.0f, 
                   static_cast<glm::f32>(raw.a) / 255.0f
                   );
}

const Color Color::white  (0xFF, 0xFF, 0xFF, 0xFF);
const Color Color::black  (0x00, 0x00, 0x00, 0xFF);
const Color Color::red    (0xFF, 0x00, 0x00, 0xFF);
const Color Color::green  (0x00, 0xFF, 0x00, 0xFF);
const Color Color::blue   (0x00, 0x00, 0xFF, 0xFF);

