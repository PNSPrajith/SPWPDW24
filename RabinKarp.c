#include <stdio.h>
#include <string.h>
#define ll long long
ll power(int base, int exp){
    if (exp==0){return 1;}
    int temp = power(base, exp/2);
    temp *=temp;
    if (exp%2==0){
        return temp;
    }
    else {
        return temp*base;
    }
}

//     ll horner(char * p) {
//     ll l = strlen(p);
//    ll sum = p[0]-'0';
//    for (int i=1;i<l;i++){
//     sum += sum*10+(p[i]-'0');
//    }
//    return sum;
// }

    
void RabinKarpMatcher(char* pat, char* txt, int base, int mod, char first_char){ //first_char is to be taken as first char in the chosen alphabet set
    int n = strlen(txt);
    int m = strlen(pat);
    int t0=0,p=0,ts;
    int h = power(base, m-1) % mod; 
    for (int i=0;i<m;i++){
        t0 = (t0*base+(txt[i]-first_char+1)) % mod;
        p = (p*base+(pat[i]-first_char+1)) % mod;
    }
    if (t0==p){
        int count = 0;
        for (int i=0;i<m;i++){
            if (txt[i]==pat[i]){
                count++;
            }
            else {break;}
        }
        if (count == m){printf("0 is valid shift\n");}
        else {printf("0 is spurious hit\n");}
    }

    ts = (t0 - (txt[0]-first_char+1)*h % mod + mod) % mod;
    ts = (ts*base + (txt[m]-first_char+1)) % mod;
    
    for (int j=1;j<=n-m;j++){
    if (ts==p){
        int count = 0;
        for (int i=0;i<m;i++){
            if (pat[i]==txt[i+j]){
                count++;
            }
            else {break;}
        }
        if (count == m){printf("%d is valid shift\n",j);}
        else {printf("%d is spurious hit\n",j);}
    }
    ts = (ts - (txt[j]-first_char+1)*h % mod + mod) % mod;
    ts = (ts*base + (txt[j+m]-first_char+1)) % mod;
    }  
}

    
int main() {
    char *p = "26";
    char *t = "3141592653589793";
    RabinKarpMatcher(p,t,10,11,'0');
    return 0;
}