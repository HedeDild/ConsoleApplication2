#define _CRT_SECURE_NO_WARNINGS
#include "calculator.h"

// Removed: Global definitions of last_result and prev_result

/**
 * @brief Main function to run the advanced calculator program.
 * The program runs in a loop until the user chooses to exit.
 */
int main() {
    int choice = 0;
    double top_level_result = NAN; // Variable to capture the result of the top-level operation

    printf("--- Welcome to the Advanced Calculator ---\n");
    printf("Note: You can enter a menu number (1, 2, or 3) for a nested calculation when prompted for numerical input.\n");

    // Main program loop
    // Updated maximum choice to 4 (Exit is now 4)
    while (choice != 4) {
        display_menu();
        choice = get_menu_choice(4);

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
            // Exit option (New case 4)
            printf("\n--- Exiting Calculator. Goodbye! ---\n");
            break;
            // Removed Case 4 (Clear/Restart)
        default:
            // Should be caught by get_menu_choice, but for safety:
            printf("An unexpected error occurred. Please try again.\n");
            break;
        }

        // Removed: Logic to update R and P
    }

    return 0;
}