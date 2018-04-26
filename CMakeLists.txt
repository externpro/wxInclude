cmake_minimum_required(VERSION 3.6)
project(wxInclude)
include(flags)
set(Boost_LIBS filesystem program_options system)
set(XP_MODULE_PATH ${CMAKE_MODULE_PATH})
add_executable(${CMAKE_PROJECT_NAME} wxInclude.cpp)
xpTargetExtern(${CMAKE_PROJECT_NAME} PRIVATE boost)
string(TOLOWER ${PROJECT_NAME} prj)
install(TARGETS ${CMAKE_PROJECT_NAME} EXPORT ${prj}-targets
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  )
install(EXPORT ${prj}-targets DESTINATION bin/cmake)
