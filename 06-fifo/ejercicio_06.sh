#!/bin/env sh

gcc -o fifo_06_reader fifo_06_reader.c
gcc -o fifo_06_writer fifo_06_writer.c

./fifo_06_writer & ./fifo_06_reader
