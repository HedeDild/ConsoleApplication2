#define _CRT_SECURE_NO_WARNINGS
#include "calculator.h"

/**
 * @brief Main function to run the advanced calculator program.
 * The program runs in a loop until the user chooses to exit.
 */
int main() {
    int choice = 0;
    double top_level_result = NAN;

    printf("--- Welcome to the Advanced Calculator ---\n");
    printf("Made by Jakob and Frederik\n");
    printf("Note: You can enter a sub-menu for a nested calculation when prompted for numerical input.\n");

    // Main program loop (now exits on 5, which maps to "Exit")
    while (choice != 5) {
        display_menu();
        choice = get_main_menu_choice_string(); // Uses string-based input

        if (choice == -1) {
            // Invalid input, loop continues to redisplay menu
            continue;
        }

        top_level_result = NAN; // Reset result at the start of loop iteration

        switch (choice) {
        case 1:
            // Mathematical Operations (Math)
            top_level_result = handle_math_operations();
            break;
        case 2:
            // Trigonometric Operations (Trig)
            top_level_result = handle_trig_operations();
            break;
        case 3:
            // Number System Conversions (Conv)
            top_level_result = handle_conversion_operations();
            break;
        case 4:
            // Clear/Restart option (Clear)
            printf("\n--- Calculator Cleared. Ready for a new calculation! ---\n");
            break;
        case 5:
            // Exit option
            printf("\n--- Exiting Calculator. Goodbye! ---\n");
            break;
        default:
            printf("An unexpected error occurred. Please try again.\n");
            break;
        }
    }

    return 0;
}