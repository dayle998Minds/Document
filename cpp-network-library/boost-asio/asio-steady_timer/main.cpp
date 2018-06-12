#include <boost/asio/io_service.hpp>
#include <boost/asio/steady_timer.hpp>
#include <iostream>
#include <boost/date_time.hpp>

using namespace boost::asio;

int main()
{
  // Get current system time
  {
    boost::posix_time::ptime timeLocal =
      boost::posix_time::second_clock::local_time();

    std::cout << "Start Time = " << timeLocal << std::endl;
  }

  io_service ioservice;

  steady_timer timer1{ioservice, std::chrono::seconds{3}};
  timer1.async_wait([](const boost::system::error_code &ec)
                    { std::cout << "3 sec\n"; });

  steady_timer timer2{ioservice, std::chrono::seconds{7}};
  timer2.async_wait([](const boost::system::error_code &ec)
                    { std::cout << "7 sec\n"; });

  ioservice.run();

  {
    boost::posix_time::ptime timeLocal =
      boost::posix_time::second_clock::local_time();

    std::cout << "End Time = " << timeLocal << std::endl;
  }

}