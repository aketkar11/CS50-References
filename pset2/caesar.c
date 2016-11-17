#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main(int argc, string argv[]) {
    
    if(argc < 2) {
        printf("%s\n","Input the key!");
        return 1;
    }
    int key = atoi(&argv[1][0]); //have the cipher key
    printf("%s", "");
    string plainText = GetString();
    
    //switch from ascii to alphabet
    string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int stringLen = strlen(plainText);
    
    for(int i = 0; i< stringLen; i++) {
        if(isalpha(plainText[i])) { 
            for (int j =0; j<26; j++) {
                if(toupper(plainText[i]) == (int)alphabet[j]) {
                    //int alphaCode = j;
                    int computeCipherIndex = (j+key)%26;
                    char alphaCipher = alphabet[computeCipherIndex];
                    if(islower(plainText[i])){
                        printf("%c", tolower(alphaCipher));
                    }
                    else {
                        printf("%c", alphaCipher);
                    }
                }
            }
        }
        else {
            printf("%c", plainText[i]);
        }
        
    }
    printf("\n");

}