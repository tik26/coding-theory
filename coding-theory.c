#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

unsigned int division(unsigned int dividend, unsigned int divisor);
unsigned int countBits(unsigned int number);
void polyExpress(unsigned int x);
int isPrimPoly(unsigned int irreducible);

FILE *output;


int main(void){
    unsigned int irreducible[220000] = {0b10, 0b11};
    unsigned int j, index = 2;
    unsigned int tmp;

    for(unsigned int i=4; i < 2097152; i++){
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
    for(unsigned int k=0; k<index; k++){
        polyExpress(irreducible[k]);
        output = fopen("ans.txt", "a");
        if(isPrimPoly(irreducible[k]) == 1){
            printf("  Primitive polynomial");
            fprintf(output, "  Primitive polynomial");
        }
        printf("\n");
        fprintf(output, "\n");
        fclose(output);
    }
    return 0;
}

unsigned int division(unsigned int dividend, unsigned int divisor){
    unsigned int dividend_digit = countBits(dividend);
    unsigned int divisor_digit = countBits(divisor);    
    
    unsigned int diff = dividend_digit - divisor_digit;
    
    unsigned int xor = (dividend >> diff) ^ divisor;
    unsigned int remainder = (xor << 1) + ((dividend >> (diff-1)) & 1);
    unsigned int quotient = 1;

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

void polyExpress(unsigned int x) {
    // char ans[100] = "";
    // char tmp[100];
    output = fopen("ans.txt", "a");
    for(unsigned int i=0; i<countBits(x); i++){
        char ans[100] = "";
        char tmp[100];
        if(((x >> i) & 1) == 1){
            printf("X^%d", i);
            sprintf(tmp, "X^%d", i);
            strcat(ans, tmp);
            if(i != countBits(x)-1){
                printf(" + ");
                strcat(ans, " + ");
            }
            fprintf(output, ans);
        }
        // strcat
        
    }
    fclose(output);
}

int isPrimPoly(unsigned int irreducible){
    unsigned int degree = countBits(irreducible) - 1;
    unsigned int n = (unsigned int)pow(2.0, (double)degree) - 1;
    unsigned int alpha[n];
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