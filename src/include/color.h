#ifndef COLOR_H
#define COLOR_H

#include "rtweekend.h"

#include <iostream>

inline void write_color(std::ostream &out, color pixel_color, double samples_per_pixel = 1.0)
{
  // Write the translated [0,255] value of each color component.
  out << static_cast<int>(255.999 * clamp(pixel_color.x() / samples_per_pixel, 0.0, 0.999)) << ' '
      << static_cast<int>(255.999 * clamp(pixel_color.y() / samples_per_pixel, 0.0, 0.999)) << ' '
      << static_cast<int>(255.999 * clamp(pixel_color.z() / samples_per_pixel, 0.0, 0.999)) << '\n';
}

#endif