/*
 * xApp authorization framework to be integrated into the reference RAN Intelligent Controller (RIC) of the 
 * Linux Foundation (LF) for distributing access tokens to xApps from an OAUTH 2.0 server using JSON web tokens
 * as the execution method of the tokens
 *
 * XRF client for sending out CURL commands
 *
 * ! file xrf_client.hpp
 *  \brief
 * \author: Tolga Omer Atalay
 * \Affiliation: VirginiaTech
 * \date: 2022
 * \email: tolgaoa@vt.edu
*/


#ifndef FILE_XRF_CLIENT_HPP_SEEN
#define FILE_XRF_CLIENT_HPP_SEEN

#include <thread>
#include <curl/curl.h>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <map>
#include <memory>
#include <nlohmann/json.hpp>
#include <shared_mutex>
#include <utility>
#include <vector>

#include <unistd.h>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/date_time/posix_time/posix_time_types.hpp>
#include <boost/date_time/posix_time/time_formatters.hpp>
#include <boost/uuid/random_generator.hpp>
#include <boost/uuid/uuid_io.hpp>


#include "spdlog/spdlog.h"
#include <string>
#include <iostream>

#include <nlohmann/json.hpp>

namespace xrf {
namespace app {

class xrf_client {
	private:
		CURL *curl;
		CURLcode res;
		std::string datasend;
		//std::string readBuffer;
		nlohmann::json json_send;
		std::string content_type;	
		struct curl_slist *headers;

	public: 
		xrf_client();
		virtual ~xrf_client() = default;

		xrf_client(xrf_client const&) = delete;
		void operator=(xrf_client const &) = delete;
		
		void curl_create_handle(const std::string& uri, const std::string& data,
                         std::string& response_data, uint8_t http_version);
		/*
		 * @param[uri] : target address/port/path
		 * @param[data] : data to send
		 * @param[response_data] : response from target
		 * @param[http_versoin] : http version
		 * @return CURL
		 */

		void curl_create_handle(const std::string& uri, const nlohmann::json& data,
                         std::string& response_data, uint8_t http_version);
                /*
                 * @param[uri] : target address/port/path
                 * @param[data] : data to send
                 * @param[response_data] : response from target
                 * @param[http_versoin] : http version
                 * @return CURL
                 */

		void to_json(nlohmann::json& j, const std::string& kv1, const std::string& kv2);
		/*
		 * @param[j] : empty json object to load
		 * @param[kv1] : keyvalue pair value1
		 * @param[kv2] : keyvalue pair value2
		 * return void
		 */

		void send_curl_easy(const std::string& uri, const std::string& data, 
				     std::string& response_data, uint8_t http_version);
		/*
		 * @param[uri] : URI
		 * @param[data] : data to send
		 * @param[response_data] : response to the data
		 * return void
		 */

		void perform_curl_multi();
		/*
		 * Carry out the curl multi to process the data
		 * return void
		 */

		void wait_curl_end();
		/*
		 * Finish the curl transfers
		 * @param void
		 * @return void
		 */

		void curl_release_handles();
		/*
		 * Release curl handles
		 * @param void
		 * @return void
		 */
	
};


} // namespace app
} // namespace xrf



#endif 
