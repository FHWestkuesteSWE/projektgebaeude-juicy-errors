/****
SSLServer.cpp

(c) Kristina Schädler 2017
****/

#include "SSLServer.h"

SSLServer::SSLServer(): context_(boost::asio::ssl::context::sslv23)
{
	context_.set_options(
		boost::asio::ssl::context::default_workarounds
		| boost::asio::ssl::context::no_sslv2
		| boost::asio::ssl::context::single_dh_use);
	context_.use_certificate_chain_file("server.crt");
	context_.use_private_key_file("server.key", boost::asio::ssl::context::pem);
	context_.use_tmp_dh_file("dh1024.pem");

}


SSLServer::~SSLServer()
{
}

void SSLServer::start(char port[]) {
	boost::asio::io_service io_service;

	using namespace std; // For atoi.
	using boost::asio::ip::tcp;
	tcp::acceptor a(io_service, tcp::endpoint(tcp::v4(), atoi(port)));
	start_accept(io_service, a);
	io_service.run();
}

void SSLServer::start_accept(boost::asio::io_service& io_service_, boost::asio::ip::tcp::acceptor& acceptor)
{
    Session* new_session = new Session(io_service_, context_, this);
    acceptor.async_accept(new_session->socket(),
        boost::bind(&SSLServer::handle_accept, this, new_session, &io_service_, &acceptor,
            boost::asio::placeholders::error));

}

void SSLServer::handle_accept(Session* new_session, boost::asio::io_service* io_service, boost::asio::ip::tcp::acceptor* acceptor,
   const boost::system::error_code& error)
{
    if (!error)
    {
        new_session->start();
    }
    else
    {
        delete new_session;
    }

    start_accept(*io_service, *acceptor);
}
