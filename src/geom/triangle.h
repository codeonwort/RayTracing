#pragma once

#include "hit.h"
#include "material.h"

class Triangle : public Hitable
{

public:
	Triangle(const vec3& inV0, const vec3& inV1, const vec3& inV2, Material* inMaterial)
		: v0(inV0)
		, v1(inV1)
		, v2(inV2)
		, material(inMaterial)
	{
		n = cross(v1 - v0, v2 - v0);
		n.Normalize();
	}

	virtual bool Hit(const ray& r, float t_min, float t_max, HitResult& outResult) const;

private:
	vec3 v0;
	vec3 v1;
	vec3 v2;
	vec3 n;
	Material* material;
	
};

// http://geomalgorithms.com/a06-_intersect-2.html
bool Triangle::Hit(const ray& r, float t_min, float t_max, HitResult& outResult) const
{
	float s1, t1;

	float t = dot((v0 - r.o), n) / dot(r.d, n);
	vec3 p = r.o + t * r.d;

	if (t < t_min || t > t_max)
	{
		return false;
	}

	vec3 u = v1 - v0;
	vec3 v = v2 - v0;
	vec3 w = p - v0;

	float uv = dot(u, v);
	float wv = dot(w, v);
	float uu = dot(u, u);
	float vv = dot(v, v);
	float wu = dot(w, u);
	float uvuv = uv * uv;
	float uuvv = uu * vv;

	s1 = (uv * wv - vv * wu) / (uvuv - uuvv);
	t1 = (uv * wu - uu * wv) / (uvuv - uuvv);

	if (0.0f <= s1 && 0.0f <= t1 && s1 + t1 <= 1.0f)
	{
		outResult.t = t;
		outResult.p = p;
		outResult.n = n;
		outResult.material = material;

		return true;
	}

	return false;
}
