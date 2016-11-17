#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main (void) {
    
    //declaring variables
    float change = -0.01;
    int quarters = 0.0;
    int dimes = 0.0;
    int nickels = 0.0;
    int pennies = 0.0;
    
    //prompting a valid input
    while(change <= 0) {
        printf("O hai! How much change is owed? \n");
        change = GetFloat();
    }

    //converting input to cents
    int remainder =  (int)round(change*100);

    //math to count the number of coins    
    quarters = remainder / 25;
    remainder = remainder % 25;
    dimes = remainder / 10;
    remainder = remainder % 10;
    nickels = remainder / 5;
    remainder = remainder % 5;
    pennies = remainder;
    
    int coins = quarters + dimes + nickels + pennies;

    //final output
    printf("%i\n", coins);
}