#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main(int argc, string argv[]) {
    
    if(argc != 2) {
        printf("%s\n","Input the key!");
        return 1;
    }
    //int key = atoi(&argv[1]); //have the cipher key
    string key = argv[1];
    for(int s = 0; s < strlen(key); s++) {
        if(!isalpha(key[s])) {
            printf("%s", "Keyword must contain letters!");
            return 1;
        }
    }
    
    int keyLen = strlen(argv[1]);
    printf("%s", "");
    string plainText = GetString();
    
    //switch from ascii to alphabet
    string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int stringLen = strlen(plainText);
    int l = 0;

    for(int i = 0; i< stringLen; i++) {
        if(isalpha(plainText[i])) { 
            for (int j =0; j<26; j++) {
                if(toupper(plainText[i]) == (int)alphabet[j]) {
                    for(int k=0; k< 26;k++) {
                        if(toupper(key[l%keyLen]) == (int)alphabet[k]) {
                            int computeCipherIndex = (j+k)%26;
                            char alphaCipher = alphabet[computeCipherIndex];
                            //keyCount++;
                            if(islower(plainText[i])){
                                printf("%c", tolower(alphaCipher));
                            }
                            else {
                                printf("%c", alphaCipher);
                            }
                        }
                    }
                }
            }
            l++;
        }
        else {
            printf("%c", plainText[i]);
        }
        
    }
    printf("\n");

}