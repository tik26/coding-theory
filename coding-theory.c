#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

unsigned long long division(unsigned long long dividend, unsigned long long divisor);
unsigned long long countBits(unsigned long long number);
void polyExpress(unsigned long long x);
int isPrimPoly(unsigned long long irreducible);

int main(void){
    unsigned long long irreducible[1000000] = {0b10, 0b11};
    unsigned long long j, index = 2;
    unsigned long long tmp;
    
    printf("Generating irreducible polynomials from degree 1 to 20\n");
    for(unsigned long long i=4; i < 4294967295; i++){
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
    
    for(unsigned long long k=index-30; k<index; k++){
        polyExpress(irreducible[k]);
        // if(isPrimPoly(irreducible[k]) == 1){
        //     printf("  Primitive polynomial");
        // }
        printf("\n");
    }
    return 0;
}

unsigned long long division(unsigned long long dividend, unsigned long long divisor){
    unsigned long long dividend_digit = countBits(dividend);
    unsigned long long divisor_digit = countBits(divisor);    
    
    unsigned long long diff = dividend_digit - divisor_digit;
    
    unsigned long long xor = (dividend >> diff) ^ divisor;
    unsigned long long remainder = (xor << 1) + ((dividend >> (diff-1)) & 1);
    unsigned long long quotient = 1;

    for(unsigned long long i=diff; i>0; i--) {        
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

unsigned long long countBits(unsigned long long number) 
{       
      return (unsigned long long)log2(number)+1;
}

void polyExpress(unsigned long long x) {
    for(unsigned long long i=0; i<countBits(x); i++){
        if(((x >> i) & 1) == 1){
            printf("X^%d", i);
            if(i != countBits(x)-1){
                printf(" + ");
            }
        }
    }
}

int isPrimPoly(unsigned long long irreducible){
    unsigned long long degree = countBits(irreducible) - 1;
    unsigned long long n = (unsigned long long)pow(2.0, (double)degree) - 1;
    unsigned long long alpha[n];
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