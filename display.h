#ifndef _DISPLAY_H_
#define _DISPLAY_H_

/**
 * display.h
 */

#include <sys/sysctl.h>

void init_display();
void destroy_display();

void print_error(const char* const);
void render_processes(struct kinfo_proc *, int);


#endif
