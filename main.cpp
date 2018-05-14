#include "Builder.h"

int main (int argc, char** argv)
{
    if (argc != 4)
    {
        printf ("usage: symbol limit timeframe\n");
	return 0;
    }
    BinanceInterfacer bint;
    bint.ping ();
    std::string symbol (argv[1]);
    if (!bint.CheckSymbolValidity (symbol)) return 1; 
    const int size = atoi (argv[2]);
    double* data = new double[size];
    memset (data, 0, sizeof (double)*size);
    int got = bint.QueryData (symbol, data, size, argv[3]);
    if (!got) return 1;
    FILE* f = fopen ("data.txt", "w");
    for (int i = 0; i < got; i++)
    {
        fprintf (f, "%d %g\n", i, data[i]);
    }
    fclose (f);
    
    /*if (!httpData.empty ())
    {
        printf ("\nGot successful response from %s\n", url.c_str());
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
    }*/
    
    return 0;
}
