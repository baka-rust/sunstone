Project Sunstone
=================

Here is our CSE132 game, written in a language untaught in CSE132.
Also, it's not ECS based anymore.


Building
--------

We use `cmake` to do all of our work here.

Our `CMakeLists.txt` should handle SFML linking now.

### Compiling ###

1. Open command line at project root
2. `touch <path-to-CMakeLists.txt>` (this will force rebuild CMake's sources list)
3. Create and `cd` to an empty desired output directory (`build/` by convention)
4. `cmake <path-to-project-root>` so it would be `cmake ..` if you are running from the `build/` directory
5. `make`
6. `./Moonstone`

### Xcode Project Generation ###

**NOTE:** Do *not* generate new classes through Xcode as it will put the new files in the wrong place. Generate files by hand, then rerun this build script (or add the files manually after)

1. Follow steps 1-3 from **Compiling**.
2. `cmake -G Xcode --build <path-to-project-root>`
3. Open the newly generated Xcode project.
4. Change compile target to `Moonstone`

Files will be in `Sources/Moonstone/`

### CodeBlocks Project Generation ###

Should function like Xcode, but `-G "CodeBlocks - Ninja"`

### Visual Studio ###

Unsurprisingly: `-G "Visual Studio 10"`
