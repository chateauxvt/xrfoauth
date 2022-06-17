/**
* XRF OAuth2 Initial Authentication Request API
* XRF OAuth2 Authorization server, initial authentication with the xApp API 
*
* The version of the OpenAPI document: 1
* Contact: tolgaoa@vt.edu
*
* NOTE: This class is auto generated by OpenAPI Generator (https://openapi-generator.tech).
* https://openapi-generator.tech
* Do not edit the class manually.
*/

#include "InitialAuthenticationRequestApiImpl.h"
#include "InitAuthRsp.h"

namespace xrf::api {

using namespace xrf::model;
using namespace xrf::app;

InitialAuthenticationRequestApiImpl::InitialAuthenticationRequestApiImpl(
		std::shared_ptr<Pistache::Rest::Router>& rtr, xrf_main* xrf_main_inst,
	       	std::string addr)
    		: InitialAuthenticationRequestApi(rtr), m_xrf_main(xrf_main_inst), m_addr(addr) {}

void InitialAuthenticationRequestApiImpl::init_auth_request(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter &response) {
	spdlog::info("Incoming Authentication Request");
	int http_code = 200;
	ProblemDetails problem_details = {};
	InitAuthRsp init_auth_rsp = {};
	spdlog::debug("Entering Challenge Handle");
	m_xrf_main->handle_auth_request(request.body(), init_auth_rsp, http_code, 1, problem_details);
	spdlog::debug("Finished Challenge Handle");
	nlohmann::json json_data = {};
	std::string content_type = "application/problem+json";

	if (http_code != 200) {
		spdlog::debug("Authentication request HTTP code not 200");
		to_json(json_data, problem_details);
		content_type = "application/problem+json";
	} else {
		spdlog::debug("Authentication request HTTP code is 200");
		to_json(json_data, init_auth_rsp);
	};

	response.headers().add<Pistache::Http::Header::ContentType>(Pistache::Http::Mime::MediaType(content_type));
        
	response.send(Pistache::Http::Code(http_code), json_data.dump().c_str());	
	spdlog::debug("Created JSON Response for Authentication Challenge");
}

}

