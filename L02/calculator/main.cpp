#include <iostream>
#include <cmath>

using namespace std;

int get_number_of_operands(char operation)
{
    switch (operation)
    {
        // Binary operators
        case '+':
        case '-':
        case '*':
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
        // Exit (no operands are required)
        case 'x':
            return 0;
            break;
        // Wrong operator
        default:
            return -1;
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
        case '*':
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
        // Exit (no operands are required)
        case 'x':
            return 0;
            break;
    }
    return 0;
}

int main()
{
    double op1, op2;
    char operation;

    cout << "Supercalc greets you!" << endl;

    while (true)
    {
        cout << "Enter operand" << endl;
        cin >> op1;
        cin.clear();
        cout << "Operand = " << op1 << endl;

        int number_of_operands = -1;

        bool first_iteration = true;

        while (number_of_operands < 0)
        {

            if (first_iteration)
            {
                first_iteration = false;
                cout << "Enter operation. Can be one of the following:" << endl;
            }
            else
            {
                cout << "Wrong operation. Can be one of the following:" << endl;
            }

            cout << "  +  : Sum" << endl;
            cout << "  -  : Difference" << endl;
            cout << "  *  : Multiplication" << endl;
            cout << "  /  : Division" << endl;
            cout << "  ^  : Power" << endl;
            cout << "  r  : Square root" << endl;
            cout << "  s  : Sinus" << endl;
            cout << "  c  : Cosinus" << endl;
            cout << "  t  : Tangens" << endl;
            cout << "============================================" << endl;
            cout << "  x  : Exit" << endl;
            cin >> operation;
            cin.clear();

            cout << "Operation \"" << operation << "\" was selected" << endl;
            number_of_operands = get_number_of_operands(operation);
        }

        switch(number_of_operands)
        {
            case 0:
                return 0;
            case 1:
                cout << operation << " " << op1 << " = "
                     << calculate(op1, op2, operation) << endl;
                break;
            case 2:
                cout << "Enter second operand" << endl;
                cin >> op2;
                cin.clear();
                cout << "Second operand = " << op1 << endl;
                cout << op1 << " " << operation << " " << op2 << " = "
                     << calculate(op1, op2, operation) << endl;
                break;
        }
    }

    return 0;
}

