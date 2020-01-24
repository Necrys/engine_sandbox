#pragma once

#include <glm/vec2.hpp>

struct Position: glm::ivec2 {
  Position() {};
  Position( const uint32_t x, const uint32_t y ):
    glm::ivec2( x, y ) {};
};
