#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;

int get_number_of_operands(char operation)
{
    switch (operation)
    {
        // Binary operators
        case '+':
        case '-':
        case 'x':
        case '/':
        case '^':
            return 2;
            break;
        // Unary operators
        case 'r':
        case 's':
        case 'c':
        case 't':
            return 1;
            break;
        // Wrong operator
        default:
            return 0;
    }
}

double calculate (double op1, double op2, char operation)
{
    switch(operation)
    {
        // Binary operators
        case '+':
            return op1 + op2;
        case '-':
            return op1 - op2;
        case 'x':
            return op1 * op2;
        case '/':
            return op1 / op2;
        case '^':
            return pow(op1,op2);
            break;
        // Unary operators
        case 'r':
            return sqrt(op1);
            break;
        case 's':
            return sin(op1);
            break;
        case 'c':
            return cos(op1);
            break;
        case 't':
            return tan(op1);
            break;
    }
    return 0;
}

void usage(void)
{
    cout << "This is a simple console calc." << endl;
    cout << "Use it in the following way:" << endl;
    cout << "    cmd_line_calc a <operation> [b]" << endl;
    cout << "Argument [b] is optional and depends on a operation" << endl;
    cout << "Following operations can be used:" << endl;
    cout << "    a + b : Sum" << endl;
    cout << "    a - b : Difference" << endl;
    cout << "    a x b : Multiplication" << endl;
    cout << "    a / b : Division" << endl;
    cout << "    a ^ b : Power" << endl;
    cout << "    a r  : Square root" << endl;
    cout << "    a s  : Sinus" << endl;
    cout << "    a c  : Cosinus" << endl;
    cout << "    a t  : Tangens" << endl;
}

int main(int argc, char **argv)
{
    double op1, op2;

    if ((argc < 3) || (argc > 4))
    {
        cout << "Wrong number of arguments" << endl;
        usage();
        return 0;
    }

    // Get required number of operands (0,1,2)
    char operation = *argv[2];
    int op_req = get_number_of_operands(operation);

    // Check number of operands
    if (op_req == 0)
    {
        cout << "Unknown operation \"" << operation << "\"" << endl;
        usage();
        return 0;
    }
    else if (op_req != (argc - 2))
    {
        cout << "Wrong number of operands for operation \"" << operation << "\"" << endl;
        usage();
        return 0;
    }

    op1 = atof(argv[1]);
    if (op_req == 2)
    {
        op2 = atof(argv[3]);
    }

    switch(op_req)
    {
        case 1:
            cout << op1 << " " << operation << " = "
                 << calculate(op1, op2, operation) << endl;
            break;
        case 2:
            cout << op1 << " " << operation << " " << op2 << " = "
                 << calculate(op1, op2, operation) << endl;
            break;
    }

    return 0;
}

