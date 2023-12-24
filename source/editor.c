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
 * EDITOR.C
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
void wolfie_init(void)
{
	/* clear tilemap */
	memset(&tilemap, 0, sizeof(tilemap));
}

/* run wolfie editor */
/* NOTE: eui_begin() must have been called before this! */
void wolfie_run(void)
{

}

/* quit wolfie editor */
void wolfie_quit(void)
{

}

