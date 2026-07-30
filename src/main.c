#include <raylib.h>
#include <stdbool.h>
#include <stdlib.h>

#define WIN_W 1920
#define WIN_H 1280
#define TILE_SIZE 20

typedef enum e_tile
{
	TILE_FLOOR = 0,
	TILE_WALL = 1,
	TILE_PLAYER = 2
} t_tile;

typedef struct s_size
{
	int width;
	int height;
} t_size;

typedef struct s_pos
{
	int x;
	int y;
} t_pos;

typedef struct s_board
{
	t_size   size;
	t_pos    player;
	int      tile_size;
	t_tile **tiles;
} t_board;

t_board *board_init(void)
{
	t_board *board;

	board = malloc(sizeof(t_board));
	if (!board)
		return (NULL);
	board->size.width = WIN_W / TILE_SIZE;
	board->size.height = WIN_H / TILE_SIZE;
	board->player.x = board->size.width / 2;
	board->player.y = board->size.height / 2;
	board->tile_size = TILE_SIZE;
	board->tiles = (t_tile **) calloc(WIN_H / TILE_SIZE, sizeof(t_tile *));
	if (!board->tiles)
	{
		free(board);
		return (NULL);
	}
	for (int row = 0; row < board->size.height; row++)
	{
		board->tiles[row] = (t_tile *) calloc(WIN_W / TILE_SIZE, sizeof(t_tile));
		if (!board->tiles[row])
		{
			while (row > 0)
			{
				free(board->tiles[row - 1]);
				row--;
			}
			free(board->tiles);
			free(board);
			return (NULL);
		}
	}
	// set player on board
	board->tiles[board->player.y][board->player.x] = TILE_PLAYER;
	// set borders
	for (int row = 0; row < board->size.height; row++)
	{
		board->tiles[row][0] = TILE_WALL;
		board->tiles[row][board->size.width - 1] = TILE_WALL;
	}
	for (int i = 0; i < board->size.width; i++)
	{
		board->tiles[0][i] = TILE_WALL;
		board->tiles[board->size.height - 1][i] = TILE_WALL;
	}
	return (board);
}

void tile_draw(t_tile tile, int px, int py)
{
	if (tile == TILE_FLOOR)
		DrawText("", px, py, 20, BLACK);
	else if (tile == TILE_WALL)
		DrawText("#", px, py, 20, BLACK);
	else if (tile == TILE_PLAYER)
		DrawText("@", px, py, 20, BLACK);
}

void board_move_player(t_board *board, int x, int y)
{
	if (board->tiles[board->player.y + y][board->player.x + x] == TILE_WALL)
		return;
	board->tiles[board->player.y][board->player.x] = TILE_FLOOR;
	board->player.x += x;
	board->player.y += y;
	board->tiles[board->player.y][board->player.x] = TILE_PLAYER;
}

void board_draw(t_board *board)
{
	for (int row = 0; row < board->size.height; row++)
		for (int col = 0; col < board->size.width; col++)
			tile_draw(board->tiles[row][col], col * TILE_SIZE, row * TILE_SIZE);
}

void board_free(t_board *board)
{
	for (int row = 0; row < board->size.height; row++)
		free(board->tiles[row]);
	free(board->tiles);
	free(board);
}

int main(void)
{
	InitWindow(WIN_W, WIN_H, "DANDD");
	SetTargetFPS(120);

	t_board *board = board_init();
	if (!board)
	{
		CloseWindow();
		return (1);
	}

	while (!WindowShouldClose())
	{
		if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_K))
			board_move_player(board, 0, -1);
		else if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_J))
			board_move_player(board, 0, 1);
		else if (IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_H))
			board_move_player(board, -1, 0);
		else if (IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_L))
			board_move_player(board, 1, 0);

		BeginDrawing();
		ClearBackground(WHITE);
		board_draw(board);
		EndDrawing();
	}
	board_free(board);
	CloseWindow();

	return (0);
}
