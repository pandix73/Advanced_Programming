#include <stdio.h>
#include <string.h>

int end[25] = { 1, 1, 1, 1, 1,
                0, 1, 1, 1, 1,
                0, 0, 2, 1, 1,
                0, 0, 0, 0, 1,
                0, 0, 0, 0, 0};
int now[25];

int dirx[8] = {-2, -1, 1, 2, 2, 1, -1, -2};
int diry[8] = {1, 2, 2, 1, -1, -2, -2, -1};

int cmp(int* a, int* b){
    int i, diff = 0;
    for(i = 0; i < 25; i++)
        if(a[i] != b[i])
            diff++;
    return diff/2;
}

int swap(int a, int b){
    int temp = now[a];
    now[a] = now[b];
    now[b] = temp;
}

int dfs(int limit, int step, int n){
    if(limit == step) return (cmp(now, end) == 0) ? 1 : 0;
    if(step + cmp(now, end) > limit) return 0;
    int i;
    for(i = 0; i < 8; i++){
        int x = n / 5 + dirx[i];
        int y = n % 5 + diry[i];
        if(x < 0 || x > 4 || y < 0 || y > 4)continue;
        if(now[n] != 2)printf("fuck");
        swap(x*5+y, n);
        if(dfs(limit, step+1, x*5+y) == 1) return 1;
        swap(x*5+y, n);
    }
    return 0;
}

int main(){
    int t;
    scanf("%d", &t);
    while(t--){
        int i, j, block;
        char input;
        for(i = 0; i < 5; i++)
            for(j = 0; j < 5; j++){
                scanf("%c", &input);
                if(input == ' '){
                    now[i * 5 + j] = 2;
                    block = i * 5 + j;
                } else if(input == '\n'){
                    j--;
                } else {
                    now[i * 5 + j] = input - '0';
                }
            }
        int ans = -1;
        for(i = 0; i < 11; i++){
            if(dfs(i, 0, block) == 1){
                ans = i;
                break;
            }
        }
        if(ans == -1) printf("Unsolvable in less than 11 move(s).\n");
        else printf("Solvable in %d move(s).\n", ans);
    }
    return 0;
}
