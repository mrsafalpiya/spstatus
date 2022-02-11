#include <stdio.h>
#include <stdlib.h>
#include <X11/Xlib.h>
#include <time.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>

/* Global declarations */
static Display *dpy;
static Window root;
static int screen;

/* config file */
#include "config.h"

/* Function declarations */
void cur_time(char *str);
void cleanup(int num);

/* Function implementations */
void
cur_time(char *str)
{
	time_t timer;
	struct tm *t;
	char meridiem[3];
	int hour, minute, second;

	timer = time(NULL);
	t = localtime(&timer);

	if (t->tm_hour < 13) {
		hour = t->tm_hour;
		meridiem[0] = 'A';
		meridiem[1] = 'M';
		meridiem[2] = '\0';
	} else {
		hour = t->tm_hour - 12;
		meridiem[0] = 'P';
		meridiem[1] = 'M';
		meridiem[2] = '\0';
	}
	minute = t->tm_min;
	second = t->tm_sec;

	sprintf(str, "%.2d:%.2d:%.2d%s", hour, minute, second, meridiem);
}

void
cleanup(int num)
{
	(void)num;

	/* X11 clean */
	XCloseDisplay(dpy);
	exit(EXIT_SUCCESS);
}

int
main(int argc, char **argv)
{
	char *display_name = NULL;
	char time[11];

	/* Parse arguments */
	if (argc == 2 && !strcmp("-v", argv[1])) {
		printf("spstatus-" VERSION "\n");
		exit(0);
	} else if (argc != 1) {
		printf("usage: spstatus [-v]\n");
		exit(1);
	}

	/* X11 init */
	dpy = XOpenDisplay(display_name);
	if (!dpy) {
		fprintf(stderr, "Cannot open connection to display");
		exit(1);
	}
	screen = XDefaultScreen(dpy);
	root = RootWindow(dpy, screen);

	/* Signal handling */
	signal(SIGINT, cleanup);
	signal(SIGTERM, cleanup);

	/* Main loop */
	while (1) {
		cur_time(time);

		XStoreName(dpy, root, time);
		XFlush(dpy);

		sleep(INTERVAL);
	}

	return 0;
}
