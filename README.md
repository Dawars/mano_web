## How to build

### Optional for Homebrew

LLVM_ROOT=/usr/local/opt/emscripten/libexec/llvm/bin


## Manual build
`emcc main.cpp -s NO_EXIT_RUNTIME=1 -s WASM=1 -O3 --shell-file shell.html -s MODULARIZE=1 -s EXPORT_NAME=StartModule -s EXPORTED_FUNCTIONS=[_main,_manoUpdateGeometry,_malloc,_free] -s EXTRA_EXPORTED_RUNTIME_METHODS=[ccall,cwrap] -o build/HandVR.html`

### CMake args
`-DCMAKE_TOOLCHAIN_FILE=/home/linuxbrew/.linuxbrew/opt/emscripten/libexec/cmake/Modules/Platform/Emscripten.cmake`
