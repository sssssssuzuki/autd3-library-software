cmake_minimum_required(VERSION 3.10)

set (CMAKE_CXX_STANDARD 17)

execute_process(COMMAND git submodule update)
message("-- Updating git submodule done")

set(SOEM_PATH ./SOEM)

if(WIN32)
	set(OS win32)
elseif(APPLE)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -arch arm64 -arch x86_64")
	set(OS macosx)
else()
	set(OS linux)
endif()

include_directories(
	../include
	${SOEM_PATH}/soem
	${SOEM_PATH}/osal
	${SOEM_PATH}/osal/${OS}
	${SOEM_PATH}/oshw/${OS}
)

if(WIN32)
	include_directories(
		${SOEM_PATH}/oshw/${OS}/wpcap/Include
		${SOEM_PATH}/oshw/${OS}/wpcap/Include/pcap
	)
endif()

if(WIN32)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4996")
endif()

file(GLOB_RECURSE SRC_FILES ${SOEM_PATH}/soem/*.c ${SOEM_PATH}/osal/${OS}/*.c ${SOEM_PATH}/oshw/${OS}/*.c)
#SET_SOURCE_FILES_PROPERTIES(${SRC_FILES} PROPERTIES LANGUAGE CXX)

add_library(soem STATIC ${SRC_FILES})

if(NOT WIN32)
  set_target_properties(soem PROPERTIES POSITION_INDEPENDENT_CODE ON)
endif()
