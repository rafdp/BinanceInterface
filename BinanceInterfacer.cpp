#include "BinanceInterfacer.h"

const char* API_ENDPOINT = "https://api.binance.com/api";
BinanceInterfacer::BinanceInterfacer () : 
    querier  (),
    error    (SUCCESS)
{}

void BinanceInterfacer::ping ()
{
    //std::string request = "https://api.binance.com/api/v1/klines?symbol=LTCBTC&interval=5m&limit=1";
    
    IF_LAST_ERROR return;
	
    std::string request = API_ENDPOINT;
    request += "/v1/ping";
    querier.SetUrl (request);
    querier.Query ();
    if (querier.GetError() != SUCCESS) 
        PRINT_ERROR (PING_FAILED)
}

bool BinanceInterfacer::CheckSymbolValidity (std::string symbol)
{
    IF_LAST_ERROR return false;
    std::string request = API_ENDPOINT;
    request += "/v3/ticker/price?symbol=";
    request += symbol;
    printf ("Request url: |%s|\n", request.c_str ());
    querier.SetUrl (request);
    int code = querier.Query (true);
    if (querier.GetError () != SUCCESS)
        PRINT_ERROR (CHECK_SYMBOL_VALIDITY_FAILED);
    if (code != HTTP_OK_CODE) return false;
    Document received;
    ParseResult ok = received.Parse (querier.GetStr ().c_str ());
    if (!ok)
    {
	PRINT_ERROR (JSON_PARSING_FAILED);
	return false;
    }
    SOFT_ASSERT (received.IsObject (), return false)
    auto iterSymbol = received.FindMember ("symbol");
    auto iterPrice  = received.FindMember ("price");

    if (iterSymbol != received.MemberEnd () &&
        iterSymbol->value.IsString () &&
	iterPrice != received.MemberEnd () &&
	iterPrice->value.IsString ())
	return true;
    SOFT_ASSERT (false, return false)
    return false;
}

size_t BinanceInterfacer::QueryData (std::string symbol,
 		                     double* data,
		                     int limit, 
				     const char* timeframe)
{
    IF_LAST_ERROR return 0;
    if (limit > 500 || limit < 1)
    {
        PRINT_ERROR (BAD_LIMIT);
	return 0;
    }
    //check timeframe
    
    //std::string request = "https://api.binance.com/api/v1/klines?symbol=LTCBTC&interval=5m&limit=1";
    std::string request = API_ENDPOINT; 
    request += "/v1/klines?symbol=";
    request += symbol;
    request += "&interval=";
    request += timeframe;
    request += "&limit=";
    request += std::to_string (limit);

    querier.SetUrl (request);
    querier.Query ();
    if (querier.GetError ())
    {
        PRINT_ERROR (QUERY_DATA_FAILED)
	return 0;
    }

    Document received;
    received.Parse (querier.GetStr().c_str());

    SOFT_ASSERT (received.IsArray(), return 0)
    size_t i = 0;
    size_t loaded = received.Size ();
    while (i < loaded)
    {
	SOFT_ASSERT (received[i][1u].IsString (), return 0)
        data[i] = atof (received[i][1u].GetString());
	i++;
    }
    return loaded;
}
