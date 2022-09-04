#version 400

in vec3 pos;

void main() {
	gl_Position = vec4(vec3(pos.x, pos.y, 0.0), 1.0);
}
