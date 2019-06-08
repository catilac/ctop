/*
 * ctop.c
 * An htop clone
 *
 * AUTHOR: Chirag Davé
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/sysctl.h>
#include <unistd.h>
#include <ncurses.h>

#include "display.h"

int main(int argc, char **argv) {
  int mib[4] = { CTL_KERN, KERN_PROC, KERN_PROC_ALL, 0 };
  size_t count = 0;
  struct kinfo_proc *processes = NULL;

  // Init screen
  display_init();

  if (sysctl(mib, 4, NULL, &count, NULL, 0) < 0) {
    print_error("ERROR getting process COUNTS\n");
    return -1;
  }

	// TODO - move this into its own module
  if (processes != NULL) {
    free(processes);
  }
  processes = (struct kinfo_proc *)malloc(sizeof(struct kinfo_proc) * count);

  if (sysctl(mib, 4, processes, &count, NULL, 0) < 0) {
    print_error("ERROR getting process DETAILS\n");
    // free up processes
    free(processes);
    return -1;
  }

  // create proc window
  WINDOW *proc_win = display_create_window(LINES, COLS, 0, 0);

  int offset = 0;
  while (1) {
    render_processes(proc_win, processes, count, offset);
    offset++;
    sleep(1);
  }

  display_destroy();

  // free up processes
  free(processes);

  return 0;
}
