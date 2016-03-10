#include <stdio.h>


void clean(int *a){
    int i;
    for(i = 1; i <= a[0]; i++){
        if(a[i] >= 10){
            a[i+1] += a[i]/10;
            a[i] %= 10;
            if(i == a[0])a[0]++;
        }
    }
}

void add(int *a, int *b, int *c){
    int i;
    for(i = 1; i <= a[0] || i <= b[0]; i++){
        c[i] = a[i] + b[i];
    }
    c[0] = (a[0] > b[0]) ? a[0] : b[0];
    clean(c);
}

void mul(int *a, int *b, int *c){
    int i;
    for(i = 1; i <= a[0]; i++){
        int j;
        for(j = 1; j <= b[0]; j++){
            c[i+j-1] += a[i] * b[j];
        }
    }
    c[0] = a[0] + b[0] - 1;
    clean(c);
}

int main(){
    int n;
    while(scanf("%d", &n)!=EOF){
        int a[100000] = {0}, b[100000] = {0}, c[100000] = {0};
        printf("%d!\n", n);
        a[0] = 1;
        a[1] = 1;
        b[0] = 1;
        b[1] = 1;
        int i;
        for(i = 0; i < n; i++){
            mul(a, b, c);
            a[1]++;
            clean(a);
            int j;
            b[0] = c[0];
            c[0] = 0;
            for(j = 1; j <= b[0]; j++){
                b[j] = c[j];
                c[j] = 0;
            }
        }
        for(i = b[0]; i > 0; i--)
            printf("%d", b[i]);
        printf("\n");
    }
    return 0;
}

