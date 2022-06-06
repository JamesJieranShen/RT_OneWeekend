#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "vec3.h"

class sphere : public hittable{
  public:
    point3 center;
    double radius;

  public: 
    sphere(){}
    sphere(point3 c, double r): center(c), radius(r){};

    virtual bool hit(const ray & r, double t_min, double t_max, hit_record& rec) const override;
};

inline bool sphere::hit(const ray & r, double t_min, double t_max, hit_record& rec) const{
  vec3 oc = r.origin() - center;
  auto a = r.direction().length_squared();
  auto half_b = dot(oc, r.direction());
  auto c = oc.length_squared() - radius * radius;
  auto discriminant = half_b * half_b - a * c;
  auto sqrtd = sqrt(discriminant);
  if (discriminant < 0) {
    return false;
  }
  auto root = (-half_b - sqrtd) / a;
  if (root > t_max || root < t_min){
    root = (-half_b + sqrtd) / a;
    if (root > t_max || root < t_min){
      return false;
    }
  }
  rec.t = root;
  rec.p = r.at(rec.t);
  rec.set_face_normal(r, (rec.p - center) / radius);
  return true;
}

#endif