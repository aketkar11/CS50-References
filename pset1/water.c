#include <stdio.h>
#include <cs50.h>

int main (void) {

    printf("minutes: ");

    int length = GetInt();
    
    while (length < 0) {
        printf("Retry: ");
        length = GetInt();
    }
    
    int bottles = length*12;

    printf("bottles: %i\n", bottles);
}