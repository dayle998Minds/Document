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
## 개발 팁
### shell script 실행시 debug 출력
```
sh -x test.sh
```
