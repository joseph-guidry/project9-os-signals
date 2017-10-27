CC=gcc
CFLAGS+=-Wall -Wextra -Wpedantic
CFLAGS+=-Wwrite-strings -Wfloat-equal
CFLAGS+=-Waggregate-return -Winline

all: SIG_RX SIG_TX

SIG_RX: signaler.c
	gcc -o SIG_RX signaler.c -lm -pthread

SIG_TX: sender.c
	gcc -o SIG_TX sender.c

clean:
	$(RM) SIG_TX SIG_RX
