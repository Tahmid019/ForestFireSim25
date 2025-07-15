#version 330 core

in vec2 localPos;
out vec4 FragColor;

uniform vec2 borderThickness;
uniform vec2 cellSize;

void main() {
    bool onBorder = 
        localPos.x <= borderThickness.x ||
        localPos.y <= borderThickness.y ||
        localPos.x >= (cellSize.x - borderThickness.x) ||
        localPos.y >= (cellSize.y - borderThickness.y);

    if (onBorder) {
        FragColor = vec4(0.0, 0.0, 1.0, 1.0); // 🔵 Blue border
    } else {
        discard; // Transparent inside
    }
}
