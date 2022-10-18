/**
* XRF OAuth2 Token Introspection Request API
* XRF OAuth2 Authorization server, token introspection API 
*
* The version of the OpenAPI document: 1
* Contact: tolgaoa@vt.edu
*
* NOTE: This class is auto generated by OpenAPI Generator (https://openapi-generator.tech).
* https://openapi-generator.tech
* Do not edit the class manually.
*/

#include "TokenIntrospectionRequestApiImpl.h"

const char *tokallextIP = "TOKALL_EXT_IP";
static size_t WriteCallback4(void *contents, size_t size, size_t nmemb, void *userp)
{
        ((std::string*)userp)->append((char*)contents, size * nmemb);
        return size * nmemb;
}

void send_custom_curl4(std::string& uri, std::string& message, std::string& response) {
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
                curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback4);
                curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
                res = curl_easy_perform(curl);
                curl_easy_cleanup(curl);
        }
        response = readBuffer;
}
namespace xrf {
namespace api {

using namespace xrf::model;


TokenIntrospectionRequestApiImpl::TokenIntrospectionRequestApiImpl(std::shared_ptr<Pistache::Rest::Router>& rtr,
								   xrf_main* xrf_main_inst, std::string addr)
    : TokenIntrospectionRequestApi(rtr) , m_xrf_main(xrf_main_inst), m_addr(addr) {}

void TokenIntrospectionRequestApiImpl::token_intro_request(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter &response) {

	spdlog::info("=============Incoming Token Introspection Request=============");
	
	int http_code = 200;

	bool validity;

	//m_xrf_main->validate_token(request.body(), validity);

        //---------------------External Isolation Handler------------------
        const char *tmp1 = getenv("TOKALL_EXT_IP");
        std::string TOKALLEXTIP(tmp1 ? tmp1 : "");
        if (TOKALLEXTIP.empty()) {
                spdlog::error("token handler remote server IP not found");
                exit(EXIT_FAILURE);
        }
        spdlog::debug("token handler remote server IP is: {}", TOKALLEXTIP.c_str());

        //std::string AUTHEXTIP = "127.0.0.1";
        std::string uritokallext="http://" + TOKALLEXTIP + ":9999/xrftokintroext";
        std::string tokallext_send = request.body();
        std::string resptokallext;

        send_custom_curl4(uritokallext, tokallext_send, resptokallext);//external handle

        spdlog::debug("Validity is: {}", resptokallext);
	validity = true;
        //-------------------External Isolation Handler End----------------


	nlohmann::json data;
	data["result"] = "true";

	if (validity) response.send(Pistache::Http::Code(http_code), data.dump().c_str());
	else spdlog::error("token not valid");
}

}
}

