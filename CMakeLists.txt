cmake_minimum_required(VERSION 2.8)
project(TaskSys)

IF (CMAKE_BUILD_TYPE STREQUAL "")
    set(CMAKE_BUILD_TYPE "Debug")
ENDIF()

IF (USE_LIBC++)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
ENDIF()

IF (CMAKE_BUILD_TYPE MATCHES Debug)
    message("Building in debug mode.")

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D TASKSYS_DEBUG")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wextra")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-parameter")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-variable")
ELSEIF (CMAKE_BUILD_TYPE MATCHES RELEASE)
    message("Building in release mode.")

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")

ENDIF ()

#set(CMAKE_CXX_FLAGS_DEBUG  "${CMAKE_CXX_FLAGS} -Wall")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++1z")


set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH    ${PROJECT_SOURCE_DIR}/lib)

set(SRC_FILES
        src/task_queue.cpp
        src/task.cpp
        )


message("Building on ${CMAKE_HOST_SYSTEM_NAME} platform.")
if (${CMAKE_HOST_SYSTEM_NAME} MATCHES "Linux")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D TASKSYS_LINUX")


ELSEIF (${CMAKE_HOST_SYSTEM_NAME} MATCHES "Darwin")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D TASKSYS_DARWIN")
    set(CMAKE_MACOSX_RPATH ON)

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-c++1z-extensions")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unknown-escape-sequence")

ELSEIF (${CMAKE_HOST_SYSTEM_NAME} MATCHES "Windows")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D TASKSYS_LINUX")

endif ()


if (TASKSYS_TRACE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D TASKSYS_TRACE")
endif()


link_directories(${PROJECT_SOURCE_DIR}/lib)
include_directories(${PROJECT_SOURCE_DIR}/include)

############################################################
#
# Boost Config
#
############################################################

find_package(Boost REQUIRED COMPONENTS context coroutine)
link_directories(${Boost_LIBRARY_DIRS})
include_directories(${Boost_INCLUDE_DIRS})


set(DEP_LIBS boost_coroutine-mt boost_context-mt curl)

set(LIBS tasksys ${DEP_LIBS})

message("Building libraries: ${LIBS}")
message("Building flags: ${CMAKE_CXX_FLAGS}")

add_library(tasksys STATIC ${SRC_FILES} )

add_library(tasksys_dynamic SHARED src/task_queue.cpp)
set_target_properties(tasksys_dynamic PROPERTIES OUTPUT_NAME tasksys)
target_link_libraries(tasksys_dynamic TASKSYS ${DEP_LIBS})


if (BUILD_TEST)

    set(TEST_SRC_FILES
            test/simulator.cpp
            test/test.cpp
            )
    add_executable(test ${TEST_SRC_FILES})
    target_link_libraries(test ${LIBS})

endif()

#if (BUILD_EXAMPLE)
#    add_subdirectory(example)
#endif()

message("${INCLUDE_DIRECTORIES}")
message("${CXX_INCLUDE}")

