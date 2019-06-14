# ctop - an htop clone

## TODO
  [ ] Need an actual window abstraction
  [ ] Scrolling using arrow keys (or vim commands?)

  [ ] Write datastructures for holding process information
    - sortable by different keys

  [ ] Select processes to kill

  [x] Make sure we're shutting down gracefully -- signal handling

  [x] Write system calls to get list of processes

  [x] Create an ncurses based lib for creating a dashboard
    - needs to involve using WINDOW

## What will this do?

* HUD
  - Displays process information
  - High level data

* Table View
  - List processes sorted by some field
  - can go through it with arrow controls, paging
  - sort controls
  - tree view
