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
 * helper macros
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
 * xbm icons
 *
 */

#define logo_width 64
#define logo_height 16
static unsigned char logo_bits[] = {
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x39, 0xc7, 0xf3, 0x03,
	0xc3, 0x03, 0xe7, 0xe7, 0x39, 0x83, 0xf3, 0x03, 0xc3, 0x03, 0xc3, 0xc3,
	0x39, 0x39, 0xf3, 0xf3, 0xe7, 0xf3, 0xc3, 0xc3, 0x39, 0x39, 0xf3, 0xf3,
	0xe7, 0xf3, 0xc3, 0xc3, 0x29, 0x39, 0xf3, 0xf3, 0xe7, 0xf3, 0xc3, 0xc3,
	0x29, 0x39, 0xf3, 0x83, 0xe7, 0x83, 0xe7, 0xe7, 0x29, 0x39, 0xf3, 0x83,
	0xe7, 0x83, 0xe7, 0xe7, 0x29, 0x39, 0xf3, 0xf3, 0xe7, 0xf3, 0xe7, 0xe7,
	0x01, 0x39, 0xf3, 0xf3, 0xe7, 0xf3, 0xe7, 0xe7, 0x93, 0x39, 0xf3, 0xf3,
	0xe7, 0xf3, 0xff, 0xff, 0x93, 0x39, 0xf3, 0xf3, 0xe7, 0xf3, 0xff, 0xff,
	0x93, 0x83, 0x03, 0xf3, 0xc3, 0x03, 0xe7, 0xe7, 0x93, 0xc7, 0x03, 0xf3,
	0xc3, 0x03, 0xe7, 0xe7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
};

/* pen icon */
#define pen_width 16
#define pen_height 16
static unsigned char pen_bits[] = {
	0xff, 0xff, 0x01, 0x80, 0x01, 0x80, 0x01, 0x82, 0x01, 0x87, 0x01, 0x8e,
	0x81, 0x9c, 0xc1, 0x89, 0xe1, 0x83, 0xf1, 0x81, 0xf1, 0x80, 0x79, 0x80,
	0x19, 0x80, 0x01, 0x80, 0x01, 0x80, 0xff, 0xff
};

/* fill icon */
#define fill_width 16
#define fill_height 16
static unsigned char fill_bits[] = {
	0xff, 0xff, 0x01, 0x80, 0x01, 0x80, 0x01, 0x80, 0x89, 0x81, 0xd1, 0x83,
	0x61, 0x9e, 0x71, 0xa4, 0x99, 0xa4, 0x0d, 0xae, 0x19, 0xab, 0xb1, 0xb9,
	0xe1, 0x90, 0x41, 0x80, 0x01, 0x80, 0xff, 0xff
};

/* hollow rect icon */
#define hollow_rect_width 16
#define hollow_rect_height 16
static unsigned char hollow_rect_bits[] = {
	0xff, 0xff, 0x01, 0x80, 0x01, 0x80, 0xf9, 0x9f, 0x09, 0x90, 0x09, 0x90,
	0x09, 0x90, 0x09, 0x90, 0x09, 0x90, 0x09, 0x90, 0x09, 0x90, 0x09, 0x90,
	0xf9, 0x9f, 0x01, 0x80, 0x01, 0x80, 0xff, 0xff
};

/* filled rect icon */
#define filled_rect_width 16
#define filled_rect_height 16
static unsigned char filled_rect_bits[] = {
	0xff, 0xff, 0x01, 0x80, 0x01, 0x80, 0xf9, 0x9f, 0xf9, 0x9f, 0xf9, 0x9f,
	0xf9, 0x9f, 0xf9, 0x9f, 0xf9, 0x9f, 0xf9, 0x9f, 0xf9, 0x9f, 0xf9, 0x9f,
	0xf9, 0x9f, 0x01, 0x80, 0x01, 0x80, 0xff, 0xff
};

/* undo icon */
#define undo_width 16
#define undo_height 16
static unsigned char undo_bits[] = {
	0xff, 0xff, 0x01, 0x80, 0x01, 0x80, 0x81, 0x83, 0xe1, 0x8e, 0x3d, 0x98,
	0xf9, 0xb0, 0x79, 0xa0, 0x11, 0xa0, 0x01, 0xa0, 0x01, 0xa0, 0x01, 0xb0,
	0x01, 0x98, 0x01, 0x8e, 0x01, 0x80, 0xff, 0xff
};

/* redo icon */
#define redo_width 16
#define redo_height 16
static unsigned char redo_bits[] = {
	0xff, 0xff, 0x01, 0x80, 0x01, 0x80, 0xc1, 0x81, 0x71, 0x87, 0x19, 0xbc,
	0x0d, 0x9f, 0x05, 0x9e, 0x05, 0x88, 0x05, 0x80, 0x05, 0x80, 0x0d, 0x80,
	0x19, 0x80, 0x71, 0x80, 0x01, 0x80, 0xff, 0xff
};

/*
 *
 * editor state
 *
 */

/* tool callback function */
typedef void tool_func_t(int x, int y, eui_color_t color);

/* tool info type */
typedef struct toolinfo_t {
	eui_vec2_t pos;
	int xbm_width;
	int xbm_height;
	unsigned char *xbm_bits;
	tool_func_t *func;
} toolinfo_t;

/* tool enum */
enum {
	TOOL_FILLED_RECT,
	TOOL_HOLLOW_RECT,
	TOOL_FILL,
	TOOL_PEN,
	TOOL_REDO,
	TOOL_UNDO,
	NUM_TOOLS
};

/* tilemap */
static struct {
	wolfie_tile_t walls[WOLFIE_MAP_HEIGHT][WOLFIE_MAP_WIDTH];
	wolfie_tile_t things[WOLFIE_MAP_HEIGHT][WOLFIE_MAP_WIDTH];
	char name[16];
} tilemap;

/* tilemap info */
eui_vec2_t tilemap_pos, tilemap_size;

/* tool info */
static toolinfo_t toolinfo[NUM_TOOLS];

/* current tool */
static int current_tool = TOOL_PEN;

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
	int i;

	/* clear tilemap */
	memset(&tilemap, 0, sizeof(tilemap));

	/* setup tilemap draw info */
	tilemap_size.x = WOLFIE_TILE_WIDTH * WOLFIE_MAP_WIDTH;
	tilemap_size.y = WOLFIE_TILE_HEIGHT * WOLFIE_MAP_HEIGHT;
	tilemap_pos.x = WOLFIE_WIDTH - tilemap_size.x;
	tilemap_pos.y = WOLFIE_HEIGHT - tilemap_size.y;

	/* setup tool info */
	toolinfo[TOOL_PEN].xbm_width = pen_width;
	toolinfo[TOOL_PEN].xbm_height = pen_height;
	toolinfo[TOOL_PEN].xbm_bits = pen_bits;

	toolinfo[TOOL_FILL].xbm_width = fill_width;
	toolinfo[TOOL_FILL].xbm_height = fill_height;
	toolinfo[TOOL_FILL].xbm_bits = fill_bits;

	toolinfo[TOOL_HOLLOW_RECT].xbm_width = hollow_rect_width;
	toolinfo[TOOL_HOLLOW_RECT].xbm_height = hollow_rect_height;
	toolinfo[TOOL_HOLLOW_RECT].xbm_bits = hollow_rect_bits;

	toolinfo[TOOL_FILLED_RECT].xbm_width = filled_rect_width;
	toolinfo[TOOL_FILLED_RECT].xbm_height = filled_rect_height;
	toolinfo[TOOL_FILLED_RECT].xbm_bits = filled_rect_bits;

	toolinfo[TOOL_UNDO].xbm_width = undo_width;
	toolinfo[TOOL_UNDO].xbm_height = undo_height;
	toolinfo[TOOL_UNDO].xbm_bits = undo_bits;

	toolinfo[TOOL_REDO].xbm_width = redo_width;
	toolinfo[TOOL_REDO].xbm_height = redo_height;
	toolinfo[TOOL_REDO].xbm_bits = redo_bits;

	/* setup tool info positions */
	for (i = 0; i < NUM_TOOLS; i++)
	{
		toolinfo[i].pos.x = -1 * ((toolinfo[i].xbm_width * i) + (4 * (i + 1)));
		toolinfo[i].pos.y = (tilemap_pos.y / 2) - (toolinfo[i].xbm_height / 2);
	}

	/* offset UNDO and REDO buttons */
	toolinfo[TOOL_UNDO].pos.x -= 24;
	toolinfo[TOOL_REDO].pos.x -= 24;

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
	eui_vec2_t tile_size, tile_pos;
	eui_vec2_t selected_tile;
	eui_vec2_t cursor_pos;
	eui_vec2_t pos, size;
	int i, x, y;

	/* get cursor pos */
	cursor_pos = eui_get_cursor_pos();

	/* clear screen */
	eui_clear(30);

	/* draw tilemap background */
	eui_filled_box(tilemap_pos, tilemap_size, 0);

	/* draw logo */
	pos.x = (tilemap_pos.x / 2) - (logo_width / 2);
	pos.y = 2;
	eui_xbm(pos, 15, logo_width, logo_height, logo_bits);

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

	/* draw selected tile */
	if (eui_is_hovered(tilemap_pos, tilemap_size))
	{
		/* get tile size */
		tile_size.x = WOLFIE_TILE_WIDTH + 2;
		tile_size.y = WOLFIE_TILE_HEIGHT + 2;

		/* get tile pos */
		tile_pos.x = cursor_pos.x - tilemap_pos.x;
		tile_pos.y = cursor_pos.y - tilemap_pos.y;

		/* get selected tile */
		selected_tile.x = (tile_pos.x - (tile_pos.x % WOLFIE_TILE_WIDTH)) / WOLFIE_TILE_WIDTH;
		selected_tile.y = (tile_pos.y - (tile_pos.y % WOLFIE_TILE_HEIGHT)) / WOLFIE_TILE_HEIGHT;

		/* clamp selected tile to valid range */
		selected_tile.x = CLAMP(selected_tile.x, 0, WOLFIE_MAP_WIDTH - 1);
		selected_tile.y = CLAMP(selected_tile.y, 0, WOLFIE_MAP_HEIGHT - 1);

		/* get selected tile outline pos */
		tile_pos.x = ((selected_tile.x * WOLFIE_TILE_WIDTH) + tilemap_pos.x) - 1;
		tile_pos.y = ((selected_tile.y * WOLFIE_TILE_HEIGHT) + tilemap_pos.y) - 1;

		/* draw tile outline */
		eui_border_box(tile_pos, tile_size, 1, 255);

		/* draw help text */
		pos.x = tilemap_pos.x;
		pos.y = tilemap_pos.y - 30;
		eui_textf(pos, 15, "tile: %02dx%02d", selected_tile.x, selected_tile.y);
		pos.x = tilemap_pos.x;
		pos.y = tilemap_pos.y - 20;
		eui_textf(pos, 15, "wall: 0x%04x", tilemap.walls[selected_tile.y][selected_tile.x]);
		pos.x = tilemap_pos.x;
		pos.y = tilemap_pos.y - 10;
		eui_textf(pos, 15, "thing: 0x%04x", tilemap.things[selected_tile.y][selected_tile.x]);
	}
	else
	{
		/* draw help text */
		pos.x = tilemap_pos.x;
		pos.y = tilemap_pos.y - 30;
		eui_text(pos, 15, "tile: --x--");
		pos.x = tilemap_pos.x;
		pos.y = tilemap_pos.y - 20;
		eui_text(pos, 15, "wall: ------");
		pos.x = tilemap_pos.x;
		pos.y = tilemap_pos.y - 10;
		eui_text(pos, 15, "thing: ------");
	}

	/* move to top left alignment */
	eui_set_align(EUI_ALIGN_END, EUI_ALIGN_START);

	/* draw tools */
	for (i = 0; i < NUM_TOOLS; i++)
	{
		eui_xbm(toolinfo[i].pos, 15, toolinfo[i].xbm_width, toolinfo[i].xbm_height, toolinfo[i].xbm_bits);
	}

	return EUI_TRUE;
}

/* quit wolfie editor */
void wolfie_quit(void)
{

}

