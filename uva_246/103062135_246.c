#include <stdio.h>

int deck[53];
int piles[7][53];
int status[70];
int ans;

int ht[2100000];
int kt[2100000];
int h1 = 1999999;
int h2 = 1000001;

int hash(int h, int *s){
    int n = 0, i;
    for(i = 1; i <= s[0]; i++)
        n = (n*13 + s[i])%h;
    return n;
}

int exist(int *s){
    int s1 = hash(h1, s);
    int s2 = hash(h2, s);
    while(ht[s1] == 1 && kt[s1] != s2) s1++;
    if(ht[s1] == 1){
        return 1;
    } else {
        ht[s1] = 1;
        kt[s1] = s2;
        return 0;
    }
}

void push_back(int num, int *a){
    a[++a[0]] = num;
}

void pop_front(int *a){
    int i;
    for(i = 1; i <= a[0]; i++)
        a[i] = a[i+1];
    a[0]--;
}

void pop_back(int *a){
    a[0]--;
}

int checkvalid(int a, int b, int c){
    return ((a+b+c)%10 == 0);
}

void checkpile(int *pile){
    if(pile[0] < 3){
        return;
    } else if(checkvalid(pile[1], pile[2], pile[pile[0]])){
        push_back(pile[1], deck);
        push_back(pile[2], deck);
        push_back(pile[pile[0]], deck);
        pop_front(pile);
        pop_front(pile);
        pop_back(pile);
        checkpile(pile);
    } else if(checkvalid(pile[1], pile[pile[0]-1], pile[pile[0]])){
        push_back(pile[1], deck);
        push_back(pile[pile[0]-1], deck);
        push_back(pile[pile[0]], deck);
        pop_front(pile);
        pop_back(pile);
        pop_back(pile);
        checkpile(pile);
    } else if(checkvalid(pile[pile[0]-2], pile[pile[0]-1], pile[pile[0]])){
        push_back(pile[pile[0]-2], deck);
        push_back(pile[pile[0]-1], deck);
        push_back(pile[pile[0]], deck);
        pop_back(pile);
        pop_back(pile);
        pop_back(pile);
        checkpile(pile);
    } else {
        return;
    }
}

void make_status(){
    int i;
    for(i = 0; i < 70; i++)
        status[i] = 0;
    for(i = 1; i <= deck[0]; i++)
        push_back(deck[i], status);
    push_back(11, status);
    for(i = 0; i < 6; i++){
        int j;
        for(j = 1; j < piles[i][0]; j++)
            push_back(piles[i][j], status);
        push_back(11, status);
    }
}

void dealt(){
    int n = 0;
    ans = 8;
    while(1){
        push_back(deck[1], piles[n]);
        pop_front(deck);
        checkpile(piles[n]);

        make_status();
        if(deck[0] == 0){
            printf("Loss: %d\n", ans);
            return;
        } else if(deck[0] == 52){
            printf("Win : %d\n", ans);
            return;
        } else if(exist(status) == 1){
            printf("Draw: %d\n", ans);
            return;
        }

        n = (n+1)%7;
        ans++;
        while(piles[n][0] == 0)
            n = (n+1)%7;
    }
}

int main(){
    int input;
    while(scanf("%d", &input), input > 0){
        piles[0][0] = 0;
        push_back(input, piles[0]);
        int i;
        for(i = 1; i < 7; i++){
            scanf("%d", &input);
            piles[i][0] = 0;
            push_back(input, piles[i]);
        }
        deck[0] = 0;
        for(i = 0; i < 45; i++){
            scanf("%d", &input);
            push_back(input, deck);
        }

        dealt();
    }
}
