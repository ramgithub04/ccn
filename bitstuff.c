#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 100
void bitStuffing(char* data, int* size) { // Function to perform bit stuffing
    int count = 0;
    int newSize = *size;
      for (int i = 0; i < *size; i++) {
        if (data[i] == '1') {
            count++;
        } else {
            count = 0;
        }
           if (count == 5) {
            count = 0;
            for (int j = newSize; j > i + 1; j--) { // Shift all elements to the right by one
                data[j] = data[j - 1];
            }
            data[i + 1] = '0'; // Insert '0' after the fifth consecutive '1'
            newSize++;
            count = 0;
        }
    }
    *size = newSize;
    data[*size] = '\0'; // Null-terminate the string
}
void bitDestuffing(char* data, int* size) { // Function to perform bit destuffing
    int count = 0;
    int newSize = *size;
     for (int i = 0; i < newSize; i++) {
        if (data[i] == '1') {
            count++;
        } else {
            count = 0;
        }
         if (count == 5 && i < newSize - 1 && data[i + 1] == '0') {
            for (int j = i + 1; j < newSize; j++) { // Shift all elements to the left by one
                data[j] = data[j + 1];
            }
            count = 0;
            newSize--; // Adjust newSize after shifting
        }
    }
    *size = newSize;
    data[*size] = '\0'; // Null-terminate the string
}
int main() {
    char data[MAX_SIZE];
    int size;
    printf("Enter the data (consisting of 0's and 1's): "); // Input data
    scanf("%s", data);
     for (size = 0; data[size] != '\0'; size++); // Calculate the size of the data
     bitStuffing(data, &size); // Perform bit stuffing
    printf("Stuffed data: %s\n", data);
    bitDestuffing(data, &size); // Perform bit destuffing
    printf("Destuffed data: %s\n", data);
    return 0;
}
