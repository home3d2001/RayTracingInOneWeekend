#include "hitablelist.h"

bool HitableList::hit(const Ray& r, float tMin, float tMax, hitRecord& rec) const {
	hitRecord tempRec;
	bool hitAnything = false;
	double closestSoFar = tMax;

	for (int i = 0; i < listSize; ++i) {
		if (list[i]->hit(r, tMin, closestSoFar, tempRec)) {
			hitAnything = true;
			closestSoFar = tempRec.t;
			rec = tempRec;
		}
	}

	return hitAnything;
}
