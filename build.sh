#!/bin/sh
#
#
#

export CC=cc
export LD=cc
export CFLAGS="-x c -std=c99 -Wall -Werror -fstack-protector-all -Wstrict-prototypes -Wmissing-prototypes -Wmissing-declarations -Wshadow -Wpointer-arith -Wcast-qual -Wsign-compare -O2 -g"

./mmk0 -o mmk mmk.c |while read line; do
    echo $line
    $line || exit 1;
done
