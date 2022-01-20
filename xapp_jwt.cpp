/*
 * xApp authorization framework to be integrated into the reference RAN Intelligent Controller (RIC) of the 
 * Linux Foundation (LF) for distributing access tokens to xApps from an OAUTH 2.0 server using JSON web tokens
 * as the execution method of the tokens
 *
 *
 * ! file xapp_jwt.cpp
 *  \brief
 * \author: Tolga Omer Atalay
 * \Affiliation: VirginiaTech
 * \date: 2022
 * \email: tolgaoa@vt.edu
*/


#include "xrf_jwt.hpp"
#include "iostream"
#include "jwt/jwt.hpp"

using namespace xrf::app;

bool xrf_jwt::generate_signature(const std::string& xapp_consumer_id, const std::string& scope,
				 const std::string& target_xapp_id,
				 const std::string& xrf_id, std::string& signature) const {

	std::string key;
	get_secret_key(scope, target_xapp_id, key);

	jwt::jwt_object obj{jwt::params::algorithm("HS256"),
                        jwt::params::payload({{"iss", xrf_instance_id},
                                            {"sub", xapp_consumer_id},
                                            {"aud", target_xapp_instance_Id},
                                            {"scope", scope},
                                            {"exp", "1000"}}),  // seconds
                        jwt::params::secret(key)};

	signature = obj.signature();
	return true;

}


bool xrf_jwt::get_secret_key(const std::string& scope, const std::string& target_xapp_id,
			     const std::string& key) const {

	key = "secret";
	return true;

}

void xrf_jwt::test_jwt() {

	using namespace jwt::params;

	auto key = "secret";  // Secret to use for the algorithm
	// Create JWT object
	jwt::jwt_object obj{algorithm("HS256"), payload({{"some", "payload"}}),
		      secret(key)};

	// Get the encoded string/assertion
	auto enc_str = obj.signature();
	std::cout << enc_str << std::endl;

	// Decode
	auto dec_obj = jwt::decode(enc_str, algorithms({"HS256"}), secret(key));
	std::cout << dec_obj.header() << std::endl;
	std::cout << dec_obj.payload() << std::endl;
}
