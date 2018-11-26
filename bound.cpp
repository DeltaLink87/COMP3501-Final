#include "bound.h"

namespace game {

Bound::Bound(glm::vec3 p1, glm::vec3 p2, float radius) {
	this->p1 = p1;
	this->p2 = p2;
	this->radius = radius;
}


Bound::~Bound(){}

void Bound::setPositions(glm::vec3 p1, glm::vec3 p2) {
	this->p1 = p1;
	this->p2 = p2;
}

bool Bound::intersects(const Bound other) {
	const float SMALLNUM = 0.000000001;
	glm::vec3 u = this->p2 - this->p1;
	glm::vec3 v = other.p2 - other.p1;
	glm::vec3 w = this->p1 - other.p1;
	float a = glm::dot(u, u);
	float b = glm::dot(u, v);
	float c = glm::dot(v, v);
	float d = glm::dot(u, w);
	float e = glm::dot(v, w);
	float D = a * c - b * b;
	float ti, tN, tD = D;
	float oi, oN, oD = D;

	//Checking if lines are close enough to parralel to be considered parralel
	if (D < SMALLNUM) {
		tN = 0;
		tD = 1;
		oN = e;
		oD = c;
	}
	else {
		tN = b * e - c * d;
		oN = a * e - b * d;
		if (tN < 0) {
			tN = 0;
			oN = e;
			oD = c;
		}
		else if (tN > tD) {
			tN = tD;
			oN = e + b;
			oD = c;
		}
	}

	if (oN < 0) {
		oN = 0;
		if (-d < 0) tN = 0;
		else if (-d > a) tN = tD;
		else {
			tN = -d;
			tN = a;
		}
	}
	else if (oN > oD) {
		oN = oD;
		if (-d + b < 0) tN = 0;
		else if (-d + b > a) tN = tD;
		else {
			tN = -d + b;
			tN = a;
		}
	}

	ti = tN / tD;
	oi = oN / oD;
	glm::vec3 dis = w + (ti * u) + (oi * v);

	return glm::length(dis) < this->radius + other.radius;
}
            
} // namespace game
