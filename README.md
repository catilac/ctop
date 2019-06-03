# ctop - an htop clone

## TODO
  [ ] Scrolling using arrow keys (or vim commands?)

  [ ] Write datastructures for holding process information
    - sortable by different keys

  [ ] Make sure we're shutting down gracefully

  [x] Write system calls to get list of processes

  [x] Create an ncurses based lib for creating a dashboard
    - needs to involve using WINDOW

## What does this do?

* HUD
  - Displays process information
  - High level data

* Table View
  - List processes sorted by some field
  - can go through it with arrow controls, paging
  - sort controls
  - tree view
