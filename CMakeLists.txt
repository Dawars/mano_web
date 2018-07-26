cmake_minimum_required(VERSION 3.7)
project(mano_cpp)

SET(CMAKE_BUILD_TYPE_INIT "Release")
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")
set(SOURCE_FILES mano.cpp mano/mean.h mano/indices.h mano/shapes.h mano/joints.h mano/weights.h)

include_directories(
        /emscripten/
        /emscripten/emscripten/incoming/system/include
        lib/eigen
)

add_executable(mano_cpp ${SOURCE_FILES})

set_target_properties(mano_cpp PROPERTIES LINK_FLAGS " -s NO_EXIT_RUNTIME=1 -s WASM=1 -O3 -s MODULARIZE=1 -s EXPORT_NAME=ManoModule -s EXTRA_EXPORTED_RUNTIME_METHODS=[ccall,cwrap] --llvm-lto 3")


file(INSTALL web/. DESTINATION .) # only runs when refreshing cmake