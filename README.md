# Multithreaded Game
[![build](https://github.com/asd1o1/multithread-game/actions/workflows/build.yml/badge.svg?branch=main)](https://github.com/asd1o1/multithread-game/actions/workflows/build.yml)
[![test](https://github.com/asd1o1/multithread-game/actions/workflows/test.yml/badge.svg)](https://github.com/asd1o1/multithread-game/actions/workflows/test.yml)

I don't know quite where I'm going with this yet, but for now, this is an """infinite"""" open-world medieval-era (NOT fantasy) exploration game. The game is based on a 2D board of "tiles, which each contain... stuff. Different parts of the game will run on different threads, not out of necessity or even performance requirements, but rather to better familiarize myself with threads.

For a more detailed explanation of implemented and planned features, see the roadmap [here](https://github.com/asd1o1/multithread-game/issues/1).

## Building
#### Build for release (recommended):
```
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make
```
#### Build for debug (enables debugger symbols and unit tests):
```
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Debug ..
make
```
All unit tests are built into build/tests.

## Usage
From the build directory, run:
```
bin/multithread-game
```

## Contributing
Feel free! There aren't any guidelines yet, but good features will likely be implemented.

## License
[GNU GPLv3](https://choosealicense.com/licenses/gpl-3.0/)
