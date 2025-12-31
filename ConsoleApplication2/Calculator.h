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
 * @brief Gets a double operand from the user, allowing a number or nested sub-menu calls (Math, Trig or Conv).
 * @param prompt The message to display to the user.
 * @return The double value entered, or NAN if input is invalid or a nested operation fails.
 */
double get_double_input(const char* prompt); //

// --- Mathematical Operations ---
double add(double a, double b);					  // allows adding
double subtract(double a, double b);			  // allows substracting
double multiply(double a, double b);			  // allows multipling
double divide(double a, double b);			      // allows dividing
long long remainder_op(long long a, long long b); // allows for remainder calculations
double exponential(double x);					  // allows exponential
double logarithm(double x);						  // allows logaritmic calculations
double abs_square_root(double x);				  // allows for finding the squareroot
double power(double base, double exp);			  // allows calculating power functions
unsigned long long factorial(int n);			  // allows finding factorials

// --- Trigonometric Operations (Inputs in Degrees for user-friendliness) ---
double sine_deg(double deg);					  // allows sinus	
double cosine_deg(double deg);					  // allows	cosinus
double tangent_deg(double deg);					  // allows tangent
double cotangent_deg(double deg);				  // allows cotangent
double hypotenuse(double a, double b);			  // allows hypothenus

// --- Number System Conversions ---
void dec_to_bin(long long dec);					  // Dec to Bin
long long bin_to_dec(const char* bin_str);		  // Bin to Dec
				
void dec_to_hex(long long dec);					  // Dec to Hex
long long hex_to_dec(const char* hex_str);		  // Hex to Dec

void hex_to_bin(const char* hex_str);			  // Hex to bin
void bin_to_hex(const char* bin_str);			  // Bin to Hex

#endif // CALCULATOR_H