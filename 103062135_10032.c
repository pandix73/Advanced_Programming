#include <stdio.h>

void clean(int *a){
    int i;
    for(i = 1; i <= a[0]; i++){
        a[i+1] += a[i] / 10;
        a[i] %= 10;
        if(i == a[0] && a[i+1] != 0)a[0]++;
    }
    while(a[a[0]] == 0 && a[0] != 1)a[0]--;
}

void addint(int *a, int b){
    a[1] += b;
    clean(a);
}

void mulint(int *a, int b){
    int i;
    for(i = 1; i <= a[0]; i++)
        a[i] *= b;
    clean(a);
}

void sub(int *a, int *b){
    int i;
    for(i = 1; i <= a[0]; i++){
        a[i] -= b[i];
        if(a[i] < 0){
            a[i] += 10;
            a[i+1] --;
        }
    }
    clean(a);
}

void clone(int *a, int *b){
    int i;
    for(i = b[0]; i >= 0; i--)
        a[i] = b[i];
}

int cmp(int *a, int *b){
    if(a[0] != b[0]) return (a[0] > b[0]) ? 1 : -1;
    int i;
    for(i = a[0]; i > 0; i++)
        if(a[i] != b[i]) return (a[i] > b[i]) ? 1 : -1;
    return 0;
}

void print(int *a){
    int i;
    for(i = a[0]; i > 0; i--)
        printf("%d", a[i]);
    printf("\n");
}

int sqr(int *a, int *b){
    int done[501] = {0}, now;
    done[0] = 1;
    int i;
    for(i = a[0]; i > 0; i-=2){
        if(i%2){
            now = a[i];
            i++;
        } else {
            now = a[i]*10+a[i-1];
        }
        addint(done, now);
        int j;
        for(j = 9; j >= 0; j--){
            int temp[501] = {0};
            clone(temp, b);
            mulint(temp, 2);
            addint(temp, j);
            mulint(temp, j);
            if(cmp(temp, done) <= 0){
                mulint(b, 10);
                addint(b, j);
                sub(done, temp);
                mulint(done, 100);
                break;
            }
        }
    }
}

int main(){
    int a[100] = {3, 1, 2, 1}, b[100] = {0};
    b[0] = 2;
    sqr(a, b);
    print(b);
    return 0;
}
