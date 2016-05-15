#include <stdio.h>
#define MAX ((unsigned long long)-1 >> 1)

int map[52][52];
long long best[52];
int used[52];
int path[52];

int start;
int end;

void set(){
    int i;
    for(i = 0; i < 52; i++){
        int j;
        for(j = 0; j < 52; j++)
            map[i][j] = 0;
        best[i] = MAX;
        used[i] = 0;
        path[i] = 53;
    }
}

int trans(char n){
    return (n <= 'z' && n >= 'a') ? n - 'a' + 26: n - 'A';
}

char itoc(int n){
    return (n < 26) ? n + 'A' : n - 26 + 'a';
}

void dijkstra(){
    int i;
    int min = -1;
    for(i = 0; i < 52; i++){
        if(!used[i] && best[i] != MAX){
            if(min == -1) min = i;
            else if (best[min] > best[i]) min = i;
        }
    }
    if(min == -1)return;
    used[min] = 1;
    for(i = 0; i < 52; i++){
        if(map[min][i])
            if(min >= 26 && (best[i] > best[min] + 1 || best[i] == best[min] + 1 && path[i] > min)){
                best[i] = best[min] + 1;
                path[i] = min;
            } else if(min < 26 && (best[i] > (best[min]*20/19 + ((best[min]%19 == 0) ? 0 : 1)) ||
                    best[i] == (best[min]*20/19 + ((best[min]%19 == 0) ? 0 : 1)) && path[i] > min)){
                best[i] = best[min]*20/19 + ((best[min]%19 == 0) ? 0 : 1);
                path[i] = min;
            }
    }
    dijkstra();
}

int main(){
    int n;
    int casen = 1;
    while(scanf("%d", &n), n > -1){
        set();
        int i;
        char a[5], b[5];
        for(i = 0; i < n; i++){
            scanf("%s%s", a, b);
            int aint = trans(a[0]);
            int bint = trans(b[0]);
            map[aint][bint] = 1;
            map[bint][aint] = 1;
        }
        long long value;
        scanf("%lld%s%s", &value, a, b);
        start = trans(a[0]);
        end = trans(b[0]);
        best[end] = value;
        dijkstra();
        printf("Case %d:\n%lld\n", casen++, best[start]);
        int temp = start;
        while(1){
            if(temp == end){
                printf("%c\n", itoc(end));
                break;
            }
            printf("%c-", itoc(temp));
            temp = path[temp];
        }
    }

    return 0;
}
