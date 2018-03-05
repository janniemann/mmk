#!/bin/sh

cc -x c -std=c99 -Wall -Werror -fstack-protector-all -Wstrict-prototypes -Wmissing-prototypes \
    -Wmissing-declarations -Wshadow -Wpointer-arith -Wcast-qual -Wsign-compare -O2 -g mmk.c -o mmk0
