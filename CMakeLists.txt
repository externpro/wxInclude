cmake_minimum_required(VERSION 3.12)
project(wxInclude)
include(flags)
set(XP_MODULE_PATH ${CMAKE_MODULE_PATH})
xpFindPkg(PKGS boost)
add_executable(${CMAKE_PROJECT_NAME} wxInclude.cpp)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE Boost::filesystem Boost::program_options)
string(TOLOWER ${PROJECT_NAME} prj)
install(TARGETS ${CMAKE_PROJECT_NAME} EXPORT ${prj}-targets
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  )
if(DEFINED XP_NAMESPACE)
  set(nameSpace NAMESPACE ${XP_NAMESPACE}::)
endif()
install(EXPORT ${prj}-targets DESTINATION bin/cmake ${nameSpace})
add_executable(decompressor decompress.cpp)
target_link_libraries(decompressor PRIVATE Boost::filesystem Boost::iostreams)
