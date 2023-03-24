#include <graphics.h>

std::vector<double> interpolate(int32_t i0, double d0, int32_t i1, double d1)
{
	// function to interpolate between two points. one of the coordinates is in integers as dealing with pixels

	std::vector<double> d_vec{};
	double grad{};
	double d{};

	if (i0 == i1)
	{
		d_vec.emplace_back(d0);
		return d_vec;
	}

	grad = (d1 - d0) / (static_cast<double>(i1) - static_cast<double>(i0)); // finding the gradient for interpolation
	d = d0;

	for (int i{ i0 }; i <= i1; ++i) // for loop finds related d value for every i value
	{
		d_vec.emplace_back(d);
		d = d + grad;
	}

	return d_vec;
}


void drawLine(Vector2d p0, Vector2d p1, PixelColourBuffer &pixelColourBuffer, RGB colours)
{
	if (abs(p1.x() - p0.x()) > abs(p1.y() - p0.y()))
	{
		// gradient is less than 1
		if (p0.x() > p1.x())
		{
			Vector2d temp{ p1 };
			p1 = p0;
			p0 = temp;
		}
		
		int32_t x0{ static_cast<int32_t>(p0.x()) };
		int32_t x1{ static_cast<int32_t>(p1.x()) };
		std::vector<double> ys{ interpolate(x0, p0.y(), x1, p1.y()) };

		for (int x{ x0 }; x <= x1; ++x)
		{
			int32_t y{ static_cast<int32_t>(std::round(ys.at(x - x0))) }; // converts y value in ys vec to int
			pixelColourBuffer.r.at(y).at(x) = colours.r;
			pixelColourBuffer.g.at(y).at(x) = colours.g;
			pixelColourBuffer.b.at(y).at(x) = colours.b;
		}
	}

	else
	{
		// gradient is greater than 1
		if (p0.y() > p1.y())
		{
			Vector2d temp{ p1 };
			p1 = p0;
			p0 = temp;
		}

		int32_t y0{ static_cast<int32_t>(p0.y()) };
		int32_t y1{ static_cast<int32_t>(p1.y()) };
		std::vector<double> xs{ interpolate(y0, p0.x(), y1, p1.x()) };

		for (int y{ y0 }; y <= y1; ++y)
		{
			int32_t x{ static_cast<int32_t>(std::round(xs.at(y - y0))) }; // converts y value in ys vec to int
			pixelColourBuffer.r.at(y).at(x) = colours.r;
			pixelColourBuffer.g.at(y).at(x) = colours.g;
			pixelColourBuffer.b.at(y).at(x) = colours.b;
		}
	}
}


void drawWireTriangle(Vector2d p0, Vector2d p1, Vector2d p2, PixelColourBuffer &pixelColourBuffer, RGB colours)
{
	drawLine(p0, p1, pixelColourBuffer, colours);
	drawLine(p1, p2, pixelColourBuffer, colours);
	drawLine(p2, p0, pixelColourBuffer, colours);
}


void drawFilledTriangle(Vector2d p0, Vector2d p1, Vector2d p2, PixelColourBuffer& pixelColourBuffer, RGB colours)
{
	Vector2d temp{};

	// sorting points so that y0 <= y1 <= y2
	if (p1.y() < p0.y())
	{
		temp = p1;
		p1 = p0;
		p0 = temp;
	}

	if (p2.y() < p0.y())
	{
		temp = p2;
		p2 = p0;
		p0 = temp;
	}

	if (p2.y() < p1.y())
	{
		temp = p2;
		p2 = p1;
		p1 = temp;
	}

	// computing x coordinates of triangle edges
	int32_t y0{ static_cast<int32_t>(p0.y()) };
	int32_t y1{ static_cast<int32_t>(p1.y()) };
	int32_t y2{ static_cast<int32_t>(p2.y()) };

	std::vector<double> x01{ interpolate(y0, p0.x(), y1, p1.x()) };
	std::vector<double> x12{ interpolate(y1, p1.x(), y2, p2.x()) };
	std::vector<double> x02{ interpolate(y0, p0.x(), y2, p2.x()) };

	// concatenating non-hypotenuse sides
	x01.pop_back();
	std::vector<double> x012{ x01.begin(), x01.end() };
	x012.insert(x012.end(), x12.begin(), x12.end());
	
	uint16_t m{};
	std::vector<double> x_left{};
	std::vector<double> x_right{};
	m = static_cast<uint16_t>(floor(x012.size() / 2));

	if (x02.at(m) < x012.at(m))
	{
		x_left = x012;
		x_right = x02;
	}
	else
	{
		x_left = x012;
		x_right = x02;
	}

	// drawing horizontal segments of triangle
	for (int y{ y0 }; y <= y2; ++y)
	{
		for (int x{ static_cast<int32_t>(std::round(x_left.at(y - y0))) }; x <= static_cast<int32_t>(std::round(x_right.at(y - y0))); ++x)
		{
			pixelColourBuffer.r.at(y).at(x) = colours.r;
			pixelColourBuffer.g.at(y).at(x) = colours.g;
			pixelColourBuffer.b.at(y).at(x) = colours.b;
		}
	}
}


void drawShadedTriangle(Vector2d p0, Vector2d p1, Vector2d p2, PixelColourBuffer& pixelColourBuffer, RGB colours, std::array<double, 3> h)
{	
	Vector2d temp{};

	// sorting points so that y0 <= y1 <= y2
	if (p1.y() < p0.y())
	{
		temp = p1;
		p1 = p0;
		p0 = temp;
	}

	if (p2.y() < p0.y())
	{
		temp = p2;
		p2 = p0;
		p0 = temp;
	}

	if (p2.y() < p1.y())
	{
		temp = p2;
		p2 = p1;
		p1 = temp;
	}

	// computing x coordinates of triangle edges
	int32_t y0{ static_cast<int32_t>(p0.y()) };
	int32_t y1{ static_cast<int32_t>(p1.y()) };
	int32_t y2{ static_cast<int32_t>(p2.y()) };

	std::vector<double> x01{ interpolate(y0, p0.x(), y1, p1.x()) };
	std::vector<double> h01{ interpolate(y0, h.at(0), y1, h.at(1)) };

	std::vector<double> x12{ interpolate(y1, p1.x(), y2, p2.x()) };
	std::vector<double> h12{ interpolate(y1, h.at(1), y2, h.at(2)) };

	std::vector<double> x02{ interpolate(y0, p0.x(), y2, p2.x()) };
	std::vector<double> h02{ interpolate(y0, h.at(0), y2, h.at(2)) };

	// concatenating non-hypotenuse sides
	x01.pop_back();
	std::vector<double> x012{ x01.begin(), x01.end() };
	x012.insert(x012.end(), x12.begin(), x12.end());

	// doing the same for the shading values
	h01.pop_back();
	std::vector<double> h012{ h01.begin(), h01.end() };
	h012.insert(h012.end(), h12.begin(), h12.end());
	
	uint16_t m{};
	std::vector<double> x_left{};
	std::vector<double> x_right{};
	std::vector<double> h_left{};
	std::vector<double> h_right{};
	m = static_cast<uint16_t>(floor(x012.size() / 2));

	if (x02.at(m) < x012.at(m))
	{
		x_left = x012;
		h_left = h02;

		x_right = x02;
		h_right = h012;
	}
	else
	{
		x_left = x012;
		h_left = h012;
		
		x_right = x02;
		h_right = h02;
	}

	std::vector<double> h_segment{};
	int32_t x_l{};
	int32_t x_r{};

	// drawing horizontal segments of triangle
	for (int y{ y0 }; y <= y2; ++y)
	{
		x_l = static_cast<int32_t>(std::round(x_left.at(y - y0)));
		x_r = static_cast<int32_t>(std::round(x_right.at(y - y0)));

		h_segment = interpolate(x_l, h_left.at(y - y0), x_r, h_right.at(y - y0));
		
		for (int32_t x{x_l}; x <= x_r; ++x)
		{
			pixelColourBuffer.r.at(y).at(x) = static_cast<uint8_t>(std::round(static_cast<double>(colours.r) * h_segment.at(x - x_l)));
			pixelColourBuffer.g.at(y).at(x) = static_cast<uint8_t>(std::round(static_cast<double>(colours.g) * h_segment.at(x - x_l)));
			pixelColourBuffer.b.at(y).at(x) = static_cast<uint8_t>(std::round(static_cast<double>(colours.b) * h_segment.at(x - x_l)));
		}
	}

}
