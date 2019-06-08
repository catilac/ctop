#ifndef _DISPLAY_H_
#define _DISPLAY_H_

/**
 * display.h
 */

#include <sys/sysctl.h>

void display_init();
void display_destroy();

void display_scroll();

WINDOW *display_create_window(int height, int width, int starty, int startx);

void print_error(const char* const);
void render_processes(WINDOW *win, struct kinfo_proc *processes, 
                      int count, int offset);

#endif
