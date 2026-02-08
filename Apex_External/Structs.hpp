#pragma once
#include <cstdint>

struct Vector2 {
	float x, y;
};

struct Vector3 {
	float x, y, z;
};

struct Matrix {
	float matrix[16];
};

class Matrix3x4
{
public:
	union
	{
		struct
		{
			float _11, _12, _13, _14;
			float _21, _22, _23, _24;
			float _31, _32, _33, _34;
		};

		float m[3][4];
		float mm[12];
	};
};

struct Bone {
	BYTE shit[0xCC];
	float x;
	BYTE shit2[0xC];
	float y;
	BYTE shit3[0xC];
	float z;
};