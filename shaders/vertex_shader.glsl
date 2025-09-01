#version 330 core
layout(location = 0) in vec3 aPos;

uniform vec2 offset;


out vec2 localPos;

void main() {
    vec2 worldPos = aPos.xy + offset;
    localPos = aPos.xy; // in-cell position
    gl_Position = vec4(worldPos, 0.0, 1.0);
}
