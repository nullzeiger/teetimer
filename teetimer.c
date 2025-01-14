/* teetimer.c
 *
 * teetimer - A simple ncurses-based timer
 * Copyright (C) 2025 Ivan Guerreschi
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "teetimer.h"
#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>


/* Initialize the ncurses environment and set up the terminal
   This function must be called before any other timer functions */
void init_timer(void)
{
    initscr();               /* Initialize ncurses */
    cbreak();                /* Disable line buffering */
    noecho();                /* Don't echo keypresses */
    nodelay(stdscr, TRUE);   /* Non-blocking input */
    curs_set(0);             /* Hide cursor */
    start_color();           /* Enable colors */
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
}

/* Clean up ncurses and restore terminal to normal operation
   Must be called before program exit */
void cleanup_timer(void)
{
    /* End ncurses mode and restore terminal */
    endwin();
}

/* Display the current time remaining in the center of the screen
   @param minutes: Minutes remaining
   @param seconds: Seconds remaining */
void display_time(int minutes, int seconds)
{
    /* Clear the screen */
    clear();

    /* Enable the green-on-black color pair */
    attron(COLOR_PAIR(1));

    /* Display timer information centered on screen */
    mvprintw(LINES / 2 - 1, COLS / 2 - 10, "Time remaining:");
    mvprintw(LINES / 2, COLS / 2 - 4, "%02d:%02d", minutes, seconds);
    mvprintw(LINES / 2 + 2, COLS / 2 - 12, "Press 'q' to quit");

    /* Disable the color pair */
    attroff(COLOR_PAIR(1));

    /* Update the screen with all changes */
    refresh();
}

/* Handle keyboard input during timer operation
   Currently only handles quit command */
void handle_input(void)
{
    int ch = getch(); /* Get character (non-blocking) */

    /* Check for quit command */
    if (ch == 'q' || ch == 'Q') {
        cleanup_timer();
        exit(0);
    }
}

/* Main timer loop function
   @param minutes: Initial number of minutes to count down from */
void run_timer(int minutes)
{
    /* Convert minutes to total seconds */
    int total_seconds = minutes * 60;
    int remaining_seconds;

    /* Main countdown loop */
    while (total_seconds > 0) {
        /* Calculate minutes and seconds for display */
        remaining_seconds = total_seconds % 60;
        display_time(total_seconds / 60, remaining_seconds);
        handle_input();
        sleep(1);
        total_seconds--;
    }

    /* Timer completed */
    clear();
    mvprintw(LINES / 2, COLS / 2 - 10, "Timer completed!");
    refresh();
    sleep(2);
}
