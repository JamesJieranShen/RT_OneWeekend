#include <iostream>

#include "include/color.h"
#include "include/ray.h"
#include "include/vec3.h"

double hit_sphere(const point3 &center, double radius, const ray &r) {
  vec3 oc = r.origin() - center;
  auto a = r.direction().length_squared();
  auto half_b = dot(oc, r.direction());
  auto c = oc.length_squared() - radius * radius;
  auto discriminant = half_b * half_b - a * c;

  if (discriminant < 0) {
    return -1.0;
  } else {
    return (-half_b - sqrt(discriminant)) / a;
  }
}

color ray_color(const ray &r) {
  auto sphere_center = point3(0, 0, -1);
  auto sphere_radius = 0.5;
  auto t = hit_sphere(sphere_center, sphere_radius, r);
  if (t > 0.0) {
    vec3 N = unit_vector(r.at(t) - sphere_center);
    return 0.5 * color(N.x() + 1, N.y() + 1, N.z() + 1);
  }
  vec3 unit_direction = unit_vector(r.direction());
  auto mix = 0.5 * (unit_direction.y() + 1.0);
  return (1.0 - mix) * color(1.0, 1.0, 1.0) + mix * color(0.5, 0.7, 1.0);
}

int main() {

  // Image
  const auto aspect_ratio = 16.0 / 9.0;
  const auto image_width = 400;
  const auto image_height = static_cast<int>(image_width / aspect_ratio);

  // Camera
  auto viewport_height = 2.0;
  auto viewport_width = aspect_ratio * viewport_height;
  auto focal_length = 1.0;

  auto origin = point3(0.0, 0.0, 0.0);
  auto lower_left_corner = origin - point3(0, 0, focal_length) -
                           point3(viewport_width / 2, 0, 0) -
                           point3(0, viewport_height / 2, 0);
  auto pixel_width = viewport_height / image_height;
  // Render

  std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

  for (int j = image_height - 1; j >= 0; --j) {
    std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
    for (int i = 0; i < image_width; ++i) {
      auto ray_dir =
          lower_left_corner + point3(i * pixel_width, j * pixel_width, 0);
      auto pixel_color = ray_color(ray(origin, ray_dir));
      write_color(std::cout, pixel_color);
    }
  }
  std::cerr << "\nDone.\n";
}