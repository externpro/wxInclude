cmake_minimum_required(VERSION 3.6)
project(wxInclude)
include(flags)
set(Boost_LIBS filesystem program_options system)
set(XP_MODULE_PATH ${CMAKE_MODULE_PATH})
xpGetExtern(externIncs externLibs PUBLIC boost)
add_executable(${CMAKE_PROJECT_NAME} wxInclude.cpp)
target_include_directories(${CMAKE_PROJECT_NAME} ${externIncs})
target_link_libraries(${CMAKE_PROJECT_NAME} ${externLibs})
string(TOLOWER ${PROJECT_NAME} prj)
install(TARGETS ${CMAKE_PROJECT_NAME} EXPORT ${prj}-targets
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  )
install(EXPORT ${prj}-targets DESTINATION bin/cmake)
