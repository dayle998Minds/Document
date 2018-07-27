## Docker 환경 설정
### sudo 없이 사용
```
sudo usermod -aG docker $USER # 현재 접속중인 사용자에게 권한주기
sudo usermod -aG docker your-user # your-user 사용자에게 권한주기
```

## Docker Image 생성을 위한 Directory 및 파일 구성
### 1. Directory생성
[user1@ip-10-0-0-151 ~]$ cd docker-images/
[user1@ip-10-0-0-151 docker-images]$ mkdir centos7-base
[user1@ip-10-0-0-151 docker-images]$ cd centos7-base/
### 2. Dockerfile 생성
[user1@ip-10-0-0-151 centos7-base]$ vi Dockerfile
```
FROM docker.io/centos:7.4.1708
 
# 사용자 지정
USER root
 
# 언어셋 설치
RUN yum clean all \
 && yum repolist \
 && yum -y update \
 && sed -i "s/en_US/all/" /etc/yum.conf  \
 && yum -y reinstall glibc-common
  
# 기본적으로 필요한 OS 패키지를 설치한다.
RUN  yum -y install tar unzip vi vim telnet net-tools curl openssl \
 && yum -y install apr apr-util apr-devel apr-util-devel \
 && yum -y install elinks locate python-setuptools \
 && yum clean all
  
ENV LANG=ko_KR.utf8 TZ=Asia/Seoul
 
# 컨테이너 실행시 실행될 명령
CMD ["/bin/bash"]
```

### 3. Image 생성
Dockerfile 파일을 작성했으면 build 명령으로 이미지를 생성합니다.
```
docker build <옵션> <Dockerfile 경로> 
```
-  --tag 옵션으로 이미지 이름과 태그 설정

```
# docker build -t [이미지명] .
[user1@ip-10-0-0-151 centos7-base]$ sudo docker build -t centos7-base:7.4 .
Sending build context to Docker daemon 2.048 kB
Step 1 : FROM docker.io/centos:7
 ---> 0584b3d2cf6d
Step 2 : USER root
 ---> Running in 070a0180b355
 ---> ce587d6b302b
...
# 생성된 이미지 확인
[user@ip-10-0-0-151 centos7-base]$ sudo docker images
REPOSITORY           TAG                 IMAGE ID            CREATED              SIZE
user1-centos7-base   7.4              04df9befd9c6        About a minute ago   286.5 MB
```

### 4. 컨테이너 실행
```
# 컨테이너 실행하고 바로 터미널로 접속
[user1@ip-10-0-0-151 centos7-base]$ sudo docker run -ti --name=user1-centos7-base centos7-base:7.4
 
# 컨테이너 내부
[root@7048f9eb2833 /]# hostname
7048f9eb2833
  
[root@7048f9eb2833 /]# cat /etc/redhat-release
CentOS Linux release 7.2.1511 (Core)
 
[root@7048f9eb2833 /]# ifconfig
eth0: flags=4163<UP,BROADCAST,RUNNING,MULTICAST>  mtu 1500
        inet 172.17.0.3  netmask 255.255.0.0  broadcast 0.0.0.0
        inet6 fe80::42:acff:fe11:3  prefixlen 64  scopeid 0x20<link>
        ether 02:42:ac:11:00:03  txqueuelen 0  (Ethernet)
        RX packets 8  bytes 648 (648.0 B)
        RX errors 0  dropped 0  overruns 0  frame 0
        TX packets 8  bytes 648 (648.0 B)
        TX errors 0  dropped 0 overruns 0  carrier 0  collisions 0
lo: flags=73<UP,LOOPBACK,RUNNING>  mtu 65536
        inet 127.0.0.1  netmask 255.0.0.0
        inet6 ::1  prefixlen 128  scopeid 0x10<host>
        loop  txqueuelen 1  (Local Loopback)
        RX packets 0  bytes 0 (0.0 B)
        RX errors 0  dropped 0  overruns 0  frame 0
        TX packets 0  bytes 0 (0.0 B)
        TX errors 0  dropped 0 overruns 0  carrier 0  collisions 0
 ```

### 5. 컨테이너 종료
```
# docker run -ti 로 실행한 경우 빠져나오면 바로 컨테이너가 종료됨
[root@7048f9eb2833 /]# exit
exit
[user1@ip-10-0-0-151 centos7-base]$ sudo docker ps -a
CONTAINER ID        IMAGE                COMMAND              CREATED              STATUS                      PORTS               NAMES
7048f9eb2833        centos7-base   "/bin/bash"          About a minute ago   Exited (0) 10 seconds ago                       user1-centos7-base
d25d3240a374        httpd                "httpd-foreground"   20 minutes ago       Up 14 minutes               80/tcp              user1-httpd
```

### 6. 컨테이너 삭제
```
# 종료된 컨테이너 조회
[user1@ip-10-0-0-151 centos7-base]$ sudo docker ps -a
CONTAINER ID        IMAGE                COMMAND              CREATED             STATUS                          PORTS               NAMES
7048f9eb2833        centos7-base   "/bin/bash"          2 minutes ago       Exited (0) About a minute ago                       user1-centos7-base
 
# 컨테이너 삭제
[user1@ip-10-0-0-151 centos7-base]$ sudo docker rm user1-centos7-base
user1-centos7-base
```
---
## 명령어 정리
### Docker Hub 에서 이미지 검색 / search
```
16:32 $ docker search ubuntu
NAME                                                      DESCRIPTION                                     STARS     OFFICIAL   AUTOMATED
ubuntu                                                    Ubuntu is a Debian-based Linux operating s...   7494      [OK]       
dorowu/ubuntu-desktop-lxde-vnc                            Ubuntu with openssh-server and NoVNC            178                  [OK]
rastasheep/ubuntu-sshd                                    Dockerized SSH service, built on top of of...   139                  [OK]
ansible/ubuntu14.04-ansible                               Ubuntu 14.04 LTS with ansible                   91                   [OK]
ubuntu-upstart                                            Upstart is an event-based replacement for ...   85        [OK]       
neurodebian                                               NeuroDebian provides neuroscience research...   47        [OK]       
ubuntu-debootstrap                                        debootstrap --variant=minbase --components...   37        [OK]       
```

### 이미지 받기 / pull
```
$ sudo docker pull ubuntu:latest
```
사용예제
```
$ sudo docker pull ubuntu:16.04
```

### 설치된 이미지 목록 보기 / images
```
$ sudo docker images
```

### 이미지를 컨테이너 생성뒤 Bash Shell을 실행 / run
```
docker run <옵션> <이미지 이름> <실행할 파일>
```
-i(interactive), -t(Pseudo-tty) 옵션을 Bash Shell에 입력 및 출력 가능\
--name 컨테이너의 이름\

```
$ sudo docker run -i -t --name hello ubuntu /bin/bash
```
### 컨테이너 목록 출력 / ps

```
$ sudo docker ps -a
```
-a 옵션 : 정지된 컨테이너까지 출력

### 정지된 컨테이너 시작 & 종료  / start & stop
```
$ docker start <컨테이너 이름>
$ docker stop <컨테이너 이름>
```

### 컨테이너를 재시작 / restart
```
$ docker restart <컨테이너 이름>
```
### 컨테이너 접속 / attach
```
$ docker attach <컨테이너 이름>
```
### 외부에서 컨테이너 안에 명령 실행 / exec
```
$ docker exec <컨테이너 이름> <명령> <매개 변수>
```
> bash로 접속
```
$ docker exec -ti container_id /bin/bash
```

### 생성된 컨테이너 삭제 / rm
```
$ docker rm <컨테이너 이름>
```
### 생성된 이미지 삭제 / rmi
```
$ docker rmi <이미지 이름>:<태그>
```

## 기타 관리 명령
### 이미지 히스토리 조회 / history
```
docker history <이미지 이름>:<태그>
```
### 컨테이너에서 파일 전송 / cp
> 호스트 -> 컨테이너

docker cp [host 파일경로] [container name]:[container 내부 경로]

> 컨테이너 -> 호스트

docker cp [container name]:[container 내부 경로] [host 파일경로]

### 컨테이너의 변경 사항을 이미지 파일로 생성 / commit
```
docker commit <옵션> <컨테이너 이름> <이미지 이름>:<태그>
```
> 옵션
>   -a, --author=""  : 생성자 정보\
>   -m, --message="" : 이미지 메시지\
>   -p, --pause=true/false : 이미지를 생성할 때 컨테이너를 중지(stop) 한 뒤 commit 여부

### 생성된 이미지를 기준으로 컨테이너에 변경된 목록 출력 / diff
```
docker diff <컨테이너 이름>
```
- A는 추가된 파일, C는 변경된 파일, D는 삭제된 파일

### 이미지또는 컨테이너의 세부 설정 정보를 출력 / inspect
```
docker inspect <이미지 또는 컨테이너 이름>
```
---
## load & save
### 이미지를 tar파일로 저장 / save
```
docker save <옵션> <이미지 이름>:<태그>
```
- -o, --output=””: 저장할 파일명을 지정합니다.
```
$ sudo docker save -o nginx.tar nginx:latest
$ sudo docker save -o redis.tar redis:latest
$ sudo docker save ubuntu:14.04 > ubuntu14.04.tar
$ sudo docker save ubuntu > ubuntu.tar
```
```
$ docker images
REPOSITORY          TAG                 IMAGE ID            CREATED             SIZE
ubuntu              16.04               f975c5035748        4 months ago        112 MB
centos              7.4.1708            3afd47092a0e        8 months ago        197 MB
$ sudo docker save ubuntu:16.04 > ubuntu-16.04.tar

```
현재의 컨테이너를 이미지로 저장후에 backup으로 만드는 방법 
```
$ sudo docker ps -a | grep oracle // Oracle 컨테이너가 존재하는지 확인 
$ sudo docker commit oracle oracle_backup  // oracle 컨테이너를  'oracle_backup' 이라는 이미지로 저장
$ sudo docker save oracle_backup > /backup/oracle_xx.tar  // 'oracle_xx.tar'  라는 이름으로 백업

```
### tar파일에서 이미지를 생성 / load
```
docker load <옵션>
```
- -i, --input=””: 표준 입력을 사용하지 않고 파일 경로를 설정하여 이미지를 생성합니다.
```
$ sudo docker load < ubuntu.tar
$ sudo docker load -i ubuntu.img
```
---
## 빠른 실행
### 컨테이너 생성후 접속
```
mkdir -p ~/centos_share

docker run -t -i \
  -d \
  -h centos_host \
  --name centos_container \
  -v ~/centos_share:/home/root/git \
  -p 10022:22 \
  centos:7.3

ssh -p 10022 root@localhost
```
> run 실행시 자주 사용하는 옵션들
>	> -t, --tty                     Allocate a pseudo-TTY\
>	> -i, --interactive             Keep STDIN open even if not attached\
>	> -d, --detach                  Run container in background and print container ID  \
>	> --name=""                     Assign a name to the container\
>	> -v, --volume=[host-src:]container-dest[:<options>]\
>	> -p, --publish=[]              Publish a container's port(s) to the host
### image download 후 바로 실행하기
local에 16.04가 없는 경우 아래와 같이 다운로드후 컨테이너까지 생성합니다.
```
$ docker run ubuntu:16.04
Unable to find image 'ubuntu:16.04' locally
16.04: Pulling from library/ubuntu
..
Digest: sha256:9ee3b83bcaa383e5e3b657f042f4034c92cdd50c03f73166c145c9ceaea9ba7c
Status: Downloaded newer image for ubuntu:16.04

# docker ps -a
CONTAINER ID        IMAGE               COMMAND             CREATED             STATUS                      PORTS               NAMES
41ec7dccdc3e        ubuntu:16.04        "/bin/bash"         40 seconds ago      Exited (0) 39 seconds ago                       nostalgic_colden
```

```
docker run -it ubuntu:16.04 /bin/bash
root@fce967c97188:/#
```
---
## 참조 사이트
<http://pyrasis.com/Docker/Docker-HOWTO#section-5>
<https://docs.docker.com/v1.11/engine/reference/commandline/run>
