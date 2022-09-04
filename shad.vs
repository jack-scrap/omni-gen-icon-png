#version 400

in vec3 pos;

uvec2 res = uvec2(128, 128);

float ratio = float(res.x) / float(res.y);

void main() {
	gl_Position = vec4(vec3(pos.x / ratio, pos.y, 0.0), 1.0);
}
