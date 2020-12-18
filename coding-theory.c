#include <stdio.h>
#include <stdlib.h>
#include <math.h>

unsigned long long int division(unsigned long long int dividend, unsigned long long int divisor);
unsigned int countBits(unsigned int number);
void polyExpress(unsigned long long int x);
int isPrimPoly(unsigned long long int irreducible);

int main(void){
    unsigned long long int irreducible[500000] = {0b10, 0b11};
    unsigned long long int j, index = 2;
    unsigned long long int tmp;

    for(unsigned long long int i=4; i < 100; i++){
        j = 0;
        while(j<index){
            if(division(i, irreducible[j]) == 0) break;
            j++;
        }
        if(j == index){
            irreducible[index] = i;
            index++;
        }        
    }

    // printf("\nindex: %u\n", index);
    for(unsigned long long int k=0; k<index; k++){
        polyExpress(irreducible[k]);
        if(isPrimPoly(irreducible[k]) == 1){
            printf("  Primitive polynomial");
        }
        printf("\n");
    }
    return 0;
}

unsigned long long int division(unsigned long long int dividend, unsigned long long int divisor){
    unsigned int dividend_digit = countBits(dividend);
    unsigned int divisor_digit = countBits(divisor);    
    
    unsigned int diff = dividend_digit - divisor_digit;
    
    unsigned long long int xor = (dividend >> diff) ^ divisor;
    unsigned long long int remainder = (xor << 1) + ((dividend >> (diff-1)) & 1);
    unsigned long long int quotient = 1;

    for(unsigned int i=diff; i>0; i--) {        
        if(countBits(remainder) == divisor_digit){
            xor = remainder ^ divisor;
            remainder = (xor << 1) + ((dividend >> (i-2)) & 1);
            quotient = (quotient << 1) + 1;
        } else {
            remainder = (remainder << 1) + ((dividend >> (i-2)) & 1);
            quotient <<= 1;
        }
    }
    

    return remainder;
}

unsigned int countBits(unsigned int number) 
{       
      // log function in base 2  
      // take only integer part 
      return (unsigned int)log2(number)+1;
}

void polyExpress(unsigned long long int x) {
    for(unsigned int i=0; i<countBits(x); i++){
        if(((x >> i) & 1) == 1){
            printf("X^%d", i);
            if(i != countBits(x)-1){
                printf(" + ");
            }
        }
    }
    // if(isPrimPoly(x) == 1){
    //     FILE *output;
    //     output = fopen("result.txt", "a");
    //     fprintf(output, )
    // }
    // printf("\n");
}

int isPrimPoly(unsigned long long int irreducible){
    unsigned int degree = countBits(irreducible) - 1;
    unsigned int n = (unsigned int)pow(2.0, (double)degree) - 1;
    unsigned long long int alpha[n];
    for(int i=0; i<=degree; i++){
        alpha[i] = (1 << i);
    }

    alpha[degree] = (irreducible ^ alpha[degree]);
    
    for(int i=degree+1; i<n; i++){
        alpha[i] = alpha[i-1] << 1;
        if((alpha[i]^irreducible) == 1){
            return 0;
            break;
        }
        if(countBits(alpha[i]) == (degree+1)){
            alpha[i] = alpha[i] ^ ((1 << degree) + alpha[degree]);
        }
    }
    return 1;
}