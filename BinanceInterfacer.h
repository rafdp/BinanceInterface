
#include "includes.h"
#include "QueryRequest.h"
class BinanceInterfacer
{
    QueryRequest querier;
    int error;
public:
    BinanceInterfacer ();

    void ping ();
    bool CheckSymbolValidity (std::string symbol);
    size_t QueryData (std::string symbol, 
		      double * data,
		      int limit = 500, 
		      const char* timeframe = "5m");
};

