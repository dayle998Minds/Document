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
#include <stdarg.h>

extern int errno;

// maximum received data byte
#define MAXBTYE     10
#define LISTENQ     20
#define LOCAL_ADDR  "0.0.0.0"
#define TIMEOUT     500

// task item in thread pool
struct task {
  // file descriptor or user_data
  epoll_data_t data;
  // next task
  struct task *next;
};

// for data transporting
struct user_data {
  int fd;
  // real received data size
  unsigned int n_size;
  // content received
  char line[MAXBTYE];
};

void *readtask(void *args);

void *writetask(void *args);

// epoll descriptor from epoll_create()
int epfd;
// register epoll_ctl()
struct epoll_event ev;
// store queued events from epoll_wait()
struct epoll_event events[LISTENQ];
// mutex lock to protect readhead/readtail
pthread_mutex_t r_mutex;
pthread_cond_t r_condl;
// mutex lock to protect writehead/writetail
pthread_mutex_t w_mutex;
pthread_cond_t w_condl;
struct task *readhead = NULL, *readtail = NULL;
struct task *writehead = NULL, *writetail = NULL;

// Print error information
int errexit(const char* format, ...)
{
  va_list args;
  va_start(args, format);
  vfprintf(stderr, format, args);
  va_end(args);
  exit(1);
}

// Print work information
void echo(const char* format, ...)
{
  va_list args;
  va_start(args, format);
  vfprintf(stderr, format, args);
  va_end(args);
}


void setnonblocking(int sock) {
  int opts;
  if ((opts = fcntl(sock, F_GETFL)) < 0)
    errexit("GETFL %d failed", sock);
  opts = opts | O_NONBLOCK;
  if (fcntl(sock, F_SETFL, opts) < 0)
    errexit("SETFL %d failed", sock);
}

int main(int argc, char *argv[]) {
  // nfds is number of events (number of returned fd)
  int i, maxi, nfds;
  int listenfd, connfd;
  // read task threads
  pthread_t tid1, tid2;
  // write back threads
  pthread_t tid3, tid4;
  // task node
  struct task *new_task = NULL;
  socklen_t clilen;
  struct sockaddr_in clientaddr;
  struct sockaddr_in serveraddr;

  pthread_mutex_init(&r_mutex, NULL);
  pthread_cond_init(&r_condl, NULL);
  pthread_mutex_init(&w_mutex, NULL);
  pthread_cond_init(&w_condl, NULL);

  // threads for reading thread pool
  pthread_create(&tid1, NULL, readtask, NULL);
  pthread_create(&tid2, NULL, readtask, NULL);
  // threads for respond to client
  pthread_create(&tid3, NULL, writetask, NULL);
  pthread_create(&tid4, NULL, writetask, NULL);

  // epoll descriptor, for handling accept
  epfd = epoll_create(256);
  listenfd = socket(PF_INET, SOCK_STREAM, 0);
  // set the descriptor as non-blocking
  setnonblocking(listenfd);
  // event related descriptor
  ev.data.fd = listenfd;
  // monitor in message, edge trigger
  ev.events = EPOLLIN | EPOLLET;
  // register epoll event
  epoll_ctl(epfd, EPOLL_CTL_ADD, listenfd, &ev);

  short port = 8842;
  if (argc > 1)
    port = atoi(argv[1]);

  bzero(&serveraddr, sizeof(serveraddr));
  serveraddr.sin_family = AF_INET;
  char *local_addr = LOCAL_ADDR;
  inet_aton(local_addr, &(serveraddr.sin_addr));
  serveraddr.sin_port = htons(port);
  bind(listenfd, (struct sockaddr *) &serveraddr, sizeof(serveraddr));
  printf("Thread-Echo-Server bind(%d)..ok", port);
  listen(listenfd, LISTENQ);

  maxi = 0;
  for (;;) {
    // waiting for epoll event
    nfds = epoll_wait(epfd, events, LISTENQ, TIMEOUT);
    // In case of edge trigger, must go over each event
    for (i = 0; i < nfds; ++i) {
      // Get new connection
      if (events[i].data.fd == listenfd) {
        // accept the client connection
        connfd = accept(listenfd, (struct sockaddr *) &clientaddr, &clilen);
        if (connfd < 0)
          errexit("connfd < 0");
        setnonblocking(connfd);
        echo("[SERVER] connect from %s \n", inet_ntoa(clientaddr.sin_addr));
        ev.data.fd = connfd;
        // monitor in message, edge trigger
        ev.events = EPOLLIN | EPOLLET;
        // add fd to epoll queue
        epoll_ctl(epfd, EPOLL_CTL_ADD, connfd, &ev);
      }
        // Received data
      else if (events[i].events & EPOLLIN) {
        if (events[i].data.fd < 0)
          continue;
        echo("[SERVER] put task %d to read queue\n", events[i].data.fd);
        new_task = static_cast<task *>(malloc(sizeof(struct task)));
        new_task->data.fd = events[i].data.fd;
        new_task->next = NULL;
        pthread_mutex_lock(&r_mutex);
        if (readhead == NULL) {
          readhead = new_task;
          readtail = new_task;
        }
          // queue is not empty
        else {
          readtail->next = new_task;
          readtail = new_task;
        }
        // trigger readtask thread
        pthread_cond_broadcast(&r_condl);
        pthread_mutex_unlock(&r_mutex);
      }
        // Have data to send
      else if (events[i].events & EPOLLOUT) {
        if (events[i].data.ptr == NULL)
          continue;
        echo("[SERVER] put task %d to write queue\n", ((struct task *) events[i].data.ptr)->data.fd);
        new_task = static_cast<task *>(malloc(sizeof(struct task)));
        new_task->data.ptr = (struct user_data *) events[i].data.ptr;
        new_task->next = NULL;
        pthread_mutex_lock(&w_mutex);
        // the queue is empty
        if (writehead == NULL) {
          writehead = new_task;
          writetail = new_task;
        }
          // queue is not empty
        else {
          writetail->next = new_task;
          writetail = new_task;
        }
        // trigger writetask thread
        pthread_cond_broadcast(&w_condl);
        pthread_mutex_unlock(&w_mutex);
      } else {
        echo("[SERVER] Error: unknown epoll event");
      }
    }
  }

  return 0;
}

void *readtask(void *args) {
  int fd = -1;
  int n, i;
  struct user_data *data = NULL;
  while (1) {
    // protect task queue (readhead/readtail)
    pthread_mutex_lock(&r_mutex);
    while (readhead == NULL)
      // if condl false, will unlock mutex
      pthread_cond_wait(&r_condl, &r_mutex);

    fd = readhead->data.fd;
    struct task *tmp = readhead;
    readhead = readhead->next;
    free(tmp);

    pthread_mutex_unlock(&r_mutex);

    echo("[SERVER] readtask %d handling %d\n", pthread_self(), fd);
    data = static_cast<user_data *>(malloc(sizeof(struct user_data)));
    data->fd = fd;
    if ((n = recv(fd, data->line, MAXBTYE, 0)) < 0) {
      if (errno == ECONNRESET)
        close(fd);
      echo("[SERVER] Error: readline failed: %s\n", strerror(errno));
      if (data != NULL)
        free(data);
    } else if (n == 0) {
      close(fd);
      echo("[SERVER] Error: client closed connection.\n");
      if (data != NULL)
        free(data);
    } else {
      data->n_size = n;
      for (i = 0; i < n; ++i) {
        if (data->line[i] == '\n' || data->line[i] > 128) {
          data->line[i] = '\0';
          data->n_size = i + 1;
        }
      }
      echo("[SERVER] readtask %d received %d : [%d] %s\n", pthread_self(), fd, data->n_size, data->line);
      if (data->line[0] != '\0') {
        // modify monitored event to EPOLLOUT,  wait next loop to send respond
        ev.data.ptr = data;
        // Modify event to EPOLLOUT
        ev.events = EPOLLOUT | EPOLLET;
        // modify moditored fd event
        epoll_ctl(epfd, EPOLL_CTL_MOD, fd, &ev);
      }
    }
  }
}

void *writetask(void *args) {
  unsigned int n;
  // data to wirte back to client
  struct user_data *rdata = NULL;
  while (1) {
    pthread_mutex_lock(&w_mutex);
    while (writehead == NULL)
      // if condl false, will unlock mutex
      pthread_cond_wait(&w_condl, &w_mutex);

    rdata = (struct user_data *) writehead->data.ptr;
    struct task *tmp = writehead;
    writehead = writehead->next;
    free(tmp);

    pthread_mutex_unlock(&w_mutex);

    echo("[SERVER] writetask %d sending %d : [%d] %s\n", pthread_self(), rdata->fd, rdata->n_size, rdata->line);
    // send responce to client
    if ((n = send(rdata->fd, rdata->line, rdata->n_size, 0)) < 0) {
      if (errno == ECONNRESET)
        close(rdata->fd);
      echo("[SERVER] Error: send responce failed: %s\n", strerror(errno));
    } else if (n == 0) {
      close(rdata->fd);
      echo("[SERVER] Error: client closed connection.");
    } else {
      // modify monitored event to EPOLLIN, wait next loop to receive data
      ev.data.fd = rdata->fd;
      // monitor in message, edge trigger
      ev.events = EPOLLIN | EPOLLET;
      // modify moditored fd event
      epoll_ctl(epfd, EPOLL_CTL_MOD, rdata->fd, &ev);
    }
    // delete data
    free(rdata);
  }
}