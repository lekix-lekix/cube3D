# Cub3D - Raycasting rendering engine

Cub3D is a 42 School group project. The goal is to create a pseudo 3D raycasting rendering engine from scratch that renders a 3D scene from a 2D .cub file, that represents a level.
It is written in C and uses the 42 graphics library called MinilibX (a low level and small simple rendering library).

![cub3d screenshot](./cub3d.png?raw=true "cub3D")

# 🎯 Learning Objectives

- Understand and implement the **raycasting** algorithm, using DDA (Digital Differential Analyzer)
- Work with a graphics library (**MiniLibX**)
- Manage memory properly (no leaks)
- Parse and validate configuration files (`.cub`)
- Structure a sizeable C project

## 🗂️ Map File Format (.cub)

The `.cub` file contains:

- Wall textures: North (`NO`), South (`SO`), East (`EA`), West (`WE`)
- Floor color (`F`) and ceiling color (`C`) in RGB
- The map itself, made up of:
  - `1` : wall
  - `0` : empty space
  - `N`, `S`, `E`, `O` : player's starting position and orientation
  - the map must be surrounded by walls
    Minimal example:

```
NO ./textures/north.xpm
SO ./textures/south.xpm
WE ./textures/west.xpm
EA ./textures/east.xpm

F 220,100,0
C 225,30,0

111111
100001
101101
1000N1
111111
```

## ⚙️ Features

- [x] Full parsing and validation of the `.cub` file
- [x] 3D raycasting view rendering
- [x] Player movement (forward/backward/left/right)
- [x] Camera rotation (mouse and/or arrow keys)
- [x] Different textures depending on wall orientation
- [x] Clean exit handling (window close button, ESC key)
- [x] No memory leaks / crashes

### Bonus (optional)

- [x] Minimap
- [x] Doors that open/close
- [x] Advanced collision detection

## 🛠️ Installation

```bash
git clone https://github.com/lekix-lekix/cube3D.git
cd cub3D
make
```

## ▶️ Usage

```bash
./cub3D maps/example.cub
```

## 📦 Dependencies

- MiniLibX
- `libft` (personal C library)
- Make
- C Standard Library

## 🧱 Project Structure

```
cub3D/
├── src/
├── obj/
├── includes/
├── 42-MEGALIBFT/
├── mlx/
├── maps/
├── textures/
├── Makefile
└── README.md
```

## 🧪 Testing

- Valid / invalid maps (malformed formats, unclosed map, etc.)
- Memory checks with Valgrind (leaks, memory errors)
- Norminette (42's coding standard)

## 👥 Authors

- kipouliq - sabakar-

## 📄 License

Project made as part of the 42 School curriculum.
