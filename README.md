## CUB3D

This is a 3D graphics project made in collaboration with Laura Guillén, @solleksmori.
The projects is about creating a 3D maze game (inspired by the 1992 Wolfenstein 3D) with a map that is given as an argument to the program.

While Laura did the mathematic operations to display the 3D maze (raycasting), I was in charge of parsing the user input, which in this case was the game map.
In addition, I worked on a minimap to display the player's movements on the map. I also did the beautiful graphics (walls) for our maze.

### Our requirements and limitations included:

- coding everything in C
- using the MLX42 graphics library

### For the map parsing specifically:
  - only accepting characters '0' for an empty space, '1' for a wall, and 'N','S','E' or 'W' for the player’s start position and spawning orientation.
  - the map must be closed/surrounded by walls (character '1')
  - content separation rules (eg. ach type of element can be separated by one or more empty line(s))
  - the map file also includes specifiers for each wall (NO, WE, SO, EA for north, west, south, east) that give the path to fetch the PNG file used as the wall,
    as well as the colour for the floor and the ceiling
