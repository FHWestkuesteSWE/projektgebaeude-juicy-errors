#pragma once
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

typedef enum {
  ERR_ABORT = -1,
  ERR_NONE,
  ERR_RETRY,
} ERR_CODES;

class BasicClient
{
public:
  BasicClient();
  BasicClient(char server[], char port[]);
  int sendRequest(const char request[], char answer[]);
  ~BasicClient();
protected:
  
  static const int max_length=1024;
  
  char *server, *port;

};

