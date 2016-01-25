#include <iostream>
#include <iomanip>
#include <stdarg.h>

using namespace std;

void print_em_all(const char * fmt, ... ) {
    enum {
        MD_PRINT,
        MD_SPECIFIER,
    } mode = MD_PRINT;

    va_list args;
    va_start( args, fmt );

    while (*fmt != '\0')
    {
        unsigned int arg_width = 0;
        switch(mode)
        {
            case MD_PRINT:
                if (*fmt == '%')
                    mode = MD_SPECIFIER;
                else
                    cout << *fmt;
                fmt++;
                break;
            case MD_SPECIFIER:
                // Check if there is a width
                arg_width = 0;
                while (isdigit(*fmt)){
                    arg_width *= 10;
                    arg_width += *fmt - '0';
                    fmt++;
                }
                switch (*fmt)
                {
                    case 'i':
                        cout << setw(arg_width) << va_arg(args, int);
                        fmt++;
                        break;
                    case 'g':
                        cout << setw(arg_width) << va_arg(args, double);
                        fmt++;
                        break;
                    case 's':
                        cout << setw(arg_width) << va_arg(args, char *);
                        fmt++;
                        break;
                    case 'c':
                        {
                            char ch = (char)va_arg(args, int);
                            for (unsigned int i = 0; i < arg_width; ++i)
                                cout << ch;
                        }
                        fmt++;
                        break;
                    case '%':
                        cout << "%%";
                        fmt++;
                }
                mode = MD_PRINT;
                break;

        }
    }
    va_end( args );
}

int main()
{
    cout << "Custom printf :)" << endl;
    print_em_all("integer = %7i,\n"
                 "double = %8g\n"
                 "string = %8s\n"
                 "%%\n%17c", 12, 0.3, "test", '=');
    return 0;
}
