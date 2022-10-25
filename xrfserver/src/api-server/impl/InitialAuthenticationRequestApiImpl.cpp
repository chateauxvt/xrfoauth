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

const char *authextIP = "AUTH_EXT_IP";

namespace xrf::api {

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
        ((std::string*)userp)->append((char*)contents, size * nmemb);
        return size * nmemb;
}

void send_custom_curl(std::string& uri, std::string& message, std::string& response) {
        CURL *curl;
        CURLcode res;
        std::string readBuffer;

        struct curl_slist *slist1;
        slist1 = NULL;
        slist1 = curl_slist_append(slist1, "Content-Type: application/json");

        curl = curl_easy_init();

        if(curl) {
                curl_easy_setopt(curl, CURLOPT_URL, uri.c_str());
                curl_easy_setopt(curl, CURLOPT_POST, 1);
                curl_easy_setopt(curl, CURLOPT_HTTPHEADER, slist1);
                curl_easy_setopt(curl, CURLOPT_POSTFIELDS, message.c_str());
                curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
                curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
                res = curl_easy_perform(curl);
                curl_easy_cleanup(curl);
        }
        response = readBuffer;
}

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


	//m_xrf_main->handle_auth_request(request.body(), init_auth_rsp, http_code, 1, problem_details); //internal handle


	//-------------------External handler isolation-------------------

        //Get IP Addresses for Remote Auth Server
        const char *tmp1 = getenv("AUTH_EXT_IP");
        std::string AUTHEXTIP(tmp1 ? tmp1 : "");
        if (AUTHEXTIP.empty()) {
		spdlog::error("auth remote server IP not found");
                exit(EXIT_FAILURE);
        }
	spdlog::debug("auth remote server IP is: {}", AUTHEXTIP.c_str());

	//std::string AUTHEXTIP = "127.0.0.1";
	std::string uriauthext="http://" + AUTHEXTIP + ":9999/xrfauthext";
	std::string authext_send = request.body();
	std::string respauthext;	

	send_custom_curl(uriauthext, authext_send, respauthext);//external handle
	
	init_auth_rsp.setChallenge(respauthext);
	//-------------------External handler isolation-------------------


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

