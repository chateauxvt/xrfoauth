/**
* XRFc Service test API
* XRFc service testing API 
*
* The version of the OpenAPI document: 1
* Contact: tolgaoa@vt.edu
*
* NOTE: This class is auto generated by OpenAPI Generator (https://openapi-generator.tech).
* https://openapi-generator.tech
* Do not edit the class manually.
*/

#include "ServiceTestRequestApiImpl.h"

namespace xrf {
namespace api {

using namespace xrf::model;
using namespace xrf::app;

ServiceTestRequestApiImpl::ServiceTestRequestApiImpl(std::shared_ptr<Pistache::Rest::Router>& rtr, xapp_main* xapp_main_inst,
		                                     std::string addr) 
    						     : ServiceTestRequestApi(rtr) , m_xapp_main(xapp_main_inst), m_addr(addr) {}

void ServiceTestRequestApiImpl::serv_test_req(const Pistache::Rest::Request &request, std::string& bearer, Pistache::Http::ResponseWriter &response) {
    	spdlog::debug("Passed bearer: {} to the handler", bearer);
	
	bool tokenValid;
	const std::string jwksEndpoint = "http://127.0.0.1:9090/oauth/jwks";
	const std::string introEndpoint = "http://127.0.0.1:9090/oauth/intro";

	//m_xapp_main->validate_token_self(jwksEndpoint, bearer, tokenValid);
	m_xapp_main->validate_token_remote(introEndpoint, bearer, tokenValid);
	
	if (tokenValid) {	
		response.send(Pistache::Http::Code::Ok, "https://www.tomorrowtides.com/service15.html\n");
	}else spdlog::error("OAuth Token invalid");

}

}
}

