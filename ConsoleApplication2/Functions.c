#define _CRT_SECURE_NO_WARNINGS
#include "calculator.h"

// Helper constant for degree to radian conversion
#define PI 3.14159265358979323846
#define DEG_TO_RAD (PI / 180.0)

// Helper Function: Reads the first token from a line safely using fgets
static char* get_string_token(const char* prompt, char* buffer, size_t size) {
    char temp_line[MAX_INPUT_LENGTH];
    printf("%s", prompt);

    if (fgets(temp_line, MAX_INPUT_LENGTH, stdin) == NULL) {
        return NULL; // EOF or error
    }

    // Use sscanf to extract the first token (word) from the line read by fgets
    // This safely puts the first token into 'buffer' and null-terminates it.
    if (sscanf(temp_line, "%s", buffer) != 1) {
        return NULL; // No token found
    }
    return buffer;
}

// Helper Function: Reads the first token, converts it to lowercase. Used for Math/Trig/Main menus.
static char* read_and_standardize_token(char* buffer, size_t size) {
    char temp_line[MAX_INPUT_LENGTH];

    if (fgets(temp_line, (int)size, stdin) == NULL) {
        return NULL; // EOF or error
    }

    // Extract the first token (word) from the line
    if (sscanf(temp_line, "%s", buffer) != 1) {
        return NULL; // No token found
    }

    // Convert to lowercase for case-insensitive matching
    for (int i = 0; buffer[i]; i++) {
        buffer[i] = tolower(buffer[i]);
    }
    return buffer;
}

// Helper Function: Reads the entire line, removes newline, converts to lowercase. Used for Conversion menu (multi-word commands).
static char* read_and_standardize_line(char* buffer, size_t size) {
    if (fgets(buffer, (int)size, stdin) == NULL) {
        return NULL; // EOF or error
    }

    // Trim trailing newline
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }

    // Convert entire line to lowercase for case-insensitive matching
    for (int i = 0; buffer[i]; i++) {
        buffer[i] = tolower(buffer[i]);
    }
    return buffer;
}

/**
 * @brief Displays the main menu options to the user.
 */
void display_menu() {
    printf("\n======================================================\n");
    printf("              Advanced Calculator Options\n");
    printf("======================================================\n");
    printf("Math. Mathematical Operations (+, -, x, /, %%, exp, log, |x|, x^y, n!)\n");
    printf("Trig. Trigonometric Operations (sin, cos, tan, cot, hyp)\n");
    printf("Conv. Number System Conversions (Dec/Bin/Hex)\n");
    printf("Clear. Clear/Restart Calculator\n");
    printf("Exit. Exit Program\n");
    printf("------------------------------------------------------\n");
    printf("Enter your choice: ");
}

/**
 * @brief Gets a valid choice from the main menu using descriptive string input (e.g., "Math", "Exit").
 * @return The internal choice number (1-5) or -1 if invalid.
 */
int get_main_menu_choice_string() {
    char input_buffer[MAX_INPUT_LENGTH];

    // Read and standardize the first token
    if (read_and_standardize_token(input_buffer, MAX_INPUT_LENGTH) == NULL) {
        return -1; // No token found or error
    }

    // Map the string to an internal integer choice
    if (strcmp(input_buffer, "math") == 0) return 1;
    if (strcmp(input_buffer, "trig") == 0) return 2;
    if (strcmp(input_buffer, "conv") == 0) return 3;
    if (strcmp(input_buffer, "clear") == 0) return 4;
    if (strcmp(input_buffer, "exit") == 0) return 5;

    printf("Invalid choice. Please enter 'Math', 'Trig', 'Conv', 'Clear', or 'Exit'.\n");
    return -1;
}

/**
 * @brief Gets a valid choice from the Math sub-menu using descriptive string input (e.g., "Add", "Fact").
 * @return The internal choice number (1-11) or -1 if invalid.
 */
int get_math_menu_choice_string() {
    char input_buffer[MAX_INPUT_LENGTH];
    if (read_and_standardize_token(input_buffer, MAX_INPUT_LENGTH) == NULL) return -1;

    if (strcmp(input_buffer, "add") == 0) return 1;
    if (strcmp(input_buffer, "sub") == 0) return 2;
    if (strcmp(input_buffer, "mult") == 0) return 3;
    if (strcmp(input_buffer, "divi") == 0) return 4;
    if (strcmp(input_buffer, "remain") == 0) return 5;
    if (strcmp(input_buffer, "exp") == 0) return 6;
    if (strcmp(input_buffer, "log") == 0) return 7;
    if (strcmp(input_buffer, "abs") == 0) return 8;
    if (strcmp(input_buffer, "pow") == 0) return 9;
    if (strcmp(input_buffer, "fact") == 0) return 10;
    if (strcmp(input_buffer, "back") == 0) return 11;

    printf("Invalid choice. Please enter a valid operation shortcut (e.g., 'Add', 'Fact') or 'Back'.\n");
    return -1;
}

/**
 * @brief Gets a valid choice from the Trig sub-menu using descriptive string input (e.g., "Sin", "Hyp").
 * @return The internal choice number (1-6) or -1 if invalid.
 */
int get_trig_menu_choice_string() {
    char input_buffer[MAX_INPUT_LENGTH];
    if (read_and_standardize_token(input_buffer, MAX_INPUT_LENGTH) == NULL) return -1;

    if (strcmp(input_buffer, "sin") == 0) return 1;
    if (strcmp(input_buffer, "cos") == 0) return 2;
    if (strcmp(input_buffer, "tan") == 0) return 3;
    if (strcmp(input_buffer, "cotan") == 0) return 4;
    if (strcmp(input_buffer, "hyp") == 0) return 5;
    if (strcmp(input_buffer, "back") == 0) return 6;

    printf("Invalid choice. Please enter a valid operation shortcut (e.g., 'Sin', 'Hyp') or 'Back'.\n");
    return -1;
}

/**
 * @brief Gets a valid choice from the Conversion sub-menu using descriptive string input (e.g., "Dec to Bin", "Back").
 * @return The internal choice number (1-7) or -1 if invalid.
 */
int get_conv_menu_choice_string() {
    char input_line[MAX_INPUT_LENGTH];
    // This menu uses multi-word commands, so we read the full line
    if (read_and_standardize_line(input_line, MAX_INPUT_LENGTH) == NULL) return -1;

    if (strcmp(input_line, "dec to bin") == 0) return 1;
    if (strcmp(input_line, "bin to dec") == 0) return 2;
    if (strcmp(input_line, "dec to hex") == 0) return 3;
    if (strcmp(input_line, "hex to dec") == 0) return 4;
    if (strcmp(input_line, "hex to bin") == 0) return 5;
    if (strcmp(input_line, "bin to hex") == 0) return 6;
    if (strcmp(input_line, "back") == 0) return 7;

    printf("Invalid choice. Please enter a full conversion command (e.g., 'Dec to Bin') or 'Back'.\n");
    return -1;
}


/**
 * @brief Gets a double operand from the user, allowing a number or nested sub-menu calls (Math, Trig, or Conv).
 * @param prompt The message to display to the user.
 * @return The double value entered, or NAN if input is invalid or a nested operation fails.
 */
double get_double_input(const char* prompt) {
    // Buffer size defined in header
    char input_buffer[MAX_INPUT_LENGTH];
    double value = NAN;

    // Use the robust helper function to read the first token
    if (get_string_token(prompt, input_buffer, MAX_INPUT_LENGTH) == NULL) {
        printf("Invalid input format.\n");
        return NAN;
    }

    // Convert to lowercase for case-insensitive nested command matching
    for (int i = 0; input_buffer[i]; i++) {
        input_buffer[i] = tolower(input_buffer[i]);
    }

    // Check for Nested Menu Call (now accepting strings "math", "trig", "conv")
    if (strcmp(input_buffer, "math") == 0 || strcmp(input_buffer, "trig") == 0 || strcmp(input_buffer, "conv") == 0) {
        int nested_choice;

        if (strcmp(input_buffer, "math") == 0) {
            nested_choice = 1;
        }
        else if (strcmp(input_buffer, "trig") == 0) {
            nested_choice = 2;
        }
        else { // "conv"
            nested_choice = 3;
        }

        printf("\n--- Nested Operation (%s selected) ---\n", input_buffer);

        // Call the appropriate handler, which returns a double
        switch (nested_choice) {
        case 1: value = handle_math_operations(); break;
        case 2: value = handle_trig_operations(); break;
        case 3:
            printf("Warning: Number conversions are integer-based and may lose precision when used as floating-point operands.\n");
            value = handle_conversion_operations();
            break;
        }

        if (!isnan(value)) {
            printf("-> Nested Result: %.4lf used as operand.\n", value);
            return value;
        }
        else {
            // Nested operation failed or user chose 'Back'. Retry main operand input.
            printf("\nNested operation failed or cancelled. Please re-enter the required operand.\n");
            // Recursive call to get input again
            return get_double_input(prompt);
        }
    }

    // Attempt to convert the string to a double (Standard input)
    if (sscanf(input_buffer, "%lf", &value) != 1) {
        printf("Invalid input. Must be a number or a nested menu choice ('Math', 'Trig', or 'Conv').\n");
        return NAN;
    }

    return value;
}


// --- Mathematical Operations Implementations (simplified to keep function file size manageable) ---

double add(double a, double b) { return a + b; }
double subtract(double a, double b) { return a - b; }
double multiply(double a, double b) { return a * b; }
double divide(double a, double b) {
    if (b == 0) {
        printf("Error: Division by zero!\n");
        return NAN; // Not a Number
    }
    return a / b;
}
long long remainder_op(long long a, long long b) {
    if (b == 0) {
        printf("Error: Modulo by zero!\n");
        return 0;
    }
    return a % b;
}
double exponential(double x) { return exp(x); }
double logarithm(double x) {
    if (x <= 0) {
        printf("Error: Logarithm input must be positive.\n");
        return NAN;
    }
    return log(x); // Natural logarithm
}
double abs_square_root(double x) { return fabs(x); }
double power(double base, double exp) { return pow(base, exp); }
unsigned long long factorial(int n) {
    if (n < 0) {
        printf("Error: Factorial is undefined for negative numbers.\n");
        return 0;
    }
    if (n > 20) {
        printf("Error: Input too large for factorial (max 20).\n");
        return 0;
    }
    if (n == 0) return 1;

    unsigned long long result = 1;
    for (int i = 1; i <= n; i++) {
        result *= i;
    }
    return result;
}

// --- Trigonometric Operations Implementations ---

double sine_deg(double deg) {
    return sin(deg * DEG_TO_RAD);
}
double cosine_deg(double deg) {
    return cos(deg * DEG_TO_RAD);
}
double tangent_deg(double deg) {
    double rad = deg * DEG_TO_RAD;
    double tan_val = tan(rad);
    if (fabs(cos(rad)) < 1e-9) {
        printf("Warning: Tangent is undefined near 90 or 270 degrees.\n");
        return NAN;
    }
    return tan_val;
}
double cotangent_deg(double deg) {
    double tan_val = tangent_deg(deg);
    if (isnan(tan_val)) {
        if (fabs(sin(deg * DEG_TO_RAD)) < 1e-9) {
            printf("Warning: Cotangent is undefined near 0 or 180 degrees.\n");
            return NAN;
        }
        return 0.0;
    }
    if (fabs(tan_val) < 1e-9) {
        printf("Warning: Cotangent approaches infinity.\n");
        return NAN;
    }
    return 1.0 / tan_val;
}

/**
 * @brief Calculates the hypotenuse of a right-angled triangle (c = sqrt(a^2 + b^2)).
 * @param a Length of the first side.
 * @param b Length of the second side.
 * @return The hypotenuse length.
 */
double hypotenuse(double a, double b) {
    // Uses the robust C standard library function hypot(a, b)
    return hypot(a, b);
}

// --- Number System Conversion Implementations (simplified to keep function file size manageable) ---

void dec_to_bin(long long dec) {
    if (dec == 0) { printf("Binary: 0\n"); return; }
    char binary_str[65]; int i = 0; unsigned long long temp_dec = (unsigned long long)llabs(dec);
    if (temp_dec == 0) { printf("Binary: 0\n"); return; }
    while (temp_dec > 0 && i < 64) { binary_str[i++] = (temp_dec % 2) + '0'; temp_dec /= 2; }
    binary_str[i] = '\0';
    printf("Binary: %s", (dec < 0 ? "-" : ""));
    for (int j = i - 1; j >= 0; j--) { printf("%c", binary_str[j]); } printf("\n");
}
long long bin_to_dec(const char* bin_str) {
    long long dec = 0; long long base = 1; int len = (int)strlen(bin_str);
    for (int i = len - 1; i >= 0; i--) {
        if (bin_str[i] == '1') { dec += base; }
        else if (bin_str[i] != '0') { printf("Error: Invalid binary digit '%c'.\n", bin_str[i]); return -1; }
        base *= 2;
    }
    return dec;
}
void dec_to_hex(long long dec) { printf("Hexadecimal: %llX\n", dec); }
long long hex_to_dec(const char* hex_str) {
    long long dec;
    if (sscanf(hex_str, "%llx", &dec) != 1) { printf("Error: Invalid hexadecimal format.\n"); return -1; }
    return dec;
}
void hex_to_bin(const char* hex_str) {
    long long dec = hex_to_dec(hex_str);
    if (dec != -1) { printf("Decimal: %lld\n", dec); dec_to_bin(dec); }
}
void bin_to_hex(const char* bin_str) {
    long long dec = bin_to_dec(bin_str);
    if (dec != -1) { printf("Decimal: %lld\n", dec); dec_to_hex(dec); }
}

/**
 * @brief Handles the flow for Mathematical Operations sub-menu. Returns the result as a double.
 */
double handle_math_operations() {
    int math_choice;
    double a = NAN, b = NAN, result_d = NAN;
    long long a_ll, b_ll, result_ll;
    int n;
    char input_buffer[MAX_INPUT_LENGTH];

    printf("\n--- Mathematical Operations ---\n");
    printf("Add. Add (+)\nSub. Subtract (-)\nMult. Multiply (x)\nDivi. Divide (÷)\n");
    printf("Remain. Remainder (%%)\nExp. Exponential (exp(x))\nLog. Logarithmic (log(x))\n");
    printf("Abs. Absolute value of input (|x|)\nPow. Power (x^y)\nFact. Factorial (n!)\n");
    printf("Back. Back to Previous Operation/Main Menu\n");
    printf("Enter choice: ");

    math_choice = get_math_menu_choice_string();
    if (math_choice == -1 || math_choice == 11) return NAN;

    // Handle single-operand functions (exp, log, |x|)
    if (math_choice == 6 || math_choice == 7 || math_choice == 8) {
        a = get_double_input("Enter a single number (x): ");
        if (isnan(a)) return NAN;

        switch (math_choice) {
        case 6: result_d = exponential(a); printf("exp(%.4lf) = %.4lf\n", a, result_d); break;
        case 7: result_d = logarithm(a); printf("log(%.4lf) = %.4lf\n", a, result_d); break;
        case 8: result_d = abs_square_root(a); printf("|%.4lf| (Abs) = %.4lf\n", a, result_d); break;
        }
        return result_d;
    }

    // Handle Factorial (integer only) - Requires standard integer input
    if (math_choice == 10) {
        if (get_string_token("Enter a non-negative integer (n): ", input_buffer, MAX_INPUT_LENGTH) == NULL ||
            sscanf(input_buffer, "%d", &n) != 1) {
            printf("Invalid input.\n"); return NAN;
        }
        result_ll = factorial(n);
        if (result_ll != 0) {
            printf("%d! = %llu\n", n, result_ll);
            return (double)result_ll;
        }
        return NAN;
    }

    // Handle Remainder (integer only) - Requires standard integer input
    if (math_choice == 5) {
        printf("Enter two integers (a %% b) - Note: Nested Op is NOT available for integer-only input.\n");

        if (get_string_token("Enter the first integer (a): ", input_buffer, MAX_INPUT_LENGTH) == NULL ||
            sscanf(input_buffer, "%lld", &a_ll) != 1) {
            printf("Invalid input.\n"); return NAN;
        }

        if (get_string_token("Enter the second integer (b): ", input_buffer, MAX_INPUT_LENGTH) == NULL ||
            sscanf(input_buffer, "%lld", &b_ll) != 1) {
            printf("Invalid input.\n"); return NAN;
        }

        result_ll = remainder_op(a_ll, b_ll);
        if (b_ll != 0) {
            printf("%lld %% %lld = %lld\n", a_ll, b_ll, result_ll);
            return (double)result_ll;
        }
        return NAN;
    }

    // Handle two-operand floating-point functions (Add, Sub, Mul, Div, Pow)
    a = get_double_input("Enter the first number (a or Nested operator (Math/Trig/Conv)): ");
    if (isnan(a)) return NAN;
    b = get_double_input("Enter the second number (b or Nested operator (Math/Trig/Conv)): ");
    if (isnan(b)) return NAN;

    switch (math_choice) {
    case 1: result_d = add(a, b); printf("%.4lf + %.4lf = %.4lf\n", a, b, result_d); break;
    case 2: result_d = subtract(a, b); printf("%.4lf - %.4lf = %.4lf\n", a, b, result_d); break;
    case 3: result_d = multiply(a, b); printf("%.4lf x %.4lf = %.4lf\n", a, b, result_d); break;
    case 4: result_d = divide(a, b);
        if (!isnan(result_d)) printf("%.4lf ÷ %.4lf = %.4lf\n", a, b, result_d);
        break;
    case 9: result_d = power(a, b); printf("%.4lf ^ %.4lf = %.4lf\n", a, b, result_d); break;
    default: result_d = NAN;
    }

    return result_d;
}

/**
 * @brief Handles the flow for Trigonometric Operations sub-menu. Returns the result as a double.
 */
double handle_trig_operations() {
    int trig_choice;
    double angle, a, b, result_d = NAN;

    printf("\n--- Trigonometric Operations ---\n");
    printf("NOTE: Angles are in degrees.\n");
    printf("Sin. Sine (sin)\nCos. Cosine (cos)\nTan. Tangent (tan)\nCotan. Cotangent (cot)\n");
    printf("Hyp. Hypotenuse (hyp, calculates c = sqrt(a^2 + b^2))\n");
    printf("Back. Back to Previous Operation/Main Menu\n");
    printf("Enter choice: ");

    trig_choice = get_trig_menu_choice_string();
    if (trig_choice == -1 || trig_choice == 6) return NAN;

    // Handle Hypotenuse (two-operand)
    if (trig_choice == 5) {
        a = get_double_input("Enter side a: ");
        if (isnan(a)) return NAN;
        b = get_double_input("Enter side b: ");
        if (isnan(b)) return NAN;

        result_d = hypotenuse(a, b);
        printf("Hypotenuse of %.4lf and %.4lf is %.4lf\n", a, b, result_d);
        return result_d;
    }

    // Handle single-operand functions (angle in degrees)
    angle = get_double_input("Enter the angle in degrees: ");
    if (isnan(angle)) return NAN;

    switch (trig_choice) {
    case 1: result_d = sine_deg(angle); printf("sin(%.4lf°) = %.4lf\n", angle, result_d); break;
    case 2: result_d = cosine_deg(angle); printf("cos(%.4lf°) = %.4lf\n", angle, result_d); break;
    case 3: result_d = tangent_deg(angle);
        if (!isnan(result_d)) printf("tan(%.4lf°) = %.4lf\n", angle, result_d);
        break;
    case 4: result_d = cotangent_deg(angle);
        if (!isnan(result_d)) printf("cot(%.4lf°) = %.4lf\n", angle, result_d);
        break;
    default: result_d = NAN;
    }

    return result_d;
}

/**
 * @brief Handles the flow for Number System Conversion sub-menu. Returns the decimal equivalent as a double.
 */
double handle_conversion_operations() {
    int conv_choice;
    char input_str[MAX_INPUT_LENGTH];
    long long dec_val = -1;
    double result_d = NAN;


    printf("\n--- Number System Conversions ---\n");
    printf("Note: String input conversions (Bin/Hex) do NOT support Nested Ops.\n");
    printf("Dec to Bin. Dec to Bin\nBin to Dec. Bin to Dec\nDec to Hex. Dec to Hex\nHex to Dec. Hex to Dec\n");
    printf("Hex to Bin. Hex to Bin \nBin to Hex. Bin to Hex \n");
    printf("Back. Back to Previous Operation/Main Menu\n");
    printf("Enter choice: ");

    conv_choice = get_conv_menu_choice_string();
    if (conv_choice == -1 || conv_choice == 7) return NAN;

    // Conversions involving a decimal input (supports Nested Ops via get_double_input)
    if (conv_choice == 1 || conv_choice == 3) {
        double dec_d = get_double_input("Enter Decimal number (will be truncated to integer): ");
        if (isnan(dec_d)) return NAN;

        dec_val = (long long)dec_d;

        switch (conv_choice) {
        case 1: dec_to_bin(dec_val); break;
        case 3: dec_to_hex(dec_val); break;
        }
        result_d = (double)dec_val;
        return result_d;
    }

    // Conversions involving string inputs (Bin/Hex) - Requires standard string input via helper
    if (get_string_token("Enter the number string: ", input_str, MAX_INPUT_LENGTH) == NULL) {
        printf("Invalid input.\n");
        return NAN;
    }

    switch (conv_choice) {
    case 2:
        dec_val = bin_to_dec(input_str);
        if (dec_val != -1) {
            printf("Decimal: %lld\n", dec_val);
            result_d = (double)dec_val;
        }
        break;
    case 4:
        dec_val = hex_to_dec(input_str);
        if (dec_val != -1) {
            printf("Decimal: %lld\n", dec_val);
            result_d = (double)dec_val;
        }
        break;
    case 5:
        hex_to_bin(input_str);
        break;
    case 6:
        bin_to_hex(input_str);
        break;
    }

    return result_d;
}