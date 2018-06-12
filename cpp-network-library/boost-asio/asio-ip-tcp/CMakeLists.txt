# 요구 CMake 최소 버전
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

# 프로젝트 이름 및 버전
PROJECT("scoped_ptr" CXX)
SET(OUTPUT_BIN "scoped_ptr")

SET(PROJECT_VERSION_MAJOR 0)
SET(PROJECT_VERSION_MINOR 1)

include_directories("${CMAKE_INSTALL_PREFIX}/include")
link_directories("${CMAKE_INSTALL_PREFIX}/lib")

set(CMAKE_CXX_STANDARD 11)
if (CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif ()

# 출력 디렉토리
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BUILD_TYPE})
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BUILD_TYPE}/lib)
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BUILD_TYPE}/lib)

# 빌드 대상 바이너리 추가
ADD_EXECUTABLE(asio-client client.cpp)
TARGET_LINK_LIBRARIES ( asio-client boost_system pthread)

ADD_EXECUTABLE(asio-server server.cpp)
TARGET_LINK_LIBRARIES ( asio-server boost_system pthread)