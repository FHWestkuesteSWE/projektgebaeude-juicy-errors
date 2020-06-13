#include "BasicClient.h"


// constructor
BasicClient::BasicClient() {}
BasicClient::BasicClient(char _server[], char _port[]) {
  server = _server;
  port = _port;
}

// send request to server
void BasicClient::sendRequest(const char request[], char answer[]) {
  boost::asio::io_service io_service;

  tcp::resolver resolver(io_service);
  tcp::resolver::query query(tcp::v4(), server, port);
  tcp::resolver::iterator iterator = resolver.resolve(query);

  tcp::socket s(io_service);
  
  try {
    boost::asio::connect(s, iterator);
  }
  catch (const std::exception& e) { // reference to the base of a polymorphic object      
      //std::cout << e << endl;
      std::cout << e.what(); // information from length_error printed
  }
  size_t request_length = strlen(request)+1;
  boost::asio::write(s, boost::asio::buffer(request, request_length));

  // size_t reply_length = 
  boost::asio::read(s, boost::asio::buffer(answer, max_length));
}

// destructor
BasicClient::~BasicClient() {

}
