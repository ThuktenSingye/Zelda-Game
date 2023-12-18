
#pragma once

#include "game.h"
#include "terminal.h"

/* Check for the QUICK_MODE macro */
#ifdef QUICK_MODE
    /* If QUICK_MODE is defined, skip the title splash screen */
    int main();

#else
    /* If QUICK_MODE is not defined, include the title splash screen */
    int main();
#endif
