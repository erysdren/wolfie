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

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "wolfie.h"

/*
 *
 * macros
 *
 */

#ifndef MIN
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#endif

#ifndef MAX
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#endif

#ifndef CLAMP
#define CLAMP(a, min, max) MIN(MAX(a, min), max)
#endif

#ifndef SGN
#define SGN(x) ((x < 0) ? -1 : ((x > 0) ? 1 : 0))
#endif

/*
 *
 * state
 *
 */

/* tilemap */
static int tilemap_x = WOLFIE_WIDTH - (WOLFIE_TILE_WIDTH * WOLFIE_MAP_WIDTH);
static int tilemap_y = WOLFIE_HEIGHT - (WOLFIE_TILE_HEIGHT * WOLFIE_MAP_HEIGHT);
static int tilemap_w = WOLFIE_TILE_WIDTH * WOLFIE_MAP_WIDTH;
static int tilemap_h = WOLFIE_TILE_HEIGHT * WOLFIE_MAP_HEIGHT;
static unsigned char tilemap[WOLFIE_NUM_LAYERS][WOLFIE_MAP_HEIGHT][WOLFIE_MAP_WIDTH];

/* current selections */
static int active_layer = 0;
static int active_tool = 0;
static unsigned char active_tile = 0;
static int selected_tile_x = 0;
static int selected_tile_y = 0;

/*
 *
 * private functions
 *
 */

static void draw_background(void)
{
	eui_screen_clear(0x1E);
}

static void draw_tilemap(void)
{
	int l, x, y, xx, yy, w, h, c;
	int cursor_x, cursor_y;

	/* background */
	eui_draw_box(tilemap_x, tilemap_y, tilemap_w, tilemap_h, 0x00);

	/* read cursor position */
	eui_cursor_read(&cursor_x, &cursor_y);

	/* tiles */
	for (l = 0; l < WOLFIE_NUM_LAYERS; l++)
	{
		for (y = 0; y < WOLFIE_MAP_HEIGHT; y++)
		{
			for (x = 0; x < WOLFIE_MAP_WIDTH; x++)
			{
				/* get size */
				w = WOLFIE_TILE_WIDTH;
				h = WOLFIE_TILE_HEIGHT;

				/* get pos */
				xx = tilemap_x + (x * w);
				yy = tilemap_y + (y * h);

				/* get color */
				c = tilemap[l][y][x];

				/* draw box */
				if (c)
					eui_draw_box(xx, yy, w, h, c);
			}
		}
	}

	/* selected tile */
	if (eui_cursor_hovering(tilemap_x, tilemap_y, tilemap_w, tilemap_h))
	{
		/* get tile size */
		w = WOLFIE_TILE_WIDTH + 2;
		h = WOLFIE_TILE_HEIGHT + 2;

		/* get tile pos */
		xx = cursor_x - tilemap_x;
		yy = cursor_y - tilemap_y;

		/* get selected tile */
		selected_tile_x = (xx - (xx % WOLFIE_TILE_WIDTH)) / WOLFIE_TILE_WIDTH;
		selected_tile_y = (yy - (yy % WOLFIE_TILE_HEIGHT)) / WOLFIE_TILE_HEIGHT;

		/* clamp selected tile to valid range */
		selected_tile_x = CLAMP(selected_tile_x, 0, WOLFIE_MAP_WIDTH - 1);
		selected_tile_y = CLAMP(selected_tile_y, 0, WOLFIE_MAP_HEIGHT - 1);

		/* get selected tile outline pos */
		xx = ((selected_tile_x * WOLFIE_TILE_WIDTH) + tilemap_x) - 1;
		yy = ((selected_tile_y * WOLFIE_TILE_HEIGHT) + tilemap_y) - 1;

		/* draw tile outline */
		eui_draw_box_border(xx, yy, w, h, 1, 0xFF);
	}
}

static void draw_text(void)
{
	if (eui_cursor_hovering(tilemap_x, tilemap_y, tilemap_w, tilemap_h))
	{
		eui_draw_textf(tilemap_x, tilemap_y - 10, 0x0F, "tile: %02dx%02d", selected_tile_x, selected_tile_y);
	}
	else
	{
		eui_draw_text(tilemap_x, tilemap_y - 10, 0x0F, "tile: --x--");
	}
}

/*
 *
 * public functions
 *
 */

/* init editor */
int wolfie_init(void)
{
	memset(tilemap, 0, sizeof(tilemap));

	return EUI_TRUE;
}

/* run editor */
void wolfie_main(void)
{
	/* begin eui context */
	if (eui_context_begin())
	{
		eui_frame_align_set(EUI_ALIGN_START, EUI_ALIGN_START);
		draw_background();
		draw_tilemap();
		draw_text();
		eui_context_end();
	}
}

/* quit editor */
void wolfie_quit(void)
{

}
