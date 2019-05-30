/**
 * display.c
 */

#include <ncurses.h>
#include <stdio.h>

#include "display.h"

void _init_colors() {
  start_color();
  init_pair(1, COLOR_RED, COLOR_YELLOW);
}

void init_display() {
  initscr();
  _init_colors();
  refresh();
}

void destroy_display() {
  endwin();
}

void print_error(const char* const str) {
  // TODO - clean this stuff up
  int startx = 10;
  int starty = 10;
  int width = 100;
  int height = 3;

  WINDOW *err_win = newwin(height, width, starty, startx);
  wbkgd(err_win, COLOR_PAIR(1));
  box(err_win, 0, 0);
  wprintw(err_win, "ERROR!");
  mvwprintw(err_win, 1, 3, str);
  wrefresh(err_win);
  getch();
  destroy_display();
}

void render_processes(struct kinfo_proc *processes, int count) {
  int startx = 0;
  int starty = 0;
  int width = COLS;
  int height = LINES;


  WINDOW *proc_win = newwin(height, width, startx, starty);
  box(proc_win, 0, 0);
  wbkgd(proc_win, COLOR_PAIR(1));

  /* TODO
   *  [ ] user
   *  [ ] virt
   *  [ ] res
   *  [ ] time
   *  [ ] CPU%
   *  [ ] MEM%
   *  [ ] stat fmt
   */
  mvwprintw(proc_win, 1, 1, "PID\tPRI\tNI\tS\tCommand");

  for (int i = 0; i < 25; i++) {
    mvwprintw(proc_win, i+2, 1, "%d\t%d\t%d\t%d\t%s",
      processes[i].kp_proc.p_pid,
      processes[i].kp_proc.p_priority,
      processes[i].kp_proc.p_nice,
      processes[i].kp_proc.p_stat,
      processes[i].kp_proc.p_comm
    );
  }

  wrefresh(proc_win);
	getch();
}
