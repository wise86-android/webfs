#include <curl/curl.h>
#include <iostream>

#include "rapidjson/document.h"
#include "node.h"
#include "gists/gistsRequest.h"

using namespace webfs;
#define TOCKEN ""

static size_t writefunc(void *ptr, size_t size, size_t nmemb, std::string *s){
  s->append((const char*)ptr,size*nmemb);
  return size * nmemb;
}

bool gists::create(Node *node){

	CURL *curl = curl_easy_init();
	curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");
	curl_easy_setopt(curl, CURLOPT_URL, "https://api.github.com/gists");

	struct curl_slist *headers = NULL;
	headers = curl_slist_append(headers, "cache-control: no-cache");
	headers = curl_slist_append(headers, "User-Agent: webFS");
	headers = curl_slist_append(headers, "Authorization: token "TOCKEN);
	curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
	std::string message("{\"description\": \"\", \"public\": true,"
			" \"files\": { \""+node->getName()+"\": { \"content\": \"Empty\"}}}");

	curl_easy_setopt(curl, CURLOPT_POSTFIELDS, message.c_str());

	std::string rensponseData;

	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunc);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &rensponseData);

	CURLcode ret = curl_easy_perform(curl);
	curl_easy_cleanup(curl);

	std::cout<<rensponseData<<std::endl;
	rapidjson::Document resp;
	rensponseData+='\0';
	resp.Parse(rensponseData.c_str());
	if(resp.HasMember("id")){
		node->setRemoteId(resp["id"].GetString());
		return true;
	}

	return false;
}

bool gists::download(Node *node){
	CURL *curl = curl_easy_init();
	curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "GET");
	std::string getUrl("https://api.github.com/gists/");
	getUrl.append(node->getRemoteId());
	curl_easy_setopt(curl, CURLOPT_URL, getUrl.c_str());

	struct curl_slist *headers = NULL;
	headers = curl_slist_append(headers, "cache-control: no-cache");
	headers = curl_slist_append(headers, "User-Agent: webFS");
	headers = curl_slist_append(headers, "Authorization: token "TOCKEN);
	curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

	std::string rensponseData;

	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunc);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &rensponseData);

	CURLcode ret = curl_easy_perform(curl);
	curl_easy_cleanup(curl);

	std::cout<<rensponseData<<std::endl;
	rapidjson::Document resp;
	resp.Parse(rensponseData.c_str());
	if(resp.HasMember("files")){
		std::cout<<resp["files"][node->getName()]["content"].GetString()<<std::endl;
		//node->setRemoteId(resp["id"].GetString());
		return true;
	}
	return false;
}

bool gists::remove(Node *node){
	CURL *curl = curl_easy_init();

	std::string getUrl("https://api.github.com/gists/");
	getUrl.append(node->getRemoteId());
	curl_easy_setopt(curl, CURLOPT_URL, getUrl.c_str());
	curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "DELETE");

	struct curl_slist *headers = NULL;
	headers = curl_slist_append(headers, "cache-control: no-cache");
	headers = curl_slist_append(headers, "User-Agent: webFS");
	headers = curl_slist_append(headers, "Authorization: token "TOCKEN);
	curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);


	CURLcode ret = curl_easy_perform(curl);
	uint32_t httpCode;
	curl_easy_getinfo (curl, CURLINFO_RESPONSE_CODE, &httpCode);
	curl_easy_cleanup(curl);
	std::cout<<httpCode<<std::endl;
	return httpCode==204;
}

bool gists::update(Node *node){

	CURL *curl = curl_easy_init();
	curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PATCH");
	std::string getUrl("https://api.github.com/gists/");
	getUrl.append(node->getRemoteId());
	curl_easy_setopt(curl, CURLOPT_URL, getUrl.c_str());

	struct curl_slist *headers = NULL;
	headers = curl_slist_append(headers, "cache-control: no-cache");
	headers = curl_slist_append(headers, "User-Agent: webFS");
	headers = curl_slist_append(headers, "Authorization: token "TOCKEN);
	curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
	std::string message("{\"description\": \"edit\", \"public\": true,"
			" \"files\": { \""+node->getName()+"\": { \"content\": \"Empty2\"}}}");

	curl_easy_setopt(curl, CURLOPT_POSTFIELDS, message.c_str());

	std::string rensponseData;

	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunc);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &rensponseData);

	CURLcode ret = curl_easy_perform(curl);
	curl_easy_cleanup(curl);

	std::cout<<rensponseData<<std::endl;
	rapidjson::Document resp;
	rensponseData+='\0';
	resp.Parse(rensponseData.c_str());
	if(resp.HasMember("id")){
		node->setRemoteId(resp["id"].GetString());
		return true;
	}

	return false;
}
