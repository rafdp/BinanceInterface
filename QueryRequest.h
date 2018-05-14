#include "includes.h"

class QueryRequest
{
    std::string currentUrl;
    CURL* curl;
    int httpCode; 
    std::string httpData;
    int error; 
public:
    QueryRequest ();
    ~QueryRequest ();

    void SetUrl (std::string);
    int Query (bool tolerate = false);
    std::string GetStr ();
    int GetError ();
};


