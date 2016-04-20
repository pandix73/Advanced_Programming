#include <stdio.h>

int can(int *book, int limit, int divnum){
    int i, n = 1, sum = 0;
    for(i = 0; book[i]; i++){
        if(sum + book[i] <= limit){
            sum += book[i];
        } else if(book[i] > limit){
        	return 0;
        } else{
            sum = book[i];
            n++;
        }
    }
    return divnum >= n;
}

int bs(int start, int end, int *book, int divnum){
    int mid = (start+end)/2;
    if(start + 1 == end){
        return end;
    } else if (can(book, mid, divnum)){
        return bs(start, mid, book, divnum);
    } else {
        return bs(mid, end, book, divnum);
    }
}

int main(){
    freopen("714.in", "r", stdin);
    freopen("test.out", "w", stdout);

    int t;
    scanf("%d", &t);
    for( ; t > 0; t--){
        int book[501] = {0};
        int i, bookn, booksum = 0, div;
        scanf("%d%d", &bookn, &div);
        for(i = 0; i < bookn; i++){
            scanf("%d", &book[i]);
            booksum += book[i];
        }
        int limit = bs(booksum/bookn-1, booksum, book, div);
        //printf("%d\n", limit);
        int sum = 0, slash[501] = {0};
        for(i = bookn-1; i >= 0; i--){
            if(sum + book[i] <= limit){
                sum += book[i];
            } else {
                sum = book[i];
                slash[i] = 1;
                div--;
            }
        }
        printf("%d", book[0]);
        for(i = 1; i < bookn; i++){
            if(slash[i-1]){
                printf(" / %d", book[i]);
            } else if (div != 1){
                div --;
                printf(" / %d", book[i]);
            } else printf(" %d", book[i]);
        }
        printf("\n");
    }
}
