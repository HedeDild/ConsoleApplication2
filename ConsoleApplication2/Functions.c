/* * FILE: calculator_functions.c
 * PURPOSE: Contains the logic for all mathematical and conversion operations.
 * - 'double' is a number with decimals.
 * - 'long long' is a very large integer (no decimals).
 * - 'static' means a function is only visible inside this file.
 */

#define _CRT_SECURE_NO_WARNINGS
#include "calculator.h"

/* --- Constants --- */
#define PI 3.14159265358979323846
#define DEG_TO_RAD (PI / 180.0) // Multiplier to turn degrees into radians for math.h functions

/**
 * HELPER: get_string_token
 * Logic: Reads a whole line from the keyboard, but only keeps the first word.
 * Why? This prevents the program from crashing if a user types spaces or extra text.
 */
static char* get_string_token(const char* prompt, char* buffer, size_t size) {
    char temp_line[MAX_INPUT_LENGTH];
    printf("%s", prompt);

    // fgets reads text from stdin (the keyboard) safely
    if (fgets(temp_line, MAX_INPUT_LENGTH, stdin) == NULL) {
        return NULL; 
    }

    // sscanf "scans" the string we just read to pull out the first word (%s)
    if (sscanf(temp_line, "%s", buffer) != 1) {
        return NULL; 
    }
    return buffer;
}

/**
 * HELPER: read_and_standardize_token
 * Logic: Same as above, but forces every letter to be lowercase.
 * Why? So 'MATH', 'math', and 'Math' all work the same way.
 */
static char* read_and_standardize_token(char* buffer, size_t size) {
    if (get_string_token("", buffer, size) == NULL) return NULL;

    for (int i = 0; buffer[i]; i++) {
        buffer[i] = tolower((unsigned char)buffer[i]);
    }
    return buffer;
}

/**
 * HELPER: read_and_standardize_line
 * Logic: Reads the ENTIRE line (including spaces). 
 * Used for "Dec to Bin" because it contains spaces.
 */
static char* read_and_standardize_line(char* buffer, size_t size) {
    if (fgets(buffer, (int)size, stdin) == NULL) return NULL;

    // Remove the 'Enter' key character (\n) from the end of the string
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') buffer[len - 1] = '\0';

    for (int i = 0; buffer[i]; i++) {
        buffer[i] = tolower((unsigned char)buffer[i]);
    }
    return buffer;
}

/* --- Menu Display --- */
void display_menu() {
    printf("\n======================================================\n");
    printf("              Advanced Calculator Options\n");
    printf("======================================================\n");
    printf("Math.  Basic & Advanced Math (+, -, log, factorial)\n");
    printf("Trig.  Trigonometry (sin, cos, hypotenuse)\n");
    printf("Conv.  Base Conversions (Binary, Hex, Decimal)\n");
    printf("Clear. Reset the calculator screen\n");
    printf("Exit.  Close the program\n");
    printf("------------------------------------------------------\n");
    printf("Enter your choice: ");
}

/* --- Input Handling (Strings to Numbers) --- */

int get_main_menu_choice_string() {
    char buf[MAX_INPUT_LENGTH];
    if (read_and_standardize_token(buf, MAX_INPUT_LENGTH) == NULL) return -1;

    if (strcmp(buf, "math") == 0) return 1;
    if (strcmp(buf, "trig") == 0) return 2;
    if (strcmp(buf, "conv") == 0) return 3;
    if (strcmp(buf, "clear") == 0) return 4;
    if (strcmp(buf, "exit") == 0) return 5;

    printf("Invalid choice! Try typing 'Math' or 'Exit'.\n");
    return -1;
}

int get_math_menu_choice_string() {
    char buf[MAX_INPUT_LENGTH];
    if (read_and_standardize_token(buf, MAX_INPUT_LENGTH) == NULL) return -1;

    if (strcmp(buf, "add") == 0) return 1;
    if (strcmp(buf, "sub") == 0) return 2;
    if (strcmp(buf, "mult") == 0) return 3;
    if (strcmp(buf, "divi") == 0) return 4;
    if (strcmp(buf, "remain") == 0) return 5;
    if (strcmp(buf, "exp") == 0) return 6;
    if (strcmp(buf, "log") == 0) return 7;
    if (strcmp(buf, "abs") == 0) return 8;
    if (strcmp(buf, "pow") == 0) return 9;
    if (strcmp(buf, "fact") == 0) return 10;
    if (strcmp(buf, "back") == 0) return 11;

    return -1;
}

int get_trig_menu_choice_string() {
    char buf[MAX_INPUT_LENGTH];
    if (read_and_standardize_token(buf, MAX_INPUT_LENGTH) == NULL) return -1;

    if (strcmp(buf, "sin") == 0) return 1;
    if (strcmp(buf, "cos") == 0) return 2;
    if (strcmp(buf, "tan") == 0) return 3;
    if (strcmp(buf, "cotan") == 0) return 4;
    if (strcmp(buf, "hyp") == 0) return 5;
    if (strcmp(buf, "back") == 0) return 6;

    return -1;
}

int get_conv_menu_choice_string() {
    char buf[MAX_INPUT_LENGTH];
    if (read_and_standardize_line(buf, MAX_INPUT_LENGTH) == NULL) return -1;

    if (strcmp(buf, "dec to bin") == 0) return 1;
    if (strcmp(buf, "bin to dec") == 0) return 2;
    if (strcmp(buf, "dec to hex") == 0) return 3;
    if (strcmp(buf, "hex to dec") == 0) return 4;
    if (strcmp(buf, "hex to bin") == 0) return 5;
    if (strcmp(buf, "bin to hex") == 0) return 6;
    if (strcmp(buf, "back") == 0) return 7;

    return -1;
}

/**
 * CORE LOGIC: get_double_input
 * This is the "brain" of the input system. 
 * It checks if you typed a number OR if you typed a command like "Math".
 */
double get_double_input(const char* prompt) {  //* points to prompt and checks if it is a number or word
    char buf[MAX_INPUT_LENGTH];
    double value = NAN;

    if (get_string_token(prompt, buf, MAX_INPUT_LENGTH) == NULL) return NAN; //If the input doesnt correlate to a valid string nothing happens

    // Standardize to lowercase for the check
    for (int i = 0; buf[i]; i++) buf[i] = tolower((unsigned char)buf[i]);

    // Check if the user wants to "Nest" another operation
    if (strcmp(buf, "math") == 0 || strcmp(buf, "trig") == 0 || strcmp(buf, "conv") == 0) {
        printf("\n--- Entering Nested Operation (%s) ---\n", buf);
        
        if (strcmp(buf, "math") == 0) value = handle_math_operations();
        else if (strcmp(buf, "trig") == 0) value = handle_trig_operations();
        else value = handle_conversion_operations();

        // If the operation was successful, return the result as the operand
        if (!isnan(value)) {
            printf("-> Result %.4lf used as input.\n", value);
            return value;
        } else {
            printf("\nCancelled. Please enter a number instead.\n");
            return get_double_input(prompt); // Try again
        }
    }

    // If it's not a valid command, print an error message
    if (sscanf(buf, "%lf", &value) != 1) {
        printf("Invalid input! Enter a number or a menu name (Math/Trig/Conv).\n");
        return NAN;
    }

    return value;
}

/* --- Basic Math Implementations --- */

double add(double a, double b) { return a + b; }
double subtract(double a, double b) { return a - b; }
double multiply(double a, double b) { return a * b; }
double divide(double a, double b) {                         //if b is 0 return error
    if (b == 0) {
        printf("Error: You cannot divide by zero!\n");
        return NAN;
    }
    return a / b;
}

// Modulo (%) only works on whole numbers (integers)
// Safety statement for 0 value input
long long remainder_op(long long a, long long b) {
    if (b == 0) return 0;
    return a % b;
}

double exponential(double x) { return exp(x); }
double logarithm(double x) {
    if (x <= 0) {
        printf("Error: Logarithm only works for positive numbers.\n");
        return NAN;
    }
    return log(x);
}

double abs_square_root(double x) { return fabs(x); }
double power(double base, double exp_val) { return pow(base, exp_val); }

// Factorial (n!) uses a loop to multiply numbers (e.g., 4! = 4*3*2*1)
unsigned long long factorial(int n) {
    if (n < 0 || n > 20) return 0; // Too large for computer memory if > 20
    unsigned long long res = 1;
    for (int i = 1; i <= n; i++) res *= i;
    return res;
}

/* --- Trig Implementations --- */

double sine_deg(double deg) { return sin(deg * DEG_TO_RAD); }
double cosine_deg(double deg) { return cos(deg * DEG_TO_RAD); }
double tangent_deg(double deg) { return tan(deg * DEG_TO_RAD); }
double cotangent_deg(double deg) { return 1.0 / tan(deg * DEG_TO_RAD); }
double hypotenuse(double a, double b) { return hypot(a, b); }

/* --- Base Conversions --- */

// Decimal to Binary: Uses a loop to find remainders of 2
void dec_to_bin(long long dec) {
    if (dec == 0) { printf("Binary: 0\n"); return; }
    char bin[65]; int i = 0;                                    //bin for storing
    unsigned long long u_dec = (unsigned long long)llabs(dec);  //abs value to not worrie about negative sign
    while (u_dec > 0) {                                         //runs until number is 0
        bin[i++] = (u_dec % 2) + '0';                           // adds 0 in order to store it as a character
        u_dec /= 2;
    }
    bin[i] = '\0';
    printf("Binary: ");
    if (dec < 0) printf("-");                                   // if the original number where negative print minus
    for (int j = i - 1; j >= 0; j--) printf("%c", bin[j]);      // Print backwards since it calulates the last number first
    printf("\n");
}

long long bin_to_dec(const char* bin_str) {
    // strtoll converts a string to a long long integer using base 2
    return strtoll(bin_str, NULL, 2);
}

void dec_to_hex(long long dec) {
    // %llX is a special code to print a large number in Hexadecimal format
    printf("Hexadecimal: %llX\n", dec);
}

long long hex_to_dec(const char* hex_str) {
    return strtoll(hex_str, NULL, 16); // Base 16 is Hex
}

//converts hex to dec then dec to bin (which allows for the previous calculations to be used)
void hex_to_bin(const char* hex_str) {
    long long dec = hex_to_dec(hex_str);
    dec_to_bin(dec);
}

//see above but bin to hex
void bin_to_hex(const char* bin_str) {
    long long dec = bin_to_dec(bin_str);
    dec_to_hex(dec);
}

/* --- Main Menu Handlers --- */

double handle_math_operations() {
    int choice = get_math_menu_choice_string();
    if (choice == -1 || choice == 11) return NAN;

    double a, b;
    // logic for choosing operations
    
    if (choice <= 4 || choice == 9) { // Ops requiring 2 numbers (If a or b isnt numbers return nothing)
        a = get_double_input("First number (a): ");
        if (isnan(a)) return NAN;
        b = get_double_input("Second number (b): ");
        if (isnan(b)) return NAN;

        if (choice == 1) return add(a, b);
        if (choice == 2) return subtract(a, b);
        if (choice == 3) return multiply(a, b);
        if (choice == 4) return divide(a, b);
        if (choice == 9) return power(a, b);
    }
    return NAN; 
}

double handle_trig_operations() {
    int choice = get_trig_menu_choice_string();
    if (choice == -1 || choice == 6) return NAN;

    if (choice == 5) { // Hypotenuse
        double a = get_double_input("Side a: ");
        double b = get_double_input("Side b: ");
        return hypotenuse(a, b);
    }

    double angle = get_double_input("Angle in Degrees: ");
    if (choice == 1) return sine_deg(angle);
    if (choice == 2) return cosine_deg(angle);
    if (choice == 3) return tangent_deg(angle);
    return NAN;
}

double handle_conversion_operations() {
    int choice = get_conv_menu_choice_string();
    if (choice == -1 || choice == 7) return NAN;

    // Base conversions returns the decimal value to be used in calculations
    if (choice == 1 || choice == 3) {
        double d = get_double_input("Decimal number: ");
        if (choice == 1) dec_to_bin((long long)d);
        else dec_to_hex((long long)d);
        return d;
    }
    
    char str[MAX_INPUT_LENGTH];
    get_string_token("Enter number string: ", str, MAX_INPUT_LENGTH);
    if (choice == 2) return (double)bin_to_dec(str);
    if (choice == 4) return (double)hex_to_dec(str);

    return NAN;
}