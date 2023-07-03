#include <stdio.h>
#include "my_mat.h"


int main() {
    char x;
    int i,j,ans;
    while (1) {
        scanf("%c", &x);
        if (x == 'A') {
            build_mat();
        } 
        else if (x == 'B') {
            scanf("%d",&i);
            scanf("%d",&j);
            path(i, j);
        }
        else if (x == 'C'){
            scanf("%d",&i);
            scanf("%d",&j);
            ans = shortest_path(i,j);
            printf("%d\n",ans);
        }
        else if (x == 'D'){
            break;
        }
    }
}