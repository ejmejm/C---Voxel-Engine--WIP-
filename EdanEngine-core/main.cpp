#include "src/utils/includes.h"

#define WIDTH 960
#define HEIGHT 540

int main(){
	using namespace edan;
	using namespace graphics;
	using namespace math;
	
	Window window("Edan Engine", WIDTH, HEIGHT);
	//glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	mat4 ortho = mat4::perspective(67, WIDTH/HEIGHT, 0.1f, 3.0f); //NOTE: I think the far clipping plane is broken, it doesn't seem to affect anything

	Shader shader("src/shaders/basic.vert", "src/shaders/basic.frag");
	shader.enable();
	shader.setUniformMat4("pr_matrix", ortho);

	srand(time(NULL));
	
	std::vector<Cube*> cubes;

	Batch3DRenderer renderer;

	for (float x = -2.0f; x < 2.0f; x += 0.2f)
	{
		for (float y = -0.6f; y < 0.6f; y += 0.2f)
		{
			for (float z = -2.0f; z < 2.0f; z += 0.2f)
			{
				cubes.push_back(new Cube(x, y, z, 0.2f, math::vec4((rand() % 1000 / 1000.0f), 0, 1, 1)));
			}
		}
	}

	Camera camera(vec3(0.0f, 1.4f, 0.0f), 0.0f, 0.0f, 0.0f, shader);

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

		Movement::movementUpdate(window, camera, 2.0f, delta, window.getDeltaX(), window.getDeltaY());

		camera.updateView();

		renderer.begin();

		for (int i = 0; i < cubes.size(); i++)
		{
			renderer.submit(cubes[i]);
		}

		renderer.end();
		renderer.flush();
		
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