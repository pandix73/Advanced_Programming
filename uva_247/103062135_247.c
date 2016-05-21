#include <stdio.h>
#include <string.h>

char name[30][30];
int namen;

int map[30][30];
int flag[30];

void init(){
    memset(name, 0, sizeof(name));
    memset(map, 0, sizeof(map));
    memset(flag, 0, sizeof(flag));
    namen = 0;
}

int trans(char user[]){
    int i;
    for(i = 0; i < namen; i++)
        if(strcmp(user, name[i]) == 0)
            return i;
    strcpy(name[namen], user);
    return namen++;
}

void FW(int n){
    int i, j, k;
    for(k = 0; k < n; k++)
        for(i = 0; i < n; i++)
            for(j = 0; j < n; j++)
                map[i][j] = (map[i][j] || (map[i][k] && map[k][j]));
}

int main(){
    int man, n;
    int cycle = 0;
    while(scanf("%d%d", &man, &n), man != 0 && n != 0){
        if(cycle)printf("\n");
        init();
        int i;
        for(i = 0; i < n; i++){
            char input1[30], input2[30];
            scanf("%s %s", input1, input2);
            int from = trans(input1);
            int to = trans(input2);
            map[from][to] = 1;
        }
        FW(man);
        printf("Calling circles for data set %d:\n", ++cycle);
        for(i = 0; i < man; i++){
            if(flag[i] == 0){
                flag[i] = 1;
                printf("%s", name[i]);
                int j;
                for(j = i + 1; j < man; j++){
                    if(map[i][j] && map[j][i]){
                        flag[j] = 1;
                        printf(", %s", name[j]);
                    }
                }
                printf("\n");
            }
        }
    }

    return 0;
}
