#include <iostream>
#include <memory>

#include "include/color.h"
#include "include/hittable_list.h"
#include "include/rtweekend.h"
#include "include/sphere.h"

color ray_color(const ray &r, const hittable &scene)
{
  hit_record rec;
  if (scene.hit(r, 0, infinity, rec)) {
    // convert normal vector direction to RGB
    return 0.5 * (rec.normal + color(1, 1, 1));
  }

  // no hit, show sky
  vec3 unit_direction = unit_vector(r.direction());
  auto t = 0.5 * (unit_direction.y() + 1.0);
  return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}

int main()
{
  // Image
  const auto aspect_ratio = 16.0 / 9.0;
  const auto image_width = 400;
  const auto image_height = static_cast<int>(image_width / aspect_ratio);

  // scene
  hittable_list scene;
  scene.add(make_shared<sphere>(point3(0, 0, -1), 0.5));
  scene.add(make_shared<sphere>(point3(0, -100.5, -1), 100));

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
      auto pixel_color = ray_color(ray(origin, ray_dir), scene);
      write_color(std::cout, pixel_color);
    }
  }
  std::cerr << "\nDone.\n";
}