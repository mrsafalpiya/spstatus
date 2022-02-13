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
void clean_exit(int num);

/* Function implementations */
void
cur_time(char *str)
{
	time_t timer;
	struct tm *t = NULL;
	char meridiem[3];
	int hour, minute, second;

	timer = time(NULL);
	t = localtime(&timer);
	if (!t) {
		fprintf(stderr, "Cannot get current time\n");
		clean_exit(1);
	}

	if (t->tm_hour < 13) {
		hour = t->tm_hour;
		if (!hour)
			hour = 12;
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

	if (TIME_SHOW_SECONDS)
		sprintf(str, "%.2d:%.2d:%.2d%s", hour, minute, second, meridiem);
	else
		sprintf(str, "%.2d:%.2d%s", hour, minute, meridiem);
}

void
clean_exit(int num)
{
	/* X11 clean */
	if (XCloseDisplay(dpy) < 0) {
		fprintf(stderr, "XCloseDisplay: Failed to close display\n");
	}

	if (num == 1)
		exit(1);
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
	signal(SIGINT, clean_exit);
	signal(SIGTERM, clean_exit);

	/* Main loop */
	while (1) {
		cur_time(time);

		if (XStoreName(dpy, root, time) < 0) {
			fprintf(stderr, "XStoreName: Allocation failed\n");
			clean_exit(1);
		}
		XFlush(dpy);

		sleep(INTERVAL);
	}

	return 0;
}
