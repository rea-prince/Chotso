## Chotso

This is my implementation of a Chip8 emulator/interpreter based on [this guide](https://tobiasvl.github.io/blog/write-a-chip-8-emulator/)

## Usage

```bash
cmake -G "MinGW Makefiles" -S . -B build 
# or "Unix Makefiles" or whatever you prefer

cmake --build build
./build/Chip8 <ROM> 
# e.g. `./build/Chip8 ./data/PONG`
```

---

## References
- http://devernay.free.fr/hacks/chip8/C8TECH10.HTM
- https://tobiasvl.github.io/blog/write-a-chip-8-emulator/
- https://www.youtube.com/watch?v=YtSgV3gY3fs

The ROMs were taken from [this repository](https://github.com/cj1128/chip8-emulator/tree/master/rom).
