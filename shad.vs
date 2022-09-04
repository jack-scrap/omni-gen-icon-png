#version 400

in vec3 pos;

uniform float scale;

void main() {
	gl_Position = vec4(vec3(pos.x, pos.y, 0.0) * vec3(scale), 1.0);
}
