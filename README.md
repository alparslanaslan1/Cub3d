# Cub3D

**Cub3D** is a simple 3D game engine in C that renders a 2D map as a first-person 3D scene using raycasting, inspired by Wolfenstein 3D. Built with MiniLibX for graphics and user input.

## File Structure

```
Cub3d-main/
├── includes/
│   └── cub3d.h              # Structs, macros, and function prototypes
├── srcs/
│   ├── main.c               # Program entry: initialization and game loop
│   ├── parsing.c            # Map file parsing and validation
│   ├── utils.c              # Helper functions (error handling, memory)
│   ├── raycasting.c         # Core raycasting logic and distance calculations
│   ├── draw.c               # Pixel drawing routines and rendering walls
│   ├── textures.c           # Loading and applying textures
│   ├── movement.c           # Player movement and rotation handlers
│   └── close.c              # Cleanup and resource deallocation
├── maps/
│   └── example.cub          # Sample map file (must be rectangular)
├── textures/
│   ├── north.xpm
│   ├── south.xpm
│   ├── east.xpm
│   └── west.xpm             # Wall textures in XPM format
├── Makefile                 # Build rules for the `cub3d` executable
└── README.md                # This file
```

## Compilation

From the project root directory (`Cub3d-main`), run:

```bash
make
```

This will compile all source files, link MiniLibX, and produce the `cub3d` executable.

Common Make targets:

```bash
make clean    # remove object files
make fclean   # remove object files and executable
make re       # full rebuild (fclean + make)
```

## Usage

Launch the game by specifying a `.cub` map file:

```bash
./cub3d maps/example.cub
```

The window will open displaying the 3D scene based on your map.

## Controls

* **W / ↑**: Move forward
* **S / ↓**: Move backward
* **A**: Strafe left
* **D**: Strafe right
* **← / →**: Rotate camera left/right
* **ESC**: Exit game

## Map Format

* File extension must be `.cub`.
* First four lines specify texture paths:

  ```
  NO ./textures/north.xpm
  SO ./textures/south.xpm
  WE ./textures/west.xpm
  EA ./textures/east.xpm
  ```
* Next lines form a rectangular map grid using:

  * `1` for walls
  * `0` for empty space
  * `N`, `S`, `E`, or `W` for player start position and orientation
  * Spaces for padding outside the map

Example:

```
111111
1N0  1
100001
111111
```

## Author

* **Alparslan Aslan** ([alparslanaslan504@gmail.com](mailto:alparslanaslan504@gmail.com))

## License

No explicit license provided. Use, modify, and distribute at your own risk.
