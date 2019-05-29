/**
 * display.c
 */

#include <ncurses.h>

#include "display.h"

void init_display() {
	initscr();
}

void destroy_display() {
	endwin();
}

void print_error(const char* const str) {
	printw(str);
	refresh();
	getch();
	endwin();
}

void render_processes(struct kinfo_proc *processes, int count) {
  printw("PROCESS COUNT: %d\n", count);
  for (size_t i = 0; i < 25; i++) {
    printw("PROCESS: %s\n", processes[i].kp_proc.p_comm);
  }

	getch();
}
