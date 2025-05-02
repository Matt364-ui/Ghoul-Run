# Ghoul-Run
# Ghoul Run

🎮 A survival-style ASCII console game written in C++ — inspired by *Vampire Survivors*.

You are Cowardly Van Helsing. Ghouls are coming. Dodge, dash, and bomb your way through the growing horde.

---

## 🕹️ How to Play

- Move using `W`, `A`, `S`, `D` (press Enter after each)
- Survive as long as possible while your score increases
- Ghouls (`G` and `X`) will chase you — they start slow, then get faster
- Avoid contact or it's game over

---

## 💥 Power-Ups

| Symbol | Effect                                                                 |
|--------|------------------------------------------------------------------------|
| `+`    | ⚡ **Speed Boost** — Automatically doubles movement for 5 turns        |
| `0`    | 💣 **Bomb** — Pick it up, then press `P` to place a trap that kills a ghoul if they step on it |

Power-ups spawn regularly — pick them up by walking over them.

---

## 🧟 Enemy Mechanics

- Ghouls skip turns:
  - First 20 moves: skip 3 turns
  - Next 20: skip 2
  - Then: move every turn
- Fast ghouls (`X`) appear as the game progresses

---

## 🧪 Requirements

- Works on any modern C++ compiler
- **No external libraries**
- Tested and playable on [OnlineGDB](https://www.onlinegdb.com/online_c++_compiler)

---

## 📸 Demo

You can try it live at [OnlineGDB](https://www.onlinegdb.com/online_c++_compiler)

Paste the code from `ghoul_run.cpp`, run it, and start dodging.

---

## 📂 Files

- `ghoul_run.cpp` – the full game source code (console-only)

---

## 👾 Credit

Developed by [Your Name]  
Designed to be playable with zero setup

---

## ✅ License

MIT – free to use, modify, and learn from.
