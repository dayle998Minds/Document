#include <boost/asio/io_service.hpp>
#include <boost/asio/steady_timer.hpp>
#include <boost/date_time.hpp>

#include <thread>
#include <iostream>

using namespace boost::asio;
// Two threads for the I/O service object to execute handlers concurrently
int main1()
{
  io_service ioservice;

  steady_timer timer1{ioservice, std::chrono::seconds{3}};
  timer1.async_wait([](const boost::system::error_code &ec)
                    { std::cout << "main1 timer1 - 3 sec\n"; });

  steady_timer timer2{ioservice, std::chrono::seconds{5}};
  timer2.async_wait([](const boost::system::error_code &ec)
                    { std::cout << "main1 timer2 - 5 sec\n"; });

  std::thread thread1{[&ioservice](){ ioservice.run(); }};
  std::thread thread2{[&ioservice](){ ioservice.run(); }};
  thread1.join();
  thread2.join();
}

// One thread for each of two I/O service objects to execute handlers concurrently
int main2()
{
  io_service ioservice1;
  io_service ioservice2;

  steady_timer timer1{ioservice1, std::chrono::seconds{4}};
  timer1.async_wait([](const boost::system::error_code &ec)
                    { std::cout << "main2 timer1 - 4 sec\n"; });

  steady_timer timer2{ioservice2, std::chrono::seconds{8}};
  timer2.async_wait([](const boost::system::error_code &ec)
                    { std::cout << "main2 timer2 - 8 sec\n"; });

  std::thread thread1{[&ioservice1](){ ioservice1.run(); }};
  std::thread thread2{[&ioservice2](){ ioservice2.run(); }};
  thread1.join();
  thread2.join();
}
int main()
{
  // Get current system time
  {
    boost::posix_time::ptime timeLocal =
      boost::posix_time::second_clock::local_time();

    std::cout << "Start Time = " << timeLocal << std::endl;
  }

  main1();
  main2();
  // Get current system time
  {
    boost::posix_time::ptime timeLocal =
      boost::posix_time::second_clock::local_time();

    std::cout << "End Time = " << timeLocal << std::endl;
  }

  return 0;
}