cmake_minimum_required(VERSION 3.31)
set(CMAKE_PROJECT_TOP_LEVEL_INCLUDES .devcontainer/cmake/xproinc.cmake)
project(wxInclude)
xpFindPkg(PKGS boost)
add_executable(${CMAKE_PROJECT_NAME} wxInclude.cpp)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE Boost::filesystem Boost::program_options Boost::timer)
set(targetsFile ${PROJECT_NAME}-targets)
if(DEFINED XP_NAMESPACE)
  xpExternPackage(NAMESPACE ${XP_NAMESPACE}
    TARGETS_FILE ${targetsFile} EXE ${CMAKE_PROJECT_NAME}
    BASE v1.0 XPDIFF "intro" PVT_DEPS boost
    WEB "http://wiki.wxwidgets.org/Embedding_PNG_Images"
    DESC "embed resources into cross-platform code"
    LICENSE "[wxWindows](http://wiki.wxwidgets.org/Embedding_PNG_Images 'assumed wxWindows license, since source can be downloaded from wxWiki')"
    )
  set(nameSpace NAMESPACE ${XP_NAMESPACE}::)
elseif(NOT DEFINED XP_INSTALL_CMAKEDIR)
  set(XP_INSTALL_CMAKEDIR ${CMAKE_INSTALL_DATADIR}/cmake)
endif()
install(TARGETS ${CMAKE_PROJECT_NAME} EXPORT ${targetsFile}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  )
install(EXPORT ${targetsFile} DESTINATION ${XP_INSTALL_CMAKEDIR} ${nameSpace})
add_executable(decompressor decompress.cpp)
target_link_libraries(decompressor PRIVATE Boost::filesystem Boost::iostreams)
