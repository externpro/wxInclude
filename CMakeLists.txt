cmake_minimum_required(VERSION 4.3)
project(wxInclude)
find_package(Boost)
add_executable(${PROJECT_NAME} wxInclude.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE Boost::chrono Boost::filesystem Boost::program_options Boost::timer)
set(targetsFile ${PROJECT_NAME}-targets)
if(COMMAND xpExternPackage)
  xpExternPackage(TARGETS_FILE ${targetsFile} EXE ${PROJECT_NAME}
    BASE v1.0 XPDIFF "intro"
    WEB "http://wiki.wxwidgets.org/Embedding_PNG_Images"
    DESC "embed resources into cross-platform code"
    LICENSE "[wxWindows](http://wiki.wxwidgets.org/Embedding_PNG_Images 'assumed wxWindows license, since source can be downloaded from wxWiki')"
    )
elseif(NOT DEFINED CMAKE_INSTALL_CMAKEDIR)
  set(CMAKE_INSTALL_CMAKEDIR ${CMAKE_INSTALL_DATADIR}/cmake)
endif()
install(TARGETS ${PROJECT_NAME} EXPORT ${targetsFile}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  )
install(EXPORT ${targetsFile} DESTINATION ${CMAKE_INSTALL_CMAKEDIR} NAMESPACE ${PROJECT_NAME}::)
add_executable(decompressor decompress.cpp)
target_link_libraries(decompressor PRIVATE Boost::filesystem Boost::iostreams)
