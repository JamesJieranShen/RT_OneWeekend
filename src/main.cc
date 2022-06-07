#include <iostream>
#include <memory>

#include "include/camera.h"
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
  const int samples_per_pixel = 100;

  // scene
  hittable_list scene;
  scene.add(make_shared<sphere>(point3(0, 0, -1), 0.5));
  scene.add(make_shared<sphere>(point3(0, -100.5, -1), 100));

  // Camera
  camera cam;
  // Render

  std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

  for (int j = image_height - 1; j >= 0; --j) {
    std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
    for (int i = 0; i < image_width; ++i) {
      color pixel_color(0, 0, 0);
      for (int s = 0; s < samples_per_pixel; s++) {
        // original implementation uses (width-1), which is not necessary? We want to sample from 0-1
        auto sample_u = (i + random_double()) / image_width;
        auto sample_v = (j + random_double()) / image_height;
        ray r = cam.get_ray(sample_u, sample_v);
        pixel_color += ray_color(r, scene);
      }
      write_color(std::cout, pixel_color, samples_per_pixel);
    } // end pixel
  }
  std::cerr << "\nDone.\n";
}