#include <stdio.h>
#include <stdint.h>


 //Decodes multiple integers from a single bitstream.
 //Each integer is preceded by a 5-bit length L, followed by L bits of data.
void decode_bitstream(int line_number, int num_bytes, const uint8_t *bytes) {

    //bit_offset: Tracks our position in the bitstream (in bits)
    //integer_index: Tracks how many integers we've decoded on this line
    int bit_offset = 0;
    int integer_index = 1;


     //We'll decode integers as long as there are
     //at least 5 bits remaining to read length (L).
    while ((bit_offset + 5) <= (num_bytes * 8)) {
        //Extract first 5 bits to determine L (length in bits of next integer). */
        int L = 0;
        for (int i = 0; i < 5; i++) {
            int bit_position = bit_offset + i;
            int byte_pos = bit_position / 8;           // Which byte?
            int bit_pos = 7 - (bit_position % 8);      // Position within that byte (big-endian)
            L = (L << 1) | ((bytes[byte_pos] >> bit_pos) & 1);
        }

        //Advance our offset past these 5 bits.
        bit_offset += 5;


         //If L is zero or if there aren't enough bits left to read L bits,
         //we stop decoding further integers from this line.
        if (L == 0 || (bit_offset + L) > (num_bytes * 8)) {
            break;
        }

        //Extract the next L bits as a signed 32-bit integer.
        int32_t result = 0;
        for (int i = 0; i < L; i++) {
            int bit_position = bit_offset + i;
            int byte_pos = bit_position / 8;
            int bit_pos = 7 - (bit_position % 8);
            result = (result << 1) | ((bytes[byte_pos] >> bit_pos) & 1);
        }

        // Advance the bit offset by L bits.
        bit_offset += L;

         //If the integer is negative (the top bit of L-bit integer is 1),
         //we sign-extend it by subtracting 2^L from its value.
        if (result & (1 << (L - 1))) {
            result |= -(1 << L);
        }

        //Print the decoded integer for this line.
        printf("Line %d, integer %d: %d\n", line_number, integer_index, result);
        integer_index++;
    }
}

int main() {
    int N;
    scanf("%d", &N);


    //We read N lines, each line having B bytes of data.
    //Then we decode all integers in that bitstream.
    for (int i = 1; i <= N; i++) {
        int B;
        scanf("%d", &B);


         //Dynamically create an array to store the B bytes
         //read in hexadecimal form.
        uint8_t bytes[B];
        for (int j = 0; j < B; j++) {
            scanf("%hhx", &bytes[j]);
        }

        //Decode all integers found in these B bytes.
        decode_bitstream(i, B, bytes);
    }

    return 0;
}
