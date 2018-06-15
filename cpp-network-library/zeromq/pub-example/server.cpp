#include <zmq.hpp>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

int main() {
  zmq::context_t context(1);
  const char *protocol =
    "tcp://localhost:5555";
  //  Socket to talk to server
  printf("Connecting to hello world server...");
  zmq::socket_t sock(context, ZMQ_SUB);
  sock.connect(protocol);
  sock.setsockopt(ZMQ_SUBSCRIBE, "", 0);
  printf("done. \n");

  int request_nbr;
  while (true) {
    zmq::message_t reply;
    sock.recv(&reply, 0);
    printf("Received Word %d bytes: \"%s\"\n", reply.size(), reply.data());
  }
  sock.close();
  return 0;
}
