#include <stdio.h>

int notprime[50000];
int prime[4000];

void makeprime(){
    int i;
    for(i = 2; i < 50000; i++){
        int j;
        if(notprime[i] == 0){
            for(j = i*2; j < 50000; j+=i){
                notprime[j] = 1;
            }
        }
    }
    int prime_n = 0;
    for(i = 2; prime_n < 4000; i++)
        if(notprime[i] == 0)
            prime[prime_n++] = i;
}

int man[3600];

int kill(int n){
    int i;
    man[0] = 1;
    for(i = 1; i < n; i++)
        man[i] = i+1;
    man[n] = 1;
    int now = 0;
    for(i = 0; i < n - 1; i++){
        int j;
        int nexttime = (prime[i]%(n - i) == 0) ? n - i : prime[i]%(n - i);
        for(j = 0; j < nexttime - 1; j++){
            now = man[now];
        }
        man[now] = man[man[now]];
    }
    return now;
}

int main(){
    makeprime();
    int input;
    while(scanf("%d", &input)!=EOF && input > 0){
        if(input == 1)printf("1\n");
        else printf("%d\n", kill(input));
    }
    return 0;
}
