#include <stdio.h>
#include <string.h>

int map[5][5];
int press[5][5];
int trans[3][3];

int n, m;
int ans;

void init(){
    memset(map, 0, sizeof(map));
    memset(press, 0, sizeof(press));
    memset(trans, 0, sizeof(trans));
    ans = 0;
}

void press_button(int x, int y){
    int i, j;
    for(i = 0; i < 3; i++)
        for(j = 0; j < 3; j++)
            if(x+i-1 >= 0 && x+i-1 < n && y+j-1 >= 0 && y+j-1 < m)
                if(trans[i][j] == 1)map[x+i-1][y+j-1] = 1-map[x+i-1][y+j-1];
}

void print(){
    int i, j;
    for(i = 0; i < n; i++){
        for(j = 0; j < m; j++)
            printf("%d ", map[i][j]);
        printf("\n");
    }printf("\n");
}

int check(int x){
    if(x >= 0){
        int i, j;
        for(i = 0; i <= x; i++)
            for(j = 0; j < m; j++)
                if(map[i][j] == 0)return 0;
    }
    return 1;
}

int full(){
    int i, j;
    for(i = 0; i < n; i++)
        for(j = 0; j < m; j++)
            if(!map[i][j])return 0;
    return 1;
}

void walk(int num){
    if(ans)return;
    if(full()){
        int i, first = 1;
        for(i = 0; i < n*m; i++)
            if(press[i/m][i%m]){
                if(!first)printf(" ");
                printf("%d", i+1);
                first = 0;
            }
        printf("\n");
        ans = 1;
        return;
    }

    if(!check(num/m-2))return;

    press[num/m][num%m] = 0;
    if(num < n*m)walk(num+1);

    press_button(num/m, num%m);
    press[num/m][num%m] = 1;
    if(num < n*m)walk(num+1);
    press_button(num/m, num%m);
    press[num/m][num%m] = 0;
}

int main(){
    int t = 0;
    while(scanf("%d%d", &n, &m), n > 0 || m > 0){
        init();
        char input[5];
        int i;
        for(i = 0; i < 3; i++){
            scanf("%s", input);
            trans[i][0] = (input[0] == '*');
            trans[i][1] = (input[1] == '*');
            trans[i][2] = (input[2] == '*');
        }
        printf("Case #%d\n", ++t);
        walk(0);
        if(!ans)printf("Impossible.\n");
    }
    return 0;
}
