
#include "QueryRequest.h"

namespace
{
    std::size_t callback(const char* in,
                         std::size_t size,
                         std::size_t num,
                         std::string* out)
    {
        const std::size_t totalBytes(size * num);
	out->append(in, totalBytes);
        return totalBytes;
    }
}

QueryRequest::QueryRequest () : 
    currentUrl    (),
    curl          (curl_easy_init ()),
    httpCode      (),
    httpData      (),
    error         ()
{}

QueryRequest::~QueryRequest ()
{
    curl_easy_cleanup (curl);
}

void QueryRequest::SetUrl (std::string url)
{
    currentUrl = url;
    httpData.clear ();
    httpCode = 0;
    error = SUCCESS;
}

int QueryRequest::Query (bool tolerate)
{
    curl_easy_setopt(curl, CURLOPT_URL, currentUrl.c_str());
    curl_easy_setopt(curl, CURLOPT_IPRESOLVE, CURL_IPRESOLVE_V4);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &httpData);
    
    curl_easy_perform(curl);
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpCode);
    
    if (httpCode == HTTP_OK_CODE || tolerate)
    {
	error = SUCCESS;
    }
    else if (!tolerate)
    {
	PRINT_ERROR (REQUEST_FAILED);
	printf ("httpCode = %d\n", httpCode);
    } 
    if (tolerate) return httpCode;
    return SUCCESS;
}

std::string QueryRequest::GetStr ()
{
    return httpData;
}

int QueryRequest::GetError ()
{
    return error;
}
