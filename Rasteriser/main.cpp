#include <graphics.h>
#include <SDL.h>
#include <Eigen/Dense>
#include <iostream>
#include <vector>
#include <array>
#include <stdexcept>
#include <algorithm>

#undef main
int main()
{
	// Testing area

	#define RED RGB{255, 0, 0}
	#define GREEN RGB{0, 255, 0}
	#define BLUE RGB{0, 0, 255}
	#define YELLOW RGB{255, 255, 0}
	#define PURPLE RGB{255, 0, 255}
	#define CYAN RGB{0, 255, 255}

	scene theScene{};

	instance inst1{};
	inst1.model = graphicalObject::cube;
	inst1.position = Vector3d(3, 1, 7.5);
	inst1.rotation = Vector3d(90.0, 110.0, 90.0);

	instance inst2{};
	inst2.model = graphicalObject::cube;
	inst2.position = Vector3d(-3, -2, 15);
	inst2.rotation = Vector3d(0, 0, 0);

	bool moveFlag{ true };

	theScene.addInstance(inst1);
	theScene.addInstance(inst2);

	// End of testing area
	
	double camDistance = 1;
	constexpr int16_t width{ 1600 };
	constexpr int16_t height{ 800 };
	PixelColourBuffer pixelColourBuffer{}; // r g b values for all the pixels on the screen
	uint32_t pixelColour{}; // for putting the channels into
	bool isRunning = true;
	SDL_Event event{};

	// setting the colour channel sizes to the screen size
	pixelColourBuffer.r.resize(height, std::vector<uint8_t>(width, 0));
	pixelColourBuffer.g.resize(height, std::vector<uint8_t>(width, 0));
	pixelColourBuffer.b.resize(height, std::vector<uint8_t>(width, 0));

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		return false;
	}

	auto *pWindow = SDL_CreateWindow("El Rasteriser", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);

	if (!pWindow)
		throw std::invalid_argument("pWindow is NULL");

	auto *pRenderer = SDL_CreateRenderer(pWindow, -1, 0);

	if (!pRenderer)
		throw std::invalid_argument("pRenderer is NULL");

	uint32_t rmask{}, gmask{}, bmask{}, amask{};

	#if SDL_BYTEORDER == BIG_ENDIAN
	rmask = 0xff000000;
	gmask = 0x00ff0000;
	bmask = 0x0000ff00;
	amask = 0x000000ff;
	#else
	rmask = 0x000000ff;
	gmask = 0x0000ff00;
	bmask = 0x00ff0000;
	amask = 0xff000000;
	#endif

	auto *tempSurface = SDL_CreateRGBSurface(0, width, height, 32, rmask, gmask, bmask, amask);
	auto *pTexture = SDL_CreateTextureFromSurface(pRenderer, tempSurface);
	SDL_FreeSurface(tempSurface);

	while (isRunning)
	{
		while (SDL_PollEvent(&event) != 0)
		{
			if (event.type == SDL_QUIT)
			{
				isRunning = false;
			}
		}

		// set background colour
		//SDL_SetRenderDrawColor(pRenderer, 255, 255, 0, 255);
		//SDL_RenderClear(pRenderer);

		theScene.instances.at(0).rotation.x() += 0.03;
		theScene.instances.at(0).rotation.y() += 0.06;
		theScene.instances.at(0).rotation.z() += 0.09;

		theScene.instances.at(1).rotation.z() += 0.01;

		if (theScene.instances.at(0).position.x() > 3)
			moveFlag = true;
		else if (theScene.instances.at(0).position.x() < -3)
			moveFlag = false;

		if (moveFlag)
			theScene.instances.at(0).position.x() -= 0.1;
		else
			theScene.instances.at(0).position.x() += 0.1;

		renderScene(theScene, pixelColourBuffer, width, height, camDistance);

		uint32_t* tempPixels = new uint32_t[height * width];
		memset(tempPixels, 0, width * height * sizeof(uint32_t));

		for (int y{}; y < height; ++y)
		{
			for (int x{}; x < width; ++x)
			{
				pixelColour = (255 << 24) + (pixelColourBuffer.r.at(y).at(x) << 16) + (pixelColourBuffer.g.at(y).at(x) << 8) + pixelColourBuffer.b.at(y).at(x);
				tempPixels[(y * width) + x] = pixelColour;
			}
		}

		SDL_UpdateTexture(pTexture, NULL, tempPixels, width * sizeof(uint32_t));
		
		delete[] tempPixels;
		
		for (int i{}; i < pixelColourBuffer.r.size(); ++i)
		{
			std::fill(pixelColourBuffer.r.at(i).begin(), pixelColourBuffer.r.at(i).end(), 0);
			std::fill(pixelColourBuffer.g.at(i).begin(), pixelColourBuffer.g.at(i).end(), 0);
			std::fill(pixelColourBuffer.b.at(i).begin(), pixelColourBuffer.b.at(i).end(), 0);
		}

		// copying texture to the renderer
		SDL_Rect srcRect{}, bounds{};
		srcRect.x = 0;
		srcRect.y = 0;
		srcRect.w = width;
		srcRect.h = height;
		bounds = srcRect;
		SDL_RenderCopy(pRenderer, pTexture, &srcRect, &bounds);

		// render to screen
		SDL_RenderPresent(pRenderer);
	}

	// tidy up
	SDL_DestroyRenderer(pRenderer);
	SDL_DestroyWindow(pWindow);
	pWindow = NULL;
	SDL_Quit();
	return 0;
}