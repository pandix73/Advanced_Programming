#include <stdio.h>
#define MAX ((unsigned)-1>>1)

unsigned int dis[501][501];
unsigned int dis1[501];
int used[501];

void set(int n){
    int i;
    for(i = 0; i < n; i++){
        int j;
        for(j = 0; j < n; j++)
            dis[i][j] = (i == j) ? 0 : MAX;
        used[i] = 0;
        dis1[i] = MAX;
    }
    dis1[0] = 0;
}

void dijkstra(int n){
    int i;
    int min_now = -1;
    for(i = 1; i < n; i++){
        if(!used[i] && dis1[i] != MAX){
            if(min_now == -1) min_now = i;
            else if (dis1[min_now] > dis1[i]) min_now = i;
        }
    }
    if(min_now == -1)return;
    used[min_now] = 1;
    for(i = 1; i < n; i++){
        if(dis1[min_now] + dis[min_now][i] < dis1[i])
            dis1[i] = dis1[min_now] + dis[min_now][i];
    }
    dijkstra(n);
}

int main(){
    int n, m, count = 0;
    while(scanf("%d%d", &n, &m), n != 0 || m != 0){
        int i;
        set(n);
        for(i = 0; i < m; i++){
            int a, b, c;
            scanf("%d%d%d", &a, &b, &c);
            dis[a-1][b-1] = c;
            dis[b-1][a-1] = c;
            if(a == 1)dis1[b-1] = c;
            if(b == 1)dis1[a-1] = c;
        }
        dijkstra(n);
        int vmax = 0, v = 0;
        double emax = 0;
        int e1, e2;
        for(i = 0; i < n; i++){
            int j;
            for(j = i+1; j < n; j++){
                if(dis[i][j] != MAX){
                    double edgedis = (double)(dis1[i] + dis1[j] + dis[i][j])/2;
                    if(edgedis > emax){
                        emax = edgedis;
                        e1 = i;
                        e2 = j;
                    }
                }
            }
            if(dis1[i] > vmax){
                vmax = dis1[i];
                v = i;
            }
        }
        printf("System #%d\n", ++count);
        if((double)vmax >= emax)
            printf("The last domino falls after %.1f seconds, at key domino %d.\n\n", (double)vmax, v+1);
        else
            printf("The last domino falls after %.1f seconds, between key dominoes %d and %d.\n\n", emax, e1+1, e2+1);
    }
    return 0;
}
