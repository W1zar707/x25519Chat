#pragma once
#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio.hpp>
#include <queue>
#include <iostream>
#include "ecdh.h"
namespace beast = boost::beast;
namespace websocket = beast::websocket;
namespace net = boost::asio;
using tcp = net::ip::tcp;
using namespace std;
struct Server : public std::enable_shared_from_this<Server> {
	beast::flat_buffer buffer_;
	tcp::resolver resolver_;
	queue<vector<uint8_t>> writeQueue;

	websocket::stream<tcp::socket> socket;
	bool isWriting = false;

	uint8_t secret_[32] = {};

	string host_;
	int port_ = 8080;
	explicit Server(net::io_context& ioc)
		: resolver_(ioc), socket(ioc) {}
	void run();
	void send(const string& message);
private:
	void on_read();
	void do_send();
	void on_send(beast::error_code ec, std::size_t);
	vector<uint8_t> encrypt(const uint8_t* plaintext, size_t plaintext_len);
	vector<uint8_t> decrypt(const std::vector<uint8_t>& message);
	void fail(beast::error_code ec, const char* what);
};