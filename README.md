# Snake

This is my take on the classic game snake/slither. Made with Raylib.

Raylib and cmocka are statically linked, so to build this program, compile raylib and cmocka (for tests) from source into .a files and drop them into the lib/ directory. The headers are already copy/pasted from their respective repositories into include/ (raylib.h and cmocka.h).

### Building cmocka

- `git clone git@github.com:clibs/cmocka.git`
- `cd cmocka`
- `mkdir build`
- `cd build`
- `cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr/local -DBUILD_SHARED_LIBS=OFF -DWITH_EXAMPLES=OFF -DWITH_TESTS=OFF`
- `make`

Then, copy `libcmocka.a` into lib/ at the root of the project.

### Building raylib

Taken + modified from the raylib github repository under MacOS instructions):

- `git clone https://github.com/raysan5/raylib.git`
- `cd raylib/src`
- `make`

Then, copy `libraylib.a` into lib/ at the root of the project

### Building

- `mkdir build`
- `cd build`
- `cmake ..`
- `make`

Now you can run targets individually

### Running tests

- `cmake --build build --target run_test`

### Running the app

- `cmake --build build --target run`
