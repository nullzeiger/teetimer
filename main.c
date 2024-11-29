/* main.c
 *
 * teetimer - A simple ncurses-based timer
 * Copyright (C) 2024 Ivan Guerreschi
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
#include <stdio.h>
#include <stdlib.h>

/* Main entry point for the timer program
   @return: 0 on success, 1 on error */
int main(int argc, char *argv[])
{
	int minutes;

	if (argc != 2) {
		printf("Usage: %s <minutes>\n", argv[0]);
		return 1;
	}

	minutes = atoi(argv[1]);
	if (minutes <= 0) {
		printf("Please enter a positive number of minutes\n");
		return 1;
	}

	init_timer();
	run_timer(minutes);
	cleanup_timer();

	return 0;
}
