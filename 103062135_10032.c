#include <stdio.h>

void clean(int *a){
    int i;
    for(i = 1; i <= a[0]; i++){
        a[i+1] += a[i] / 10;
        a[i] %= 10;
        if(i == a[0] && a[i+1] != 0)a[0]++;
    }
}

void addint(int *a, int b){
    int i;
    a[1] += b;
    clean(a);
}

void mulint(int *a, int b){
    int i;
    for(i = 1; i <= a[0]; i++)
        a[i] *= b;
    clean(a);
}

int cmp(int *a, int *b){
    if(a[0] != b[0]) return (a[0] > b[0]) ? 1 : -1;
    int i;
    for(i = a[0]; i > 0; i++)
        if(a[i] != b[i]) return (a[i] > b[i]) ? 1 : -1;
    return 0;
}

int sqr(int *a, int *b){

}

int main(){
    return 0;
}
