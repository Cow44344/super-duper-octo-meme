//
// daytime_server.cpp
// ~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2017 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <ctime>
#include <iostream>
#include <string>
#include <boost/asio.hpp>
using namespace std;
using boost::asio::ip::tcp;

string make_daytime_string()
{
  using namespace std; // For time_t, time and ctime;
  time_t now = time(0);
  return ctime(&now);
}

int main()
{
  try
  {
    boost::asio::io_context io_context;

    tcp::endpoint endpoint(tcp::v4(), 1300);
    tcp::acceptor acceptor(io_context, endpoint);

    for (;;)
    {
      tcp::iostream stream;
      boost::system::error_code ec;
      acceptor.accept(stream.socket(), ec);
      if (!ec)
      {
        stream << make_daytime_string();
        //stream << "Tristan Meyers inducted into the Toy Hall of Fame!\n";
      }
    }
  }
  catch (exception& e)
  {
    cerr << e.what() << endl;
  }
}
