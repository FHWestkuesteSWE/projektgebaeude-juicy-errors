/****
SSLClient.h

(c) Kristina Schädler 2017
****/

#pragma once
#include "BasicClient.h"
#include <boost/asio/ssl.hpp>
#include <boost/bind.hpp>
class SSLClient: public BasicClient
{
public:
	SSLClient(char _server[], char _port[]);
	~SSLClient();

	virtual void sendRequest(const char request[], char answer[]);
	bool verify_certificate(bool preverified,
		boost::asio::ssl::verify_context& ctx);
	void handle_connect(const boost::system::error_code& error);

	void handle_handshake(const boost::system::error_code& error);

	void handle_write(const boost::system::error_code& error,
		size_t bytes_transferred);

	void handle_read(const boost::system::error_code& error,
		size_t bytes_transferred);
private:
	boost::asio::ssl::stream<boost::asio::ip::tcp::socket> *socket_;
	char request_[max_length];
	char reply_[max_length];
};

