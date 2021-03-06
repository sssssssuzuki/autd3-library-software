cmake_minimum_required(VERSION 3.1)

set (CMAKE_CXX_STANDARD 17)

set(EIGEN_PATH ../deps/Eigen3)
include_directories(../include ${EIGEN_PATH} examples)

file(GLOB hpp_files examples/*.hpp)

if(USE_DOUBLE)
add_definitions(-DUSE_DOUBLE_AUTD)
endif()

add_executable(example_soem soem.cpp ${hpp_files})
target_link_libraries(example_soem autd3)
target_link_libraries(example_soem soem_link)

if(WIN32)
    target_link_libraries(example_soem ws2_32.lib)
    target_link_libraries(example_soem winmm.lib)
elseif(APPLE)
    target_link_libraries(example_soem pcap)
else()
    target_link_libraries(example_soem rt)
endif()

add_executable(example_debug debug.cpp ${hpp_files})
target_link_libraries(example_debug autd3)
if(WIN32)
    target_link_libraries(example_debug ws2_32.lib)
    target_link_libraries(example_debug winmm.lib)
elseif(APPLE)
    target_link_libraries(example_debug pcap)
else()
    target_link_libraries(example_debug rt)
endif()

if(WIN32)
    add_executable(example_twincat twincat.cpp ${hpp_files})
    target_link_libraries(example_twincat autd3)
    target_link_libraries(example_twincat ws2_32.lib)
    target_link_libraries(example_twincat winmm.lib)
    target_link_libraries(example_twincat twincat_link)

    add_executable(example_emulator emulator.cpp ${hpp_files})
    target_link_libraries(example_emulator autd3)
    target_link_libraries(example_emulator ws2_32.lib)
    target_link_libraries(example_emulator winmm.lib)
endif()
