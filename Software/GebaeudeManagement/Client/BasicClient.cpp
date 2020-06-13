#include "BasicClient.h"
#include <boost/exception/all.hpp>
#include <exception>


// constructor
BasicClient::BasicClient() {}
BasicClient::BasicClient(char _server[], char _port[]) {
  server = _server;
  port = _port;
}

// send request to server
int BasicClient::sendRequest(const char request[], char answer[]) {
  boost::asio::io_service io_service;

  tcp::resolver resolver(io_service);
  tcp::resolver::query query(tcp::v4(), server, port);
  tcp::resolver::iterator iterator = resolver.resolve(query);

  tcp::socket s(io_service);
  
  try {
    boost::asio::connect(s, iterator);
  }
  catch (const std::exception& e) { // reference to the base of a polymorphic object      
      std::cout << "ERROR: " << e.what() << "\n\n"; // information from length_error printed
      std::cout << "Server could not be reached.\n\n";
      std::cout << "(r)etry\n";
      std::cout << "(a)bort\n\n";
      char choice;
      std::cin >> choice;
      std::cin.ignore(INT_MAX, '\n');
      std::cin.clear(); 
      if ( choice == 'r' ) return 1; // retry
      else return -1; // error, abort!
  }

  size_t request_length = strlen(request)+1;
  boost::asio::write(s, boost::asio::buffer(request, request_length));

  // size_t reply_length =   
  try {
      boost::asio::read(s, boost::asio::buffer(answer, max_length));
  }
  catch (const std::exception& e) { // reference to the base of a polymorphic object
      std::cout << "ERROR: " << e.what() << "\n\n"; // information from length_error printed
  }
  
  return 0; // all good
}

// destructor
BasicClient::~BasicClient() {

}
