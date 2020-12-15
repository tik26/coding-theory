#include <stdio.h>
#include <stdlib.h>
#include <math.h>

unsigned int division(unsigned int dividend, unsigned int divisor);
unsigned int division3(unsigned int dividend, unsigned int divisor);
unsigned int get_digit(unsigned int n);
int int_bits(unsigned int n);
int bit_length(unsigned int n);
unsigned countBits(unsigned int number);
int logn(int base, double antilog);

int main(void){
    unsigned int irreducible[300000] = {0b10, 0b11};
    // ans = division(0b1001110, 0b1011);
    int index = 2;
    int j;
    unsigned int ans = 0;
    for(unsigned int i=4; i < 10000000; i++){
        j = 0;
        while(j<index){
            ans = division3(i, irreducible[j]);
            // printf("%d ", ans);
            if(ans == 0) break;
            // printf("%d\n", j);
            j++;
        }
        if(j == index){
            irreducible[index] = i;
            index++;
            // printf("index %d", index);
        }
        // for(int j=0; j<index; j++){
        //     printf("i: %d, j: %d", i, j);
        //     // if((division3(i, irreducible[j]) & 0) == 0){
        //     //     printf("%d", i);
        //     //     irreducible[index] = i;
        //     //     // printf("%d", i);
        //     //     index++;
        //     // }
        //     printf("Final ans: %d\n", division3(i, irreducible[j]));
            
        // }
        // index = index2;
        
    }
    printf("\nindex: %u\n", index);
    // printf("%d\n", irreducible[0]);
    for(int k=0; k<index; k++){
        printf("%d\n", irreducible[k]);
    }
    
    
    return 0;
}

unsigned int division(unsigned int dividend, unsigned int divisor){
    unsigned int dividend_digit = countBits(dividend);
    unsigned int divisor_digit = countBits(divisor);
    // printf("dividend %d divisor %d\n", dividend_digit, divisor_digit);
    
    unsigned int diff = dividend_digit - divisor_digit;
    unsigned int divident_shift = dividend >> diff;
    // printf("shift%u", divident_shift);
    unsigned int xor = divident_shift ^ divisor;
    unsigned int remainder = (xor << 1) + ((dividend >> (diff-1)) & 1);
    unsigned int quotient;

    for(int i=diff; i>1; i--) {
        printf("%d\n", xor);
        printf("%d\n", remainder);
        
        if(remainder >= divisor){
            xor = remainder ^ divisor;
            remainder = (xor << 1) + ((dividend >> (i-2)) & 1);
            printf("round%d remainder >= divisor\n", i);
        } else {
            remainder = (remainder << 1) + ((dividend >> (i-2)) & 1);
            printf("round%d\n", i);
        }
    }
    

    return remainder;
}

// unsigned int division2(unsigned int dividend, unsigned int divisor){
//     unsigned int dividend_digit = countBits(dividend);
//     unsigned int divisor_digit = countBits(divisor);
//     // printf("dividend %d divisor %d\n", dividend_digit, divisor_digit);
    
//     unsigned int diff = dividend_digit - divisor_digit;
//     unsigned int divident_shift = dividend >> diff;
//     // printf("shift%u", divident_shift);
//     unsigned int xor = divident_shift ^ divisor;
//     unsigned int remainder = dividend;
//     unsigned int quotient;

//     for(int i=diff+1; i>0; i--) {
//         xor = (remainder >> (i-1)) ^ divisor;
//         remainder = (xor << 1) + ((dividend >> (i-2)) & 1);
//         printf("%d\n", xor);
//         printf("%d\n", remainder);
        
//         if(remainder >= divisor){
//             xor = remainder ^ divisor;
//             remainder = (xor << 1) + ((dividend >> (i-2)) & 1);
//             printf("round%d remainder >= divisor\n", i);
//         } else {
//             remainder = (remainder << 1) + ((dividend >> (i-2)) & 1);
//             printf("round%d\n", i);
//         }
//     }
    

//     return remainder;
// }

unsigned int division3(unsigned int dividend, unsigned int divisor){
    unsigned int dividend_digit = countBits(dividend);
    unsigned int divisor_digit = countBits(divisor);
    // printf("dividend %d divisor %d\n", dividend_digit, divisor_digit);
    
    unsigned int diff = dividend_digit - divisor_digit;
    // printf("shift%u", divident_shift);
    unsigned int xor = (dividend >> diff) ^ divisor;
    unsigned int remainder = (xor << 1) + ((dividend >> (diff-1)) & 1);
    unsigned int quotient = 1;

    for(int i=diff; i>0; i--) {
        // printf("%d\n", xor);
        // printf("%d\n", remainder);
        
        if(countBits(remainder) == divisor_digit){
            xor = remainder ^ divisor;
            remainder = (xor << 1) + ((dividend >> (i-2)) & 1);
            // printf("round%d remainder >= divisor\n", i);
            quotient = (quotient << 1) + 1;
        } else {
            remainder = (remainder << 1) + ((dividend >> (i-2)) & 1);
            // printf("round%d\n", i);
            quotient <<= 1;
        }
    }
    

    return remainder;
}

unsigned int get_digit(unsigned int n){
    char s[32];
    return sprintf(s, "%u", n);
}

/*--- unsigned型のビット数を返却 ---*/
int int_bits(unsigned int n)
{
    int count  = 0;
    unsigned int x = ~n;

    while (x) {
        if (x & 1U) count++;
        x >>= 1;
    }
    return count;
}

int bit_length(unsigned int n) {
    int count = 0;
    unsigned int check = ~0U;
    while(check) {
        if((n | check) != 0) count++;
        n >>= 1;
    }
    return count;
}

int logn(int base, double antilog) {
    return log(antilog) / log((double)base);
}


unsigned countBits(unsigned int number) 
{       
      // log function in base 2  
      // take only integer part 
      return (int)log2(number)+1;
    //   return logn(2, number+1);
}