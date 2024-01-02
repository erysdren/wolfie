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
 * WAD.C
 *
 */

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "tinyfiledialogs.h"
#include "wad.h"
#include "wolfie.h"

/* filter patterns for save/load dialogs */
static const char *patterns[2] = {"*.wad", "*.WAD"};

/* load textmap from wad */
int wad_load_textmap(void)
{
	char *filename;

	filename = tinyfd_openFileDialog("Load WAD", NULL, 2, patterns, "WAD Files", 0);
	if (!filename)
		return EUI_FALSE;

	return EUI_TRUE;
}

/* save textmap to wad */
int wad_save_textmap(void)
{
	char *filename;
	FILE *file;
	int i, x, y;

	filename = tinyfd_saveFileDialog("Save WAD", NULL, 2, patterns, "WAD Files");
	if (!filename)
		return EUI_FALSE;

	/* open file */
	file = fopen(filename, "wb");
	if (!file)
		return EUI_FALSE;

	/* write textmap header */
	fprintf(file, "namespace=\"%s\";", map_namespace);
	fprintf(file, "name=\"%s\";", map_name);
	fprintf(file, "tilesize=64;");
	fprintf(file, "width=64;");
	fprintf(file, "height=64;");

	/* write plane */
	fprintf(file, "plane{depth=64;}");

	/* write sector */
	fprintf(file, "sector{textureceiling=\"#383838\";texturefloor=\"#707070\";}");

	/* write tiledefs */
	for (i = 0; i < num_tiledefs; i++)
	{
		fprintf(file, "tile{");
		fprintf(file, "texturenorth=\"%s\";", tiledefs[i].texturenorth);
		fprintf(file, "textureeast=\"%s\";", tiledefs[i].textureeast);
		fprintf(file, "texturesouth=\"%s\";", tiledefs[i].texturesouth);
		fprintf(file, "texturewest=\"%s\";", tiledefs[i].texturewest);
		fprintf(file, "}");
	}

	/* write planemap */
	fprintf(file, "planemap{");
	for (y = 0; y < WOLFIE_MAP_HEIGHT; y++)
	{
		for (x = 0; x < WOLFIE_MAP_WIDTH; x++)
		{
			fprintf(file, "{%d,%d,%d}", tilemap[y][x].tile, tilemap[y][x].sector, tilemap[y][x].zone);
		}
	}
	fprintf(file, "}");

	return EUI_TRUE;
}
