
enum ERRORS
{
    SUCCESS = 0,
    ERROR_REQUEST_FAILED = 5

};

#define PRINT_ERROR(code) \
	printf ("\033[1;31mError \"%s\" = %d occurred\033[0m\n", #code, ERROR_##code); \
        error = ERROR_##code;
