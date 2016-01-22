#include "str_utils.h"

int str_utils_get_len(const char * line)
{
    const char * start = line;

    // Loop until the first null
    while (*(line++) != '\0');

    // Return pointer difference;
    return line - start - 1;
}
