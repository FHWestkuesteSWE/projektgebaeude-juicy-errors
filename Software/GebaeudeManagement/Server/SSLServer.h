/****
SSLServer.h

(c) Kristina Schädler 2017
****/

#pragma once
#include <boost/asio/ssl.hpp>
#include "BasicServer.h"
#include "Session.h"

class SSLServer : public BasicServer
{
public:

	void start(char port[]);
	SSLServer();
	~SSLServer();
	boost::asio::ssl::context context_;
	void start_accept(boost::asio::io_service& io_service_, boost::asio::ip::tcp::acceptor& acceptor);
	void handle_accept(Session* new_session, boost::asio::io_service* io_service, boost::asio::ip::tcp::acceptor* acceptor,
		 const boost::system::error_code& error);
};

