#include <raylib.h>

#define WIDTH 1920
#define HEIGHT 1280

int main(void)
{
	InitWindow(WIDTH, HEIGHT, "DANDD");
	int l = MeasureText("Hello World", 20);

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(WHITE);
		DrawText("Hello World", (WIDTH + l) / 2, HEIGHT / 2, 20, BLACK);
		EndDrawing();
	}
	CloseWindow();

	return (0);
}
