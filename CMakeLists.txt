cmake_minimum_required(VERSION 3.20)

project(wxInclude)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# -----------------------------
# Build wxInclude
# -----------------------------

find_package(Boost COMPONENTS program_options timer REQUIRED)

add_executable(wxInclude wxInclude.cpp)

target_include_directories(wxInclude PRIVATE
                           ${Boost_INCLUDE_DIRS}
)

target_link_libraries(wxInclude PRIVATE
                      Boost::boost
                      Boost::program_options
                      Boost::timer
)

install(TARGETS wxInclude DESTINATION bin)

# -----------------------------
# Build decompressor
# -----------------------------

find_package(Boost COMPONENTS iostreams REQUIRED)
find_package(BZip2 REQUIRED)
find_package(ZLIB REQUIRED)

add_executable(decompressor decompress.cpp)

target_include_directories(decompressor PRIVATE
                           ${Boost_INCLUDE_DIRS}
)

target_link_libraries(decompressor PRIVATE
                      Boost::boost
                      Boost::iostreams
                      BZip2::BZip2
                      ZLIB::ZLIB
)

install(TARGETS decompressor DESTINATION bin)