# cpp-engine

cpp-engine is a simple game engine written in C++ using OpenGL. It provides a basic framework for creating 3D games, including support for graphics, input, audio, and physics.

## Dependencies

MyGame requires the following dependencies to be installed:

- GLFW (https://www.glfw.org/)
- GLAD (https://glad.dav1d.de/)
- Assimp (https://github.com/assimp/assimp)

You can install these dependencies manually or use a package manager such as Homebrew or vcpkg.

## Building

To build MyGame, you'll need to install CMake and a C++ compiler. Here are the steps to build the project:

1. Clone the repository:
    git clone https://github.com/thelapfox/cpp-engine.git

2. Navigate to the project directory:
    cd cpp-engine

3. Create a build directory:
    mkdir build
    cd build

4. Generate build files using CMake:
    cmake ..

5. Build the project using the generated build files:
    make

6. Run the game:
    ./bin/cpp-engine.exe

## License

cpp-engine is released under the MIT License. See LICENSE for more information.
