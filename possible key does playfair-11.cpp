#include <stdio.h>
#include <math.h>

int main() {
    unsigned long long factorial = 1;
    int n;
    printf("enter the number:");
    scanf("%d",&n);
    for (int i = 1; i <= n; i++) {
        factorial *= i;
    }
    double powerOf2 = log2(factorial);
    printf("Approximate number of possible keys: 2^%.2f\n", powerOf2);

    return 0;
}

