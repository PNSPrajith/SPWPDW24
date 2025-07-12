#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define max_symbols 256

typedef struct{
    char symbol;
    double upper,lower;
}SymbolRange;


void initlializeRanges(SymbolRange ranges[], char symbols[], double probs[], int n, double min, double max){
    double var = min;
    for (int i=0;i<n;i++){
        ranges[i].symbol = symbols[i];
        ranges[i].lower = var;
        ranges[i].upper = var+(max-min)*probs[i];
        var = ranges[i].upper; 
    }
}

void printRanges(SymbolRange ranges[], char symbols[], double probs[], int n, double min, double max){
    initlializeRanges(ranges, symbols, probs, n, min, max);
    for (int i=0;i<n;i++){
        printf("%c: Low=%f,High=%f\n", ranges[i].symbol, ranges[i].lower, ranges[i].upper);
    }
}

double encode(char *msg, SymbolRange ranges[], char symbols[], double probs[], int n){ //here, n = number of characters having non zero probability
    double low = 0,high = 1,range;
    int len_msg = strlen(msg);
    for (int i=0;i<len_msg;i++){
        char curr = msg[i];
        for (int j=0;j<n;j++){
            if (ranges[j].symbol == curr){
                range = high-low;
                high = low+range*(ranges[j].upper);
                low = low+range*(ranges[j].lower);
                break;
            }
        }
    }
    return (low+high)/2;
}

char* decode(double code, SymbolRange ranges[], char symbols[], double probs[], int n, int len_msg){
    // char res[len_msg+1];
    char *res = (char*) malloc(sizeof(char)*(len_msg+1));
    res[0]='\0';
    double low = 0,high=1,range;
    for (int i=0;i<len_msg;i++){
        for (int j=0;j<n;j++){
            if (ranges[j].lower<=code && ranges[j].upper>code){
                int len = strlen(res);
                res[len] = ranges[j].symbol;
                res[len + 1] = '\0';
                
                initlializeRanges(ranges, symbols, probs, n, ranges[j].lower, ranges[j].upper);
                break;
            }
        }
    }
    return res;
}
int main() {
    //here you should provide the symbols and their probabilities..
    char symbols[3] = {'a','b','c'};
    double probs[3] = {0.5,0.25,0.25};
    char *msg = "abca"; //msg to encode
    SymbolRange ranges[3];
    initlializeRanges(ranges, symbols, probs, 3,0,1);
    printf("%s is encoded into %lf\n",msg,encode(msg,ranges,symbols,probs,3));
    double code = 0.351363; //code to decode
    printf("%lf is decoded into %s\n",code,decode(code,ranges,symbols,probs,3,4));
    return 0;
}