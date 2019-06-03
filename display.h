#ifndef _DISPLAY_H_
#define _DISPLAY_H_

/**
 * display.h
 */

#include <sys/sysctl.h>

void display_init();
void display_destroy();

void display_scroll();

void print_error(const char* const);
void render_processes(struct kinfo_proc *, int);

#endif
