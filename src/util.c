/*******************************************************************************
* @filename: util.c
* @brief: Miscellaneous functions for terminal and keyboard handling for both
*         Windows and Linux
*
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
#include "include/util.h"

/**
 * @brief  Computes the time difference
 * @param  start_t: initial time in microseconds
 * @retval The time elapsed in milliseconds since start_time
 * @note   clock() doesn't measure wall-clock time, i.e. can't be used with msleep in linux
 */
double time_diff(uint64_t start_t)
{
    return ((double) (get_clock() - start_t)) / 1000;
}
//**************************************************************************************

/**
 * @brief  Get time and date information
 * @param  None
 * @retval The system date and time as a string pointer
 * @note   Source code: https://www.w3resource.com/c-programming/time/c-asctime.php
 */
char *get_timeinfo(time_t timestamp)
{
    static struct tm *new_time;
    time_t lctime = timestamp;

    // Get the timestamp in seconds
    if (timestamp == 0)
    {
        time(&lctime);
    }

    // Convert it to the structure tm
    new_time = localtime(&lctime);

    return asctime(new_time);
}
//**************************************************************************************

/**
 * @brief  Get user string input from keyboard
 * @param  input_layer: screen layer to print over the background
 * @param  str_buffer: buffer to store the input string
 * @param  max_str_len: maximum input string length
 * @retval string length when input confirmed, -1 when input canceled and -2 otherwise
 */
int get_keyboard_str(char *input_layer, char *str_buffer, int max_str_len)
{
    static int str_len = 0, blink_latch = 0;
    static uint64_t blink_timer = 0;

    int ch = 0;
    if(kbhit()){
        // Read a key form keyboard
        ch = get_char();

        switch(ch)
        {
            // Cancel input
            case ESC:
                str_len = 0;
                return -1;

            // Finished typing
            case ENTER:
                int aux = str_len;
                str_len = 0;
                return aux;

            // Erase character
            case BACKSPACE:
                if (str_len > 0)
                    str_len -= 1;

                break;
            // Add new character
            default:
                if (str_len < max_str_len)
                {
                    if (str_buffer != NULL)
                    {
                        str_buffer[str_len] = ch;
                    }
                    str_len += 1;
                }
                break;
        }
    }

    if (input_layer != NULL && str_buffer != NULL)
    {
        memcpy(input_layer, str_buffer, str_len);
        if ( time_diff(blink_timer) >= 500 )
        {
            blink_timer = get_clock();
            blink_latch = !blink_latch;
        }
        if (blink_latch)
        {
            memcpy(input_layer + str_len, "_", 1);
        }
    }
    return -2;
}
//****************************************************************************************

#ifdef _WIN32 // @windows

/**
 * @brief  Get time in microseconds
 * @retval The wall-clock time in microseconds
 */
long long get_clock()
{
    //The epoch used by FILETIME starts from January 1, 1601
    FILETIME ft;
    ULARGE_INTEGER ui;

    // Get the current system time as a FILETIME
    GetSystemTimeAsFileTime(&ft);

    // Convert FILETIME to ULARGE_INTEGER
    ui.LowPart = ft.dwLowDateTime;
    ui.HighPart = ft.dwHighDateTime;

    // Convert to microseconds (1 tick = 100 nanoseconds)
    return  (long long) (ui.QuadPart / 10);
}
//**************************************************************************************

/**
 * @brief  Move terminal cursor
 * @param  x: row number
 * @param  y: column number
 */
void gotoxy(int x, int y)
{
    COORD coord = {0, 0};
    coord.X = y;
    coord.Y = x;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
//****************************************************************************************

/**
 * @brief  Hide terminal cursor
 * @param  State: disable or enable
 */
void hide_cursor(int state)
{
    CONSOLE_CURSOR_INFO cursor = {1, !state};
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
}
//****************************************************************************************

/**
 * @brief  Read a pressed key from keyboard
 * @retval The key pressed
 */
char get_char()
{
    return getch();
}
//****************************************************************************************

/**
 * @brief  Dummy function
 * @retval None
 */
void set_nonblock(int state)
{
    (void) state;
}
//****************************************************************************************
#else // @linux

/**
 * @brief  Read a pressed key from keyboard
 * @retval The key pressed
 */
char get_char()
{
    char ch = 0;
    // read last character in case ANSI escape sequences
    while(read(STDIN_FILENO, &ch, 1) > 0);
    return ch;
}
//**************************************************************************************

/**
 * @brief  Get time in microseconds
 * @retval The wall-clock time in microseconds
 */
long long get_clock()
{
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    return (long long) ((ts.tv_sec * 1000000LL) + (ts.tv_nsec / 1000));
}
//**************************************************************************************

/**
 * @brief  Move terminal cursor
 * @param  x: row number
 * @param  y: column number
 */
void gotoxy(int x, int y)
{
    printf("\033[%d;%dH",x+1, y+1);
}
//****************************************************************************************

/**
 * @brief  Hide terminal cursor
 * @param  State: disable or enable
 */
void hide_cursor(int state)
{
    if (state)
    {
        printf("\e[?25l");
    }
    else
    {
        printf("\e[?25h");
    }

}
//****************************************************************************************

/**
 * @brief  Verify keyboard input
 * @param  None
 * @retval True if a key was pressed or false otherwise
 */
int kbhit()
{
    struct timeval tv;
    fd_set fds;
    tv.tv_sec = 0;
    tv.tv_usec = 0;
    FD_ZERO(&fds);
    FD_SET(STDIN_FILENO, &fds);
    select(STDIN_FILENO+1, &fds, NULL, NULL, &tv);
    return FD_ISSET(STDIN_FILENO, &fds);
}
//****************************************************************************************

/**
 * @brief  Set non-blocking terminal input and disable echo mode
 * @param  state: enable or disable
 * @retval The system date and time as a string pointer
 * @note   Canonical mode: waits until ENTER is pressed to take input
 *         Echo mode     : prints all typed input
 */
void set_nonblock(int state)
{
    struct termios ttystate;

    // get the terminal state
    tcgetattr(STDIN_FILENO, &ttystate);

    if (state)
    {
        // turn off canonical and echo mode
        ttystate.c_lflag &= ~(ICANON | ECHO);
    }
    else
    {
        // turn on canonical and echo mode
        ttystate.c_lflag |= (ICANON | ECHO);
    }

    // minimum of number input read.
    ttystate.c_cc[VMIN] = 0;
    // timeout in deciseconds
    ttystate.c_cc[VTIME] = 0;

    // set the terminal attributes.
    tcsetattr(STDIN_FILENO, TCSANOW, &ttystate);

}
//****************************************************************************************
#endif
