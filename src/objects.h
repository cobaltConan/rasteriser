#pragma once

#include <vector>
#include "../../libs/eigen/Eigen/Dense"

using Eigen::Vector2d;
using Eigen::Vector3d;

enum class graphicalObject { cube };

struct RGB
{
	uint8_t r;
	uint8_t g;
	uint8_t b;
};

struct Triangle
{
	int32_t v0;
	int32_t v1;
	int32_t v2;
	RGB colour;
};


#define RED RGB{255, 0, 0}
#define GREEN RGB{0, 255, 0}
#define BLUE RGB{0, 0, 255}
#define YELLOW RGB{255, 255, 0}
#define PURPLE RGB{255, 0, 255}
#define CYAN RGB{0, 255, 255}


class cube
{
public:
	cube();
	std::vector<Vector3d> verticies;
	std::vector<Triangle> triangles;
};


class instance
{
public:
	graphicalObject model;
	Vector3d position;
	Vector3d rotation;

	cube returnModel();
};


class scene
{
public:
	std::vector<instance> instances;
	void addInstance(const instance& inst);
};
