This is a space-arcade game, made in C
The game runs in Terminal.
.....NOTE: Install ncurses support in your terminal, if not present already.
(in linux:
   sudo apt update
   sudo apt install libncurses-dev
   ) -- This command installs the ncurses lib for C
TO RUN THE GAME:
  first remove any previus .o files, using make clean command
  then, use make command to compile the code, and form an executable(escape_v)
  run the executable ./escape_v

after this, you will enter into TITLE SCREEN.
from there, you can start the game, view leader board, or quit.

In the game, we have planet obstacles (O), which have a radius of gravitational field, and if our
space ship comes into this radius, we experience a gravitational pull. (Not accurate though :) )
