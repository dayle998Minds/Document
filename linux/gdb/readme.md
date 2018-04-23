# DBG 간단 사용법
## 컴파일시 디버깅 옵션 추가
```
$ g++ -g -o <App Name> <Source File>
```
## gdb 실행
```
$ gdb ./<App Name>
$ gdb ./<App Name> ./<Core Name> // 비정상 종료시 코어 파일 생성
$ gdb ./<App Name> ./<pid Name> // 실정중인 프로세스와 연결하여 디버깅
```
## gdb 코어 파일 생성유무및 사이즈 설정
```
$ ulimit -c             // 현재 설정된 코어 파일 크기를 확인
$ ulimit -c <Size>  //<Size>에 1024와 같이 직접 크기를 지정,  unlimited로 무제한으로 설정
```
# gdb 명령어 정리
### run (r) 프로세스 실행
```
(dgb) run -arg1 arg2
```
### quit / kill (k) 프로그램을 종료
### break (b) 중단점을 설정
```
(gdb) b main.c:func // main.c의 func함수에 브레이크 설정.
(gdb) b CMain::func // CMain클래스의 func맴버함수에 브레이크 설정.
(gdb) b main.c:10    // main.c의 10번 라인에 브레이크 설정.
(gdb) b +2               // 현재행에서 2라인 이후의 지점에 브레이크 설정.
(gdb) b *0x00000001 // 0x00000001주소에 브레이크 설정.
```
### info 각종 정보 보기
```
(gdb) info b              // 현재 설정된 브레이크 포인트의 정보를 보여준다.
(gdb) info locals       // 현재 상태의 지역변수 정보을 보여준다.
(gdb) info variables   // 현재 상태의 전역변수 정보를 보여준다.
(gdb) info registers   // 레지스터 정보를 보여준다.
(gdb) info frame       // 현재 스택 프레임 정보 보여준다.
(gdb) info args         // 현재 스택 프레임의 함수가 호출될때 인자를 보여준다.
(gdb) info catch       // 현재 스택 프레임의 함수내에 예외 핸들러를 보여준다.
(gdb) info signals    // 보낼 수 있는 시그널의 종류를 보여준다.
(gdb) info set          // 변경 가능한 환경설정 정보를 보여준다.
(gdb) info functions // 함수 리스트를 보여준다.
```
### condition 브레이크 포인트에 조건을 설정
```
(gdb) condition 1 bCheck == true // 1번 브레이크 포인트 (info b로 확인)에 bCheck가 true일 때 동작하도록 설정.
```
### clear (cl) 브레이크 포인트를 삭제
```
(gdb) cl 1                 // 1번 브레이크 포인트 삭제.
(gdb) cl CMain::func // CMain클래스의 func맴버함수의 브레이크 포인트 삭제.
(gdb) cl                   // 모든 브레이크 포인트 삭제.
```
### enable / disable 브레이크 포인트를 활성화 하거나 비활성화
```
(gdb) enable 1  // 1번 브레이크 포인트를 활성화 한다.
(gdb) disable 1 // 1번 브레이크 포인트를 비활성화 한다.
```
### step (s) / next (n) 브레이크 포인트를 라인단위로 실행
```
(gdb) s       // 현재 행을 수행한다. (함수의 경우 내부로 진입한다)
(gdb) s 10   // step 명령을 10번 수행한다.
(gdb) n       // 현재 행을 수행한다. (함수의 경우 진입하지 않고 함수를 실행한 후 넘어간다)
(gdb) n 10   // next 명령을 10번 수행한다.
```
### finish / return
```
(gdb) finish         // 현재 함수를 실행하고 빠져나간다.
(gdb) return         // 현재 함수를 실행하지 않고 빠져나간다.
(gdb) return false // 함수를 빠져나갈때 리턴값을 false로 준다.
```
### watch
```
(gdb) watch bCheck   // bCheck의 값이 변경될 때마다 브레이크가 걸리도록 한다.
```
### print (p)
```
(gdb) p bCheck        // bCheck 값을 확인한다.
(gdb) p func             // func함수의 주소를 확인한다.
(gdb) p tVal             // tVal 구조체의 주소를 확인한다. (*의 포인터로 값을 확인할 수 있다)
// 아래와 같이 포인터, 캐스팅등이 가능하다.
// p[/출력형식] <변수명/함수명> [@배열크기]
(gdb) p &eax           // eax레지스터 값을 확인한다.
(gdb) p *pByte@8    // 8크기 배열로 가져와 확인한다.
(gdb) p/t  val          // 변수를 2진수로 출력.
(gdb) p/o val          // 변수를 8진수로 출력.
(gdb) p/d val          // 변수를 signed 10진수로 출력.
(gdb) p/u val          // 변수를 unsigned 10진수로 출력.
(gdb) p/x val          // 변수를 16진수로 출력.
(gdb) p/a addr       // addr주소와 가장 가까운 심볼의 오프셋 출력. (예: main+10)
```
### display / undisplay
```
(gdb) display pVal          // pVal을 매번 화면에 표시한다.
(gdb) undisplay 1           // 1번 디스플레이 설정을 지운다.
(gdb) enable display 1    // 1번 디스플레이를 활성화 한다.
(gdb) disable display 1   // 1번 디스플레이를 비활성화 한다.
```
### frame / up / down
```
(gdb) frame [N]   // n번 스택 프레임으로 이동.
(gdb) up [N]       // 상위 프레임으로 이동.
(gdb) down[N]    // 하위 프레임으로 이동.
```
### signal
```
(gdb) signal SIGKILL    // KILL 시그널을 보낸다.
```
### backtrace (bt) 프로그램의 스텍 보기
