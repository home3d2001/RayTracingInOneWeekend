#pragma once
#include <vector>
#include "hitable.h"

class HitableList : public Hitable {
public:
	HitableList() : list() {}
	HitableList(std::vector<Hitable*>& l) : list(l) {}
	virtual ~HitableList();
	virtual bool hit(const Ray& r, float tMin, float tMax, hitRecord& rec) const override;

	std::vector<Hitable*> list;
};
