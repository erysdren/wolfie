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
 * MAIN.C
 *
 */

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

#include "wolfie.h"
#include "eui_sdl2.h"
#include "palette_wolf3d.h"
#include "wolfie_icon_rgba.h"

/* SDL2 state */
static SDL_Window *window;
static SDL_Surface *icon;
static SDL_Surface *surface8;
static SDL_Surface *surface32;
static SDL_Renderer *renderer;
static SDL_Texture *texture;
static SDL_Rect rect;
static SDL_Color colors[256];
static SDL_Event event;

/* quit */
void quit(int code)
{
	wolfie_quit();
	eui_quit();

	if (icon) SDL_FreeSurface(icon);
	if (surface8) SDL_FreeSurface(surface8);
	if (surface32) SDL_FreeSurface(surface32);
	if (texture) SDL_DestroyTexture(texture);
	if (renderer) SDL_DestroyRenderer(renderer);
	if (window) SDL_DestroyWindow(window);

	SDL_Quit();

	exit(code);
}

/* main */
int main(int argc, char **argv)
{
	uint32_t format;
	unsigned int rmask, gmask, bmask, amask;
	int bpp;
	int i;

	EUI_UNUSED(argc);
	EUI_UNUSED(argv);

	/* init */
	SDL_Init(SDL_INIT_VIDEO);

	/* create window */
	window = SDL_CreateWindow(WOLFIE_TITLE,
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		WOLFIE_WIDTH, WOLFIE_HEIGHT,
		SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI
	);

	/* create renderer */
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
	SDL_RenderSetLogicalSize(renderer, WOLFIE_WIDTH, WOLFIE_HEIGHT);
	SDL_RenderSetIntegerScale(renderer, SDL_TRUE);
	SDL_SetWindowMinimumSize(window, WOLFIE_WIDTH, WOLFIE_HEIGHT);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest");

	/* add icon */
	icon = SDL_CreateRGBSurfaceFrom(wolfie_icon_rgba, 32, 32, 32, 128, 0xFF, 0xFF00, 0xFF0000, 0xFF000000);
	SDL_SetWindowIcon(window, icon);

	/* create our render surface */
	surface8 = SDL_CreateRGBSurface(0, WOLFIE_WIDTH, WOLFIE_HEIGHT, 8, 0, 0, 0, 0);
	SDL_FillRect(surface8, NULL, 0);

	/* init palette */
	for (i = 0; i < 256; i++)
	{
		colors[i].r = palette[i * 3];
		colors[i].g = palette[i * 3 + 1];
		colors[i].b = palette[i * 3 + 2];
	}

	/* install palette */
	SDL_SetPaletteColors(surface8->format->palette, colors, 0, 256);

	/* create display surface */
	format = SDL_GetWindowPixelFormat(window);
	SDL_PixelFormatEnumToMasks(format, &bpp, &rmask, &gmask, &bmask, &amask);
	surface32 = SDL_CreateRGBSurface(0, WOLFIE_WIDTH, WOLFIE_HEIGHT, bpp, rmask, gmask, bmask, amask);
	texture = SDL_CreateTexture(renderer, format, SDL_TEXTUREACCESS_STREAMING, WOLFIE_WIDTH, WOLFIE_HEIGHT);

	/* make sure relative mouse mode is disabled */
	SDL_SetRelativeMouseMode(SDL_FALSE);

	/* setup blit rect */
	rect.x = 0;
	rect.y = 0;
	rect.w = WOLFIE_WIDTH;
	rect.h = WOLFIE_HEIGHT;

	/* init eui */
	eui_init(surface8->w, surface8->h, surface8->format->BitsPerPixel, surface8->pitch, surface8->pixels);

	/* init editor */
	wolfie_init();

	/* main loop */
	while (!SDL_QuitRequested())
	{
		/* push events */
		while (SDL_PollEvent(&event))
			eui_sdl2_event_push(&event);

		/* process events */
		eui_event_queue_process();

		/* run editor */
		wolfie_main();

		/* copy to screen */
		SDL_BlitSurface(surface8, &rect, surface32, &rect);
		SDL_UpdateTexture(texture, NULL, surface32->pixels, surface32->pitch);
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, texture, NULL, NULL);
		SDL_RenderPresent(renderer);
	}

	/* quit */
	quit(0);
	return 0;
}
