
enum ERRORS
{
    SUCCESS = 0,
    HTTP_OK_CODE = 200,
    ERROR_REQUEST_FAILED = 5,
    ERROR_PING_FAILED    = 6,
    ERROR_CHECK_SYMBOL_VALIDITY_FAILED = 7,
    ERROR_JSON_PARSING_FAILED = 8,
    ERROR_BAD_LIMIT = 9,
    ERROR_QUERY_DATA_FAILED = 10,
    ERROR_WTF = 100500
};

#define PRINT_ERROR(code) {\
printf ("\033[1;33m%s (%d): \033[1;31mError \"%s\" = %d occurred\033[0m\n", __PRETTY_FUNCTION__, __LINE__, #code, ERROR_##code); \
error = ERROR_##code; }

#define IF_LAST_ERROR \
if (error != SUCCESS) \
printf ("\033[1;35m%s: Cannot run, error %d encountered\033[0m\n", __PRETTY_FUNCTION__, error);\
if (error != SUCCESS) 

#define SOFT_ASSERT(what, ret) \
if (!what) {PRINT_ERROR (WTF); ;} 
