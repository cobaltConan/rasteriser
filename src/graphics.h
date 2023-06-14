#pragma once

#include "objects.h"
#include <vector>
#include <array>
#include <cmath>
#include "../../libs/eigen/Eigen/Dense"
#include <cmath>
#include <iostream>

using Eigen::Vector2d;
using Eigen::Vector3d;

struct PixelColourBuffer
{
	std::vector<std::vector<uint8_t>> r;
	std::vector<std::vector<uint8_t>> g;
	std::vector<std::vector<uint8_t>> b;
};


std::vector<double> interpolate(int32_t i0, double d0, int32_t i1, double d1);
void drawLine(Vector2d p0, Vector2d p1, PixelColourBuffer &pixelColourBuffer, RGB colours);
void drawWireTriangle(Vector2d p0, Vector2d p1, Vector2d p2, PixelColourBuffer& pixelColourBuffer, RGB colours);
void drawFilledTriangle(Vector2d p0, Vector2d p1, Vector2d p2, PixelColourBuffer& pixelColourBuffer, RGB colours);
void drawShadedTriangle(Vector2d p0, Vector2d p1, Vector2d p2, PixelColourBuffer& pixelColourBuffer, RGB colours, std::array<double, 3> h);
Vector2d viewportToCanvas(Vector2d point, const sceneInfo& sceneInfo);
Vector2d projectVertex(Vector3d vert, const sceneInfo& sceneInfo);
void renderObject(std::vector<Vector3d> verticies, std::vector<Triangle> triangles, PixelColourBuffer& pixelColourBuffer, const sceneInfo& sceneInfo);
void renderTriangle(Triangle triangle, std::vector<Vector2d> projectedVerticies, PixelColourBuffer& pixelColourBuffer);
void renderInstance(instance instance, PixelColourBuffer& pixelColourBuffer, const sceneInfo& sceneinfo, const cameraInfo& cameraInfo);
void renderScene(scene scene, PixelColourBuffer& pixelColourBuffer, const sceneInfo& sceneInfo, const cameraInfo& cameraInfo);
void calcRotMatrix(Eigen::Matrix4d& hrm, const Vector3d& rotVec);
void calcInverseRotMatrix(Eigen::Matrix4d& hrm, const Vector3d& rotVec);
void calcProjectionMatrix(const sceneInfo& sceneInfo, Eigen::Matrix<double, 3, 4>& projectionMatrix);
