cmake_minimum_required(VERSION 3.0)
project(wxInclude)
include(flags OPTIONAL)
set(externpro ${CMAKE_INSTALL_PREFIX})
########################################
# find boost
# see FindBoost.cmake for details on the following variables
set(BOOST_ROOT ${externpro})
set(BOOST_LIBRARYDIR ${externpro}/lib)
set(Boost_NO_BOOST_CMAKE TRUE)
set(Boost_NO_SYSTEM_PATHS TRUE)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_STATIC_RUNTIME ON)
#set(Boost_DEBUG TRUE) # enable debugging output of FindBoost.cmake
#set(Boost_DETAILED_FAILURE_MSG TRUE) # output detailed information
# TODO: remove the following conditional (setting Boost_COMPILER)
#       once FindBoost.cmake detects clang
if("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
  if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    exec_program(${CMAKE_CXX_COMPILER}
      ARGS ${CMAKE_CXX_COMPILER_ARG1} -dumpversion
      OUTPUT_VARIABLE CLANG_VERSION
      )
    string(REGEX REPLACE "([0-9]+)\\.([0-9]+)(\\.[0-9]+)?"
      "-clang-darwin\\1\\2"
      Boost_COMPILER ${CLANG_VERSION}
      )
  else()
    string(REGEX REPLACE "([0-9]+)\\.([0-9]+)(\\.[0-9]+)?"
      "-clang\\1\\2"
      Boost_COMPILER ${CMAKE_CXX_COMPILER_VERSION}
      )
  endif()
endif()
if(DEFINED BOOST_VER)
  string(REGEX REPLACE "([0-9]+)\\.([0-9]+)(\\.[0-9]+)?" "\\1.\\2" BOOST_VER2 ${BOOST_VER})
  set(Boost_ADDITIONAL_VERSIONS ${BOOST_VER} ${BOOST_VER2})
  message(STATUS "Searching for specific Boost version: ${BOOST_VER}, ${BOOST_VER2}")
endif()
if(MSVC)
  # NOTE: use automatic linking of boost libraries with MSVC
  find_package(Boost ${BOOST_VER} REQUIRED)
  link_directories(${externpro}/lib)
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
string(TOLOWER ${PROJECT_NAME} prj)
install(TARGETS ${CMAKE_PROJECT_NAME} EXPORT ${prj}-targets
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  )
install(EXPORT ${prj}-targets DESTINATION bin/cmake)
