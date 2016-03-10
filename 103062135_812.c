#include <stdio.h>
#include <stdlib.h>

int ans[1010] = {0};
int valid[51][21] = {0};

void combine(int sum, int n, int max){
    if(n == max){
        ans[sum] = 1;
        return;
    } else {
        int i;
        for(i = 0; valid[n][i] || i == 0; i++){
            combine(sum+valid[n][i], n+1, max);
        }
    }
}

int main(){

    int n;
    int yard_num = 1;
    while(scanf("%d", &n), n > 0){
        if(yard_num > 1)printf("\n");
        printf("Workyards %d\n", yard_num++);
        int i, input[51][21] = {0};
        for(i = 0; i < 51; i++){
            int j;
            for(j = 0; j < 21; j++)
                valid[i][j] = 0;
        }
        for(i = 0; i < 1010; i++)
            ans[i] = 0;


        for(i = 0; i < n; i++){
            int j, prul;
            scanf("%d", &prul);
            for(j = 0; j < prul; j++)
                scanf("%d", input[i]+j);
        }
        int profit = 0;
        for(i = 0; i < n; i++){
            int j;
            int sum = 0, max = 0;
            for(j = 0; input[i][j]; j++){
                sum += 10-input[i][j];
                if(sum > max)max = sum;
            }
            profit += max;
            int valid_n = 0;
            if(max == 0)valid[i][valid_n++] = 0;
            sum = 0;
            for(j = 0; input[i][j]; j++){
                sum += 10-input[i][j];
                if(sum == max)valid[i][valid_n++] = j+1;
            }
        }
        printf("Maximum profit is %d.\n", profit);
        printf("Number of pruls to buy:");
        combine(0, 0, n);
        int ten = 10;
        for(i = 0; i < 1001 && ten; i++)
            if(ans[i]){
                printf(" %d", i);
                ten--;
            }
        printf("\n");

    }
    return 0;
}
