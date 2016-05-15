#include <stdio.h>
#include <string.h>

int validway[11][11][4][4]; // 0->N, 1->S, 2->W, 3->E
//i, j, how come, to
int validpoint[11][11][4];

typedef struct _point{
    int i;
    int j;
    int k;
    int now;
    int pre;
}point;

point q[50000]; // queue
int qs; // start
int qe; // end

int targeti;
int targetj;
int starti;
int startj;
int startk;

void clone(int i, int j){
    q[i].i = q[j].i;
    q[i].j = q[j].j;
    q[i].k = q[j].k;
}

void push(int i, int j, int k, int pre){
    q[qe].i = i;
    q[qe].j = j;
    q[qe].k = k;
    q[qe].now = qe;
    q[qe].pre = pre;
    qe  = (qe+1)%50000;
}

point pop(){
    int t = qs;
    qs = (qs+1)%50000;
    return q[t];
}

void set(){
    int i, j, k, l;
    for(i = 0; i < 11; i++){
        for(j = 0; j < 11; j++){
            for(k = 0; k < 4; k++){
                validpoint[i][j][k] = 0;
                for(l = 0; l < 4; l++)
                    validway[i][j][k][l] = 0;
            }
        }
    }
    qs = 0;
    qe = 0;
}

void print(int n){
    int path[500][2];
    int pathn = 0;
    while(1){
        path[pathn][0] = q[n].i;
        path[pathn][1] = q[n].j;
        pathn++;
        n = q[n].pre;
        if(n == -1){
            path[pathn][0] = starti;
            path[pathn][1] = startj;
            break;
        }
    }
    int i;
    int nl = 1;
    printf("  ");
    for(i = pathn; i >= 0; i--){
        printf("(%d,%d)%s", path[i][0], path[i][1], (i == 0) ? "\n" : (nl%10) ? " " : "\n  ");
        nl++;
    }
}

void bfs(){
    int diri[4] = {-1, 1, 0, 0};
    int dirj[4] = {0, 0, -1, 1};
    push(starti+diri[startk], startj+dirj[startk], startk, -1);
    while(qs != qe){
        point temp = pop();
        if(targeti == temp.i && targetj == temp.j){
            print(temp.now);
            return;
        }
        if(validpoint[temp.i][temp.j][temp.k] == 1) continue;
        validpoint[temp.i][temp.j][temp.k] = 1;
        if(validway[temp.i][temp.j][temp.k][0] == 1)
            push(temp.i-1, temp.j, 0, temp.now);
        if(validway[temp.i][temp.j][temp.k][1] == 1)
            push(temp.i+1, temp.j, 1, temp.now);
        if(validway[temp.i][temp.j][temp.k][2] == 1)
            push(temp.i, temp.j-1, 2, temp.now);
        if(validway[temp.i][temp.j][temp.k][3] == 1)
            push(temp.i, temp.j+1, 3, temp.now);
    }
    printf("  No Solution Possible\n");
}


int main(){
    char name[100];
    while(scanf("%s", name), strcmp(name, "END")){
        set();
        char dir;

        scanf("%d %d %c %d %d", &starti, &startj, &dir, &targeti, &targetj);
        startk = (dir == 'N') ? 0 : (dir == 'S') ? 1 : (dir == 'W') ? 2 : 3;

        int a, b, i;
        while(scanf("%d", &a), a != 0){
            scanf("%d", &b);
            char fourway[10];
            while(scanf("%s", fourway), fourway[0]!='*'){
                if(fourway[0] == 'N'){
                    for(i = 1; fourway[i]!='\0'; i++){
                        if(fourway[i] == 'F'){
                            validway[a][b][0][0] = 1;
                        } else if(fourway[i] == 'L'){
                            validway[a][b][0][2] = 1;
                        } else if(fourway[i] == 'R'){
                            validway[a][b][0][3] = 1;
                        }
                    }
                } else if(fourway[0] == 'S'){
                    for(i = 1; fourway[i]!='\0'; i++){
                        if(fourway[i] == 'F'){
                            validway[a][b][1][1] = 1;
                        } else if(fourway[i] == 'L'){
                            validway[a][b][1][3] = 1;
                        } else if(fourway[i] == 'R'){
                            validway[a][b][1][2] = 1;
                        }
                    }
                } else if(fourway[0] == 'W'){
                    for(i = 1; fourway[i]!='\0'; i++){
                        if(fourway[i] == 'F'){
                            validway[a][b][2][2] = 1;
                        } else if(fourway[i] == 'L'){
                            validway[a][b][2][1] = 1;
                        } else if(fourway[i] == 'R'){
                            validway[a][b][2][0] = 1;
                        }
                    }
                } else if(fourway[0] == 'E'){
                    for(i = 1; fourway[i]!='\0'; i++){
                        if(fourway[i] == 'F'){
                            validway[a][b][3][3] = 1;
                        } else if(fourway[i] == 'L'){
                            validway[a][b][3][0] = 1;
                        } else if(fourway[i] == 'R'){
                            validway[a][b][3][1] = 1;
                        }
                    }
                }
            }
        }
        printf("%s\n", name);
        bfs();
    }
    return 0;
}
