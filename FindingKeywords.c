#include "KMP.c"
typedef struct{
    char* word;
    int freq;
}Word;

int main() {
    char *filename;
    printf("Enter filename: ");
    scanf("%s",filename);

    FILE *fptr = fopen(filename,"r");
    if (fptr == NULL){
        printf("Could not open file");
        return -1;
    }
    
    char* keywords[] = {
        "auto", "break", "case", "char", "const", "continue", "default", "do",
        "double", "else", "enum", "extern", "float", "for", "goto", "if",
        "inline", "int", "long", "register", "restrict", "return", "short",
        "signed", "sizeof", "static", "struct", "switch", "typedef", "union",
        "unsigned", "void", "volatile", "while", "_Alignas", "_Alignof",
        "_Atomic", "_Bool", "_Complex", "_Generic", "_Imaginary", "_Noreturn",
        "_Static_assert", "_Thread_local"
    };

char str[3000] = " ";
    printf("%s\n",str);
    char c; 
    char txt[1000]="";
    c = fgetc(fptr);
    int l=0;
    while (c!=EOF){
        if (c=='\n'){c=' ';}
        l = strlen(txt);
        txt[l]=c;
        txt[l+1]='\0'; 
        c = fgetc(fptr);
    }
    // printf("%s\n",txt);
    Word words[32];
    for (int i=0;i<32;i++){
        // printf("Yes");
        words[i].word = keywords[i];
        words[i].freq = 0;
    }

    for (int i=0;i<32;i++){
        words[i].freq = KMPSearch(words[i].word,txt);
    }

    for (int i=0;i<32;i++){
        printf("\"%s\": %d ", words[i].word, words[i].freq);
    }

    fclose(fptr);
    return 0;
}