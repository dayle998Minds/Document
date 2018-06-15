#include <boost/network/protocol/http/client.hpp>
#include <string>
#include <sstream>
#include <iostream>

namespace http = boost::network::http;

int main(int argc, char *argv[]) {
  char *url = nullptr;
  int port = 80;
  if (argc != 3) {
    std::cerr << "Usage: " << argv[0] << " address port" << std::endl;
    std::cout << "Force www.google.com 80" << std::endl;
    url = const_cast<char *>("www.google.com");
  } else {
    url = argv[1];
    port = atoi(argv[2]);
  }

  try {
    http::client client;
    std::ostringstream http_url;
    http_url << "http://" << url << ":" << port << "/";
    http::client::request request(http_url.str());
    http::client::response response =
      client.get(request);
    std::cout << body(response) << std::endl;
  } catch (std::exception &e) {
    std::cerr << e.what() << std::endl;
    return 1;
  }
  return 0;
}