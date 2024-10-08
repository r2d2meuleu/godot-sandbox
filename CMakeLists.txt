cmake_minimum_required(VERSION 3.9.4)
project(riscv CXX)

option(SANITIZE    "Enable sanitizers" OFF)
option(STATIC_BUILD "Build statically" OFF)

set(SOURCES
	src/cpp/resource_loader_cpp.cpp
	src/cpp/resource_saver_cpp.cpp
	src/cpp/script_cpp.cpp
	src/cpp/script_language_cpp.cpp
	src/elf/resource_loader_elf.cpp
	src/elf/resource_saver_elf.cpp
	src/elf/script_elf.cpp
	src/elf/script_instance.cpp
	src/elf/script_language_elf.cpp
	src/rust/resource_loader_rust.cpp
	src/rust/resource_saver_rust.cpp
	src/rust/script_rust.cpp
	src/rust/script_language_rust.cpp
	src/docker.cpp
	src/godot/script_instance.cpp
	src/gvar.cpp
    src/register_types.cpp
    src/sandbox.cpp
    src/sandbox_functions.cpp
	src/sandbox_project_settings.cpp
	src/syscalls.cpp

	src/tests/assault.cpp
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")

if (MINGW)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libgcc -static-libstdc++ -static")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")
endif()

# Add godot-cpp library
add_subdirectory(godot-cpp)

# Add sandboxing library
option(RISCV_BINARY_TRANSLATION "" ON)
add_subdirectory(libriscv/lib libriscv)
target_compile_definitions(riscv PUBLIC
	RISCV_SYSCALLS_MAX=600
	RISCV_BRK_MEMORY_SIZE=0x100000  # 1MB (we don't need much)
)
if (RISCV_BINARY_TRANSLATION AND RISCV_LIBTCC)
	target_compile_options(libtcc PRIVATE -fPIC)
endif()

add_library(godot-riscv SHARED ${SOURCES})
target_link_libraries(godot-riscv PUBLIC riscv godot-cpp)

if (STATIC_BUILD)
    target_link_libraries(godot-riscv PUBLIC -static)
endif()
if (SANITIZE)
	#target_compile_options(godot-riscv PUBLIC -fsanitize=scudo,undefined)
	#target_link_libraries(godot-riscv PUBLIC -fsanitize=scudo,undefined -L/usr/lib/llvm-18/lib/clang/18/lib/linux -l:libclang_rt.ubsan_standalone-x86_64.so -l:libclang_rt.scudo_standalone-x86_64.so -Wl,-rpath=/usr/lib/llvm-18/lib/clang/18/lib/linux)
	target_compile_options(godot-riscv PUBLIC -fsanitize=undefined -fno-sanitize=vptr)
	target_link_libraries(godot-riscv PUBLIC -fsanitize=undefined -L/usr/lib/llvm-18/lib/clang/18/lib/linux -l:libclang_rt.ubsan_standalone-x86_64.a)
endif()
