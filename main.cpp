#include "Builder.h"

int main()
{
    const std::string url("http://date.jsontest.com/");
    QueryRequest qr;
    qr.SetUrl (url);
    qr.Query ();
    std::string httpData = qr.GetStr ();
    
    if (!httpData.empty ())
    {
        printf ("\nGot successful response from %s\n", url.c_str());
        
        // Response looks good - done using Curl now.  Try to parse the results
        // and print them out.
        //Json::Value jsonData;
        //Json::Reader jsonReader;
	Document d;
        ParseResult ok = d.Parse(httpData.c_str());
        if (ok)
        {
            StringBuffer buffer;
            Writer<StringBuffer> writer(buffer);
            d.Accept(writer);
            printf ("%s\n", buffer.GetString());
        }
        else
        {
            printf ("Could not parse HTTP data as JSON\n");
            return 1;
        }
    }
    else
    {
        return 1;
    }
    
    return 0;
}
