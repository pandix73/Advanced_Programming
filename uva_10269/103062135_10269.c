#include <stdio.h>
#define MAX ((unsigned)-1>>1)

int map[101][101];
int used[101][12];
int best[101][12];

int v;
int c;

int boot_dis;
int boot_time;

void init(){
    int i, j;
    for(i = 0; i < 101; i++){
        for(j = 0; j < 101; j++){
            if(j < 12){
                used[i][j] = 0;
                best[i][j] = MAX;
            }
            map[i][j] = (i == j) ? 0 : MAX;
        }
    }
}

int min(int a, int b){
    return (a > b) ? b : a;
}

void make_boot(){
    int i, j, k;
    for(k = 0; k < v; k++)
        for(i = 0; i < v+c; i++)
            for(j = 0; j < v+c; j++)
                if(map[i][k] != MAX && map[k][j] != MAX)
                    map[i][j] = min(map[i][j], map[i][k]+map[k][j]);
}

void make_best(){
    int i, j;
    best[v+c-1][0] = 0;
    while(1){
        int min_i = -1, min_j = -1;
        for(i = 0; i < v+c; i++)
            for(j = 0; j <= boot_time; j++)
                if(!used[i][j])
                    if(min_i == -1 || best[min_i][min_j] > best[i][j]){
                        min_i = i;
                        min_j = j;
                    }
        if(min_i == -1 || best[min_i][min_j] == MAX)return;
        used[min_i][min_j] = 1;
        for(i = 0; i < v+c; i++){
            if(i == min_i)continue;
            if(map[i][min_i] != MAX)
                best[i][min_j] = min(best[i][min_j], best[min_i][min_j] + map[i][min_i]);
            if(map[min_i][i] <= boot_dis && min_j < boot_time)
                best[i][min_j+1] = min(best[i][min_j+1], best[min_i][min_j]);
        }
    }
}

int main(){
    int t;
    scanf("%d", &t);
    for(; t > 0; t--){
        init();
        int n, i, j;
        scanf("%d%d%d%d%d", &v, &c, &n, &boot_dis, &boot_time);
        for(i = 0; i < n; i++){
            int a, b, dis;
            scanf("%d%d%d", &a, &b, &dis);
            a--;
            b--;
            map[a][b] = dis;
            map[b][a] = dis;
        }
        make_boot();
        make_best();
        int ans = MAX;
        for(i = 0; i <= boot_time; i++)
            ans = min(best[0][i] , ans);
        printf("%d\n", ans);
    }
    return 0;
}
