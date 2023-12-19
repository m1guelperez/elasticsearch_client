//
// Created by miguel on 6/6/22.
//
export module client;

#include <curl/curl.h>
#include <string>
#include <cstring>

import queries;
import local_logger;

class Client {

    std::string HOST;
    int PORT;
    std::string baseUrl;
    std::string executionUrl;
    CURL *curl{};
    struct curl_slist *header{};
    std::string readBuffer;

    void setCurlParams(const std::string &requestMode, const std::string &query) const;

    void setCurlParamsWithoutPostBody(const std::string &requestMode) const;

    //Function overloading for different executions via cURL
    CURLcode executeQuery(const std::string &requestMode, const std::string &query);

    CURLcode executeQuery(const std::string &requestMode);

    CURLcode executeQuery(const std::string &index, QueryBuilder query, const std::string &requestMode);

    void initCurlDefaults();

    void resetReadBuffer();

public:
    Logger log{};

    explicit Client(const std::string &hostParam, int portParam);

    ~Client();

    std::string getReadBuffer() const;

    std::string getHost() const;

    int getPort() const;

    void setHost(const std::string &hostParam);

    // Several queries

    CURLcode elasticUnderscoreApi(const std::string &index, const std::string &api, const std::string &query,
                                  const std::string &requestMode);

    CURLcode elasticUnderscoreApi(const std::string &index, const std::string &api);

    CURLcode elasticUnderscoreApi(const std::string &index, const std::string &api, const std::string &query,
                                  const std::string &documentID,
                                  const std::string &requestMode);

    CURLcode elasticSingleRequest(const std::string &index, const std::string &query, const std::string &requestMode);

    CURLcode elasticSingleRequest(const std::string &index, const std::string &requestMode);

    CURLcode search(const std::string &index, const std::string &query);

    CURLcode search(const std::string &index);

    CURLcode count(const std::string &index);

    CURLcode count(const std::string &index, const std::string &query);

    CURLcode refresh(const std::string &index);

    CURLcode bulk(const std::string);

    CURLcode remove(const std::string &index);

    CURLcode index(const std::string &indexName, const std::string &query);

    CURLcode index(const std::string &indexName);

    CURLcode update(const std::string &index, const std::string &query, const std::string &id);

    //TODO: Eventually put it into the index function
    CURLcode insertDocument(const std::string &index, const std::string &query, const std::string &id);

    CURLcode insertDocument(const std::string &index, const std::string &query);

    CURLcode stringQuery(const std::string &requestMode, const std::string &index, const std::string &query);

    //1L will activate verbose output and 0L will deactivate it.
    void verboseLogging(long param) const;

    void setHeader(const std::string &headerOptions);

    void resetHeader();

    void cleanUp();
};

static size_t WriteCallback(void *receivedContents, const size_t size, const size_t nmemb, void *buffer) {
    std::string* realBuffer = static_cast<std::string*>(buffer);
    char* chars = static_cast<char*>(receivedContents);

    realBuffer->append(chars, size * nmemb);
    return size * nmemb;
}


Client::Client(const std::string &hostParam, int portParam) {
    this->HOST = hostParam;
    this->PORT = portParam;
    this->baseUrl = (HOST + ":" + std::to_string(PORT) + "/");
    this->executionUrl = baseUrl;
    initCurlDefaults();
    log.setLogLevel(log.INFO);
}

Client::~Client() {
    this->cleanUp();
}

//TODO: Reset set variables (POSTFIELDS etc.)
void Client::initCurlDefaults() {
    this->curl = curl_easy_init();
    this->header = nullptr;
    this->header = curl_slist_append(this->header, "Content-Type: application/json");
    curl_easy_setopt(this->curl, CURLOPT_BUFFERSIZE, 102400L);
    curl_easy_setopt(this->curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(this->curl, CURLOPT_WRITEDATA, &this->readBuffer);
    curl_easy_setopt(this->curl, CURLOPT_HTTPHEADER, this->header);
    curl_easy_setopt(this->curl, CURLOPT_VERBOSE, 0L);
}

CURLcode Client::elasticUnderscoreApi(const std::string &index, const std::string &api, const std::string &query,
                                      const std::string &requestMode) {
    this->executionUrl.append(index + "/" + api);
    return executeQuery(requestMode, query);
}

CURLcode Client::elasticUnderscoreApi(const std::string &index, const std::string &api, const std::string &query,
                                      const std::string &id,
                                      const std::string &requestMode) {
    this->executionUrl.append(index + "/" + api + "/" + id);
    return executeQuery(requestMode, query);
}

CURLcode Client::elasticUnderscoreApi(const std::string &index, const std::string &api) {
    this->executionUrl.append(index + "/" + api);
    return executeQuery("GET");
}

CURLcode Client::elasticSingleRequest(const std::string &index, const std::string &requestMode) {
    this->executionUrl.append(index);
    return executeQuery(requestMode);
}

CURLcode
Client::elasticSingleRequest(const std::string &index, const std::string &query, const std::string &requestMode) {
    this->executionUrl.append(index);
    return executeQuery(requestMode, query);
}

CURLcode Client::search(const std::string &index, const std::string &query) {
    return this->elasticUnderscoreApi(index, "_search", query, "GET");
}

CURLcode Client::search(const std::string &index) {
    return this->elasticUnderscoreApi(index, "_search");
}

CURLcode Client::count(const std::string &index) {
    return this->elasticUnderscoreApi(index, "_count");
}

CURLcode Client::count(const std::string &index, const std::string &query) {
    return this->elasticUnderscoreApi(index, "_search", query, "POST");
}

CURLcode Client::refresh(const std::string &index) {
    return this->elasticUnderscoreApi(index, "_refresh");
}

CURLcode Client::remove(const std::string &index) {
    return this->elasticSingleRequest(index, "DELETE");
}

CURLcode Client::update(const std::string &index, const std::string &query, const std::string &id) {
    return this->elasticUnderscoreApi(index, "_update", query, id, "POST");
}

CURLcode Client::index(const std::string &indexName) {
    return elasticSingleRequest(indexName, "PUT");
}

CURLcode Client::index(const std::string &indexName, const std::string &query) {
    return this->elasticSingleRequest(indexName, query, "PUT");
}

CURLcode Client::insertDocument(const std::string &index, const std::string &query) {
    return this->elasticUnderscoreApi(index, "_doc", query, "POST");
}

CURLcode Client::insertDocument(const std::string &index, const std::string &query, const std::string &id) {
    return this->elasticUnderscoreApi(index, "_doc", query, id, "POST");
}
//TODO: Implement
CURLcode bulk(const std::string) {}

CURLcode Client::executeQuery(const std::string &requestMode, const std::string &query) {
    resetReadBuffer();
    setCurlParams(requestMode, query);
    const CURLcode code = curl_easy_perform(this->curl);
    this->executionUrl = this->baseUrl;
    return code;
}

CURLcode Client::stringQuery(const std::string &requestMode, const std::string &index, const std::string &query) {
    resetReadBuffer();
    setCurlParams(requestMode, query);
    const CURLcode code = curl_easy_perform(this->curl);
    this->executionUrl = this->baseUrl;
    return code;
}

CURLcode Client::executeQuery(const std::string &requestMode) {
    resetReadBuffer();
    std::string requestUrl = this->executionUrl;
    setCurlParamsWithoutPostBody(requestMode);
    const CURLcode code = curl_easy_perform(this->curl);
    this->executionUrl = this->baseUrl;
    return code;
}

// Will be used for when the QueryBuilder is ready
CURLcode Client::executeQuery(const std::string &index, QueryBuilder query, const std::string &requestMode) {
    resetReadBuffer();
    const std::string temp = query.getQuery();
    std::string requestUrl = this->executionUrl + index;
    curl_easy_setopt(this->curl, CURLOPT_URL, this->executionUrl.c_str());
    curl_easy_setopt(this->curl, CURLOPT_POSTFIELDS, temp.c_str());
    curl_easy_setopt(this->curl, CURLOPT_POSTFIELDSIZE_LARGE, strlen(temp.c_str()));
    curl_easy_setopt(this->curl, CURLOPT_CUSTOMREQUEST, requestMode.c_str());
    const CURLcode code = curl_easy_perform(this->curl);
    this->executionUrl = this->baseUrl;
    return code;
}

void Client::cleanUp() {
    curl_easy_cleanup(this->curl);
    if (this->header != nullptr) {
        curl_slist_free_all(this->header);
    }
}

std::string Client::getHost() const {
    return this->HOST;
}

int Client::getPort() const {
    return this->PORT;
}

void Client::setHeader(const std::string &headerOptions) {
    this->header = nullptr;
    this->header = curl_slist_append(this->header, headerOptions.c_str());
}

void Client::setHost(const std::string &hostParam) {
    this->HOST = hostParam;
}

void Client::verboseLogging(const long param) const {
    curl_easy_setopt(this->curl, CURLOPT_VERBOSE, param);
}

//TODO: Maybe make all getter functions const?
std::string Client::getReadBuffer() const {
    return this->readBuffer;
}

void Client::resetHeader() {
    curl_slist_free_all(this->header);
    this->header = nullptr;
}

void Client::resetReadBuffer() {
    this->readBuffer = "";
}

//Used for every request which uses a body/POSTFIELDS.
void Client::setCurlParams(const std::string &requestMode, const std::string &query) const{
    curl_easy_setopt(this->curl, CURLOPT_URL, this->executionUrl.c_str());
    curl_easy_setopt(this->curl, CURLOPT_POSTFIELDS, query.c_str());
    curl_easy_setopt(this->curl, CURLOPT_POSTFIELDSIZE_LARGE, strlen(query.c_str()));
    curl_easy_setopt(this->curl, CURLOPT_CUSTOMREQUEST, requestMode.c_str());
}

//Only used for requests which do not have a body.
void Client::setCurlParamsWithoutPostBody(const std::string &requestMode) const{
    //Fields like POSTFIELDSIZE etc., have to be unset when sending a GET, which does not have any POSTFIELDS otherwise this will be reused.
    curl_easy_setopt(this->curl, CURLOPT_HTTPGET, true);
    curl_easy_setopt(this->curl, CURLOPT_URL, this->executionUrl.c_str());
    curl_easy_setopt(this->curl, CURLOPT_CUSTOMREQUEST, requestMode.c_str());
}