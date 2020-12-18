#include <stdio.h>
#include <stdlib.h>
#include <math.h>

unsigned int division(unsigned int dividend, unsigned int divisor);
unsigned long long int division3(unsigned long long int dividend, unsigned long long int divisor);
unsigned int get_digit(unsigned int n);
unsigned int countBits(unsigned int number);
void polyExpress(unsigned long long int x);
int isPrimPoly(unsigned long long int *dividend, unsigned long long int divisor);

int main(void){
    unsigned long long int irreducible[8000] = {0b10, 0b11};
    int index = 2;
    int j;
    unsigned int ans = 0;
    unsigned long long int Xn[100] = {};
    unsigned long long int tmp;

    // for loop to create (X^n - 1) array
    for(unsigned long long int i=0; i<100; i++){
        tmp = 1;
        Xn[i] = (tmp << (i+1)) + 1;
        printf("%llu\n", Xn[i]);
    }

    for(unsigned int i=4; i < 520; i++){
        j = 0;
        while(j<index){
            // ans = division3(i, irreducible[j]);
            // printf("%d ", ans);
            if(division3(i, irreducible[j]) == 0) break;
            // printf("%d\n", j);
            j++;
        }
        if(j == index){
            irreducible[index] = i;
            index++;
            // printf("index %d", index);
        }
        
        
    }
    printf("\nindex: %u\n", index);
    // printf("%d\n", irreducible[0]);
    for(int k=0; k<index; k++){
        // printf("%d\n", irreducible[k]);
        polyExpress(irreducible[k]);
        if(isPrimPoly(Xn, irreducible[k]) == 1){
            printf("^Primitive polynomial\n");
        }

        // int degree = countBits(irreducible[k]) - 1;
        // int n = (int)pow(2.0, (double)degree) - 1;
        // if(division3(Xn[n-1], irreducible[k]) == 0){
        //     printf("p(X) divides X^%d + 1\n", n);
        //     for(int l=degree; l<n-1; l++){
        //         printf("%d\n", l);
        //         if(isPrimPoly(Xn[l-1], irreducible[k]) != 0) {
        //             continue;
        //         } else {
        //             break;
        //         }
        //         printf("^ Prime Polynomial\n");

        //     }
        // }
        

    }
    
    
    printf("\nindex: %u\n", index);
    
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

    for(unsigned int i=diff; i>1; i--) {
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


unsigned long long int division3(unsigned long long int dividend, unsigned long long int divisor){
    unsigned int dividend_digit = countBits(dividend);
    unsigned int divisor_digit = countBits(divisor);
    // printf("dividend %d divisor %d\n", dividend_digit, divisor_digit);
    
    unsigned int diff = dividend_digit - divisor_digit;
    // printf("shift%u", divident_shift);
    unsigned long long int xor = (dividend >> diff) ^ divisor;
    unsigned long long int remainder = (xor << 1) + ((dividend >> (diff-1)) & 1);
    unsigned long long int quotient = 1;

    for(unsigned int i=diff; i>0; i--) {
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
    printf("\n");
}

int isPrimPoly(unsigned long long int *dividend, unsigned long long int divisor) {
    unsigned int degree = countBits(divisor) - 1;
    unsigned int n = (unsigned int)pow(2.0, (double)degree) - 1;
    // printf("degree: %d, n: %d\n", degree, n);
    // printf("%lld", dividend[n-]);
    if(division3(dividend[n-1], divisor) != 0){
        // printf("%lld %lld", dividend[n-1], divisor);
        return 0;
    } else {
        for(unsigned int i=degree; i<n-1; i++){
            // printf("%d\n", i);
            if(division3(dividend[i], divisor) == 0){
                return 0;
                break;
            }
            
        }return 1;
    }
}