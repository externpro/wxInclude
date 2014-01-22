cmake_minimum_required(VERSION 2.8.10)
project(wxInclude)
include(flags OPTIONAL)
set(externpro ${CMAKE_INSTALL_PREFIX})
########################################
# find boost
# see FindBoost.cmake for details on the following variables
set(BOOST_ROOT ${externpro})
set(BOOST_LIBRARYDIR ${externpro}/lib${NUMBITS})
set(Boost_NO_BOOST_CMAKE TRUE)
set(Boost_NO_SYSTEM_PATHS TRUE)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_STATIC_RUNTIME ON)
# TODO: remove the following conditional (setting Boost_COMPILER)
#       once FindBoost.cmake detects clang
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  exec_program(${CMAKE_CXX_COMPILER}
    ARGS ${CMAKE_CXX_COMPILER_ARG1} -dumpversion
    OUTPUT_VARIABLE CLANG_VERSION
    )
  string(REGEX REPLACE "([0-9])\\.([0-9])(\\.[0-9])?" "\\1\\2"
    CLANG_VERSION ${CLANG_VERSION}
    )
  if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(Boost_COMPILER -clang-darwin${CLANG_VERSION})
  else()
    set(Boost_COMPILER -clang${CLANG_VERSION})
  endif()
endif()
if(DEFINED BOOST_VER)
  message(STATUS "Searching for specific Boost version: ${BOOST_VER}")
endif()
if(MSVC)
  # NOTE: use automatic linking of boost libraries with MSVC
  find_package(Boost ${BOOST_VER} REQUIRED)
  link_directories(${externpro}/lib${NUMBITS})
  add_definitions(-D_CRT_SECURE_NO_WARNINGS) # wxInclude.cpp calls snprintf
else()
  find_package(Boost ${BOOST_VER} REQUIRED COMPONENTS
    filesystem
    program_options
    system
    )
endif()
include_directories(${Boost_INCLUDE_DIRS})
########################################
add_executable(${CMAKE_PROJECT_NAME} wxInclude.cpp)
target_link_libraries(${CMAKE_PROJECT_NAME} ${Boost_LIBRARIES})
install(TARGETS ${CMAKE_PROJECT_NAME} DESTINATION bin${NUMBITS})
