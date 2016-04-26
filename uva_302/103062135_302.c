#include <stdio.h>
#include <stdlib.h>

int input[2000];
int isdelete[2000];
int path[2000];
int deg[45];

int cmp(const void *a, const void *b){
    return *(int*)a - *(int*)b;
}

typedef struct _node{
    int destination;
    int num;
    struct _node *next;
}node;

node list[45] = {0};

int path_n = 0;
void find_node(int now_place){
    node* temp;
    for(temp = list[now_place].next; temp != NULL; temp = temp->next){
        if(isdelete[temp->num] == 0){
            isdelete[temp->num] = 1;
            find_node(temp->destination);
            path[path_n++] = temp->num;
        }
    }
    return;
}

int main(){
    int a, b;
    int start;
    while(scanf("%d%d", &a, &b), a != 0 && b != 0){
        int n = 0;
        scanf("%d", &input[n]);
        input[n] = input[n]*50*50 + a*50 + b;
        start = (a > b) ? b : a;
        while(scanf("%d%d", &a, &b), a != 0 && b != 0){
            n++;
            scanf("%d", &input[n]);
            input[n] = input[n]*50*50 + a*50 + b;
        }

        qsort(input, n+1, sizeof(int), cmp);

        int i;
        for(i = 0; i < 45; i++){
            list[i].next = NULL;
            deg[i] = 0;
        }
        for(i = 0; i < 2000; i++){
            isdelete[i] = 0;
            path[i] = 0;
        }
        for(i = n; i >= 0; i--){
            int number = input[i]/2500;
            int edge1 = input[i]/50%50;
            int edge2 = input[i]%50;

            node* temp = list[edge1].next;
            list[edge1].next = (node*)malloc(sizeof(node));
            list[edge1].next->num = number;
            list[edge1].next->destination = edge2;
            list[edge1].next->next = temp;
            deg[edge1]++;

            temp = list[edge2].next;
                list[edge2].next = (node*)malloc(sizeof(node));
                list[edge2].next->num = number;
                list[edge2].next->destination = edge1;
                list[edge2].next->next = temp;
                deg[edge2]++;

        }

        int fail = 0;
        for(i = 1; i < 45; i++)
            fail = fail || (deg[i]%2 == 1);
        if(fail){
            printf("Round trip does not exist.\n\n");
        } else {
            path_n = 0;
            find_node(start);
            for(i = path_n-1; i > 0; i--)
                printf("%d ", path[i]);
            printf("%d\n\n", path[0]);
        }
    }

    return 0;
}
