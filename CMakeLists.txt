cmake_minimum_required(VERSION 2.8)
project(rdp)

#set (CMAKE_CXX_STANDARD 11)

#find_package(PkgConfig REQUIRED)
find_package(OpenCV REQUIRED)
find_library(FFTW_LIBRARY NAMES fftw3)

file(GLOB CPPFILES "source/*.cpp" "source/*.h")
add_executable(rdp ${CPPFILES})

target_link_libraries(rdp ${OpenCV_LIBS} ${FFTW_LIBRARY} -pg)
