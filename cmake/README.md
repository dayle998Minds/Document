# SET() 변수 정의
### 변수 정의
`SET ( <변수명> <값> )`\
<값>에 공백이 포함되어 있는 경우, 큰따옴표 "..." 사용
```
SET ( PROJECT_VERSION_MAJOR 0 )
SET ( CMAKE_C_FLAGS_DEBUG "-DDEBUG -DC_FLAGS" )
SET ( SOURCE_FILES "benchmark.cc" "colorprint.cc" "commandlineflags.cc" )
```

### 변수 참조
```
$변수명
${<변수명>}
```
```
SET ( SRC_FILES main.c foo.c bar.c )
ADD_EXECUTABLE ( app.out ${SRC_FILES} )
```
# 프로젝트 전체
### PROJECT() - 프로젝트 이름 설정
```
PROJECT ( <프로젝트명> )
```
### CMAKE_BUILD_TYPE - 빌드 형상(Configuration)
CMake에서는 기본적으로 다음과 같이 네 가지 빌드 형상을 지원하며, 필요한 경우 사용자 정의 빌드 형상을 정의 가능
- Debug : 디버깅 목적의 빌드
- Release : 배포 목적의 빌드
- RelWithDebInfo : 배포 목적의 빌드지만, 디버깅 정보 포함
- MinSizeRel : 최소 크기로 최적화한 배포 목적 빌드
```
SET(CMAKE_BUILD_TYPE Debug)
```
### CMAKE_VERBOSE_MAKEFILE - Verbose Makefile 작성 여부
```
SET ( CMAKE_VERBOSE_MAKEFILE true )
```
### CMAKE_MINIMUM_REQUIRED() - 필요 CMake 최소 버전 명시
```
CMAKE_MINIMUM_REQUIRED ( VERSION <버전> )
```
### PROJECT() - 프로젝트 이름 설정
```
PROJECT ( <프로젝트명> )
```
### MESSAGE() - 콘솔에 메시지 출력
`MESSAGE ( [<Type>] <메시지> )`\
type의 종류
- STATUS : 상태 메시지 출력 (메시지 앞에 '--'가 추가되서 출력됨)
- WARNING : 경고 메시지를 출력하고, 계속 진행
- AUTHOR_WARNING : 프로젝트 개발자용 경고 메시지를 출력하고, 계속 진행
- SEND_ERROR : 오류 메시지를 출력하고 계속 진행하지만, Makefile 생성은 하지 않음
- FATAL_ERROR : 오류 메시지를 출력하고, 작업을 즉시 중단
```
MESSAGE ( FATAL_ERROR "Fatal error occurred!" )
```
## 빌드 대상(Target) 관련
### ADD_EXECUTABLE() - 빌드 대상 바이너리 추가
빌드 최종 결과물로 생성할 실행 파일을 추가합니다. 이 명령을 반복하여 생성할 실행 파일을 계속 추가할 수 있습니다.\
```
ADD_EXECUTABLE ( <실행_파일명> <소스_파일> <소스_파일> ... )
```
- <실행_파일명> : 생성할 바이너리의 파일명
- <소스_파일> : 실행 파일을 생성하는 데 필요한 소스 파일
```
ADD_EXECUTABLE ( app.out main.c foo.c bar.c )
```
### ADD_LIBRARY() - 빌드 대상 라이브러리 추가
빌드 최종 결과물로 생성할 라이브러리를 추가합니다. 이 명령을 반복하여 생성할 라이브러리를 계속 추가할 수 있습니다.
```
ADD_LIBRARY ( <라이브러리_이름> [STATIC|SHARED|MODULE] <소스_파일> <소스_파일> ... )
```
- <라이브러리_이름> : 생성할 라이브러리 이름 (lib~.a / lib~.so 에서 ~에 들어갈 값)
- [STATIC|SHARED|MODULE] : 라이브러리 종류 (생략시 STATIC)
- <소스_파일> : 라이브러리를 생성하는 데 필요한 소스 파일
```
ADD_LIBRARY ( app STATIC foo.c bar.c )
```
### ADD_CUSTOM_TARGET() - 사용자 정의 Target 추가
```
ADD_CUSTOM_TARGET (
                <이름> [ALL]
                [COMMENT <출력_메시지>]
                [DEPENDS <의존_대상_목록>]
                [WORKING_DIRECTORY <작업_디렉토리>]
                COMMAND <명령>
                [COMMAND <명령>]
                ...
)
```
- <이름> : Target 이름
- [ALL] : make(또는 make all) 명령에서 기본 빌드 대상에 포함할 지 여부
- <출력_메시지>: 명령 실행 전에 콘솔에 출력할 메시지
- <의존_대상_목록>: 이 Target이 의존하는 대상 목록 (공백으로 구분)
- <작업_디렉토리>: 명령을 실행할 위치(pwd)
- <명령> : Target을 생성하기 위한 명령(Recipe)
```
ADD_CUSTOM_TARGET ( flash
        COMMENT "Flashing binary"
        WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
        COMMAND python esptool.py write_flash app.bin
        DEPENDS app.out
        )
```
### ADD_DEPENDENCIES() - Target간 의존성 정의
Top-level Target간의 의존성을 지정합니다. Top-level Target이란 ADD_EXECUTABLE, ADD_LIBRARY, ADD_CUSTOM_TARGET 명령으로 정의한 Target들을 의미합니다.

Target을 빌드할 때 이 명령으로 정의한 의존 대상들이 'Outdated'인 경우 이들에 대한 빌드를 먼저 수행합니다.
```
ADD_DEPENDENCIES ( <Target_이름> <의존_대상> <의존_대상> ... )
```
- <Target_이름> : Target 이름
- <의존_대상> : 이 Target이 의존하는 대상
```
ADD_DEPENDENCIES ( flash app.out )
```
다음 명령은 flash(매크로)가 app.out에 의존적임을 명시합니다. 이렇게 작성하고 'make flash'를 실행하면 app.out이 최신인지 여부를 먼저 검사해서 필요시 app.out을 먼저 빌드하고 flash 매크로를 실행합니다.

### INSTALL() - 설치 매크로(make install) 정의
'make install' 명령을 실행했을 때 무슨 동작을 수행할지를 지정\
빌드 완료된 실행 바이너리와 라이브러리 및 기타 부속물(헤더 파일, 리소스 등)들을 시스템의 적절한 위치로 복사하는 동작\
```

INSTALL ( TARGETS <Target_목록>
        RUNTIME DESTINATION <바이너리_설치_경로>
        LIBRARY DESTINATION <라이브러리_설치_경로>
        ARCHIVE DESTINATION <아카이브_설치_경로>
        )
## 설치 경로가 동일할경우        
INSTALL ( TARGETS <Target_목록> DESTINATION <설치_경로> )        
```
설치 경로가 상대 경로인 경우 CMAKE_INSTALL_PREFIX 변수에 지정한 경로 아래에 설치됩니다.
```
INSTALL ( TARGETS app.out app
        RUNTIME_DESTINATION /usr/local/bin
        ARCHIVE_DESTINATION /usr/local/lib
        )
```
 다음 명령은 app.out은 /usr/local/bin에, libapp.a는 /usr/local/lib에 설치하는 install target을 추가합니다.
### CMAKE_INSTALL_PREFIX - 설치 디렉토리
```
SET ( CMAKE_INSTALL_PREFIX /usr/bin )
```
## 전역 빌드 설정 관련
### CMAKE_C_COMPILER - C 컴파일러
```
set(CMAKE_C_COMPILER "/path/to/your/c/compiler/executable")
set(CMAKE_CXX_COMPILER "/path/to/your/cpp/compiler/executable")
```
### ADD_COMPILE_OPTIONS() - 컴파일 옵션 추가
```
ADD_COMPILE_OPTIONS( -g -Wall )
```
### CMAKE_C_FLAGS_<빌드_형상> - 빌드 형상별 컴파일 옵션
```
SET ( CMAKE_C_FLAGS_RELEASE "-DCONFIG_RELEASE -O3" )
```
### ADD_DEFINITIONS() - 전처리기 매크로 추가 (-D)
```
ADD_DEFINITIONS( -DICACHE_FLASH -DMY_DEBUG=1 )
```
### INCLUDE_DIRECTORIES() - 헤더 디렉토리 추가 (-I)
여러개를 중복으로 사용이 가능하다.
```
INCLUDE_DIRECTORIES ( include driver/include )
```
### LINK_DIRECTORIES() - 라이브러리 디렉토리 지정 (-L)
```
LINK_DIRECTORIES ( lib /var/lib )
```
### LINK_LIBRARIES() - 링크 옵션 추가
```
LINK_LIBRARIES ( uart wifi -static )
```
### CMAKE_EXE_LINKER_FLAGS_<빌드_형상> - 빌드 형상별 링크 옵션
특정 빌드 형상에서만 사용할 링크 옵션(플래그)를 지정합니다.

```
SET ( CMAKE_EXE_LINKER_FLAGS_DEBUG "-DCONFIG_DEBUG -Wl,-whole-archive" )
```
다음은 Debug 빌드시에만 CONFIG_DEBUG 매크로를 정의하고 모든 Symbol을 포함하도록 링크 옵션을 지정합니다.

### RUNTIME_OUTPUT_DIRECTORY - 실행 바이너리 출력 디렉토리
빌드 완료한 실행 바이너리를 저장할 디렉토리를 지정합니다.
```
SET ( RUNTIME_OUTPUT_DIRECTORY output/bin )
```
### LIBRARY_OUTPUT_DIRECTORY - 라이브러리 출력 디렉토리
빌드 완료한 라이브러리를 저장할 디렉토리를 지정합니다.
```
SET ( LIBRARY_OUTPUT_DIRECTORY output/lib )
```
### ARCHIVE_OUTPUT_DIRECTORY - 아카이브 출력 디렉토리
빌드 완료한 아카이브(Static 라이브러리)를 저장할 디렉토리를 지정합니다.
```
SET ( ARCHIVE_OUTPUT_DIRECTORY output/lib/static )
```
### 특정 Target 한정 빌드 설정 관련
명령들은 모두 'TARGET_'으로 시작하고, 첫 번째 인수는 Target 이름입니다. 이 명령들을 선언하기 전에 대상 Target은 반드시 미리 선언되어 있어야 한다.

### TARGET_COMPILE_OPTIONS() - Target 컴파일 옵션 추가
```
TARGET_COMPILE_OPTIONS ( app.out PUBLIC -g -Wall )
```
- <Target_이름> : Target 이름
- PUBLIC : 전역 컴파일 옵션 변수(COMPILE_OPTIONS)와 인터페이스 컴파일 옵션 변수(INTERFACE_COMPILE_OPTIONS)를 확장합니다. 보통의 경우 PUBLIC으로 두면 됩니다.
- <옵션> : 컴파일 옵션
### TARGET_COMPILE_DEFINITIONS() - Target 전처리기 매크로 정의 (-D)
Target의 소스 파일을 컴파일하여 Object 파일을 생성할 때 전처리기에 전달할 매크로를 정의합니다. 컴파일러 옵션중 -D에 해당합니다.
```
TARGET_COMPILE_DEFINITIONS ( app.out PUBLIC UART_BUFFERED -DICACHE DEBUG=1 )
```
### TARGET_INCLUDE_DIRECTORIES() - Target 헤더 디렉토리 추가 (-I)
Target에 포함된 소스 파일에서 #include 구문으로 포함시킨 헤더 파일을 찾을 디렉토리 목록을 추가합니다. 컴파일러 옵션중 -I에 해당합니다.
```
TARGET_INCLUDE_DIRECTORIES ( include driver/include )
```
### TARGET_LINK_LIBRARIES() - Target 링크 옵션 및 라이브러리 지정 (-l)
Target 링크시 포함할 라이브러리 목록을 지정합니다. 이 때, 라이브러리 파일명의 Prefix 및 Postfix는 제외하고 라이브러리 이름만 입력합니다. (e.g. libxxx.a에서 xxx에 해당하는 부분만 입력) 컴파일러 옵션중 -l에 해당합니다.
```
TARGET_LINK_LIBRARIES ( <Target_이름> <라이브러리> <라이브러리> ... )
```
이 명령으로 링크 옵션도 함께 지정할 수 있습니다. <라이브러리>값이 하이픈('-')으로 시작하는 경우 링크 명령에 그대로 포함되고, 그렇지 않은 경우 앞에 '-l'이 자동으로 추가됩니다.
```
TARGET_LINK_LIBRARIES ( app.out uart wifi -static )
```
# 빌드 절차(Build Step) 관련
### CONFIGURE_FILE() - 템플릿 파일로부터 파일 자동 생성
빌드 시작 직전에 템플릿 파일 내용 중 빌드 스크립트에 정의된 변수를 치환해서 출력 파일로 작성합니다. 컴파일러를 실행하기 전에 수행하는 '전전처리' 과정이라 할 수 있습니다.
```
CONFIGURE_FILE ( <템플릿_파일명> <출력_파일명> )
```
템플릿 파일 내용 중 ${<변수명>} 또는 @<변수명>@이 모두 변수 값으로 치환되어 출력 파일로 저장됩니다.
*CMakeLists.txt*
```
SET ( PROJECT_VERSION_MAJOR 1 )
SET ( PROJECT_VERSION_MINOR 0 )
SET ( PROJECT_VERSION_PATCH 9 )
SET ( PROJECT_VERSION_TWEAK 7 )
CONFIGURE_FILE ( version.h.in version.h )
```
*version.h.in*
```
#define VERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}.${PROJECT_VERSION_TWEAK}"
```
출력 파일인 version.h이 빌드 직전에 다음과 같이 자동 생성
*version.h*
```
#define VERSION "1.0.9.7"
```
### ADD_CUSTOM_COMMAND(OUTPUT) - 사용자 정의 출력 파일 추가
통상적인 빌드 절차로 생성할 수 없는 출력 파일을 추가합니다. 출력 파일의 Recipe를 직접 지정해야 하는 경우 유용하게 활용할 수 있습니다.
```
ADD_CUSTOM_COMMAND (
                OUTPUT <출력_파일_목록>
                [COMMENT <출력_메시지>]
                [DEPENDS <의존_대상_목록>]
                [WORKING_DIRECTORY <작업_디렉토리>]
                COMMAND <명령>
                [COMMAND <명령>]
                ...
)
```
- 생성하는 출력 파일들이 최신인지 여부를 검사해서 명령(Recipe)을 실행할지 여부를 결정합니다. 따라서, 사용자 정의 출력 파일을 생성하는 데 많은 시간이 걸리는 경우 사용하면 유용합니다.
- 명령(Recipe)을 실행했을 때 최소 한 개 이상의 출력 파일이 있어야 하며, Outdated 판정을 위해 출력 파일을 OUTPUT 인수로 명시해야 합니다. 
```
ADD_CUSTOM_COMMAND (
                OUTPUT app.bin
                COMMENT "Generating binary from executable"
                DEPENDS app.out
                COMMAND python tools/elf2bin.py app.out app.bin
)
```
예) 다음은 app.out으로부터 임베디드 프로세서에 Flashing하기 위한 app.bin을 생성하는 명령입니다.
### ADD_CUSTOM_COMMAND(TARGET) - 빌드 과정 명령 추가
특정 Target의 빌드 전(Pre-build)/중(Pre-link)/후(Post-build)에 수행할 명령을 추가합니다.\
ELF파일로부터 임베디드 프로세서에 Flashing하기 위한 BIN파일을 생성하는 것과 같이 통상적인 빌드 과정에서 수행되는 명령으로는 처리할 수 없는 동작을 빌드 대상물에 수행해 줘야 할 필요가 있을 경우 사용합니다.
```
ADD_CUSTOM_COMMAND (
                TARGET <대상_Target_이름>
                <PRE_BUILD|PRE_LINK|POST_BUILD>
                [COMMENT <출력_메시지>]
                [WORKING_DIRECTORY <작업_디렉토리>]
                COMMAND <명령>
                [COMMAND <명령>]
                ...
)
```
- <대상_Target_이름> : 여기 지정한 Target의 빌드 과정을 대상으로 합니다.
- <PRE_BUILD|PRE_LINK|POST_BUILD> : 명령 실행 시점
```
ADD_CUSTOM_COMMAND (
                TARGET app.out
                POST_BUILD
                COMMENT "Generating binary from executable"
                COMMAND python tools/elf2bin.py app.out app.bin
)
```
다음은 app.out을 빌드 완료한 뒤, 이로부터 임베디드 프로세서에 Flashing하기 위한 app.bin을 생성하는 명령입니다.\
* ADD_CUSTOM_COMMAND(OUTPUT)에서 제시한 예시에서는 OUTPUT에 지정한 파일들이 Outdated인 경우에만 실행되지만, 여기에서는 출력물의 최신 여부에 관계 없이 TARGET에 지정한 대상 Target이 빌드되는 경우에만 실행됩니다.


# Refs
https://tuwlab.com/ece/27260

# cmake tips
## cmake에 있는 변수들 모두 출력 방법 (콘솔)
CMakeLists.txt가 있는 폴더로 이동한다음 아래와 같이 *cmake-LAH* 를 실행
$ cmake -LAH


