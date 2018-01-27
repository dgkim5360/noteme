PREFIX=/usr/local

CC=gcc
CFLAGS=-Wall -pedantic-errors `pkg-config --cflags x11 libnotify`
LDFLAGS=`pkg-config --libs x11 libnotify`
