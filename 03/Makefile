# A simple Makefile
# Samuel Rembisz 
# Advent of Code 2021 Day 3

CC = gcc
CFLAGS = -g -Wall -std=c89 -pedantic-errors -O2
LIBS = -lm

TARGET = 03

$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) -o $(TARGET).o $(TARGET).c $(LIBS)

clean:
	 rm $(TARGET).o
