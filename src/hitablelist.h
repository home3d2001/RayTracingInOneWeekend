#pragma once
#include "hitable.h"

class HitableList : public Hitable {
public:
	HitableList() : list(nullptr), listSize(0) {}
	HitableList(Hitable** l, int n) : list(l), listSize(n) {}
	virtual bool hit(const Ray& r, float tMin, float tMax, hitRecord& rec) const override;

	Hitable** list;
	int listSize;
};
