#  EDF VD in C
#
#  Copyright (C) 2019 Richi Dubey <richidubey@gmail.com>
# 
#  This work is licensed under the terms of the GNU GPL, version 2.  See
#  the LICENSE file in the top-level directory.
#

CC = gcc

%.o: %.c 
	$(CC) $< -c -o $@	

edfvd: edfvd.o
	$(CC) -o edfvd edfvd.o

clean:
	rm edfvd.o
