#include <stdio.h>
#include <string.h>
#define N strlen(gen_poly)  // Length of the generator polynomial
char data[28];  // Data to be transmitted and received
char check_value[28];  // CRC value
char gen_poly[10];  // Generator polynomial
int data_length, i, j;  // Variables
void XOR() {  // Function that performs XOR operation
    for (j = 1; j < N; j++)
        check_value[j] = ((check_value[j] == gen_poly[j]) ? '0' : '1');
}
void crc() {
    for (i = 0; i < N; i++)  // Initializing check_value
        check_value[i] = data[i];
     do {
        if (check_value[0] == '1')  // Check if the first bit is 1 and call XOR function
            XOR();
          for (j = 0; j < N - 1; j++)  // Move the bits by 1 position for the next computation
            check_value[j] = check_value[j + 1];
        
        check_value[j] = data[i++];  // Appending a bit from data
    } while (i <= data_length + N - 1);  // Loop until the data ends
}
void receiver() {  // Function to check for errors on the receiver side
    printf("Enter the received data: ");
    scanf("%s", data);
     printf("\n------------------------------\n");
    printf("Data received: %s", data);
     crc();  // Cyclic Redundancy Check
    for (i = 0; (i < N - 1) && (check_value[i] != '1'); i++);
     if (i < N - 1)
        printf("\nError detected\n\n");
    else
        printf("\nNo error detected\n\n");
}
int main() {
    printf("\nEnter data to be transmitted: ");  // Get the data to be transmitted
    scanf("%s", data);
    printf("\nEnter the Generating polynomial: ");
    scanf("%s", gen_poly);  // Get the generator polynomial
    data_length = strlen(data);  // Find the length of data
    for (i = data_length; i < data_length + N - 1; i++)  // Appending n-1 zeros to the data
        data[i] = '0';
    data[i] = '\0';
     printf("\n------------------------------\n");
    printf("\nData padded with n-1 zeros: %s", data);  // Print the data with padded zeros
     crc();  // Cyclic Redundancy Check
     printf("\nCRC or Check value is: %s", check_value);  // Print the computed check value
     for (i = data_length; i < data_length + N - 1; i++)  // Append data with check_value (CRC)
        data[i] = check_value[i - data_length];
    data[i] = '\0';
    printf("\n------------------------------\n");
    printf("\nFinal data to be sent: %s", data);  // Printing the final data to be sent
    printf("\n------------------------------\n\n");
    receiver();  // Calling the receiver function to check errors
    return 0;
}
