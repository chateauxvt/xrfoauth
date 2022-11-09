/*
 * Re-factoring of the XRF code by separating the registration module
 *
 * ! file main.cpp
 *  \brief
 * \author: Tolga Atalay 
 * \Affiliation: VirginiaTech
 * \date: 2022
 * \email: tolgaoa@vt.edu
*/

#include <pistache/endpoint.h>
#include <pistache/http.h>
#include <pistache/router.h>

#include "rapidjson/document.h"

#include <iostream>
#include "spdlog/spdlog.h"

#include "handlers.hpp"

using namespace Pistache;
using namespace xrf::app;

void handletok(const Rest::Request& req, Http::ResponseWriter resp){


        spdlog::debug("Receiving Token introspection --- Token: {}", req.body());
	handlers handler1;
	handler1.store_token(req.body());
	std::string response_send = "Token received";
        resp.send(Pistache::Http::Code::Ok, response_send);

}

void handlekey(const Rest::Request& req, Http::ResponseWriter resp){


        spdlog::debug("Receiving Token introspection --- Key: {}", req.body());
	std::string response_send;
	handlers handler1;
	int http_code;
	
	
	handler1.validate_token(req.body(), response_send);
        resp.send(Pistache::Http::Code::Ok, response_send);

}

int main(int argc, char* argv[])
{
	spdlog::set_level(spdlog::level::debug);
	using namespace Rest;

	Router router;
	Port port(9999);
	Address addr(Ipv4::any(), port);
	std::shared_ptr<Http::Endpoint> endpoint = std::make_shared<Http::Endpoint>(addr);
	auto opts = Http::Endpoint::options().threads(4);
	opts.flags(Pistache::Tcp::Options::ReuseAddr);
	endpoint->init(opts);

	Routes::Post(router, "/xrftokremexttok", Routes::bind(handletok));
	Routes::Post(router, "/xrftokremextkey", Routes::bind(handlekey));

	spdlog::info("Starting HTTP Server for XRF-Access remote introspection");
	endpoint->setHandler(router.handler());
	endpoint->serve();
}
