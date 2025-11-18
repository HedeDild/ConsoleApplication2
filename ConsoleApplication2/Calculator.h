// This is the blueprint for for the main program
// It stores all function prototypes


#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <stdio.h>  // Basic I/O library
#include <math.h>   // Math functions library
#include <stdlib.h> // Standard library for conversions and memory management
#include <string.h> // String manipulation functions
#include <limits.h> // Limits for integer types
#include <ctype.h>  // Classifies and converts characters

// Define the maximum size for string inputs
#define MAX_INPUT_LENGTH 64

// Menu Functions
void display_menu(); // Displays the main menu

int get_main_menu_choice_string(); // Gets a choice from the main menu

int get_math_menu_choice_string(); // Gets a choice from the Math sub-menu

int get_trig_menu_choice_string(); // Gets a choice from the Trig sub-menu

int get_conv_menu_choice_string(); // Gets a choice from the Conversion sub-menu


double handle_math_operations(); // Handles Math Operations

double handle_trig_operations(); // Handles Trig Operations

double handle_conversion_operations(); // Handles Conversion Operations

// --- Input Function (Refactored for Recursion only) ---
/**
 * @brief Gets a double operand from the user, allowing a number or nested sub-menu calls (1, 2, or 3).
 * @param prompt The message to display to the user.
 * @return The double value entered, or NAN if input is invalid or a nested operation fails.
 */
double get_double_input(const char* prompt); //

// --- Mathematical Operations ---
double add(double a, double b);
double subtract(double a, double b);
double multiply(double a, double b);
double divide(double a, double b);
long long remainder_op(long long a, long long b);
double exponential(double x); // exp(x)
double logarithm(double x);   // log(x) (natural log)
double abs_square_root(double x); // sqrt(x^2) which is |x|
double power(double base, double exp); // x^y
unsigned long long factorial(int n); // n!

// --- Trigonometric Operations (Inputs in Degrees for user-friendliness) ---
double sine_deg(double deg);
double cosine_deg(double deg);
double tangent_deg(double deg);
double cotangent_deg(double deg);
double hypotenuse(double a, double b); // hypot(a,b)

// --- Number System Conversions ---
void dec_to_bin(long long dec);
long long bin_to_dec(const char* bin_str);

void dec_to_hex(long long dec);
long long hex_to_dec(const char* hex_str);

void hex_to_bin(const char* hex_str);
void bin_to_hex(const char* bin_str);

#endif // CALCULATOR_H