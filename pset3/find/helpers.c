/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>
#include <stdio.h>
#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    bool variable = false;
    int left = 0;
    int right = n-1;
    int mid = 0;
    
    while(left <= right) {

        mid = (left+right)/2;
        
        if(value < values[mid]) {
            right = mid-1;
        }
        else if(value > values[mid]) {
            left = mid+1;
        }
        else {
            variable = true;
            return variable;
        }
    }
    return variable;
}
/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    int temp;
    // TODO: implement an O(n^2) sorting algorithm
    for(int i = 1; i < n; i++) {
        int j = i;
        while(j >= 0 && values[j] < values[j-1]) {
            temp = values[j];
            values[j] = values[j-1];
            values[j-1] = temp;
            j --;
        }
    }
        for(int i = 0; i < n; i++) {
        printf("%i\n",values[i]);
    }
    
}