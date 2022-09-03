cmake_minimum_required(VERSION 3.20)
project(wxInclude)
include(GNUInstallDirs)
include(flags)
set(XP_MODULE_PATH ${CMAKE_MODULE_PATH})
xpFindPkg(PKGS boost)
add_executable(${CMAKE_PROJECT_NAME} wxInclude.cpp)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE Boost::filesystem Boost::program_options Boost::timer)
string(TOLOWER ${PROJECT_NAME} prj)
install(TARGETS ${CMAKE_PROJECT_NAME} EXPORT ${prj}-targets
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  )
if(DEFINED XP_NAMESPACE)
  set(nameSpace NAMESPACE ${XP_NAMESPACE}::)
endif()
if(NOT DEFINED XP_INSTALL_CMAKEDIR)
  set(XP_INSTALL_CMAKEDIR ${CMAKE_INSTALL_DATADIR}/cmake)
endif()
install(EXPORT ${prj}-targets DESTINATION ${XP_INSTALL_CMAKEDIR} ${nameSpace})
add_executable(decompressor decompress.cpp)
target_link_libraries(decompressor PRIVATE Boost::filesystem Boost::iostreams)
