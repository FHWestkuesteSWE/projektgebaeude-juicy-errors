/****
Session.h

(c) Kristina Schädler 2017
****/

#pragma once
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <boost/bind.hpp>
#include "BasicServer.h"

typedef boost::asio::ssl::stream<boost::asio::ip::tcp::socket> ssl_socket;
class SSLServer;

class Session
{
public:
	Session(boost::asio::io_service& io_service,
		boost::asio::ssl::context& context, SSLServer* p);
	~Session(){}
	ssl_socket::lowest_layer_type& socket();
	void start();
	void handle_handshake(const boost::system::error_code& error);
	void handle_read(const boost::system::error_code& error,
		size_t bytes_transferred);
	void handle_write(const boost::system::error_code& error);
private:
	ssl_socket socket_;
	SSLServer* processor;
	char data_[BasicServer::max_length];
};

