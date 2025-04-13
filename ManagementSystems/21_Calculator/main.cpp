#include <iostream>
#include <cmath>
using namespace std;

class operation
{
public:
    static float add(float a, float b)
    {
        return a + b;
    }

    static float subtract(float a, float b)
    {
        return a - b;
    }

    static float multiply(float a, float b)
    {
        return a * b;
    }

    static float divide(float a, float b)
    {
        if (b != 0)
        {
            return a / b;
        }
        else
        {
            cout << "\n\t\t\tError: Division by zero!" << endl;
            return 0;
        }
    }

    static float sine(float angle)
    {
        return sin(angle * (3.14159 / 180)); // Convert to radians
    }

    static float cosine(float angle)
    {
        return cos(angle * (3.14159 / 180)); // Convert to radians
    }

    static float tangent(float angle)
    {
        return tan(angle * (3.14159 / 180)); // Convert to radians
    }

    static float secant(float angle)
    {
        float cosValue = cosine(angle);
        if (cosValue != 0)
        {
            return 1 / cosValue;
        }
        else
        {
            cout << "\n\t\t\tError: Division by zero in secant calculation!" << endl;
            return 0;
        }
    }

    static float cotangent(float angle)
    {
        float tanValue = tangent(angle);
        if (tanValue != 0)
        {
            return 1 / tanValue;
        }
        else
        {
            cout << "\n\t\t\tError: Division by zero in cotangent calculation!" << endl;
            return 0;
        }
    }

    static float cosecant(float angle)
    {
        float sinValue = sine(angle);
        if (sinValue != 0)
        {
            return 1 / sinValue;
        }
        else
        {
            cout << "\n\t\t\tError: Division by zero in cosecant calculation!" << endl;
            return 0;
        }
    }

    static float arcsine(float x)
    {
        if (x >= -1 && x <= 1)
        {
            return asin(x) * (180 / 3.14159); // Convert to degrees
        }
        else
        {
            cout << "\n\t\t\tError: Input for arcsin must be between -1 and 1" << endl;
            return 0;
        }
    }

    static float arccosine(float x)
    {
        if (x >= -1 && x <= 1)
        {
            return acos(x) * (180 / 3.14159); // Convert to degrees
        }
        else
        {
            cout << "\n\t\t\tError: Input for arccos must be between -1 and 1" << endl;
            return 0;
        }
    }

    static float arctangent(float x)
    {
        return atan(x) * (180 / 3.14159); // Convert to degrees
    }

    static float square(float x)
    {
        return x * x;
    }

    static float cube(float x)
    {
        return x * x * x;
    }

    static float power(float base, int exponent)
    {
        float result = 1;
        bool isNegative = false;

        if (exponent < 0)
        {
            isNegative = true;
            exponent = -exponent;
        }

        for (int i = 0; i < exponent; i++)
        {
            result *= base;
        }

        if (isNegative)
        {
            return 1 / result;
        }

        return result;
    }

    static float logBaseE(float x)
    {
        return log(x); // Natural logarithm (base e)
    }

    static float antilog(float x)
    {
        return exp(x); // e^x
    }
};

void clearInput()
{
    cin.clear();            // Clear error flags
    cin.ignore(1000, '\n'); // Discard invalid input
}


void calculator(){
    cout << "\n\t\t\t ---------- Calculator ----------" << endl;
    cout << "\n\t\t\tSupports +, -, *, /, trig, inverse trig, square, cube, power, log, and antilog." << endl;

    int choice;
    float a, b;
    int exp;

    cout << "\n\t\t\tMain Menu:" << endl;
    cout << "\n\t\t\t1. Add" << endl;
    cout << "\t\t\t2. Subtract" << endl;
    cout << "\t\t\t3. Multiply" << endl;
    cout << "\t\t\t4. Divide" << endl;
    cout << "\t\t\t5. Sine (sin)" << endl;
    cout << "\t\t\t6. Cosine (cos)" << endl;
    cout << "\t\t\t7. Tangent (tan)" << endl;
    cout << "\t\t\t8. Secant (sec)" << endl;
    cout << "\t\t\t9. Cotangent (cot)" << endl;
    cout << "\t\t\t10. Cosecant (csc)" << endl;
    cout << "\t\t\t11. Inverse Sine (asin)" << endl;
    cout << "\t\t\t12. Inverse Cosine (acos)" << endl;
    cout << "\t\t\t13. Inverse Tangent (atan)" << endl;
    cout << "\t\t\t14. Square" << endl;
    cout << "\t\t\t15. Cube" << endl;
    cout << "\t\t\t16. Power (x^n)" << endl;
    cout << "\t\t\t17. Log (Natural log)" << endl;
    cout << "\t\t\t18. Antilog (e^x)" << endl;
    cout << "\t\t\t19. Exit " << endl;
    cout << "\n\t\t\tEnter your choice (1-19): ";
    
    cin >> choice;

    while (cin.fail() || choice > 19 || choice < 0 )
    {
        clearInput();
        cout << "\n\t\t\tInvalid input. Please enter a Correct Option: " ;
        cin >> choice ;
    }

    if (choice >= 1 && choice <= 4)
    {
        // Get two numbers
        cout << "\n\t\t\tEnter two numbers: ";
        while (true)
        {
            cin >> a >> b;
            if (cin.fail())
            {
                clearInput();
                cout << "\n\t\t\tInvalid input. Please enter numeric values: ";
            }
            else
            {
                break;
            }
        }

        if (choice == 1)
            cout << "\n\t\t\tResult: " << operation::add(a, b) << endl;
        else if (choice == 2)
            cout << "\n\t\t\tResult: " << operation::subtract(a, b) << endl;
        else if (choice == 3)
            cout << "\n\t\t\tResult: " << operation::multiply(a, b) << endl;
        else if (choice == 4)
            cout << "\n\t\t\tResult: " << operation::divide(a, b) << endl;
    }

    else if (choice >= 5 && choice <= 7)
    {
        // Get angle in degrees for sin, cos, and tan
        cout << "\n\t\t\tEnter angle in degrees (e.g., 30 for 30 degrees): ";
        while (true)
        {
            cin >> a;
            if (cin.fail())
            {
                clearInput();
                cout << "\n\t\t\tInvalid input. Please enter a numeric value for the angle in degrees: ";
            }
            else
            {
                break;
            }
        }

        if (choice == 5)
            cout << "\n\t\t\tsin(" << a << " degree) = " << operation::sine(a) << endl;
        else if (choice == 6)
            cout << "\n\t\t\tcos(" << a << " degree) = " << operation::cosine(a) << endl;
        else if (choice == 7)
            cout << "\n\t\t\ttan(" << a << " degree) = " << operation::tangent(a) << endl;
    }

    else if (choice == 8)
    {
        // Get angle for secant
        cout << "\n\t\t\tEnter angle in degrees (e.g., 60 for 60 degrees): ";
        while (true)
        {
            cin >> a;
            if (cin.fail())
            {
                clearInput();
                cout << "\n\t\t\tInvalid input. Please enter a numeric value for the angle in degrees: ";
            }
            else
            {
                break;
            }
        }
        cout << "\n\t\t\tsec(" << a << " degree) = " << operation::secant(a) << endl;
    }

    else if (choice == 9)
    {
        // Get angle for cotangent
        cout << "\n\t\t\tEnter angle in degrees (e.g., 45 for 45 degrees): ";
        while (true)
        {
            cin >> a;
            if (cin.fail())
            {
                clearInput();
                cout << "\n\t\t\tInvalid input. Please enter a numeric value for the angle in degrees: ";
            }
            else
            {
                break;
            }
        }
        cout << "\n\t\t\tcot(" << a << " degree) = " << operation::cotangent(a) << endl;
    }

    else if (choice == 10)
    {
        // Get angle for cosecant
        cout << "\n\t\t\tEnter angle in degrees (e.g., 90 for 90 degrees): ";
        while (true)
        {
            cin >> a;
            if (cin.fail())
            {
                clearInput();
                cout << "\n\t\t\tInvalid input. Please enter a numeric value for the angle in degrees: ";
            }
            else
            {
                break;
            }
        }
        cout << "\n\t\t\tcsc(" << a << " degree) = " << operation::cosecant(a) << endl;
    }

    else if (choice == 11)
    {
        // Get value for arcsine (asin)
        cout << "\n\t\t\tEnter value for arcsine (must be between -1 and 1): ";
        while (true)
        {
            cin >> a;
            if (cin.fail() || a < -1 || a > 1)
            {
                clearInput();
                cout << "\n\t\t\tInvalid input. Please enter a numeric value between -1 and 1 for arcsine: ";
            }
            else
            {
                break;
            }
        }
        cout << "\n\t\t\tasin(" << a << ") = " << operation::arcsine(a) << " degrees" << endl;
    }

    else if (choice == 12)
    {
        // Get value for arccosine (acos)
        cout << "\n\t\t\tEnter value for arccosine (must be between -1 and 1): ";
        while (true)
        {
            cin >> a;
            if (cin.fail() || a < -1 || a > 1)
            {
                clearInput();
                cout << "\n\t\t\tInvalid input. Please enter a numeric value between -1 and 1 for arccosine: ";
            }
            else
            {
                break;
            }
        }
        cout << "\n\t\t\tacos(" << a << ") = " << operation::arccosine(a) << " degrees" << endl;
    }

    else if (choice == 13)
    {
        // Get value for arctangent (atan)
        cout << "\n\t\t\tEnter value for arctangent (can be any real number): ";
        while (true)
        {
            cin >> a;
            if (cin.fail())
            {
                clearInput();
                cout << "\n\t\t\tInvalid input. Please enter a numeric value for arctangent: ";
            }
            else
            {
                break;
            }
        }
        cout << "\n\t\t\tatan(" << a << ") = " << operation::arctangent(a) << " degrees" << endl;
    }

    else if (choice == 14)
    {
        // Get number for square
        cout << "\n\t\t\tEnter number: ";
        while (true)
        {
            cin >> a;
            if (cin.fail())
            {
                clearInput();
                cout << "\n\t\t\tInvalid input. Please enter a numeric value: ";
            }
            else
            {
                break;
            }
        }
        cout << "\n\t\t\tSquare of " << a << " = " << operation::square(a) << endl;
    }

    else if (choice == 15)
    {
        // Get number for cube
        cout << "\n\t\t\tEnter number: ";
        while (true)
        {
            cin >> a;
            if (cin.fail())
            {
                clearInput();
                cout << "\n\t\t\tInvalid input. Please enter a numeric value: ";
            }
            else
            {
                break;
            }
        }
        cout << "\n\t\t\tCube of " << a << " = " << operation::cube(a) << endl;
    }

    else if (choice == 16)
    {
        // Get base and exponent for power
        cout << "\n\t\t\tEnter base: ";
        while (true)
        {
            cin >> a;
            if (cin.fail())
            {
                clearInput();
                cout << "\n\t\t\tInvalid input for base. Please enter a numeric value: ";
            }
            else
            {
                break;
            }
        }

        cout << "\n\t\t\tEnter exponent (integer): ";
        while (true)
        {
            cin >> exp;
            if (cin.fail())
            {
                clearInput();
                cout << "\n\t\t\tInvalid input for exponent. Please enter an integer: ";
            }
            else
            {
                break;
            }
        }

        cout << "\n\t\t\t" << a << "^" << exp << " = " << operation::power(a, exp) << endl;
    }

    else if (choice == 17)
    {
        // Get number for log
        cout << "\n\t\t\tEnter number for log (must be > 0): ";
        while (true)
        {
            cin >> a;
            if (cin.fail() || a <= 0)
            {
                clearInput();
                cout << "\n\t\t\tInvalid input. Please enter a positive numeric value: ";
            }
            else
            {
                break;
            }
        }
        cout << "\n\t\t\tlog(" << a << ") = " << operation::logBaseE(a) << endl;
    }

    else if (choice == 18)
    {
        // Get number for antilog
        cout << "\n\t\t\tEnter number for antilog: ";
        while (true)
        {
            cin >> a;
            if (cin.fail())
            {
                clearInput();
                cout << "\n\t\t\tInvalid input. Please enter a numeric value: ";
            }
            else
            {
                break;
            }
        }
        cout << "\n\t\t\tantilog(" << a << ") = " << operation::antilog(a) << endl;
    }
    else
        exit(EXIT_SUCCESS);
}

int main()
{
    char again;
    do {
        calculator();
        system("PAUSE");
        system("cls");
        cout << "\n\t\t\tDo you want to perform another operation? (Y/N): ";
        cin >> again;
        
        
    } while (again == 'Y'); 
    
    cout << "\n\t\t\t -----THANK YOU! -----" << endl;
    return 0;
}
