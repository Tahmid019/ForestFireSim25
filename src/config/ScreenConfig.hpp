#define HEIGHT 900
#define WIDTH 1200

int W = 80; int H = 60;
float cellwidth = 2.0f / W;
float cellheight = 2.0f / H;

float vertices[] = {
        0.0f, 0.0f, 0.0f,
        cellwidth, 0.0f, 0.0f,
        cellwidth, cellheight, 0.0f,

        0.0f, 0.0f, 0.0f,
        0.0f, cellheight, 0.0f,
        cellwidth, cellheight, 0.0f,
};