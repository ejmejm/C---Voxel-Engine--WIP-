#include "src/utils/includes.h"

#define BATCH 1

#define WIDTH 960
#define HEIGHT 540

int main(){
	using namespace edan;
	using namespace graphics;
	using namespace math;
	
	Window window("Edan Engine", WIDTH, HEIGHT);
	//glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	mat4 ortho = mat4::perspective(67, WIDTH/HEIGHT, 0.1f, 20.0f); //NOTE: I think the far clipping plane is broken, it doesn't seem to affect anything

	Shader shader("src/shaders/basic.vert", "src/shaders/basic.frag");
	shader.enable();
	shader.setUniformMat4("pr_matrix", ortho);

	srand(time(NULL));
	

#if BATCH 1
	std::vector<Cube*> cubes;

	Batch3DRenderer renderer;

	for (float x = -10.0f; x < 10.0f; x += 1.0f)
	{
		for (float y = -5.0f; y < 1.0f; y += 1.0f)
		{
			for (float z = -10.0f; z < 10.0f; z += 1.0f)
			{
				cubes.push_back(new Cube(x, y, z, 1.0f, math::vec4((rand() % 1000 / 1000.0f), 0, 1, 1)));
			}
		}
	}
#else
	std::vector<StaticCube*> cubes;

	Simple3DRenderer renderer;

	for (float x = -5.0f; x < 5.0f; x += 0.2f)
	{
		cubes.push_back(new StaticCube(x, 0, 0, 0.2f, math::vec4((rand() % 1000 / 1000.0f), 0.1f, 1, 1), shader));
	}

#endif

	Camera camera(vec3(0.0f, 2.0f, 0.0f), 0.0f, 0.0f, 0.0f, shader);

	PointLight light(vec3(0.0f, 20.0f, 0.0f), vec4(1.0f, 1.0f, 1.0f, 1.0f), shader);
	light.render();

	Timer time;
	float timer = 0;
	double newTime, delta = 0;
	unsigned int frames = 0;

	double mousePosX, mousePosY;

	newTime = time.elapsed();

	while (!window.closed()){
		
		newTime = time.elapsed();

		window.clear();
		window.getMousePosition(mousePosX, mousePosY);
		window.deltaMouseUpdate();

		Movement::movementUpdate(window, camera, 8.0f, 150.0f, delta, window.getDeltaX(), window.getDeltaY());

		camera.updateView();

#if BATCH 1
		renderer.begin();

		for (int i = 0; i < cubes.size(); i++)
		{
			renderer.submit(cubes[i]);
		}

		renderer.end();
		renderer.flush();
#else
		for (int i = 0; i < cubes.size(); i++)
		{
			renderer.submit(cubes[i]);
		}

		renderer.flush();
#endif
		
		window.update();

		frames++;


		if (time.elapsed() - timer > 1.0f)
		{
			timer += 1.0f;
			printf("%d fps\n", frames);
			frames = 0;
		}

		delta = time.elapsed() - newTime;
	}

	for (int i = 0; i < cubes.size(); i++)
	{
		delete cubes[i];
	}

	return(0);
}