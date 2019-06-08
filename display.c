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

void display_init() {
  initscr();
  _init_colors();
  curs_set(0);
  refresh();
}

void display_destroy() {
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
  display_destroy();
}

WINDOW *display_create_window(int height, int width, int starty, int startx) {
  WINDOW *win = newwin(height, width, starty, startx);
  scrollok(win, true);
  box(win, 0, 0);
  wbkgd(win, COLOR_PAIR(1));
  return win;
}

/* TODO Move this into a utils.h ? */
int imin(int x, int y) {
  if (x <= y)
    return x;
  return y;
}

void render_processes(WINDOW *win, struct kinfo_proc *processes, 
                      int count, int offset) {
  /* TODO
   *  [ ] user
   *  [ ] virt
   *  [ ] res
   *  [ ] time
   *  [ ] CPU%
   *  [ ] MEM%
   *  [ ] stat fmt
   */

  mvwprintw(win, 1, 1, "PID\tPRI\tNI\tS\tCommand");
  wrefresh(win);

  int total = imin(LINES + offset - 3, count);
  for (int i = offset, pos = 2; i < total; i++, pos++) {
    mvwprintw(win, pos, 1, "%d\t%d\t%d\t%d\t%s\n",
      processes[i].kp_proc.p_pid,
      processes[i].kp_proc.p_priority,
      processes[i].kp_proc.p_nice,
      processes[i].kp_proc.p_stat,
      processes[i].kp_proc.p_comm
    );

    wrefresh(win);
  }
}
