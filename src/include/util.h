/*******************************************************************************
* @filename: util.h
* @brief: util.c header

*  Copyright 2025 eduardofabbris
*
*  Licensed under the Apache License, Version 2.0 (the "License");
*  you may not use this file except in compliance with the License.
*  You may obtain a copy of the License at
*
*      http://www.apache.org/licenses/LICENSE-2.0
*
*  Unless required by applicable law or agreed to in writing, software
*  distributed under the License is distributed on an "AS IS" BASIS,
*  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*  See the License for the specific language governing permissions and
*  limitations under the License.
********************************************************************************/
#ifndef UTIL_H
#define UTIL_H

/**********************************************
 * Includes
 *********************************************/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include <time.h>

/**********************************************
 * Defines
 *********************************************/

// Special ASCII keys
#define SPACE 32
#define ESC 27

/**********************************************
 * Function Prototypes
 *********************************************/

// Time
long long get_clock();
double time_diff(uint64_t start_t);
char *get_timeinfo(time_t timestamp);

// Terminal
void gotoxy(int x, int y);
void hide_cursor(int state);
void set_nonblock(int state);

char get_char();

#ifdef _WIN32
// @windows

/**********************************************
 * WINDOWS Includes
 *********************************************/

#include <windows.h>
#include <conio.h>

/**********************************************
 * WINDOWS Defines
 *********************************************/

// Miscellaneous
#define FILE_SEPARATOR "\\\\"
#define msleep(a) Sleep(a)
#define clrscr() system("cls")

// ASCII keys
#define UP 72
#define DOWN 80
#define ENTER 13
#define BACKSPACE 8

// Flags
#define LINUX_EN 0      // Linux enabled flag
#define WINDOWS_EN 1    // Windows enabled flag

#else
// @linux

/**********************************************
 * LINUX Includes
 *********************************************/

#include <unistd.h>
#include <termios.h>
#include <sys/select.h>

/**********************************************
 * LINUX Defines
 *********************************************/

// Miscellaneous
#define FILE_SEPARATOR "/"
#define msleep(a) for(int ii = 0; ii < 1000; ii++) {usleep(a);}
#define clrscr() system("clear")

// ASCII keys
#define UP 65
#define DOWN 66
#define ENTER 10
#define BACKSPACE 127

// Flags
#define LINUX_EN 1      // Linux enabled flag
#define WINDOWS_EN 0    // Windows enabled flag

/**********************************************
 * LINUX Typedefs
 *********************************************/


/**********************************************
 * LINUX Function Prototypes
 *********************************************/

int kbhit();

#endif

#endif // UTIL_H
