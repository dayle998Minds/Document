# 구글 C++ 스타일
### 파일 이름
파일 이름은 모두 소문자이고 밑줄(_) 사용\
```
url_table.h      // 클래스 선언
url_table.cc     // 클래스 정의
```
### 타입 이름
단어의 시작은 대문자로, 그 외에는 소문자로 쓰며 밑줄(_)은 사용하지 않는다.\
클래스, 구조체, 타입 정의, 열거형과 같은 모든 타입 이름은 이름 규칙이 같다.
```
// classes & structs
class UrlTable { ...
class UrlTableTester { ...
struct UrlTableProperties { ...
 
// typedefs
typedef hash_map PropertiesMap;
 
// enums
enum UrlTableErrors { ...
```
### 변수 이름
변수 이름은 모두 소문자이며 단어 사이에 밑줄을 쓴다. 클래스 멤버 변수는 마지막에 밑줄을 붙인다. 
```
// 일반적인 변수
int num_sessions;

class ChatServer
{
	...
	int num_sessions_; // 클래스 멤버 변수(이름 끝에 밑줄(_)을 넣었다.)
	...
};
```

### 구조체 변수
구조체 데이터 멤버 이름 규칙은 일반 변수와 같으나 클래스 데이터 멤버와 달리 끝에 밑줄을 붙이지 않는다.
```
struct UrlTableProperties 
{
  string name;
  int num_entries;
}
```
### 상수 이름
각 단어는 대문자로 시작하고, 이름에 k를 접두어로 붙인다.
```
const int kDaysInAWeek = 7;
```
6. 함수 이름
일반 함수는 대소문자를 섞어 쓰며 접근자와 변경자(get/set 함수)는 변수 이름과 일치시킨다.
- 일반 함수
새 단어의 시작마다 대문자를 쓴다. 밑줄은 사용하지 않는다.
```
AddTableEntry();
DeleteUrl();
OpenFile();
```
- 접근자와 변경자(get/set 함수)
```
class MyClass {
 public:
  ...
  int num_entries() const { return num_entries_; }
  void set_num_entries(int num_entries) { num_entries_ = num_entries; }
 
 private:
  int num_entries_;
};
```
### 매크로 이름
일반적으로 매크로는 사용하지 않아야 한다. 하지만 절대적으로 필요하다면 이름에는 모두 대문자와 밑줄을 쓴다.
```
#define ROUND(x) ...
#define PI_ROUNDED 3.0
```
### 열거형 이름
열거형은 상수(접두어로 k) 또는 매크로 이름(모두 대문자) 규칙 중 하나를 선택한다.(kEnumName 또는 ENUM_NAME)\
열거자 각각은 상수처럼 이름 짓는 것을 선호하지만 매크로처럼 할 수도 있다. \
열거형 이름 UrlTableErrors와 AlternateUrlTableErrors는 타입이므로 대소문자를 섞어 쓴다.
```
enum UrlTableErrors {
  kOK = 0,
  kErrorOutOfMemory,
  kErrorMalformedInput,
};
enum AlternateUrlTableErrors {
  OK = 0,
  OUT_OF_MEMORY = 1,
  MALFORMED_INPUT = 2,
};
```
