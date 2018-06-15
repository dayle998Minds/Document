# cpp-netlib install
```
git clone git://github.com/cpp-netlib/cpp-netlib.git
cd cpp-netlib
git checkout cpp-netlib-0.12.0-final 
git submodule update --init --recursive
cd ..
mkdir cpp-netlib-build && cd cpp-netlib-build
cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_C_COMPILER=gcc   -DCMAKE_CXX_COMPILER=g++ ../cpp-netlib
make -j4
make test
sudo amke install
```
make test시 15번 테스트에서 failed이 발생하나 이문제는 비정상적인 접근에 의한 에러이므로 skip해도 된다.\
참조 https://github.com/cpp-netlib/cpp-netlib/issues/286 \
`15/18 Test #15: cpp-netlib-http-client_get_streaming_test ...........***Failed    1.84 sec`
설치가 완료되면 아래와 같이 header파일은 /usr/local/include/ 에 lib파일은 /usr/local/lib/libcppnetlib 로 설치되는것을 확인할수 있다.
```
install the project...
/usr/bin/cmake -P cmake_install.cmake
-- Install configuration: "Debug"
-- Up-to-date: /usr/local/include/boost
...
-- Installing: /usr/local/lib/libcppnetlib-uri.a
-- Installing: /usr/local/lib/libcppnetlib-server-parsers.a
-- Installing: /usr/local/lib/libcppnetlib-client-connections.a
-- Installing: /usr/local/lib/libgmock.a
-- Installing: /usr/local/lib/libgmock_main.a
```
# Using cpp-netlib
## CMake projects
 Projects using CMake can add the following lines in their CMakeLists.txt to be able to use cpp-netlib:
```
 set ( CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} ~/cpp-netlib-build )
 find_package ( cppnetlib 0.11.0 REQUIRED )
 include_directories ( ${CPPNETLIB_INCLUDE_DIRS} )
 target_link_libraries ( MyApplication ${CPPNETLIB_LIBRARIES} )
```
CMAKE_PREFIX_PATH의 경우 default로 /usr/local를 찾는 경우는 set을 안해도 된다.

## 참조
<https://cpp-netlib.org/0.11.0/getting_started.html>\
<https://cpp-netlib.org/0.9.4/examples>
 