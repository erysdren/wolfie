/*
MIT License

Copyright (c) 2023 erysdren (it/she/they)

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

/*
 *
 * WOLFIE.C
 *
 */

/* headers */
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "wolfie.h"

/*
 *
 * editor state
 *
 */

/* tilemap */
static struct {
	wolfie_tile_t walls[WOLFIE_MAP_HEIGHT][WOLFIE_MAP_WIDTH];
	wolfie_tile_t things[WOLFIE_MAP_HEIGHT][WOLFIE_MAP_WIDTH];
	char name[16];
} tilemap;

/*
 *
 * private functions
 *
 */

/*
 *
 * public functions
 *
 */

/* init wolfie editor */
int wolfie_init(void)
{
	/* clear tilemap */
	memset(&tilemap, 0, sizeof(tilemap));

	return EUI_TRUE;
}

/* load map from uwmf */
int wolfie_load_uwmf(char *buffer, size_t buffer_size)
{
	EUI_UNUSED(buffer);
	EUI_UNUSED(buffer_size);
	return EUI_TRUE;
}

/* save current tilemap state into uwmf format */
/* returned as an allocated buffer that the caller is responsible for freeing */
char *wolfie_save_uwmf(size_t *buffer_size)
{
	EUI_UNUSED(buffer_size);
	return NULL;
}

/* run wolfie editor */
/* NOTE: eui_begin() must be called before this! */
int wolfie_run(void)
{
	eui_vec2_t tilemap_pos, tilemap_size;
	eui_vec2_t tile_size, tile_pos;
	eui_vec2_t cursor_pos;
	int x, y;

	/* get cursor pos */
	cursor_pos = eui_get_cursor_pos();

	/* clear screen */
	eui_clear(30);

	/* draw tilemap background */
	tilemap_size.x = WOLFIE_TILE_WIDTH * WOLFIE_MAP_WIDTH;
	tilemap_size.y = WOLFIE_TILE_HEIGHT * WOLFIE_MAP_HEIGHT;
	tilemap_pos.x = WOLFIE_WIDTH - tilemap_size.x;
	tilemap_pos.y = WOLFIE_HEIGHT - tilemap_size.y;
	eui_filled_box(tilemap_pos, tilemap_size, 0);

	/* draw tilemap */
	tile_size.x = WOLFIE_TILE_WIDTH;
	tile_size.y = WOLFIE_TILE_HEIGHT;
	for (y = 0; y < WOLFIE_MAP_HEIGHT; y++)
	{
		for (x = 0; x < WOLFIE_MAP_WIDTH; x++)
		{
			/* get tile pos */
			tile_pos.x = tilemap_pos.x + (x * WOLFIE_TILE_WIDTH);
			tile_pos.y = tilemap_pos.y + (y * WOLFIE_TILE_HEIGHT);

			/* draw wall */
			eui_filled_box(tile_pos, tile_size, tilemap.walls[y][x]);

			/* draw thing */
			if (tilemap.things[y][x])
				eui_filled_box(tile_pos, tile_size, 255);
		}
	}

	return EUI_TRUE;
}

/* quit wolfie editor */
void wolfie_quit(void)
{

}
