#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(void) {
    //prompt the user for name
    printf("%s","");
    
    string name = GetString();
    int length = strlen(name);
    int spaces = 0;

    int j=0;
    while(j <= length) {
        if(name[j] == ' ') {
            spaces ++;
        }
        j++;
    }

    char initArray[spaces+1];
    initArray[0] = toupper(name[0]);
    int i = 1;
    j = 0;
    while(j <= length) {
        if(name[j]==' '){
            initArray[i] = toupper(name[j+1]);
            i++;
        }
        j++;
    }

    int k;
    for (k=0;k < (sizeof (initArray) /sizeof (initArray[0]));k++) {
        printf("%c",initArray[k]);
    }
    printf("\n");
}