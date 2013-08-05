cmake_minimum_required(VERSION 2.8.10)
project(wxInclude)
include(flags OPTIONAL)
set(externpro ${CMAKE_INSTALL_PREFIX})
if(UNIX)
  # see FindBoost.cmake for details on the following variables
  set(Boost_NO_SYSTEM_PATHS TRUE)
  #set(Boost_USE_STATIC_LIBS ON)
  #set(Boost_USE_MULTITHREADED ON)
  #set(Boost_USE_STATIC_RUNTIME ON)
  #set(Boost_DEBUG TRUE) # enable debugging output of FindBoost.cmake
  #set(Boost_DETAILED_FAILURE_MSG) # output detailed information
  set(Boost_ROOT ${externpro})
  # TODO: remove the following conditional (setting _boost_COMPILER)
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
      set(_boost_COMPILER -clang-darwin${CLANG_VERSION})
    else()
      set(_boost_COMPILER -clang${CLANG_VERSION})
    endif()
  endif()
  find_package(Boost 1.49 REQUIRED COMPONENTS filesystem)
  include_directories(${Boost_INCLUDE_DIRS})
else()
  include_directories(${externpro}/include/boost-1_49)
endif()
add_executable(${CMAKE_PROJECT_NAME} wxInclude.cpp)
target_link_libraries(${CMAKE_PROJECT_NAME} ${Boost_LIBRARIES})
install(TARGETS ${CMAKE_PROJECT_NAME} DESTINATION bin${NUMBITS})
