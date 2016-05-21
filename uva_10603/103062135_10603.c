#include <stdio.h>
#include <string.h>
#define MAX ((unsigned)-1>>1)

int status[201][201];
int used[201][201];
int possible[1000][2];
int possiblen;
int amax, bmax, cmax;

void init(){
    int i, j;
    for(i = 0; i < 201; i++)
        for(j = 0; j < 201; j++)
            status[i][j] = MAX;
    memset(used, 0, sizeof(used));
    memset(possible, 0, sizeof(possible));
    possiblen = 0;
}

void dijkstra(){
    int min = -1;
    int i;
    for(i = 0; i < possiblen; i++){
        if(!used[possible[i][0]][possible[i][1]])
            if(min == -1 || status[possible[min][0]][possible[min][1]] > status[possible[i][0]][possible[i][1]])
                min = i;
    }
    if(min == -1)return;
    int a = possible[min][0];
    int b = possible[min][1];
    int c = cmax - a - b;
    used[a][b] = 1;
    possible[min][0] = possible[possiblen-1][0];
    possible[min][1] = possible[possiblen-1][1];
    possiblen--;
    if(bmax - b > a){
        if(status[a][b] + a < status[0][a+b]){
            status[0][a+b] = status[a][b] + a;
            possible[possiblen][0] = 0;
            possible[possiblen][1] = a+b;
            possiblen++;
        }
    } else {
        if(status[a][b] + (bmax-b) < status[a-(bmax-b)][bmax]){
            status[a-(bmax-b)][bmax] = status[a][b] + (bmax-b);
            possible[possiblen][0] = a-(bmax-b);
            possible[possiblen][1] = bmax;
            possiblen++;
        }
    }

    if(cmax - c > a){
        if(status[a][b] + a < status[0][b]){
            status[0][b] = status[a][b] + a;
            possible[possiblen][0] = 0;
            possible[possiblen][1] = b;
            possiblen++;
        }
    } else {
        if(status[a][b] + (cmax-c) < status[a-(cmax-c)][b]){
            status[a-(cmax-c)][b] = status[a][b] + (cmax-c);
            possible[possiblen][0] = a-(cmax-c);
            possible[possiblen][1] = b;
            possiblen++;
        }
    }

    if(amax - a > b){
        if(status[a][b] + b < status[a+b][0]){
            status[a+b][0] = status[a][b] + b;
            possible[possiblen][0] = a+b;
            possible[possiblen][1] = 0;
            possiblen++;
        }
    } else {
        if(status[a][b] + (amax-a) < status[amax][b-(amax-a)]){
            status[amax][b-(amax-a)] = status[a][b] + (amax-a);
            possible[possiblen][0] = amax;
            possible[possiblen][1] = b-(amax-a);
            possiblen++;
        }
    }

    if(cmax - c > b){
        if(status[a][b] + b < status[a][0]){
            status[a][0] = status[a][b] + b;
            possible[possiblen][0] = a;
            possible[possiblen][1] = 0;
            possiblen++;
        }
    } else {
        if(status[a][b] + (cmax-c) < status[a][b-(cmax-c)]){
            status[a][b-(cmax-c)] = status[a][b] + (cmax-c);
            possible[possiblen][0] = a;
            possible[possiblen][1] = b-(cmax-c);
            possiblen++;
        }
    }

    if(amax - a > c){
        if(status[a][b] + c < status[a+c][b]){
            status[a+c][b] = status[a][b] + c;
            possible[possiblen][0] = a+c;
            possible[possiblen][1] = b;
            possiblen++;
        }
    } else {
        if(status[a][b] + (amax-a) < status[amax][b]){
            status[amax][b] = status[a][b] + (amax-a);
            possible[possiblen][0] = amax;
            possible[possiblen][1] = b;
            possiblen++;
        }
    }

    if(bmax - b > c){
        if(status[a][b] + c < status[a][b+c]){
            status[a][b+c] = status[a][b] + c;
            possible[possiblen][0] = a;
            possible[possiblen][1] = b+c;
            possiblen++;
        }
    } else {
        if(status[a][b] + (bmax-b) < status[a][bmax]){
            status[a][bmax] = status[a][b] + (bmax-b);
            possible[possiblen][0] = a;
            possible[possiblen][1] = bmax;
            possiblen++;
        }
    }
    dijkstra();
}


int main(){
    int t;
    scanf("%d", &t);
    for(; t > 0; t--){
        init();
        int target;
        scanf("%d%d%d%d", &amax, &bmax, &cmax, &target);
        status[0][0] = 0;
        possible[0][0] = 0;
        possible[0][1] = 0;
        possiblen++;
        dijkstra();
        int ans = 0, anscost = MAX;
        int i, j;
        for(i = 0; i <= amax; i++)
            for(j = 0; j <= bmax; j++)
                if(status[i][j] != MAX){
                    if(i == target || j == target || cmax-i-j == target){
                        if(status[i][j] < anscost || ans != target)
                            anscost = status[i][j];
                        ans = target;
                    } else if(ans != target){
                        if(i >= ans && i < target){
                            if(i > ans || (i == ans && status[i][j] < anscost))
                                anscost = status[i][j];
                            ans = i;
                        }
                        if(j >= ans && j < target){
                            if(j > ans || (j == ans && status[i][j] < anscost))
                                anscost = status[i][j];
                            ans = j;
                        }
                        if(cmax-i-j >= ans && cmax-i-j < target){
                            if(cmax-i-j > ans || (cmax-i-j == ans && status[i][j] < anscost))
                                anscost = status[i][j];
                            ans = cmax-i-j;
                        }
                    }
                }
        printf("%d %d\n", anscost, ans);
    }
}
