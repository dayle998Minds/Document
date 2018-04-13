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
### 컨테이너에서 파일을 가져오기 / cp
```
docker cp <컨테이너 이름>:<경로> <호스트 경로>
```
예제
```
10:24 $ docker ps -a
CONTAINER ID        IMAGE                  COMMAND                  CREATED             STATUS                   PORTS                  NAMES
fcece1dcf71c        maum-dev-centos:0.19   "/usr/sbin/sshd -D"      2 days ago          Up 2 days                0.0.0.0:5022->22/tcp   cmdev2
✔ ~/git/document/docker [master {origin/master}|✚ 1…1] 
10:24 $ docker cp cmdev2:/etc/nginx/nginx.conf ./
```
### 컨테이너의 변경 사항을 이미지 파일로 생성 / commit
```
docker commit <옵션> <컨테이너 이름> <이미지 이름>:<태그>
```
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
## 참조 사이트
<http://pyrasis.com/Docker/Docker-HOWTO#section-5>