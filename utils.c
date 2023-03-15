#include "utils.h"
#include "string.h"
#include "stdio.h"



void CleanStdin() {
    int c;
    while((c = getchar()) != '\n' && c != '\0') {
        // Discard character
    }
}