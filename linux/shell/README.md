# 문법 정리

### shell script 파일 구조
#!/bin/bash
```
$ vi hello.sh

(hello.sh)
#!/bin/bash
echo hello world
```
### argument
- $1~ $n - 넘겨진 인자들
- $* : 스크립트에 전달된 인자들을 모아놓은 문자열. 하나의 변수에 저장되며 IFS 환경변수의 첫번째 문자로 구분된다. (IFS : internal field separator)
- $@ : $*과 같다. 다만 구분자가 IFS변수의 영향을 받지 않는다.
- $0 : 실행된 쉘 스크립트 이름
- $# : 스크립트에 넘겨진 인자의 갯수
```
(test1.sh)
#!/bin/bash
echo "This Script Executable File : $0"
echo "Argument Count : $#"
echo "Argument List \$* : $*"
echo "Argument List \$@ : $@"
echo "Argument 1 : $1"
echo "Argument 2 : $2"

(실행)
$./test1.sh a1 a2 a3 a4
This Script Executable File : ./test1.sh
Argument Count : 4
Argument List $* : a1 a2 a3 a4
Argument List $@ : a1 a2 a3 a4
Argument 1 : a1
Argument 2 : a2
```
### if / else
문자열비교   
- [ string ] - string이 빈 문자열이 아니라면 참
- [ string1 = string2 ] - 두 문자열이 같다면 참
- [ string1 != string2 ] - 두 문자열이 다르면 참
- [ -n string ] - 문자열이 null(빈 문자열) 이 아니라면 참
- [ -z string ] - 문자열이 null(빈 문자열) 이라면 참  
산술비교   [ expr1 -eq expr2 ] - 두 표현식 값이 같다면 참 ('EQual')
- [ expr1 -ne expr2 ] - 두 표현식 값이 같지 않다면 참 ('Not Equal')
- [ expr1 -gt expr2 ] - expr1 > expr2 이면 참 ('Greater Than')
- [ expr1 -ge expr2 ] - expr1 >= expr2 이면 참 ('Greater Equal')
- [ expr1 -lt expr2 ] - expr1 < expr2 이면 참 ('Less Than')
- [ expr1 -le expr2 ] - expr1 <= expr2 이면 참 ('Less Equal')
- [ ! expr ] - expr 이 참이면 거짓, 거짓이면 참
- [ expr1 -a expr2 ] - expr1 AND expr2 의 결과 (둘다 참이면 참, 'And')
- [ expr1 -o expr2 ] - expr1 OR expr2 의 결과 (둘중 하나만 참이면 참, 'Or')  
파일조건   [ -b FILE ] - FILE 이 블럭 디바이스 이면 참
- [ -c FILE ] - FILE 이 문자 디바이스 이면 참.
- [ -d FILE ] - FILE 이 디렉토리이면 참
- [ -e FILE ] - FILE 이 존재하면 참
- [ -f FILE ] - FILE 이 존재하고 정규파일이면 참
- [ -g FILE ] - FILE 이 set-group-id 파일이면 참
- [ -h FILE ] - FILE 이 심볼릭 링크이면 참
- [ -L FILE ] - FILE 이 심볼릭 링크이면 참
- [ -k FILE ] - FILE 이 Sticky bit 가 셋팅되어 있으면 참
- [ -p FILE ] - True if file is a named pipe.
- [ -r FILE ] - 현재 사용자가 읽을 수 있는 파일이면 참
- [ -s FILE ] - 파일이 비어있지 않으면 참
- [ -S FILE ] - 소켓 디바이스이면 참
- [ -t FD ] - FD 가 열려진 터미널이면 참
- [ -u FILE ] - FILE 이 set-user-id 파일이면 참
- [ -w FILE ] - 현재 사용자가 쓸 수 있는 파일(writable file) 이면 참
- [ -x FILE ] - 현재사용자가 실행할 수 있는 파일(Executable file) 이면 참
- [ -O FILE ] - FILE 의 소유자가 현재 사용자이면 참
- [ -G FILE ] - FILE 의 그룹이 현재 사용자의 그룹과 같으면 참
- [ FILE1 -nt FILE2 ] - : FILE1이 FILE2 보다 새로운 파일이면 ( 최근파일이면 ) 참
- [ FILE1 -ot FILE2 ] - : FILE1이 FILE2 보다 오래된 파일이면 참
- [ FILE1 -ef FILE2 ] - : FILE1 이 FILE2의 하드링크 파일이면 참 
```
if [ $1 -lt $2 ]
  then
    echo $1 is less than $2
  elif [ $1 -gt $2 ]
  then
    echo $1 is greater than $2
  else
    echo $1 equals to $2
  fi
```
### for
```
for dir in $PATH
do
   ls –ld $dir
done
```
### while
```
count=0
while [ $count -lt 10 ]
do
    echo $count
     count=$(($count+1))
done
```
### case
```
case $1 in
   *.jpg )
      echo jpg: Graphic File!! ;;
   *.txt )
      echo txt: Text File!! ;;
   * )
      echo Unknown File!! ;;
esac
```
### function
```
add()
{
  result=$(($1+$2))
  return $result
}
a=3
b=5
add $a $b
sum=$?

echo "$a + $b = $sum"
```

# 팁
### debugging option
```
$ bash -x name  
스크립트 안의 변수를 해당값으로 치환해서 보여줌
$ bash -v name
스크립트 안의 변수를 변환되기전 변수로 치환해서 보여줌
$ bash -n name
스크립트를 변환해서 보여주지만 실행은 안함.
```

출처: http://webtn.tistory.com/entry/UNIX-나도개발자다-잉-참-쉬운-Shell-스크립트-한번-해볼까요 [WEB TECH NEWS]
