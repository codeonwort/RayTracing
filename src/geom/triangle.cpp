#include "triangle.h"
#include "src/material.h"

// http://geomalgorithms.com/a06-_intersect-2.html
bool Triangle::Hit(const ray& r, float t_min, float t_max, HitResult& outResult) const
{
	float paramU, paramV;

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

	paramU = (uv * wv - vv * wu) / (uvuv - uuvv);
	paramV = (uv * wu - uu * wv) / (uvuv - uuvv);

	if (0.0f <= paramU && 0.0f <= paramV && paramU + paramV <= 1.0f)
	{
		outResult.t = t;
		outResult.p = p;
		outResult.n = n;
		outResult.paramU = (1 - paramU - paramV) * s0 + paramU * s1 + paramV * s2;
		outResult.paramV = (1 - paramU - paramV) * t0 + paramU * t1 + paramV * t2;
		outResult.material = material;

		return true;
	}

	return false;
}

void Triangle::GetVertices(vec3& outV0, vec3& outV1, vec3& outV2) const
{
	outV0 = v0;
	outV1 = v1;
	outV2 = v2;
}

void Triangle::SetVertices(const vec3& inV0, const vec3& inV1, const vec3& inV2)
{
	v0 = inV0;
	v1 = inV1;
	v2 = inV2;
	UpdateNormal();
}
