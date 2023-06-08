
//#include<gl/GL.h>
#include<SDL_opengl.h>
#include<GL/GLU.h>
#include<algorithm>
#include<functional>
#include<vector>
#include <GLFW/glfw3.h>
#include <cstdlib>
#include <ctime>

float X1 = 0.0f;
float X2 = 0.0f;
float X3 = 0.0f;
float X4 = 0.0f;

float red = 1.0f;
float green = 1.0f;
float blue = 1.0f;

const int WIDTH = 100;
const int HEIGHT = 100;

int TIME = 100;


bool cells[WIDTH][HEIGHT];
bool newCells[WIDTH][HEIGHT];

// Inicializar el autómata celular con un estado aleatorio


void start();

void updateCells() {
	for (int x = 0; x < WIDTH; ++x) {
		for (int y = 0; y < HEIGHT; ++y) {
			int aliveNeighbors = 0;
			for (int dx = -1; dx <= 1; ++dx) {
				for (int dy = -1; dy <= 1; ++dy) {
					int t = 0;
					for (int a = 0; a < TIME; a++) {
						t += 1;
					}
					if (dx == 0 && dy == 0) continue;
					int nx = x + dx;
					int ny = y + dy;
					if (nx < 0 || ny < 0 || nx >= WIDTH || ny >= HEIGHT) continue;
					if (cells[nx][ny]) ++aliveNeighbors;
				}
			}
			newCells[x][y] = (aliveNeighbors == 3) || (cells[x][y] && aliveNeighbors == 2);
		}
	}
	std::swap(cells, newCells);
}

void renderCells() {
	//glColor3f(red, green, blue);
	glBegin(GL_QUADS);
	for (int x = 0; x < WIDTH; ++x) {
		for (int y = 0; y < HEIGHT; ++y) {
			if (cells[x][y]) {
				glColor3f(float(float(x)/100), float(float(y)/100),0.0f);
				glVertex2f((x / float(WIDTH)) - 0.50f + X1, (y / float(HEIGHT)) - 0.50f + X1);
				glVertex2f(((x + 1) / float(WIDTH)) - 0.50f + X2, (y / float(HEIGHT)) - 0.50f + X2);
				glVertex2f(((x + 1) / float(WIDTH)) - 0.50f + X3, ((y + 1) / float(HEIGHT)) - 0.50f + X3);
				glVertex2f((x / float(WIDTH)) - 0.50f + X4, ((y + 1) / float(HEIGHT)) - 0.50f + X4);
			}
		}
	}
	glEnd();
}

// Función de teclado para cambiar el color del triángulo
void keyboardFunc(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (action == GLFW_PRESS) {
		switch (key) {
		case GLFW_KEY_R:
			red = 1.0f;
			green = 0.0f;
			blue = 0.0f;
			break;
		case GLFW_KEY_G:
			red = 0.0f;
			green = 1.0f;
			blue = 0.0f;
			break;
		case GLFW_KEY_B:
			red = 0.0f;
			green = 0.0f;
			blue = 1.0f;
			break;
		case GLFW_KEY_W:
			red = 1.0f;
			green = 1.0f;
			blue = 1.0f;
			break;
		case GLFW_KEY_Y:
			red = 1.0f;
			green = 1.0f;
			blue = 0.0f;
			break;
		case GLFW_KEY_1:
			TIME = 400;
			break;
		case GLFW_KEY_2:
			TIME = 600;
			break;
		case GLFW_KEY_3:
			TIME = 800;
			break;
		case GLFW_KEY_4:
			TIME = 1000;
			break;
		case GLFW_KEY_U:
			X1 = 0.1f;
			X1 = 0.0f;
			X1 = 0.0f;
			X1 = 0.0f;
			break;
		case GLFW_KEY_I:
			X2 = 0.1f;
			X1 = 0.0f;
			X3 = 0.0f;
			X4 = 0.0f;
			break;
		case GLFW_KEY_O:
			X3 = 0.1f;
			X1 = 0.0f;
			X2 = 0.0f;
			X4 = 0.0f;
			break;
		case GLFW_KEY_P:
			X4 = 0.1f;
			X1 = 0.0f;
			X2 = 0.0f;
			X3 = 0.0f;
			break;
		case GLFW_KEY_SPACE:
			start();
			break;
		case GLFW_KEY_Q:
			glfwSetWindowShouldClose(window, GLFW_TRUE);
			break;
		default:
			break;
		}

		glfwSwapBuffers(window);
	}
}

void start() {
	for (int x = 0; x < WIDTH; ++x) {
		for (int y = 0; y < HEIGHT; ++y) {
			cells[x][y] = rand() % 2;
		}
	}

	srand(time(NULL));
}

int main() {

	start();

	// Inicializar GLFW
	if (!glfwInit()) {
		return -1;
	}

	// Crear una ventana
	GLFWwindow* window = glfwCreateWindow(1000, 1000, "Game of Life", NULL, NULL);
	if (!window) {
		glfwTerminate();
		return -1;
	}

	// Hacer el contexto de la ventana actual
	glfwMakeContextCurrent(window);

	// Inicializar el autómata celular
	for (int x = 0; x < WIDTH; ++x) {
		for (int y = 0; y < HEIGHT; ++y) {
			cells[x][y] = rand() % 2;
		}
	}

	glfwSetKeyCallback(window, keyboardFunc);

	// Bucle de renderizado
	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT);

		updateCells();
		renderCells();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

