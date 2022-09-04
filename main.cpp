#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "disp.h"
#include "prog.h"
#include "util.h"

const float scale = (1.0 - -1.0) / (0.26 - -0.26);

bool scr(std::string filepath, SDL_Window* SDLWindow, SDL_Renderer* SDLRenderer) {
	SDL_Surface* saveSurface = NULL;
	SDL_Surface* infoSurface = NULL;
	infoSurface = SDL_GetWindowSurface(SDLWindow);

	if (infoSurface == NULL) {
		std::cerr << "Failed to create info surface from window in save(string), SDL_GetError() - " << SDL_GetError() << "\n";
	} else {
		unsigned char* pixels = new (std::nothrow) unsigned char[infoSurface->w * infoSurface->h * infoSurface->format->BytesPerPixel];
		if (!pixels) {
			std::cerr << "Unable to allocate memory for screenshot pixel data buffer!\n";

			return false;
		} else {
			if (SDL_RenderReadPixels(SDLRenderer, &infoSurface->clip_rect, infoSurface->format->format, pixels, infoSurface->w * infoSurface->format->BytesPerPixel) != 0) {
				std::cerr << "Failed to read pixel data from SDL_Renderer object. SDL_GetError() - " << SDL_GetError() << "\n";

				delete[] pixels;

				return false;
			} else {
				saveSurface = SDL_CreateRGBSurfaceFrom(pixels, infoSurface->w, infoSurface->h, infoSurface->format->BitsPerPixel, infoSurface->w * infoSurface->format->BytesPerPixel, infoSurface->format->Rmask, infoSurface->format->Gmask, infoSurface->format->Bmask, infoSurface->format->Amask);

				if (saveSurface == NULL) {
					std::cerr << "Couldn't create SDL_Surface from renderer pixel data. SDL_GetError() - " << SDL_GetError() << "\n";

					delete[] pixels;

					return false;
				}

				SDL_SaveBMP(saveSurface, filepath.c_str());
				SDL_FreeSurface(saveSurface);
				saveSurface = NULL;
			}

			delete[] pixels;
		}

		SDL_FreeSurface(infoSurface);
		infoSurface = NULL;
	}

	return true;
}

int main(int argc, char* argv[]) {
	if (argc == 1) {
		std::cout << "Error: No arguments" << std::endl;

		return 1;
	}

	if (argc != 1 + 1) {
		std::cout << "Error: Wrong number of arguments" << std::endl;

		return 1;
	}

	int dim = atoi(argv[1]);

	glm::vec2 res = glm::vec2(dim, dim);

	Disp disp("asdf", res[0], res[1]);

	// data
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// position
	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	GLfloat vtc[] = {
		-0.26, -0.26, 0.0,
		0.16, -0.26, 0.0,
		-0.10, -0.10, 0.0,

		0.06, -0.10, 0.0,
		0.16, -0.26, 0.0,
		0.26, -0.16, 0.0,

		0.06, -0.10, 0.0,
		0.10, -0.06, 0.0,
		0.26, -0.16, 0.0,

		0.26, 0.26, 0.0,
		0.10, -0.06, 0.0,
		0.10, 0.10, 0.0,

		0.26, 0.26, 0.0,
		-0.16, 0.26, 0.0,
		0.10, 0.10, 0.0,

		-0.06, 0.10, 0.0,
		-0.16, 0.26, 0.0,
		-0.26, 0.16, 0.0,

		-0.06, 0.10, 0.0,
		-0.10, 0.06, 0.0,
		-0.10, 0.06, 0.0,

		-0.26, 0.16, 0.0,
		-0.10, -0.10, 0.0,
		-0.26, -0.26, 0.0
	};
	glBufferData(GL_ARRAY_BUFFER, sizeof vtc, vtc, GL_STATIC_DRAW);

	GLuint ibo;
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

	GLushort idc[] = {
		0, 1, 2,

		2, 1, 3,

		4, 5, 6,

		6, 5, 7,

		8, 9, 10,

		10, 9, 11,

		12, 13, 14,

		14, 13, 15,

		16, 17, 18,

		18, 17, 19,

		20, 21, 22,

		22, 21, 23
	};
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof idc, idc, GL_STATIC_DRAW);

	// shader
	Prog prog("logo", "solid");

	// initialize
	prog.use();

	/// attribute
	GLint attrPos = glGetAttribLocation(prog._id, "pos");
	glVertexAttribPointer(attrPos, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*) 0);
	glEnableVertexAttribArray(attrPos);

	/// uniform
	GLint uniScale = glGetUniformLocation(prog._id, "scale");
	glUniform1f(uniScale, scale);

	prog.unUse();

	// draw
	disp.clear(0, 0, 0, 1);

	glBindVertexArray(vao);
	prog.use();

	glDrawElements(GL_TRIANGLES, sizeof idc, GL_UNSIGNED_SHORT, (GLvoid*) 0);

	prog.unUse();
	glBindVertexArray(0);

	disp.update();

	scr("icon.bmp", disp.win, disp.rend);

	glDeleteBuffers(1, &vao);
	glDeleteBuffers(1, &vbo);

	return 0;
}
