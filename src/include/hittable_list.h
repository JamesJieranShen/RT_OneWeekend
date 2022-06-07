// A list of hittables, and determine the closest object that this ray hits.
#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "hittable.h"

#include <memory>
#include <vector>

using std::make_shared;
using std::shared_ptr;

class hittable_list : public hittable
{
public:
  std::vector<shared_ptr<hittable>> objects;

public:
  hittable_list() {}
  hittable_list(shared_ptr<hittable> object) { add(object); }

  void clear();
  void add(shared_ptr<hittable> object) { objects.push_back(object); };
  virtual bool hit(const ray &r, double t_min, double t_max,
                   hit_record &rec) const override;
};

inline bool hittable_list::hit(const ray &r, double t_min, double t_max, hit_record &rec) const {
  hit_record record;
  bool hit_anything = false;
  auto closest_so_far = t_max;

  for(const auto& object : objects){
    if (object->hit(r, t_min, closest_so_far, record)){
      hit_anything = true;
      closest_so_far = record.t;
    }
  }
  if (hit_anything) rec = record;
  return hit_anything;
}

#endif