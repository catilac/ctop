/*
 * ctop.c
 * An htop clone
 *
 * AUTHOR: Chirag Davé
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/sysctl.h>
#include <unistd.h>
#include <ncurses.h>

#include "display.h"


struct kinfo_proc *processes = NULL;

static void sig_int(int);
void cleanup();

int main(int argc, char **argv) {
  int mib[4] = { CTL_KERN, KERN_PROC, KERN_PROC_ALL, 0 };
  size_t count = 0;

  signal(SIGINT, sig_int);

  // Init screen
  display_init();

  if (sysctl(mib, 4, NULL, &count, NULL, 0) < 0) {
    print_error("ERROR getting process COUNTS\n");
    cleanup();
    return -1;
  }

	// TODO - move this into its own module
  processes = (struct kinfo_proc *)malloc(sizeof(struct kinfo_proc) * count);

  if (sysctl(mib, 4, processes, &count, NULL, 0) < 0) {
    print_error("ERROR getting process DETAILS\n");
    // free up processes
    cleanup();
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
}

void cleanup() {
  display_destroy();
  if (processes)
    free(processes);
}

static void sig_int(int signo) {
  if (signo == SIGINT) {
    cleanup();
    exit(1);
  }
}
