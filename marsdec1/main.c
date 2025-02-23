#include <stdio.h>
#include <stdint.h>

/*
 * Decodes a single integer from a single line of input.
 * The integer's bit length L is stored in the first 5 bits of the first byte.
 * Then L bits of data follow to form the integer.
 * This is a simplified approach that only extracts one integer per line.
 */
void decode_line(int line_number, int num_bytes, const uint8_t *bytes) {

     // If there are no bytes, there's nothing to decode.
    if (num_bytes == 0) return;


     // The first 5 bits of bytes[0] give us L (the number of bits that form the integer).
     //We mask with 0x1F (11111 in binary) and shift right by 3 bits.

    int L = (bytes[0] >> 3) & 0x1F;


     //If L == 0, it indicates there's no integer to extract. So we just return.

    if (L == 0) return;


     //'result' will hold the integer once extracted.
     //'bits_read' tracks how many bits we've processed toward the integer.
     //'bit_pos' starts at 5, since we've already used 5 bits for L.

    int32_t result = 0;
    int bits_read = 0;
    int bit_pos = 5;


      //We extract the integer's L bits across provided bytes.
      //We skip first 5 bits of  first byte (those bits contained L).
    for (int i = 0; i < num_bytes && bits_read < L; i++) {
        for (int j = 7; j >= 0 && bits_read < L; j--) {

             //If we're in first byte (i == 0) and haven't skipped 5 bits yet (j >= 3),
             //we continue to skip those initial 5 bits.
            if (i == 0 && j >= 3) continue;


             //Shift 'result' to the left by 1 (making room for a new bit),
             //then OR in the extracted bit from 'bytes[i]', at position 'j'.
            result = (result << 1) | ((bytes[i] >> j) & 1);


            // Increment the count of bits we've extracted for this integer.
            bits_read++;
        }
    }


     //If the most significant bit (MSB) of the L-bit integer is 1,
     //it means the number is negative, so we sign-extend using '- (1 << L)'.
    if (L > 0 && (result & (1 << (L - 1)))) {
        result |= -(1 << L);
    }


     //Print the single decoded integer as required:
     //"Line <line_number>, integer 1: <result>"
    printf("Line %d, integer 1: %d\n", line_number, result);
}

int main() {
    int N;

      //First, read how many lines we need to decode (N).
    scanf("%d", &N);


     //For each line, we read:
     //1) B - number of bytes
     //2) B bytes in hexadecimal form
     //Then we decode the line and print result
    for (int i = 1; i <= N; i++) {
        int B;
        scanf("%d", &B);


         //We set up a small buffer (5 bytes) initialized to zero,
         //we only handle up to 5 bytes per line
        uint8_t bytes[5] = {0};


         //Read in B hex bytes into our array.
        for (int j = 0; j < B; j++) {
            scanf("%hhx", &bytes[j]);
        }


        //Decode and print the single integer for this line.
        decode_line(i, B, bytes);
    }

    return 0;
}
