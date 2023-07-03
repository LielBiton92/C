#include <stdio.h>
#include"NumClass.h"


int mypow(int a,int b)
{
    int res=1;
    for(int i=0;i<b;i++){
        res=res*a;
    }
    return res;
}
int nod(int number){

    int count=0;
int temp=number;

while(temp>0){
   temp=temp/10;
    count++;


}
return count;
}



int ArmstrongHelper(int n,int power)
{
    if(n>0)
    {
    return(mypow(n%10,power) + ArmstrongHelper(n/10,power));
    }
    else{
    return 0;
    }

}

int isArmstrong(int num){
    if(num==ArmstrongHelper(num,nod(num))){
        return 1;
    }
    else
    {
        return 0;
    }
    }
 



int Rechelper(int num, int ans){
   if (num == 0){
       return ans;
   } 
    ans=ans*10+(num%10);
    num=num/10;
    return Rechelper(num, ans);
}
int isPalindrome(int num){
    int ans=0;
    ans = Rechelper(num, ans);
    if (num==ans){
        return 1;
    }
    return 0;
}

 












