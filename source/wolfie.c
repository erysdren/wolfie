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
 * tile icons
 */

#define tile_filled_width 7
#define tile_filled_height 7
static unsigned char tile_filled_bits[] = {
	0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f
};

#define tile_dithered_width 7
#define tile_dithered_height 7
static unsigned char tile_dithered_bits[] = {
	0x55, 0x2a, 0x55, 0x2a, 0x55, 0x2a, 0x55
};

/*
 *
 * editor state
 *
 */

/* tool callback functions */
typedef void tool_activate_t(void);
typedef void tool_use_t(int x, int y, eui_color_t color);

/* tool info type */
typedef struct toolinfo_t {
	eui_vec2_t pos;
	int xbm_width;
	int xbm_height;
	unsigned char *xbm_bits;
	tool_activate_t *activate;
	tool_use_t *use;
} toolinfo_t;

/* tool enum */
enum {
	TOOL_FILLED_RECT,
	TOOL_HOLLOW_RECT,
	TOOL_FILL,
	TOOL_PEN,
	NUM_TOOLS
};

/* swatch enum */
enum {
	SWATCH_WALLS,
	SWATCH_THINGS,
	NUM_SWATCHES
};

/* tiledef type */
typedef struct tiledef_t {
	int used;
	char name[28];
	struct {
		int width;
		int height;
		unsigned char *bits;
	} xbm;
	eui_color_t color;
} tiledef_t;

/* tilemap */
static struct {
	wolfie_tile_t walls[WOLFIE_MAP_HEIGHT][WOLFIE_MAP_WIDTH];
	wolfie_tile_t things[WOLFIE_MAP_HEIGHT][WOLFIE_MAP_WIDTH];
	char name[16];
} tilemap;

/* tilemap info */
static eui_vec2_t tilemap_pos, tilemap_size;

/* tool info */
static toolinfo_t toolinfo[NUM_TOOLS];
static int current_tool = TOOL_PEN;

/* tile info */
#define NUM_TILEDEFS (256)
static tiledef_t tiledefs[NUM_TILEDEFS];
static int current_tile = 0;

/* swatch info */
static int current_swatch = SWATCH_WALLS;

/*
 *
 * private functions
 *
 */

/* undo last change */
void button_undo(void *user)
{
	EUI_UNUSED(user);
}

/* redo last change */
void button_redo(void *user)
{
	EUI_UNUSED(user);
}

/* switch to walls swatch */
void button_walls(void *user)
{
	EUI_UNUSED(user);
	current_swatch = SWATCH_WALLS;
}

/* switch to things swatch */
void button_things(void *user)
{
	EUI_UNUSED(user);
	current_swatch = SWATCH_THINGS;
}

/* plot tile on tilemap */
void tool_pen(int x, int y, int tile)
{
	/* user is not pressing any buttons */
	if (!eui_get_button())
		return;

	/* plot tile */
	tilemap.walls[y][x] = tile;
}

/* setup tilemap */
void setup_tilemap(void)
{
	/* clear tilemap */
	memset(&tilemap, 0, sizeof(tilemap));

	/* setup tilemap draw info */
	tilemap_size.x = WOLFIE_TILE_WIDTH * WOLFIE_MAP_WIDTH;
	tilemap_size.y = WOLFIE_TILE_HEIGHT * WOLFIE_MAP_HEIGHT;
	tilemap_pos.x = WOLFIE_WIDTH - tilemap_size.x;
	tilemap_pos.y = WOLFIE_HEIGHT - tilemap_size.y;
}

/* setup tiledefs */
void setup_tiledefs(void)
{
	/* clear tilemap */
	memset(&tiledefs, 0, sizeof(tiledefs));

	/* Empty */
	snprintf(tiledefs[0].name, sizeof(tiledefs[0].name), "Empty");
	tiledefs[0].used = EUI_TRUE;
	tiledefs[0].color = 0;
	tiledefs[0].xbm.width = tile_filled_width;
	tiledefs[0].xbm.height = tile_filled_height;
	tiledefs[0].xbm.bits = tile_filled_bits;

	/* Gray Stone 1 */
	snprintf(tiledefs[1].name, sizeof(tiledefs[1].name), "Gray Stone 1");
	tiledefs[1].used = EUI_TRUE;
	tiledefs[1].color = 25;
	tiledefs[1].xbm.width = tile_filled_width;
	tiledefs[1].xbm.height = tile_filled_height;
	tiledefs[1].xbm.bits = tile_filled_bits;

	/* Gray Stone 2 */
	snprintf(tiledefs[2].name, sizeof(tiledefs[2].name), "Gray Stone 2");
	tiledefs[2].used = EUI_TRUE;
	tiledefs[2].color = 25;
	tiledefs[2].xbm.width = tile_dithered_width;
	tiledefs[2].xbm.height = tile_dithered_height;
	tiledefs[2].xbm.bits = tile_dithered_bits;
}

/* setup tools */
void setup_tools(void)
{
	int i;

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

	/* setup tool info positions */
	for (i = 0; i < NUM_TOOLS; i++)
	{
		toolinfo[i].pos.x = -1 * ((toolinfo[i].xbm_width * i) + (4 * (i + 1)));
		toolinfo[i].pos.y = (tilemap_pos.y / 2) - (toolinfo[i].xbm_height / 2);
	}
}

/*
 *
 * public functions
 *
 */

/* init wolfie editor */
int wolfie_init(void)
{
	setup_tilemap();
	setup_tiledefs();
	setup_tools();
	return EUI_TRUE;
}

/* load UWMF from char buffer */
/* returns EUI_FALSE on failure */
int wolfie_read_uwmf(char *buffer, size_t buffer_size)
{
	EUI_UNUSED(buffer);
	EUI_UNUSED(buffer_size);
	return EUI_FALSE;
}

/* save current editor tilemap into char buffer as UWMF */
/* returns 0 on failure */
size_t wolfie_write_uwmf(char *buffer, size_t buffer_size)
{
	EUI_UNUSED(buffer);
	EUI_UNUSED(buffer_size);
	return 0;
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
			i = tilemap.walls[y][x];
			eui_xbm(tile_pos, tiledefs[i].color, tiledefs[i].xbm.width, tiledefs[i].xbm.height, tiledefs[i].xbm.bits);

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

		/* do tile interaction */
		switch (current_tool)
		{
			case TOOL_PEN:
				tool_pen(selected_tile.x, selected_tile.y, current_tile);
				break;

			default:
				break;
		}

		/* draw help text */
		pos.x = tilemap_pos.x;
		pos.y = tilemap_pos.y - 30;
		eui_textf(pos, 15, "tile: %02dx%02d", selected_tile.x, selected_tile.y);
		pos.x = tilemap_pos.x;
		pos.y = tilemap_pos.y - 20;
		eui_textf(pos, 15, "wall: %s", tiledefs[tilemap.walls[selected_tile.y][selected_tile.x]].name);
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

	/* move to top right alignment */
	eui_set_align(EUI_ALIGN_END, EUI_ALIGN_START);

	/* draw tools */
	for (i = 0; i < NUM_TOOLS; i++)
	{
		if (current_tool == i)
			eui_xbm(toolinfo[i].pos, 72, toolinfo[i].xbm_width, toolinfo[i].xbm_height, toolinfo[i].xbm_bits);
		else
			eui_xbm(toolinfo[i].pos, 15, toolinfo[i].xbm_width, toolinfo[i].xbm_height, toolinfo[i].xbm_bits);

		size.x = toolinfo[i].xbm_width;
		size.y = toolinfo[i].xbm_height;

		if (eui_get_button() & EUI_BUTTON_LEFT && eui_is_hovered(toolinfo[i].pos, size))
			current_tool = i;
	}

	/* move to top left alignment */
	eui_set_align(EUI_ALIGN_START, EUI_ALIGN_START);

	/* draw swatch buttons */
	pos.x = 0;
	pos.y = tilemap_pos.y;
	size.x = tilemap_pos.x / 2;
	size.y = 16;
	eui_button(pos, size, "Walls", button_walls, NULL);

	pos.x = tilemap_pos.x - size.x;
	eui_button(pos, size, "Things", button_things, NULL);

	/* draw swatches */
	if (current_swatch == SWATCH_WALLS)
	{
		pos.x = 15;
		pos.y = tilemap_pos.y + 24;
		size.x = tilemap_pos.x;
		size.y = 10;
		for (i = 0; i < NUM_TILEDEFS; i++)
		{
			if (!tiledefs[i].used)
				continue;

			/* draw tile name */
			if (current_tile == i)
				eui_text(pos, 72, tiledefs[i].name);
			else
				eui_text(pos, 15, tiledefs[i].name);

			/* draw tile logo */
			pos.x -= 11;
			eui_xbm(pos, tiledefs[i].color, tiledefs[i].xbm.width, tiledefs[i].xbm.height, tiledefs[i].xbm.bits);
			pos.x += 11;

			/* select tile */
			if (eui_get_button() & EUI_BUTTON_LEFT && eui_is_hovered(pos, size))
				current_tile = i;

			pos.y += 10;
		}
	}
	else if (current_swatch == SWATCH_THINGS)
	{

	}

	return EUI_TRUE;
}

/* quit wolfie editor */
void wolfie_quit(void)
{

}

