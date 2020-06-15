/****
Session.cpp

(c) Kristina Schädler 2017
****/

#include "Session.h"
#include "SSLServer.h"

Session::Session(boost::asio::io_service& io_service,
    boost::asio::ssl::context& context, SSLServer* p)
    : socket_(io_service, context)
{
    processor = p;
}


ssl_socket::lowest_layer_type& Session::socket()
{
    return socket_.lowest_layer();
}

void Session::start()
{
    socket_.async_handshake(boost::asio::ssl::stream_base::server,
        boost::bind(&Session::handle_handshake, this,
            boost::asio::placeholders::error));
}

void Session::handle_handshake(const boost::system::error_code& error)
{
    if (!error)
    {
        socket_.async_read_some(boost::asio::buffer(data_, BasicServer::max_length),
            boost::bind(&Session::handle_read, this,
                boost::asio::placeholders::error,
                boost::asio::placeholders::bytes_transferred));
    }
    else
    {
        delete this;
    }
}

void Session::handle_read(const boost::system::error_code& error,
    size_t bytes_transferred)
{
    if (!error)
    {
        char data2[BasicServer::max_length];
        processor->processRequest(data_, data2);
		int bytes_to_transfer = strlen(data2) + 1;
        boost::asio::async_write(socket_,
            boost::asio::buffer(data2, BasicServer::max_length),
            boost::bind(&Session::handle_write, this,
                boost::asio::placeholders::error));
    }
    else
    {
        delete this;
    }
}

void Session::handle_write(const boost::system::error_code& error)
{
    if (!error)
    {
        socket_.async_read_some(boost::asio::buffer(data_, BasicServer::max_length),
            boost::bind(&Session::handle_read, this,
                boost::asio::placeholders::error,
                boost::asio::placeholders::bytes_transferred));
    }
    else
    {
        delete this;
    }
}
