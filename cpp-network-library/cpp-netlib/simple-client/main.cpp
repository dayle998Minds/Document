#include <boost/network/protocol/http/client.hpp>
#include <iostream>

int main(int argc, char *argv[]) {
  using namespace boost::network;
  char *url = nullptr;
  if (argc != 2) {
    std::cout << "Usage: " << argv[0] << " [url]" << std::endl;
    std::cout << "Force url http://www.google.com" << std::endl;
    url = const_cast<char *>("http://www.google.com");
  } else {
    url = argv[1];
  }

  http::client client;
  http::client::request request(url);
  request << header("Connection", "close");
  http::client::response response = client.get(request);
  std::cout << body(response) << std::endl;

  return 0;
}