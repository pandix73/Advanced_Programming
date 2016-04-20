#include <stdio.h>
int isprime[60000];
int primelist[10000];

void prime(){
    int i;
    for(i = 2; i < 60000; i++){
        if(isprime[i] == 0){
            int j;
            for(j = i*2; j < 60000; j+=i)
                isprime[j] = 1;
        }
    }
    int n = 0;
    for(i = 2; i < 60000; i++){
        if(isprime[i] == 0)primelist[n++] = i;
    }
}


int main(){
    prime();
    int n;
    scanf("%d", &n);
    for(; n > 0; n--){
        int start, end;
        scanf("%d %d", &start, &end);
        int totalnum = end - start + 1;
        int num[10021][50] = {0};
        int i;
        for(i = 0; primelist[i]*primelist[i] <= end && primelist[i] > 0; i++){
            int first = (start%primelist[i] > 0) ? (start/primelist[i]+1)*primelist[i] : start;
            int j;
            for(j = first; j <= end; j+=primelist[i]){
                num[j-start][++num[j-start][0]] = primelist[i];
            }
        }
        int max = 0;
        int maxnum = 0;
        for(i = 0; i < totalnum; i++){
            int j;
            int now = i + start;
            int result = 1;
            for(j = 1; j <= num[i][0]; j++){
                int pow = 1;
                while(now%num[i][j] == 0){
                    pow++;
                    now /= num[i][j];
                }
                result *= pow;
            }
            if(now > 1)result*=2;
            if(result > max){
                max = result;
                maxnum = i+start;
            }
        }
        printf("Between %d and %d, %d has a maximum of %d divisors.\n", start, end, maxnum, max);
    }

    return 0;
}
