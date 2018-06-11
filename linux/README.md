# centos 설치후 기본 세팅
### yum epel 저장소 추가
Extra Packages for Enterprise Linux yum 저장소 추가\
epel-release 설치\
epel = Extra Packages for Enterprise Linux→ 엔터프라이즈 리눅스를 위한 추가 패키지
```
# yum install epel-release
```

### hot corner 없애기
왼쪽상단에 마우스를 가져다 놓으면 Activities Overview 가 나와서 많이 불편하다.\
없애기 위해서는 extension app을 받아서 실행을 시켜주면 된다.\
https://extensions.gnome.org/extension/118/no-topleft-hot-corner/

### windows 공유 
WinSCP를 이용하여 scp로 접속
https://winscp.net/eng/docs/lang:ko

# 개발 관련 Tools 설치
### ubuntu launcher 
gsettings set com.canonical.Unity.Launcher launcher-position Bottom


### chrome 설치

```
wget -q -O - https://dl.google.com/linux/linux_signing_key.pub | sudo apt-key add -
echo "deb [arch=amd64] http://dl.google.com/linux/chrome/deb/ stable main" | sudo tee /etc/apt/sources.list.d/google-chrome.list
sudo apt-get update
sudo apt-get -y install google-chrome-stable
sudo apt-get -y install google-chrome-beta
```

### git 설치
```
sudo apt-get install git
git config --global user.name exampleID
git config --global user.email example@email.com
git config --list
```
### git prompt 설치
```
cd ~
git clone https://github.com/magicmonty/bash-git-prompt.git .bash-git-prompt --depth=1
vi .bashrc
```
마지막줄에 추가
```
GIT_PROMPT_ONLY_IN_REPO=1
source ~/.bash-git-prompt/gitprompt.sh
```

### terminator 설치
```
$ sudo apt-get install terminator
```

### ftp 서버 설치
```
$ sudo apt-get install vsftpd
$ sudo vi /etc/vsftpd.conf
$ sudo /etc/init.d/vsftpd restart 
또는 
$ service vsftpd restart 
```
주요 vsftpd.conf 내용
- FTP의 포트 변경
  `listen=YES` 라고 써 있는 부분 아래에\
  `listen_port=21022`
- 비계정(guest)의 접속을 허용
  `anonymous_enabled=NO` 를 YES로 변경
- 업로드 가능하도록 변경
  `write_enable=YES`에 걸려있는 주석을 제거
- 계정사용자가 상위디렉토리(root 디렉토리)에 접근하는 것을 허용
  `chroot_local_user=YES`\
  `chroot_list_enable=YES`\
  `chroot_list_file=/etc/vsftpd.chroot_list`\
  주석을 제거하고 난 후에 chroot_list_file 파일에 계정이름추가\
  `$sudo vi /etc/vsftpd.chroot_list`\
   `open_user1`\
   `open_user2`
- root 계정 접속을 허용
  $sudo vi /etc/ftpuser\
  root 계정에 앞에 주석처리 해준다 (또는 삭제)

# 자주 사용하는 리눅스 명령어
## 검색
### 
```
find . -name "*.c*"  -name "*.h" | xargs tar cvf tar_files.tar
```

### 그래픽 카드 확인
```
lshw -C display
lspci -vnn | grep VGA -A 12
```

### 폴더 용량 확인
```
du -hs *
```
### 하위 디렉토리 파일들에서 문자열 검색
```
$ grep -rn "찾고자 하는 문자열" *
```
- -r 옵션은 하위 디렉토리에 있는 파일까지 검색
- -n 옵션은 라인 번호를 보여주는 것
```
$ find . -name "*" | xargs grep -n "찾고자 하는 문자열"
```
### 하위 디렉토리 파일에서 소유자 검색
```
$ find . -user root -print
```

### 파일 문자 치환
grep -rl "특정문자" * | xargs sed -i 's/특정문자/바꿀문자/g'

```
grep -rl "192.168.1.15" | xargs sed -i 's/192.168.1.15/10.122.66.35/g'
```
## RPM 패키지 관리
설치 / 확인 / 제거 / 업그레이드
```
rpm -ivh 패키지명 #설치
rpm -qa | grep 패키지명 #확인
rpm -ev 패키지명 #제거
rpm -Uvh 패키지명 #업그레이드
```
> -q	--query	패키지 정보 질의
> -i	--install	패키지 설치
> -U	--upgrade	패키지 업그레이드
> -e	--erase	패키지 삭제
> -V	--verify	패키지 검증
> -K	--checksig	서명 검증

### rpm 패키지 정보 보기(info)
```
rpm -qi 설치된패키지명
rpm -qip 파일명.rpm
```
### 파일이 속한 패키지 찾기
```
rpm -qf 파일
```
### rpm 내부 파일목록 보기(list)
```
rpm -ql 설치된패키지명
rpm -qlp 파일명.rpm
```

## yum 패키지 관리
### 패키지 설치 / 삭제 / 업데이트
```
yum install package
yum remove package
yum update package
```
> -h, --help : 해당 명령어의 도움말을 보여주고 실행이 종료됩니다.\
> -t, --tolerant : 에러를 자동으로 잡아서 설치합니다.\
> -C, --cacheonly : 캐시를 업데이트 하지 않고 전체 시스템 캐시 실행합니다.\
> -c [config file], --config=[config file] : 파일 위치를 알려줍니다.\
> -R [minutes], --randomwait=[minutes] : 최대치의 명령어 실행시 기다립니다.\
> -d [debug level], --debuglevel=[debug level] : 최종 결과를 디버깅합니다.\
> --showduplicates : 중복요소를 보여줍니다.\
> -e [error level], --errorlevel=[error level] : 결과 중 에러를 보여줍니다.\
> --rpmverbosity=[debug level name] : rpm에서 결과물을 디버깅합니다.\
> --version : Yum 버전을 보여주고 실행이 종료됩니다.\
> -y, --assumeyes : 모든 물음에 예를 진행합니다.\
> -q, --quiet : 모든 작업이 종료됩니다.\
> -v, --verbose : 작업을 장황하게 합니다.\
> --installroot=[path] : root권한으로 path위치에 인스톨을 진행합니다.\
> --enablerepo=[repo] : 1개 이상의 저장소 위치에 저장시킵니다.\
> --disablerepo=[repo] : 1개 이상의 저장소 위치에 저장시키지 않습니다.\
> -x [package], --exclude=[package] : 패키지 이름을 제외시킵니다.\
> --disableexcludes=[repo] : 이름으로 플러그인을 설치를 중단합니다.\
> --obsoletes : 오래된 패키지는 업데이트를 하는 동안 적절히 삭제 및 교체됩니다.\
> --noplugins : yum plugin이 없도록 합니다.\
> --nogpgcheck : gpg signature를 불가능하게 합니다.\
> --skip-broken : 문제 있는 패키지는 자동으로 스킵해서 넘어갑니다.\
> --color=COLOR : 컬러가 사용되었을 때 조정합니다.\
> --releasever=RELEASEVER : $releasever의 값을 yum config와 repo파일에서 조정합니다.\
> --setopt=SETOPTS : 임의로 config와 repo 옵션값을 지정합니다.\
> --disablepresto : Presto 플러그인을 중단하고 deltarpm을 다운로드 받지 않습니다.

### 정보 보기 / 검색 / 특정단어 포함된 패키지 리스트
```
yum search package
yum info package
yum list term
```
### 커널 패키지에 설치된 모든 패키지를 업데이트
```
yum -y update
```
### 의존성 확인 
```
yum deplist 패키지
```
### 패키지 오류시 오류 항목 무시후 업데이트 진행
```
yum update --skip-broken
```
### yum으로 파일이 속한 패키지 찾기
yum provides 파일
```
[root@zetawiki ~]# yum provides /bin/mailx
Loaded plugins: fastestmirror, priorities
Loading mirror speeds from cached hostfile
redhat-lsb-4.0-2.1.4.el5.x86_64 : LSB base libraries support for CentOS Enterprise Linux
Repo        : base
Matched from:
Filename    : /bin/mailx
```
# 서버 장애 파악 방법
### CPU 상태 확인
```
top
```
### 메모리 상태 확인
```
free -m
```
### 서비스 데몬 확인
```
service <daemon name> status
```
### 특정 포트에 접속 가능 확인
```
nc <hostname> <port> # tcp
nc -u <hostname> <port>  # udp
```
### 누가 내포트를 사용하고 있는지 확인
```
lsof -i TCP:80 
```
### 특정 프로세스가 어떤 포트를 사용하고 있는지 확인
```
lsof -c httpd
```
## 리눅스 로컬서버 열린 포트 확인
```
netstat -tnlp
```

### 네트워크 연결 상태 확인
```
netstat -nap | grep ESTABLISHED
netstat -nap | grep TIME_WAIT
```

TIME_WIT 수가 비정상적으로 많이면 들어오는 요청을 서버에서 처리못하고 있는 상태
### 디스크 상태
```
df -uh
```
### Netcat을 이용하여 서버&클라이언트 통신 테스트
> server
```
// tcp
$ nc -l 11010
// udp
$ nc -ul 11010
```
> client
```
// tcp
$ nc localhost 11010
// dup
$ echo -n "hello" | nc -4u -w1  localhost 11010
```
udp서버일경우 첫패킷을 받은후 close되므로 패킷수신후 재실행 필요함

##  설치후 초기설정
### 암호 변경
```
passwd
passwd <userid>
 ```
> 계정추가
```
adduser newuser
```
> sudo 권한 추가
- centos
CentOS에서는 wheel group의 멤버가 sudo 권한을 가진다.
```
usermod -aG wheel david
```
- ubuntu
david계정에 sudo 명령 권한 추가
```
usermod -G sudo david
```
###  패키지 다운로드 서버 변경
```
cp /etc/apt/sources.list /etc/apt/sources.list.old
sudo sed -i 's/archive.ubuntu.com/ftp.daum.net/g' /etc/apt/sources.list

sudo apt-get git
sudo apt-get install git
sudo apt-get install vim

apt-get update
apt-get upgrade
```
## curl
### GET
```
curl http://www.gnu.org/software/bash/manual/html_node/index.html
```
### POST
```
curl -d "first_name=Bruce&last_name=Wayne&press=%20OK%20" http://posttestserver.com/post.php
```
### Content-Type Header 설정
```
curl -d @myJson.js -H "Content-Type: application/json" http://localhost:8080/jsonEcho
```
### custom header와 json content type 보내기
```
curl -d @send.json http://127.0.0.1:8080/test --header "custom-header: xxx" --header "Content-Type: application/json"
```
### header 포함 debug출력 (-v)
```
$ curl -v -d "asdff" http://127.0.0.1:8000
* Rebuilt URL to: http://127.0.0.1:8000/
*   Trying 127.0.0.1...
* Connected to 127.0.0.1 (127.0.0.1) port 8000 (#0)
> POST / HTTP/1.1
> Host: 127.0.0.1:8000
> User-Agent: curl/7.47.0
> Accept: */*
> Content-Length: 5
> Content-Type: application/x-www-form-urlencoded
> 
* upload completely sent off: 5 out of 5 bytes
* HTTP 1.0, assume close after body
< HTTP/1.0 200 OK
< Server: BaseHTTP/0.3 Python/2.7.12
< Date: Thu, 10 May 2018 07:50:20 GMT
< Content-type: text/html
< 
* Closing connection 0
<html><body><h1>POST!</h1></body></html>
```

# 개발 팁
### shell script 실행시 debug 출력
```
sh -x test.sh
```

### 디렉토리별 tar 파일 생성 스크립트

```
$ vi tar_dir.sh

#!/bin/sh

DIRS=`ls -l $PWD | egrep '^d' | awk '{print $9}'`

for DIR in $DIRS
do
    echo ${DIR}
    tar czvf ${DIR}.tar.gz ${DIR}
    #rm -rf ${DIR}
done
```
## 자동 실행 추가방법
### crontab를 이용한 시작 프로그램 등록
```
crontab -e 

아래 추가
@reboot /home/test/test/programstart.sh 
```
추가 옵션들
> > @reboot = run at boot and reboot only\
> >  @yearly  = run at midnight Jan 1 each year (equiv to 0 0 1 1 *) \
> > @annually  = run at midnight Jan 1 each year (equiv to 0 0 1 1 *) \
> > @monthly  = run at midnight on the first day of each month (equiv to 0 0 1 * *) \
> > @weekly  = run at midnight each Sunday (equiv to 0 0 * * 0) \
> > @daily  = run at midnight each day (equiv to 0 0 * * *) \
> > @ midnight  = run at midnight each day (equiv to 0 0 * * *) \
> > @ hourly = run on the first second of every hour (equiv to 0 * * * *) 

### /etc/rc.local에서 바로 실행

### /etc/rc.local 에 스크립트 파일을 등록하고, /etc/rc.d/ 경로에 해당 스크립트 파일 넣고 실행하기
 
### /etc/profile.d/ 경로에 자동실행할 스크립트 파일추가

### upstart를 이용하는 방법
/etc/init에 추가할 서비스에 대한 conf파일을 만든후 서비스를 실행
```
$ sudo vi /etc/init/upstart_example.conf
$ sudo upstart upstart_example.conf
```
conf파일 참조
```
#author 설정
description     "upstart-Worker"
author          "david"
#자동 시작/ 중단 조건
start on runlevel [2345]
stop on runlevel [016]

#자동 재시작
respawn

#실행권한
setuid www-data
setgid www-data

#실행 환경 설정
env PORT=11000
#실행 디렉토리 변경
chdir /home/david/upstart_work

# pre-script실행
pre-start script
    mkdir -p /var/log/yourcompany/
end script

exec echo "hello world"

console output
```

-
## 동적 라이브러리(shared library)
### so 파일을 찾는 경로 설정
- system default 경로
/etc/ld.so.conf 파일에 설정된 값이 있다. 아래와 같이 /etc/ld.so.conf.d/ 에 있는 conf를 모두 include하고 있다. \
추가를 원하는 /etc/ld.so.conf.d에 conf파일을 만든후 추가할 path를 추가한후 `ldconfig -v`를 실행한다.
추가할경우 conf파일을 만든
```
david@david-ubuntu:~$ cat /etc/ld.so.conf
include /etc/ld.so.conf.d/*.conf

david@david-ubuntu:~$ ll /etc/ld.so.conf.d/*.conf
-rw-r--r-- 1 root root  45  1월 27  2017 /etc/ld.so.conf.d/cuda-8-0.conf
-rw-rw-r-- 1 root root  38 11월 24  2014 /etc/ld.so.conf.d/fakeroot-x86_64-linux-gnu.conf
-rw-r--r-- 1 root root 108  6월 17  2017 /etc/ld.so.conf.d/i386-linux-gnu.conf

david@david-ubuntu:~$ cat /etc/ld.so.conf.d/cuda-8-0.conf
/usr/local/cuda-8.0/targets/x86_64-linux/lib
david@david-ubuntu:~$ sudo ldconfig -v

```
- LD_LIBRARY_PATH 추가
bashrc 파일에 아래와 같이 LD_LIBRARY_PATH에 path를 추가한다.
```
david@david-ubuntu:~$ echo $LD_LIBRARY_PATH
/usr/local/cuda-8.0/lib64:/home/david/maum/lib
david@david-ubuntu:~$ vi ~/.bashrc 

vi 편집
export PATH=/usr/local/cuda-8.0/bin${PATH:+:${PATH}}
export LD_LIBRARY_PATH=/usr/local/cuda-8.0/lib64${LD_LIBRARY_PATH:+:${LD_LIBRARY_PATH}}
```
### 라이브러리 의존성 확인
ldd 명령어로 확인이 가능하다
```
david@david-ubuntu:~$ ldd /usr/bin/vi
	linux-vdso.so.1 =>  (0x00007fffbc0eb000)
	libtinfo.so.5 => /lib/x86_64-linux-gnu/libtinfo.so.5 (0x00007fc83eb7b000)
	libselinux.so.1 => /lib/x86_64-linux-gnu/libselinux.so.1 (0x00007fc83e959000)
	libacl.so.1 => /lib/x86_64-linux-gnu/libacl.so.1 (0x00007fc83e751000)
	libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x00007fc83e387000)
	libpcre.so.3 => /lib/x86_64-linux-gnu/libpcre.so.3 (0x00007fc83e117000)
	libdl.so.2 => /lib/x86_64-linux-gnu/libdl.so.2 (0x00007fc83df13000)
	/lib64/ld-linux-x86-64.so.2 (0x00007fc83f0ac000)
	libattr.so.1 => /lib/x86_64-linux-gnu/libattr.so.1 (0x00007fc83dd0e000)
	libpthread.so.0 => /lib/x86_64-linux-gnu/libpthread.so.0 (0x00007fc83daf1000)
```
`readelf -d `명령어로 확인 하는 방법은 아래와 같다
```
david@david-ubuntu:~$ readelf -d /usr/bin/vi

Dynamic section at offset 0xf6960 contains 27 entries:
  Tag        Type                         Name/Value
 0x0000000000000001 (NEEDED)             Shared library: [libtinfo.so.5]
 0x0000000000000001 (NEEDED)             Shared library: [libselinux.so.1]
 0x0000000000000001 (NEEDED)             Shared library: [libacl.so.1]
 0x0000000000000001 (NEEDED)             Shared library: [libc.so.6]
 0x000000000000000c (INIT)               0x1b3f8
 0x000000000000000d (FINI)               0xc9524
 0x0000000000000019 (INIT_ARRAY)         0x2ef7e8
```
## patch 파일 생성 및 적용
### 패치 생성
 diff [options] from-file to-file
```
$ diff -uNr hello.c.orig hello.c > hello-hangul.patch

% cat hello-hangul.patch
--- hello.c.orig	Sun Jan 16 16:54:32 2000
+++ hello.c	Sun Jan 16 16:53:04 2000
@@ -2,6 +2,6 @@
 
 int main(void)
 {
-	printf("hello\n");
+	printf("안녕하세요\n");
	return 0;
 }
```
### 패치 적용법
 patch [options] [originalfile [patchfile]]
```
$ cd xchat-1.2.0/
$ patch -p0 < hello-hangul.patch
```

### 원격 제어

```
 # sudo apt-get install vino
 # vino-preferences 
 # /usr/lib/vino/vino-server 

```
## scp 사용법
- 원격 서버 -> 로컬 서버로 파일 전송
```
# scp [옵션] [계정명]@[원격지IP주소]:[원본 경로 및 파일] [전송받을 위치]
# scp my@111.222.333.444:/home/david/index.html /home/david/
```
- 로컬 서버 -> 원격 서버로 파일 전송
```
# scp [옵션] [원본 경로 및 파일] [계정명]@[원격지IP주소]:[전송할 경로]
# scp /home/david/test.txt remote@111.222.333.444:/home/remote/
```
## strace
### 인자로 trace방법
strace -t -f ls
- -t 시간표시
- -f pid 표시

### 실행중인 pid로 trace 방법
strace -t -t -p pid -o log-file.log

### 정규 표현식으로 필터 걸기
```
strace -t -f -e open ls
```
```
$ strace -t -f -e open ls
12:13:55 open("/usr/local/cuda-8.0/lib64/tls/x86_64/libselinux.so.1", O_RDONLY|O_CLOEXEC) = -1 ENOENT (No such file or directory)
12:13:55 open("/usr/local/cuda-8.0/lib64/tls/libselinux.so.1", O_RDONLY|O_CLOEXEC) = -1 ENOENT (No such file or directory)
12:13:55 open("/usr/local/cuda-8.0/lib64/x86_64/libselinux.so.1", O_RDONLY|O_CLOEXEC) = -1 ENOENT (No such file or directory)
12:13:55 open("/usr/local/cuda-8.0/lib64/libselinux.so.1", O_RDONLY|O_CLOEXEC) = -1 ENOENT (No such file or directory)
12:13:55 open("/home/david/maum/lib/tls/x86_64/libselinux.so.1", O_RDONLY|O_CLOEXEC) = -1 ENOENT (No such file or directory)
12:13:55 open("/home/david/maum/lib/tls/libselinux.so.1", O_RDONLY|O_CLOEXEC) = -1 ENOENT (No such file or directory)
12:13:55 open("/home/david/maum/lib/x86_64/libselinux.so.1", O_RDONLY|O_CLOEXEC) = -1 ENOENT (No such file or directory)
12:13:55 open("/home/david/maum/lib/libselinux.so.1", O_RDONLY|O_CLOEXEC) = -1 ENOENT (No such file or directory)
12:13:55 open("/etc/ld.so.cache", O_RDONLY|O_CLOEXEC) = 3
```
### -e trace=" 옵션을 사용하면 여려 개의 시스템 콜을 출력
```
$ strace -e trace=open,read ls /home
open("/etc/ld.so.cache", O_RDONLY)      = 3
open("/lib/libselinux.so.1", O_RDONLY)  = 3
read(3, "\177ELF\1\1\1\3\3\1\260G004"..., 512) = 512
open("/lib/librt.so.1", O_RDONLY)       = 3
read(3, "\177ELF\1\1\1\3\3\1\300\30004"..., 512) = 512
..
open("/lib/libattr.so.1", O_RDONLY)     = 3
read(3, "\177ELF\1\1\1\3\3\1\360\r004"..., 512) = 512
open("/proc/filesystems", O_RDONLY|O_LARGEFILE) = 3
read(3, "nodev\tsysfs\nnodev\trootfs\nnodev\tb"..., 1024) = 315
read(3, "", 1024)                       = 0
open("/usr/lib/locale/locale-archive", O_RDONLY|O_LARGEFILE) = 3
open("/home", O_RDONLY|O_NONBLOCK|O_LARGEFILE|O_DIRECTORY|O_CLOEXEC) = 3
```
### -r 옵션을 사용해 시스템 콜의 상대 시간 정보 출력하기
```
$ strace -r ls
     0.000000 execve("/bin/ls", ["ls"], [/* 37 vars */]) = 0
     0.000846 brk(0)                    = 0x8418000
     0.000143 access("/etc/ld.so.nohwcap", F_OK) = -1 ENOENT (No such file or directory)
     0.000163 mmap2(NULL, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0xb787b000
     0.000119 access("/etc/ld.so.preload", R_OK) = -1 ENOENT (No such file or directory)
     0.000123 open("/etc/ld.so.cache", O_RDONLY) = 3
     0.000099 fstat64(3, {st_mode=S_IFREG|0644, st_size=67188, ...}) = 0
     0.000155 mmap2(NULL, 67188, PROT_READ, MAP_PRIVATE, 3, 0) = 0xb786a000
     ...
     ...
```
### -c 옵션을 사용해 시스템 콜 통계 정보 생성하기 
```
$ strace -c ls /home
bala
% time     seconds  usecs/call     calls    errors syscall
------ ----------- ----------- --------- --------- ----------------
  -nan    0.000000           0         9           read
  -nan    0.000000           0         1           write
  -nan    0.000000           0        11           open
  -nan    0.000000           0        13           close
  -nan    0.000000           0         1           execve
  -nan    0.000000           0         9         9 access
  -nan    0.000000           0         3           brk
  -nan    0.000000           0         2           ioctl
  -nan    0.000000           0         3           munmap
  -nan    0.000000           0         1           uname
  -nan    0.000000           0        11           mprotect
  -nan    0.000000           0         2           rt_sigaction
  -nan    0.000000           0         1           rt_sigprocmask
  -nan    0.000000           0         1           getrlimit
  -nan    0.000000           0        25           mmap2
  -nan    0.000000           0         1           stat64
  -nan    0.000000           0        11           fstat64
  -nan    0.000000           0         2           getdents64
  -nan    0.000000           0         1           fcntl64
  -nan    0.000000           0         2         1 futex
  -nan    0.000000           0         1           set_thread_area
  -nan    0.000000           0         1           set_tid_address
  -nan    0.000000           0         1           statfs64
  -nan    0.000000           0         1           set_robust_list
------ ----------- ----------- --------- --------- ----------------
100.00    0.000000                   114        10 total
```
