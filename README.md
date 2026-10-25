# Zombie-Game
A zombie game developed in C as a programming project.

# Zombicide (Terminal Edition) 🧟

A terminal-based puzzle game written in C, inspired by the board game *Zombicide*. Clear every zombie from the city to advance to the next level. Each new city is a little bigger than the last, until the outbreak is over and the planet is safe… for now.

Developed as the 1st project for the course **Programming II** (Department of Informatics and Telecommunications, University of the Peloponnese).

---

## Gameplay

The board represents a city of size `N x M`:

| Symbol  | Meaning |
|:------: |---------|
| `1`–`9` | A zombie (the digit is its type) |
| `#`     | A building (indestructible, blocks zombie movement) |
| `.`     | An empty square |

At the start of each level:
- **Buildings** are placed randomly. Each building is a random, connected shape (generated with a random walk), and the number of buildings varies from level to level.
- **Zombies** of random type (1 to `Z`) fill every remaining square.
- A **sound source** is placed on a random side of the board (top, bottom, left or right).

Whenever zombies are killed, the surviving ones move toward the sound source and fill the gaps, stopping when they hit a building, another zombie or the edge of the board.

When every zombie on the board is dead, the next level starts automatically with a board one row and one column bigger, new buildings, new zombies and a new sound source. The game is won when the board reaches the maximum size.

---

## Commands

Rows and columns are numbered starting from **1**.

| Command | Weapon | Description |
|---------|--------|-------------|
| `n row,col` | **Neurogun** | Shoots the zombie at `(row,col)`. The shot spreads recursively and kills every zombie of the **same type** connected to it horizontally or vertically. It cannot be used on a lonely zombie (one with no neighbour of the same type). |
| `b row,col` | **Bomb** | Kills every zombie at `(row,col)` and in the 8 surrounding squares, regardless of type. Buildings and empty squares are not affected. |
| `x` | — | Quit the game and show the levels completed and the final score. |

Commands are case-insensitive (`n`/`N`, `b`/`B`, `x`/`X`).

**Examples**
```
n 4,8
b 5,5
x
```

Invalid commands, missing coordinates or positions outside the board are rejected with an error message and the player is asked for a new move.

---

## Scoring

Points depend on how many zombies are killed in a single move. The function is **non-linear**: bigger groups earn a bonus.

| Zombies killed | Points |
|:--------------:|:------:|
| 1              | 10 |
| 2              | 25 |
| 3              | 40 |
| 4              | 50 |
| 5              | 58 |
| 6              | 77 |
| 7              | 90 |
| 8              | 100 |
| 9              | 120 |
| 10–18          | 190 |
| 19–25          | 210 |
| > 25           | 100 + 10 × zombies |

(Groups larger than 9 are only possible with the neurogun.)

---

## Settings

At startup the player chooses, once for the whole game:

- **Board size** `N` and `M`: between **7** and **20**. The board does not need to be square.
- **Number of zombie types** `Z`: between **1** and **9**.

---

## Build & Run

Requires a C compiler (e.g. `gcc`).

```bash
gcc -Wall -o zombicide C2_project_1_tsapis_kontos.c
./zombicide
```

---

## Example

```
     1  2  3  4  5  6  7  8
---------------------------
 1|  2  2  1  9  8  4  8  3
 2|  6  #  #  7  6  8  2  8
 3|  8  4  #  1  8  3  8  5
 4|  3  1  6  3  8  2  5  8
 5|  9  3  4  3  7  #  #  8
 6|  #  #  3  3  7  #  #  4
 7|  1  6  3  5  7  4  3  1

Level 1 - Score 0
The zombies overrun us, make your move: n 6,3
```

---

## Implementation Notes

- The board is a **dynamically allocated** 2D array (`char**`), allocated with checks at the start of each level and freed as soon as the level ends.
- The neurogun uses a **recursive** flood-fill function (`anadromiki_neuro`) that takes the coordinates and the zombie type.
- All randomness uses `rand()`, seeded with `srand(time(NULL))`.
- Zombie movement toward the sound source is handled by `move_zombies`, which processes each row or column and pulls the nearest zombie into every empty square, without crossing buildings.

### Main functions

| Function | Purpose |
|----------|---------|
| `new_tablo` | Allocates a new board filled with empty squares |
| `add_hashes` | Places random, connected buildings |
| `add_zombies` | Fills empty squares with random zombies |
| `show` | Prints the numbered board |
| `neuro` / `anadromiki_neuro` | Neurogun logic (recursive) |
| `bomb` | Bomb logic |
| `move_zombies` | Moves zombies toward the sound source |
| `no_more_zombies` | Checks if the level is cleared |
| `free_tablo` | Frees the board's memory |

---

## Authors

- **Giannis Tsapis**
- **Dimitris Kontos**
