#include <vector>
#include <array>
#include <cmath>
#include <Eigen/Dense>

using Eigen::Vector2d;

struct PixelColourBuffer
{
	std::vector<std::vector<uint8_t>> r;
	std::vector<std::vector<uint8_t>> g;
	std::vector<std::vector<uint8_t>> b;
};

struct RGB
{
	uint8_t r;
	uint8_t g;
	uint8_t b;
};

std::vector<double> interpolate(int32_t i0, double d0, int32_t i1, double d1);
void drawLine(Vector2d p0, Vector2d p1, PixelColourBuffer &pixelColourBuffer, RGB colours);
void drawWireTriangle(Vector2d p0, Vector2d p1, Vector2d p2, PixelColourBuffer& pixelColourBuffer, RGB colours);
void drawFilledTriangle(Vector2d p0, Vector2d p1, Vector2d p2, PixelColourBuffer& pixelColourBuffer, RGB colours);
void drawShadedTriangle(Vector2d p0, Vector2d p1, Vector2d p2, PixelColourBuffer& pixelColourBuffer, RGB colours, std::array<double, 3> h);
