#include<stdio.h>
#include"NumClass.h"
#include<math.h>

int mypow(int a, int b){
    int res=1;
    
    for(int i=0;i<b;i++){
        res=res*a;

    }
    return res;

}

int isArmstrong(int num){

int sum=0;
int power;
int ld=0;
int count=0;
int temp=num;

while(temp>0){
    temp=temp/10;
    count++;


}

int n=num;
while(n>0){
    ld=n%10;

    power=mypow(ld,count);

    sum+=power;

    n=n/10;
}
if(sum==num){
    return 1;
}
else
return 0;


}


int isPalindrome(int num){
    int n=num;
    int ind,check=0;
    while(n>0){
    
        ind=n%10;
        check=(check*10)+ind;
        n=n/10;
    }
    if(check==num) return 1;
    else{
        return 0;
    }

    }
    


  


