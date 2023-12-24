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

#pragma once
#ifndef _WOLFIE_H_
#define _WOLFIE_H_
#ifdef __cplusplus
extern "C" {
#endif

/* headers */
#include <stdint.h>
#include "eui.h"

/* tile type */
typedef uint16_t wolfie_tile_t;

/* constants */
#define WOLFIE_WIDTH (640)
#define WOLFIE_HEIGHT (480)
#define WOLFIE_TITLE "wolfie"
#define WOLFIE_MAP_WIDTH (64)
#define WOLFIE_MAP_HEIGHT (64)
#define WOLFIE_MAP_PITCH (WOLFIE_MAP_WIDTH * sizeof(wolfie_tile_t))

/* init wolfie editor */
void wolfie_init(void);

/* run wolfie editor */
/* NOTE: eui_begin() must have been called before this! */
void wolfie_run(void);

/* quit wolfie editor */
void wolfie_quit(void);

#ifdef __cplusplus
}
#endif
#endif /* _WOLFIE_H_ */
