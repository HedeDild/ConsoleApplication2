#define _CRT_SECURE_NO_WARNINGS // Used to remove unsafe function warnings
#include "calculator.h" // Include the header file with function prototypes


 // Main function to run in loops.

int main() { // Main program loop
	int choice = 0; // Ready to recieve user input
	double top_level_result = NAN; // Ready to store the result of top-level operations

    printf("--- Welcome to the Advanced Calculator ---\n");
    printf("Made by Jakob and Frederik\n");
    printf("Note: You can enter a sub-menu for a nested calculation when prompted for numerical input.\n");

    // Main program loop
	while (choice != 5) { // Loop until user chooses to exit
		display_menu(); 
        choice = get_main_menu_choice_string(); // Uses string-based input

		if (choice == -1) { //invalid input redisplays menu
            continue;
        }

        top_level_result = NAN; // Reset result at the start of loop iteration

        switch (choice) {
        case 1:
            // Mathematical Operations (Math)
			top_level_result = handle_math_operations(); // Sets top_level_result the result of math operations
            break;
        case 2:
            // Trigonometric Operations (Trig)
			top_level_result = handle_trig_operations();// Sets top_level_result to result of trig operations
            break;
        case 3:
            // Number System Conversions (Conv)
			top_level_result = handle_conversion_operations();// Sets top_level_result to result of conversion operations
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

	return 0; // When 5 is chosen, return 0 to exit program
}