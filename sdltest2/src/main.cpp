#include "SDL.h"
#include <stdio.h>
#include "Primitives/Primitive.h";
#include "Primitives/Sphere.h";
#include "Camera.h"
#include "Light.h"
#include <iostream>

//foward declare functions
void inline colorPixel(SDL_Renderer *renderer, Color *color, int x, int y);

int main(int argc, char* argv[]) {

	//define constants for window
	const int WIDTH = 600;
	const int HEIGHT = 600;

	//define # of subsamples per pixel (min is 1)
	//subsamples in x and y directions, so actual number of samples per pixel is SUB_SAMPLES squared
	const int SUB_SAMPLES = 2;

	//create window and renderer pointers
	SDL_Window *window;
	SDL_Renderer *renderer;

	//used for user input to close program
	SDL_Event event;

	//initialize SDL
	SDL_Init(SDL_INIT_VIDEO);

	//initialize window and renderer pointers
	SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, SDL_WINDOW_OPENGL, &window, &renderer);

	SDL_SetWindowTitle(window, "Raytracer");

	// Check that the window was successfully created
	if (window == NULL) {
		// In the case that the window could not be made...
		printf("Could not create window: %s\n", SDL_GetError());
		return 1;
	}

	//create our camera object
	//camera facing along x axis, positioned at origin
	Camera camera(Vec3(-1, 0, 0), Vec3(1, 0, 0), 1, WIDTH, HEIGHT);

	//Add spheres into scene
	const int NUM_SPHERES = 2;
	Sphere sphere1(Vec3(2, 0, 0), 0.5, Color(255, 255, 255)); //red sphere at (2, 0, 0), radius 1, color red
	Sphere sphere2(Vec3(5, 1, 0), 0.25, Color(125, 0, 0));
	Sphere spheres[NUM_SPHERES] = { sphere2, sphere1};

	//Add lights to the scene
	const int NUM_LIGHTS = 2;
	Light light1(Vec3(0, -2, 1), Color(255, 0, 0));
	Light light2(Vec3(0, 2, 1), Color(0, 255, 0));
	Light light3(Vec3(0, 0, -2), Color(0, 0, 255));

	Light lights[NUM_LIGHTS] = {light1, light2};

	//clear the screen to background color (black)
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);

	//iterate through every pixel on the screen
	for(int x = 0; x < WIDTH; x++)	{
		for(int y = 0; y < HEIGHT; y++) {

			//for every pixel do super sampling to average vall value surrounding pixel
			//to preform anti-aliasing
			Color colSum;
			for(int xS = 0 ; xS < SUB_SAMPLES; xS++) {
				for(int yS = 0; yS < SUB_SAMPLES; yS++) {
					//cast our ray
					Ray ray = camera.castRay(x + (1.0 / SUB_SAMPLES) * xS, y + (1.0 / SUB_SAMPLES) * yS);

					//iterate through the total number of objects in the scene (spheres)
					for(int S = 0; S < NUM_SPHERES; S++) {
						Color totalColor;
						bool normalNullPointer;
						//for each sphere, calculate lighting from all lights in scene where ray was casted
						for(int L = 0; L < NUM_LIGHTS; L++) {
							//get the intersection point, and spheres normal at intersection point
							auto hitData = spheres[S].intersectsRay(ray);
							Vec3 *normal = std::get<0>(hitData);
							Vec3 *intersect = std::get<1>(hitData);

							if(normal != nullptr) {
								//get angle between normal and vector from light to intersection
								Vec3 lightToHit = Primitive::Vec3Norm(*intersect + (lights[L].position * -1));
								float lightIntensity = Primitive::Vec3Dot(lightToHit, *normal);
								//get the absolute value of dot product, only get if < 0, which means vectors are facing each other
								float lightIntensityMag = (lightIntensity < 0) ? abs(lightIntensity) : 0;
								//calculate light based on spheres diffuse color, lights color, and intensity at point
								Color c = (lights[L].color * lightIntensityMag) + (spheres[S].color * lightIntensityMag);
								totalColor = totalColor + c;
								normalNullPointer = false;
							} else { normalNullPointer = true; }
						}
						//clamp our color into correct range (0-255)
						totalColor.clamp();
						if(!normalNullPointer) {
							//if there was an intersection at that point, sample that color, otherwise ignore it to preserve other detected hits and colors
							//(only overwrites hits that were behind current hit)
							colSum = colSum + totalColor;
						}
					}
				}
			}
			//average the colors
			colSum = colSum * (1.0 / (SUB_SAMPLES * SUB_SAMPLES));
			//clamp into correct range
			colSum.clamp();
			//render pixel
			colorPixel(renderer, &colSum, x, y);

		}
	}

	//draw image to screen
	SDL_RenderPresent(renderer);

	//wait until user exits program to quit
	while (1) {
		if (SDL_PollEvent(&event) && event.type == SDL_QUIT)
			break;
	}

	//cleanup mess
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	// Clean up
	SDL_Quit();
	return 0;
}

/**
 * Helper function for setting pixel color in image
 */
void inline colorPixel(SDL_Renderer *renderer, Color* color, int x, int y) {
	SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, color->a);
	SDL_RenderDrawPoint(renderer, x, y);
}
