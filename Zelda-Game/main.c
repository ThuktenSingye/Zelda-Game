#include "game.h"
#include "main.h"
#include <stdio.h>
#include "terminal.h"
// Check for the QUICK_MODE macro
#ifdef QUICK_MODE
    // If QUICK_MODE is defined, skip the title splash screen
    int main() {
        runGame();
        return 0;
    };

#else
    // If QUICK_MODE is not defined, include the title splash screen
    int main() {
        // Display the title screen
        printf("Welcome to the Legend of Zelda!\n");
        printf("Press any key to continue...");

        // Disable terminal buffering
        disableBuffer();

        // Wait for a key press
        getchar();  

        // Clear the screen before starting the game
        clearScreen();

        // Enable terminal buffering
        enableBuffer();

        // Start the game
        runGame();

        return 0;
    }
#endif
