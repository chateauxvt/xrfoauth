/**
* XRF OAuth2
* XRF OAuth2 Authorization server for generating access tokens to xApps 
*
* The version of the OpenAPI document: 1
* Contact: tolgaoa@vt.edu
*
* NOTE: This class is auto generated by OpenAPI Generator (https://openapi-generator.tech).
* https://openapi-generator.tech
* Do not edit the class manually.
*/

#include "AccessTokenRequestApi.h"
#include "Helpers.h"

namespace org::openapitools::server::api
{

using namespace org::openapitools::server::helpers;
using namespace org::openapitools::server::model;

const std::string AccessTokenRequestApi::base = "";

AccessTokenRequestApi::AccessTokenRequestApi(const std::shared_ptr<Pistache::Rest::Router>& rtr)
    : router(rtr)
{
}

void AccessTokenRequestApi::init() {
    setupRoutes();
}

void AccessTokenRequestApi::setupRoutes() {
    using namespace Pistache::Rest;

    Routes::Post(*router, base + "/oauth2/token", Routes::bind(&AccessTokenRequestApi::access_token_request_handler, this));

    // Default handler, called when a route is not found
    router->addCustomHandler(Routes::bind(&AccessTokenRequestApi::access_token_request_api_default_handler, this));
}

std::pair<Pistache::Http::Code, std::string> AccessTokenRequestApi::handleParsingException(const std::exception& ex) const noexcept
{
    try {
        throw;
    } catch (nlohmann::detail::exception &e) {
        return std::make_pair(Pistache::Http::Code::Bad_Request, e.what());
    } catch (org::openapitools::server::helpers::ValidationException &e) {
        return std::make_pair(Pistache::Http::Code::Bad_Request, e.what());
    } catch (std::exception &e) {
        return std::make_pair(Pistache::Http::Code::Internal_Server_Error, e.what());
    }
}

std::pair<Pistache::Http::Code, std::string> AccessTokenRequestApi::handleOperationException(const std::exception& ex) const noexcept
{
    return std::make_pair(Pistache::Http::Code::Internal_Server_Error, ex.what());
}

void AccessTokenRequestApi::access_token_request_handler(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter response) {
    try {

    try {
      this->access_token_request(request, response);
    } catch (Pistache::Http::HttpError &e) {
        response.send(static_cast<Pistache::Http::Code>(e.code()), e.what());
        return;
    } catch (std::exception &e) {
        const std::pair<Pistache::Http::Code, std::string> errorInfo = this->handleOperationException(e);
        response.send(errorInfo.first, errorInfo.second);
        return;
    }

    } catch (std::exception &e) {
        response.send(Pistache::Http::Code::Internal_Server_Error, e.what());
    }

}

void AccessTokenRequestApi::access_token_request_api_default_handler(const Pistache::Rest::Request &, Pistache::Http::ResponseWriter response) {
    response.send(Pistache::Http::Code::Not_Found, "The requested method does not exist");
}

} // namespace org::openapitools::server::api

