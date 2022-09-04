#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "disp.h"
#include "prog.h"
#include "util.h"

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
	Prog prog("shad", "shad");

	// initialize
	prog.use();

	/// attribute
	GLint attrPos = glGetAttribLocation(prog._id, "pos");
	glVertexAttribPointer(attrPos, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*) 0);
	glEnableVertexAttribArray(attrPos);

	/// uniform
	GLint uniRes = glGetUniformLocation(prog._id, "res");
	glUniform2fv(uniRes, 2, glm::value_ptr(res));

	prog.unUse();

	SDL_Event e;
	while (disp.open) {
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				SDL_Quit();
			}
		}

		disp.clear(0, 0, 0, 1);

		glBindVertexArray(vao);

		glDrawElements(GL_TRIANGLES, sizeof idc, GL_UNSIGNED_SHORT, (GLvoid*) 0);

		glBindVertexArray(0);

		disp.update();
	}

	glDeleteBuffers(1, &vao);
	glDeleteBuffers(1, &vbo);
}
