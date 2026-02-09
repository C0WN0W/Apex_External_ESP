#pragma once
#include <cstdint>
#include <Windows.h>
#include <math.h>
#include <vector>
#include <iostream>
#include <string>
#include <chrono>

struct Vector2 {
	float x, y;
};

class Vector3 {
public:
	Vector3();
	Vector3(float, float, float);
	~Vector3();

	float x, y, z;

	Vector3& operator+=(const Vector3& v) {
		x += v.x; y += v.y; z += v.z; return *this;
	}
	Vector3& operator-=(const Vector3& v) {
		x -= v.x; y -= v.y; z -= v.z; return *this;
	}
	Vector3& operator*=(float v) {
		x *= v; y *= v; z *= v; return *this;
	}
	bool operator==(const Vector3& v) {
		return (x == v.x) && (y == v.y);
	}
	Vector3 operator+(const Vector3& v) {
		return Vector3{ x + v.x, y + v.y, z + v.z };
	}
	Vector3 operator-(const Vector3& v) {
		return Vector3{ x - v.x, y - v.y, z - v.z };
	}
	Vector3 operator*(float fl) const {
		return Vector3(x * fl, y * fl, z * fl);
	}
	Vector3 operator*(const Vector3& v) const {
		return Vector3(x * v.x, y * v.y, z * v.z);
	}
	Vector3& operator/=(float fl) {
		x /= fl;
		y /= fl;
		z /= fl;
		return *this;
	}
	auto operator-(const Vector3& other) const -> Vector3 {
		auto buf = *this;

		buf.x -= other.x;
		buf.y -= other.y;
		buf.z -= other.z;

		return buf;
	}

	auto operator/(float other) const {
		Vector3 vec;
		vec.x = x / other;
		vec.y = y / other;
		vec.z = z / other;
		return vec;
	}

	float& operator[](int i) {
		return ((float*)this)[i];
	}
	float operator[](int i) const {
		return ((float*)this)[i];
	}
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

struct StrBuf32 {
	char buf[32];
};

struct Bone {
	BYTE shit[0xCC];
	float x;
	BYTE shit2[0xC];
	float y;
	BYTE shit3[0xC];
	float z;
};

struct Player {
	bool NPC;
	uint64_t Ptr;
	Vector3 Position;
	Vector3 Velocity;
	std::string Name;
	std::string SignifierName;
	int armorType;
	int Shield;
	int MaxShield;
	int Health;
	int TeamID;
	int XP;
	int Level;
	bool IsSpectator;
	bool IsValid;
	bool IsKnocked;
	bool IsVisible;
	int LifeState;
	float LastInCrosshairTime;
	float ToDistance;

	uint64_t WorldTimeBase;
};