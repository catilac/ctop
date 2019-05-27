/*
 * ctop.c
 * An htop clone
 *
 * AUTHOR: Chirag Davé
 */

#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/sysctl.h>

int main(int argc, char **argv)
{

  int mib[4] = { CTL_KERN, KERN_PROC, KERN_PROC_ALL, 0 };
  size_t count = 0;
  struct kinfo_proc *processes = NULL;

  // Init screen
  initscr();

  if (sysctl(mib, 4, NULL, &count, NULL, 0) < 0) {
    printw("ERROR getting process COUNTS\n");
    // TODO write an error handler for ncurses
    refresh();
    getch();
    endwin();
    return -1;
  }

  printw("PROCESS COUNT: %d\n", count);

  processes = (struct kinfo_proc *)malloc(sizeof(struct kinfo_proc) * count);

  if (sysctl(mib, 4, processes, &count, NULL, 0) < 0) {
    printw("ERROR getting process DETAILS\n");
    refresh();
    getch();
    endwin();

    // free up processes
    free(processes);

    return -1;
  }

  for (size_t i = 0; i < 25; i++) {
    printw("PROCESS: %s\n", processes[i].kp_proc.p_comm);
  }

  // Wait for keyboard input and then quit
  getch();
  endwin();

  // free up processes
  free(processes);

  return 0;
}
