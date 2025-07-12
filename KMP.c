#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int *computeLPSArray(char *pattern){
    int m = strlen(pattern);
    int* lps = malloc(sizeof(int)*m);
    lps[0]=0;
    int len = 0,i=1;
    while (i<m){
        if (pattern[i]==pattern[len]){
            lps[i]=len+1;
            len++;
            i++;
        }
        else {
            if (len!=0){
                len = lps[len-1];
            }
            else{
                lps[i]=0;
                i++;
            }
        }
    }
    return lps;
}

void printLpsArray(char* pattern){
    int* lps = computeLPSArray(pattern);
    int m = strlen(pattern);
    for (int i=0;i<m;i++){
        printf("%d ",lps[i]);
    }
}
int KMPSearch(char* pattern, char* text){
    int n = strlen(text);
    int m = strlen(pattern);
    int *lps = computeLPSArray(pattern);
    int i=0,j=0,shift=0,op=0;
    while(i<n){
        if (pattern[j]==text[i]){
            i++;
            j++;
        }
        else {
            if (j!=0){
                j = lps[j-1];
            }
            else {
                i++;
            }
        }
        if (j==m){
            // printf("Shift: %d\n",i-j);
            shift++;
            j = lps[j-1];
        }
        op++;
    }
    // if (shift==0){return -1;printf("No valid shift");}
    free(lps);
    return shift;
}

// int main(){
//     KMPSearch("aacaa","ababaaacaacaacbaa");
// }