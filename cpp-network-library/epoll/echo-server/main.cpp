// socket interface
#include <sys/socket.h>
// epoll interface
#include <sys/epoll.h>
// struct sockaddr_in
#include <netinet/in.h>
// IP addr convertion
#include <arpa/inet.h>
// File descriptor controller
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
// bzero()
#include <string.h>
// malloc(), free()
#include <stdlib.h>
#include <errno.h>

#define SA  struct sockaddr
#define EPOLL_SIZE    20

int main(int argc, char **argv) {
  struct sockaddr_in addr, clientaddr;
  struct eph_comm *conn;
  int sfd;
  int cfd;
  socklen_t clilen;
  int flags = 1;
  int n, i;
  int readn;
  struct epoll_event ev, *events;

  int efd;
  char buf_in[256];

  // 이벤트 풀의 크기만큼 events구조체를 생성한다.
  events = (struct epoll_event *) malloc(sizeof(*events) * EPOLL_SIZE);

  // epoll_create를 이용해서 epoll 지정자를 생성한다.
  if ((efd = epoll_create(100)) < 0) {
    perror("epoll_create error");
    return 1;
  }

  short port = 8840;
  if (argc > 1)
    port = atoi(argv[1]);

  // --------------------------------------
  // 듣기 소켓 생성을 위한 일반적인 코드
  clilen = sizeof(clientaddr);
  sfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sfd == -1) {
    perror("socket error :");
    close(sfd);
    return 1;
  }
  addr.sin_family = AF_INET;
  addr.sin_port = htons(port);
  addr.sin_addr.s_addr = htonl(INADDR_ANY);
  if (bind(sfd, (struct sockaddr *) &addr, sizeof(addr)) == -1) {
    perror("bind failed \n");
    close(sfd);
    return 1;
  }
  listen(sfd, 5);
  // --------------------------------------

  // 만들어진 듣기 소켓을 epoll이벤트 풀에 추가한다.
  // EPOLLIN(read) 이벤트의 발생을 탐지한다.
  ev.events = EPOLLIN;
  ev.data.fd = sfd;
  epoll_ctl(efd, EPOLL_CTL_ADD, sfd, &ev);
  printf("Listen Server.. port=%d", port);
  while (1) {
    // epoll이벤트 풀에서 이벤트가 발생했는지를 검사한다.
    n = epoll_wait(efd, events, EPOLL_SIZE, -1);
    if (n == -1) {
      perror("epoll wait error");
    }

    // 만약 이벤트가 발생했다면 발생한 이벤트의 수만큼
    // 돌면서 데이터를 읽어 옵니다.
    for (i = 0; i < n; i++) {
      // 만약 이벤트가 듣기 소켓에서 발생한 거라면
      // accept를 이용해서 연결 소켓을 생성한다.
      if (events[i].data.fd == sfd) {
        printf("Accept\n");
        cfd = accept(sfd, (SA *) &clientaddr, &clilen);
        ev.events = EPOLLIN;
        ev.data.fd = cfd;
        epoll_ctl(efd, EPOLL_CTL_ADD, cfd, &ev);
        printf("[0x%x] child accept\n", cfd);
      }
        // 연결소켓에서 이벤트가 발생했다면
        // 데이터를 읽는다.
      else {
        memset(buf_in, 0x00, 256);
        readn = read(events[i].data.fd, buf_in, 255);
        if (readn <= 0) {
          epoll_ctl(efd, EPOLL_CTL_DEL, events[i].data.fd, events);
          close(events[i].data.fd);
          printf("[0x%x] Close fd\n", cfd);
        } else {
          printf("[0x%x] read data %s\n", events[i].data.fd, buf_in);
          write(events[i].data.fd, buf_in, readn);
        }
      }
    }
  }
}