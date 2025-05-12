# Tales From The Future

**Tales From The Future** is a retro‐styled 2‑D adventure / puzzle platformer written in **C with SDL 1.2**.  
Originally developed as a university coursework project, the game combines real‑time action, branching dialogue and brain‑teasing enigmas in a single pixel‑art experience.

---

## ✨ Key features

| Domain | Highlights |
|--------|------------|
| Side‑scrolling levels | Classic platform movement with collisions, gravity and *moving traps* (`moving_traps/`) |
| Puzzle system | Random and file‑driven riddles (`enigme/`, `enigmeAlea*.c`) that pop up mid‑level |
| Dialogue engine | `dialogue.c/h` renders branching, text‑based conversations with NPC sprites |
| Rich assets | Hand‑drawn sprites & backgrounds (`sprites/`, `entities_sprites/`, `bgimgs/`) plus bitmap fonts |
| Soundtrack & SFX | Chip‑tune music and effects via **SDL_mixer** (`game_sound/`) |
| UI overlays | Pixel HUD, quiz boxes and animated buttons (`imgs/`, `html/`, `buttonOn.png`) |
| Optional Arduino input | `arduino.c/h` reads serial data for extra physical‑world triggers |

*(Feel free to add GIFs or screenshots in `docs/img/` and reference them here.)*

---

## 🏗 Getting started

### Prerequisites

On **Debian/Ubuntu** install SDL 1.2 and helpers:

```bash
sudo apt update
sudo apt install build-essential libsdl1.2-dev libsdl-image1.2-dev \
                 libsdl-mixer1.2-dev libsdl-ttf2.0-dev
```

> SDL 1.2 packages are still available in official repositories despite its age.  
> For other distros, look for similarly named `libsdl‑*-dev` packages.

### Clone & build

```bash
git clone https://github.com/yassine-abid/Tales-From-The-Future.git
cd Tales-From-The-Future

# Quick way – provided helper script
chmod +x buildandrun.sh
./buildandrun.sh       # compiles *.c with `sdl-config` flags then launches the game

# Manual way
gcc $(find . -name "*.c") -o tales $(sdl-config --cflags --libs) \
    -lSDL_image -lSDL_mixer -lSDL_ttf
./tales
```

On **Windows**, grab the pre‑built SDL 1.2 development ZIP, copy `SDL.dll` next to the EXE and use MinGW (`gcc ... \`sdl-config --cflags --libs\``) or Visual Studio (add SDL include/lib).

---

## 🎮 Controls (default)

| Key / button | Action |
|--------------|--------|
| ← / →        | Move left / right |
| ↑            | Jump  |
| ↓            | Interact / talk |
| **Space**    | Confirm puzzle answer |
| **Esc**      | Pause / quit |

*(You can tweak key‑bindings in `controls.h` once implemented.)*

---

## 🗂 Project structure (abridged)

```
.
├── buildandrun.sh           # helper to compile & launch
├── bg.c / bg.h              # parallax background engine
├── character.[ch]           # player entity logic
├── moving_traps/            # animated obstacles
├── dialogue/                # dialogues & fonts
├── enigme/                  # puzzle system
├── game_sound/              # music & SFX assets
├── sprites/ entities_sprites/ # PNG sprite sheets
└── html/                    # design mock‑ups & docs
```

---

## 🤝 Contributing

1. **Fork** → **branch** → commit descriptive messages.  
2. Use ANSI C 99 style; keep functions under 80 cols where possible.  
3. Submit a Pull Request with screenshots / GIF demos of new features.

---

## 📜 License

No explicit license file is present in the repository. Until one is added, all rights are reserved by the original authors.  
If you plan to reuse the code, please open an issue or contact the maintainer.

---

## 🙏 Acknowledgements

Powered by **SDL 1.2**, **SDL_image**, **SDL_mixer** and **SDL_ttf**.  
Thanks to open‑source pixel‑font creators and sound‑effect artists whose assets appear in `fonts/` and `game_sound/`.

*Enjoy the trip to the future!*
