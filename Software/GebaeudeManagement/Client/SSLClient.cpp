/****
SSLClient.cpp

(c) Kristina Schädler 2017
****/

#include "SSLClient.h"
#include <boost/bind.hpp>

SSLClient::SSLClient(char _server[], char _port[]) : BasicClient(_server,_port)
{
}

void SSLClient::sendRequest(const char request[], char answer[]) {
    strcpy(request_,request);
	boost::asio::io_service io_service;

	boost::asio::ip::tcp::resolver resolver(io_service);
	boost::asio::ip::tcp::resolver::query query(server,port);
	boost::asio::ip::tcp::resolver::iterator iterator = resolver.resolve(query);

	boost::asio::ssl::context ctx(boost::asio::ssl::context::sslv23);
	ctx.load_verify_file("server.crt");

	socket_=new boost::asio::ssl::stream<boost::asio::ip::tcp::socket>(io_service, ctx);

		socket_->set_verify_mode(boost::asio::ssl::verify_peer);
		socket_->set_verify_callback(
			boost::bind(&SSLClient::verify_certificate, this, _1, _2));

		boost::asio::async_connect(socket_->lowest_layer(), iterator,
			boost::bind(&SSLClient::handle_connect, this,
				boost::asio::placeholders::error));
		io_service.run();
    strcpy(answer, reply_);

}


SSLClient::~SSLClient()
{
}

bool SSLClient::verify_certificate(bool preverified,
    boost::asio::ssl::verify_context& ctx)
{
    // The verify callback can be used to check whether the certificate that is
    // being presented is valid for the peer. For example, RFC 2818 describes
    // the steps involved in doing this for HTTPS. Consult the OpenSSL
    // documentation for more details. Note that the callback is called once
    // for each certificate in the certificate chain, starting from the root
    // certificate authority.

    // In this example we will simply print the certificate's subject name.
    char subject_name[256];
    X509* cert = X509_STORE_CTX_get_current_cert(ctx.native_handle());
    X509_NAME_oneline(X509_get_subject_name(cert), subject_name, 256);
    std::cout << "Verifying " << subject_name << "\n";

    return preverified;
}
void SSLClient::handle_connect(const boost::system::error_code& error)
{
    if (!error)
    {
        socket_->async_handshake(boost::asio::ssl::stream_base::client,
            boost::bind(&SSLClient::handle_handshake, this,
                boost::asio::placeholders::error));
    }
    else
    {
        std::cout << "Connect failed: " << error.message() << "\n";
    }
}

void SSLClient::handle_handshake(const boost::system::error_code& error)
{

    if (!error)
    {
        size_t request_length = strlen(request_)+1;

        boost::asio::async_write(*socket_,
            boost::asio::buffer(request_, request_length),
            boost::bind(&SSLClient::handle_write, this,
                boost::asio::placeholders::error,
                boost::asio::placeholders::bytes_transferred));
    }
    else
    {
        std::cout << "Handshake failed: " << error.message() << "\n";
    }


}

void SSLClient::handle_write(const boost::system::error_code& error,
    size_t bytes_transferred)
{
    if (!error)
    {
        boost::asio::async_read(*socket_,
            boost::asio::buffer(reply_, BasicClient::max_length),
            boost::bind(&SSLClient::handle_read, this,
                boost::asio::placeholders::error,
                BasicClient::max_length));
    }
    else
    {
        std::cout << "Write failed: " << error.message() << "\n";
    }
}

void SSLClient::handle_read(const boost::system::error_code& error,
    size_t bytes_transferred)
{
    if (!error)
    {


    }
    else
    {
        std::cout << "Read failed: " << error.message() << "\n";
    }
}

