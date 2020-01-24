#pragma once

struct Rotation {
public:
  Rotation() = default;
  Rotation( const double a ):
    angle( a ) {};

  double angle;
};
