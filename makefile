# Ethan O'Connor
# ECE 231 Lab 3
# 3/8/25

CC = gcc
CFLAGS = -I.
DEPS = pin_cfg_lib.h
TARGET = start_poll

start_poll: cfg_gpio.c cfg_pwm.c poll_and_capture.c $(DEPS)
	$(CC) -o start_poll cfg_gpio.c cfg_pwm.c poll_and_capture.c $(CFLAGS)
.PHONY: clean
clean:
	rm -f start_poll
