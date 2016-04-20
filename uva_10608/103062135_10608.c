#include <stdio.h>
#include <stdlib.h>

typedef struct _node{
    int num;
    int used;
    struct _node *next;
}node;

node adjlist[30006];

int DFS(int n){
    int i;
    int max = 0;
    for(i = 1; i <= n; i++){
        if(adjlist[i].used == 0){
            adjlist[i].used = 1;
            int now = find(i);
            if(now > max)
                max = now;
        }
    }
    return max;
}

int find(int i){
    int nodes = 0;
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
    int n;
    scanf("%d", &n);
    for(; n > 0; n--){
        int num, inputn;
        int i;
        scanf("%d%d", &num, &inputn);

        for(i = 1; i <= num; i++){
            adjlist[i].num = i;
            adjlist[i].used = 0;
            adjlist[i].next = NULL;
        }

        int a, b;
        for(i = 0; i < inputn; i++){
            scanf("%d%d", &a, &b);
            node *temp = adjlist[a].next;
            adjlist[a].next = (node*)malloc(sizeof(node));
            adjlist[a].next->next = temp;
            adjlist[a].next->num = b;

            temp = adjlist[b].next;
            adjlist[b].next = (node*)malloc(sizeof(node));
            adjlist[b].next->next = temp;
            adjlist[b].next->num = a;
        }

        printf("%d\n", DFS(num));
    }

    return 0;
}
