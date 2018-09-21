cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
project(Computer-Graphics-Libraries)

# set up versioning.
set(BUILD_MAJOR "0")
set(BUILD_MINOR "0")
set(BUILD_VERSION "0")
set(BUILD_VERSION ${BUILD_MAJOR}.${BUILD_MINOR}.${BUILD_VERSION})

include_directories(src)

SET(CGL_HEADERS

)

SET(CGL_SOURCES

)

set(DATA_FILE
README.md
)


find_package(GLM REQUIRED)
if (GLEW_FOUND)
    include_directories(${GLM_INCLUDE_DIRS})
    link_libraries(${GLM_LIBRARIES})
endif()

find_package(GLFW REQUIRED)
if (GLEW_FOUND)
    include_directories(${GLFW_INCLUDE_DIRS})
    link_libraries(${GLFW_LIBRARIES})
endif()


find_package(GLEW REQUIRED)
if (GLEW_FOUND)
    include_directories(${GLEW_INCLUDE_DIRS})
    link_libraries(${GLEW_LIBRARIES})
endif()


# mark headers as headers...
SET_SOURCE_FILES_PROPERTIES( ${CGL_HEADERS} PROPERTIES HEADER_FILE_ONLY TRUE )
# append to sources so that dependency checks work on headers
LIST(APPEND CGL_SOURCES ${CGL_HEADERS})

# OS and compiler checks.
if(UNIX)
    # linux / normal unix
    add_definitions(-D_LINUX)
    set(CMAKE_CXX_STANDARD 17)
    if(CGL_DEP_ONLY)
       if(CMAKE_BUILD_TYPE MATCHES Debug)
         message("Building 'Debug' configuration.")
       elseif(CMAKE_BUILD_TYPE MATCHES Release)
         message("Building 'Release' configuration.")
       else()
         set(CMAKE_BUILD_TYPE Release)
         message("Defaulting to 'Release' configuration.")
       endif()
    endif()
    if(CYGWIN)
        # Special Cygwin stuff here
    elseif(APPLE)
        # Special Apple stuff here
        remove_definitions(-D_LINUX)
        add_definitions(-D_DARWIN)
    endif()
elseif(WIN32)
    add_definitions(-D_WIN32)
    if(MINGW)
        # Special MINGW stuff here
    elseif(MSVC)
        # Special MSVC stuff here
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")
    else()
        # No idea what it is, but there's a good chance it's too weird.
        MESSAGE( FATAL_ERROR "Using unknown WIN32 compiler... NOT. Please add to build system." )
    endif()
endif()

OPTION(CGL_DEP_ONLY "Build for use inside other CMake projects as dependency." OFF)

# make the lib
if(CGL_DEP_ONLY)
    ADD_LIBRARY(Computer-Graphics-Libraries STATIC EXCLUDE_FROM_ALL ${CGL_SOURCES} ${DATA_FILE})
else()
    ADD_LIBRARY(Computer-Graphics-Libraries STATIC ${CGL_SOURCES} ${DATA_FILE})
endif()

TARGET_LINK_LIBRARIES(Computer-Graphics-Libraries ${PROJECT_LIBS})

# install into configured prefix
if(NOT CGL_DEP_ONLY)
    install(TARGETS Computer-Graphics-Libraries ARCHIVE DESTINATION lib LIBRARY DESTINATION lib)
    install(FILES ${CGL_HEADERS} DESTINATION include)
endif()

set_target_properties(Computer-Graphics-Libraries PROPERTIES VERSION ${BUILD_VERSION} SOVERSION ${BUILD_MAJOR})

