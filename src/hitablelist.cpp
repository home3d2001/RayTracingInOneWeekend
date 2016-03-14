#include "hitablelist.h"

HitableList::~HitableList() {
	for (const Hitable* item : list) {
		delete item;
	}
}

bool HitableList::hit(const Ray& r, float tMin, float tMax, hitRecord& rec) const {
	hitRecord tempRec;
	bool hitAnything = false;
	double closestSoFar = tMax;

	for (const Hitable* item : list) {
		if (item->hit(r, tMin, closestSoFar, tempRec)) {
			hitAnything = true;
			closestSoFar = tempRec.t;
			rec = tempRec;
		}
	}

	return hitAnything;
}
