#include <stdio.h>
#include <cs50.h>

int main (void) {

    //prompt for entering the height until the number is between 0 and 23
    int height = -1;
    
    while (height < 0 || height > 23) {
        printf("height: ");
        height = GetInt();
    }
    
    int i=1;

    while (i<=height) {
        
        //accounting for all the spaces in the rows-> row 1-> space height-1
        for(int j= height-i; j > 0; j--) {
            printf(" ");
        }
        //putting pounds after entering the spaces
        for(int k=1; k<=i+1; k++) {
            printf("#");
        }
        
        //entering the newline character to give it blocks
        printf("\n");
        i++;
    }
    
}