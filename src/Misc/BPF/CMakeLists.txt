find_program(CLANG_COMPILER clang)

if(NOT CLANG_COMPILER)
    message(FATAL_ERROR "Clang compiler not found. Please install clang to build the BPF program.")
else()
    set(CMAKE_C_COMPILER "${CLANG_COMPILER}")
endif()

set(BPF_SOURCE_FILE "${CMAKE_CURRENT_SOURCE_DIR}/cgroup_dev_bpf.c")
set(BPF_OBJECT_FILE "${CMAKE_CURRENT_BINARY_DIR}/cgroup_dev_bpf.o")

if(CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64")
    set(BPF_ARCH "__TARGET_ARCH_x86")
elseif(CMAKE_SYSTEM_PROCESSOR STREQUAL "aarch64")
    set(BPF_ARCH "__TARGET_ARCH_arm64")
elseif(CMAKE_SYSTEM_PROCESSOR STREQUAL "arm")
    set(BPF_ARCH "__TARGET_ARCH_arm")
else()
    message(FATAL_ERROR "Unsupported architecture: ${CMAKE_SYSTEM_PROCESSOR}")
endif()


set(BPF_DEBUG_MODE "-DBPF_DEBUG")

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    list(APPEND BPF_COMPILE_OPTIONS -g -O2)
elseif(CMAKE_BUILD_TYPE STREQUAL "Debug")
    list(APPEND BPF_COMPILE_OPTIONS ${CMAKE_C_FLAGS_DEBUG} -O2 ${BPF_DEBUG_MODE})
elseif(CMAKE_BUILD_TYPE STREQUAL "MinSizeRel")
    list(APPEND BPF_COMPILE_OPTIONS -g -O2)
elseif(CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
    list(APPEND BPF_COMPILE_OPTIONS -g -O2)
else()
    message(FATAL_ERROR "Unknown build type: ${CMAKE_BUILD_TYPE}")
endif()

add_custom_command(
    OUTPUT ${BPF_OBJECT_FILE}
    COMMAND ${CMAKE_C_COMPILER} -target bpf ${BPF_COMPILE_OPTIONS} -D${BPF_ARCH} -c ${BPF_SOURCE_FILE} -o ${BPF_OBJECT_FILE}
    DEPENDS ${BPF_SOURCE_FILE}
    COMMENT "Building BPF object: ${BPF_OBJECT_FILE}"
)

add_custom_target(cgroup_dev_bpf_object ALL
    DEPENDS ${BPF_OBJECT_FILE}
)





