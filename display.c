/**
 * display.c
 */

#include <ncurses.h>
#include <stdio.h>

#include "display.h"

WINDOW *proc_win = NULL;

void _init_colors() {
  start_color();
  init_pair(1, COLOR_RED, COLOR_YELLOW);
}

void display_init() {
  initscr();
  //_init_colors();
  curs_set(0);
  refresh();
}

void display_destroy() {
  endwin();
}

// void display_scroll() {
//   scroll(proc_win);
//   wrefresh(proc_win);
// }

void print_error(const char* const str) {
  // TODO - clean this stuff up
  int startx = 10;
  int starty = 10;
  int width = 100;
  int height = 3;

  WINDOW *err_win = newwin(height, width, starty, startx);
  //wbkgd(err_win, COLOR_PAIR(1));
  box(err_win, 0, 0);
  wprintw(err_win, "ERROR!");
  mvwprintw(err_win, 1, 3, str);
  wrefresh(err_win);
  getch();
  display_destroy();
}

void render_processes(struct kinfo_proc *processes, int count) {
  int startx = 0;
  int starty = 0;
  int width = COLS;
  int height = LINES;


  proc_win = newwin(height, width, startx, starty);
  scrollok(proc_win, true);
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

  for (int i = 0; i < count; i++) {
    wprintw(proc_win, "%d\t%d\t%d\t%d\t%s\n",
      processes[i].kp_proc.p_pid,
      processes[i].kp_proc.p_priority,
      processes[i].kp_proc.p_nice,
      processes[i].kp_proc.p_stat,
      processes[i].kp_proc.p_comm
    );

    wrefresh(proc_win);
  }

  // TODO - is this what we want?
  getch();
}
