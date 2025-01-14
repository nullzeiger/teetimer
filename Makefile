# Makefile
# teetimer - A simple ncurses-based timer
# Copyright (C) 2025 Ivan Guerreschi
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -o2 -ggdb
LDFLAGS = -lncurses

# Target executable name
TARGET = teetimer

# Source files
SOURCES = teetimer.c main.c

# Object files
OBJECTS = $(SOURCES:.c=.o)

# Default target
all: $(TARGET)

# Link the program
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

# Compile individual object files
teetimer.o: teetimer.c teetimer.h
	$(CC) $(CFLAGS) $(LDFLAGS) -c $< -o $@

main.o: main.c teetimer.h
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up object files and the executable
clean:
	rm -f $(OBJECTS) $(TARGET)

# Install target (optional)
install: all
	install -m 755 $(TARGET) ~/.local/bin

# Uninstall target (optional)
uninstall: all
	rm -rf ~/.local/bin/$(TARGET)

# Phony targets 
.PHONY: all clean
