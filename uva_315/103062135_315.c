#include <stdio.h>
#include <stdlib.h>

typedef struct _node{
    int num;
    int used;
    struct _node *next;
}node;

node adjlist[108];

int DFS(int n){
    int i;
    int total = 0;
    for(i = 1; i <= n; i++){
        if(adjlist[i].next == NULL)
            continue;
        adjlist[i].used = 1;
        int now = find(adjlist[i].next->num);
        if(now != n-1)
            total++;
        int j;
        for(j = 1; j <= n; j++)
            adjlist[j].used = 0;
    }
    return total;
}

int find(int i){
    int nodes = 0;
    adjlist[i].used = 1;
    node *now = adjlist[i].next;
    for( ; now != NULL; now = now->next){
        if(adjlist[now->num].used == 1){
            continue;
        } else {
            adjlist[now->num].used = 1;
            nodes += find(now->num);
        }
    }
    return nodes+1;
}

int main(){
    int num;
    int i;
    while(scanf("%d", &num), num!=0){
        for(i = 1; i <= num; i++){
            adjlist[i].next = NULL;
            adjlist[i].num = 0;
            adjlist[i].used = 0;
        }

        char input;
        int now;
        while(scanf("%d%c", &now, &input), now!=0){
            int k;
            if(input == '\n')
                continue;
            while(scanf("%d%c", &k, &input)){
                node *temp = adjlist[now].next;
                adjlist[now].next = (node*)malloc(sizeof(node));
                adjlist[now].next->next = temp;
                adjlist[now].next->num = k;

                temp = adjlist[k].next;
                adjlist[k].next = (node*)malloc(sizeof(node));
                adjlist[k].next->next = temp;
                adjlist[k].next->num = now;

                if(input == '\n')
                    break;
            }
        }

        printf("%d\n", DFS(num));
    }
    return 0;
}
