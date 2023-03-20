#include <vector>

struct Colour
{
	std::vector<std::vector<uint8_t>> r;
	std::vector<std::vector<uint8_t>> g;
	std::vector<std::vector<uint8_t>> b;
};

void drawLine(
	int16_t x0,
	int16_t y0,
	int16_t x1,
	int16_t y1,
	std::vector<std::vector<std::vector<uint8_t>>>& colour
);

void drawLineLow(
	int16_t x0,
	int16_t y0,
	int16_t x1,
	int16_t y1,
	std::vector<std::vector<std::vector<uint8_t>>>& colour
);

void drawLineHigh(
	int16_t x0,
	int16_t y0,
	int16_t x1,
	int16_t y1,
	std::vector<std::vector<std::vector<uint8_t>>>& colour
);
