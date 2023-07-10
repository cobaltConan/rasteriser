#pragma once

#include <stdexcept>
#include <vector>
#include "../../libs/eigen/Eigen/Dense"
#include "linearAlgebra.h"

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

struct sceneInfo
{
    int64_t screenWidth;
    int64_t screenHeight;
    double cameraDistance;
    double viewportWidth;
    double viewportHeight;
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
    Eigen::Matrix4d htm; // homogenous transformation matrix
    Eigen::Matrix4d hrm; // homogenous rotation matrix
    Eigen::Matrix4d hsm; // homogenous scale matrix
    
    instance();
    void setPosition(const Vector3d& posVec);
    void setRotation(const Vector3d& rotVec);
    void setScale(const Vector3d& scaleVec);
	cube returnModel();
};


class scene
{
public:
	std::vector<instance> instances;
	void addInstance(const instance& inst);
};


class cameraInfo
{
public:
    Eigen::Matrix4d ihtm; // inverse homogenous transformation matrix;
    Eigen::Matrix4d ihrm; // inverse homogenous rotation matrix;

    cameraInfo();
    void setPosition(const Vector3d& posVec);
    void setRotation(const Vector3d& rotVec);
};
