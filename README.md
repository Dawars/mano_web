## Interactive Hand Viewer

#### Web demo

[Interactive web demo](https://dawars.me/mano/) for visualizing the **shape** parameters

<img src="https://dawars.me/mano/images/banner.png" alt="Mano viewer" />


### Used technologies

* WebAssembly - LLVM compile target for the web
* ThreeJS - 3D rendering library
* Eigen - linear algebra library

## How to build

The project uses the CMake build system

#### Install emscripten

Set the following environment variable: 
`LLVM_ROOT=/usr/local/opt/emscripten/libexec/llvm/bin`


#### CMake arguments
`-DCMAKE_TOOLCHAIN_FILE=/home/linuxbrew/.linuxbrew/opt/emscripten/libexec/cmake/Modules/Platform/Emscripten.cmake`

To copy the web related files to the build directory run:
`cmake install`

### Build manually
`emcc main.cpp [header files here] -s NO_EXIT_RUNTIME=1 -s WASM=1 -O3 -s MODULARIZE=1 -s EXPORT_NAME=ManoModule -s EXTRA_EXPORTED_RUNTIME_METHODS=[ccall,cwrap] --llvm-lto 3`

