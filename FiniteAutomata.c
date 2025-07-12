#include <stdio.h>
#include <string.h>


int maxLenOfSuffixOfstrWhichIsPrefixOfpat(char *pat, char * str){
    int m = strlen(pat);
    int s = strlen(str);
    int start;
    if (m>s){start = s;}
    else {start = m;}

    for (int k=start-1;k>0;k--){
        int count = 0;
        for (int j=0;j<k;j++){
            if (pat[j]!=str[s-k+j]){break;}
            else {count++;}
        }
        if (count==k){return count;}
    }
    return 0;
}

int transitionFunction(int num, char c, char *pat, char *str){ //current state = num and if you add character 'c' to str 'str', what is the next current state?
    int s = strlen(str);
    if (pat[num]==c){return num+1;}
    str[num]=c;
    str[num+1]='\0';
    int ans = maxLenOfSuffixOfstrWhichIsPrefixOfpat(pat, str);
    return ans;
}

void printTransitionFunctionTable(char *pat, char *domain){
    int m = strlen(pat);
    int lenDomain = strlen(domain);
    char str[m+2];
    str[0]='\0';
    for (int j=0;j<lenDomain;j++){
        printf("T(%d,%c)=%d ", 0, domain[j],transitionFunction(0,domain[j],pat,str));
    }
    printf("\n");

    for (int i=1;i<=m;i++){
        str[i-1]=pat[i-1];
        str[i]='\0';
        for (int j=0;j<lenDomain;j++){
            // printf("%s\n", str);
            printf("T(%d,%c)=%d ", i, domain[j],transitionFunction(i,domain[j],pat,str));
        }
        printf("\n");
    }
}

void automataMatcher(char *pat, char *txt){
    int n = strlen(txt);
    int m = strlen(pat);
    
    int initialState = 0;
    int currState = initialState;
    int acceptingState = m;
    char str[n];
    str[0]='\0';
    str[0]=txt[0];
    str[1]='\0';
    currState = transitionFunction(currState, txt[0], pat, str);
    int count = 0;
    for (int i=1;i<n;i++){
        str[i]=txt[i-1];
        str[i+1]='\0';
        currState = transitionFunction(currState, txt[i], pat, str);
        if (currState == acceptingState){
            count++;
            printf("%d is Valid shift\n", i-m+1);
            str[i]=txt[i-1];
            str[i+1]='\0';
            currState = transitionFunction(currState,txt[i],pat,str);
            }
    }
    if (count == 0){
        printf("No valid shift found!");
    }
}


int main(){
    char pat[100] = "ababaca";
    char txt[100] = "abababababacababaca";
    automataMatcher(pat, txt);
}