#define _CRT_SECURE_NO_WARNINGS
#include "calculator.h"

/**
 * @brief Main function to run the advanced calculator program.
 * The program runs in a loop until the user chooses to exit.
 */
int main() {
    int choice = 0;
    double top_level_result = NAN; // Variable to capture the result of the top-level operation

    printf("--- Welcome to the Advanced Calculator ---\n");
    printf("Note: You can enter a menu number (1, 2, or 3) for a nested calculation when prompted for numerical input.\n");

    // Main program loop (now exits on 5)
    while (choice != 5) {
        display_menu();
        choice = get_menu_choice(5); // Check up to 5 options

        if (choice == -1) {
            // Invalid input, loop continues to redisplay menu
            continue;
        }

        top_level_result = NAN; // Reset result at the start of loop iteration

        switch (choice) {
        case 1:
            // Mathematical Operations
            top_level_result = handle_math_operations();
            break;
        case 2:
            // Trigonometric Operations
            top_level_result = handle_trig_operations();
            break;
        case 3:
            // Number System Conversions
            top_level_result = handle_conversion_operations();
            break;
        case 4:
            // Clear/Restart option (simply restarts the loop iteration)
            printf("\n--- Calculator Cleared. Ready for a new calculation! ---\n");
            break;
        case 5:
            // Exit option
            printf("\n--- Exiting Calculator. Goodbye! ---\n");
            break;
        default:
            // Should be caught by get_menu_choice, but for safety:
            printf("An unexpected error occurred. Please try again.\n");
            break;
        }
    }

    return 0;
}