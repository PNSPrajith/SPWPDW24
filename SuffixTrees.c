#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_CHAR 256

typedef struct Edge Edge;

typedef struct Node{
    Edge* children[MAX_CHAR];
    int suffixIndex;
}Node;

typedef struct Edge{
    Node* child;
    Node* parent;
    int start;
    int end;
}Edge;

typedef struct{
    Node* root;
    char* text;
    int len_text;
}SuffixTree;

Node* createNode(){
    Node* node = (Node*)malloc(sizeof(Node));

    for (int i=0;i<MAX_CHAR;i++){
        node->children[i]=NULL;
    }

    node->suffixIndex = -1;
    return node;
}

Edge* createEdge(Node* parent, int start, int end){
    Edge* edge = (Edge*)malloc(sizeof(Edge));

    edge->child = createNode();
    edge->parent = parent;
    edge->start = start;
    edge->end = end;

    return edge;
}

void insertSuffix(SuffixTree* tree, char* text, int suffixStartIndex){
    Node* currNode = tree->root;
    int i = suffixStartIndex;

    while (i < (tree->len_text)){
        char currChar = text[i];
        
        //If there is no edge with currChar: 
        if (currNode->children[currChar]==NULL){
            currNode->children[currChar]=createEdge(currNode,i,(tree->len_text)-1);
            currNode->children[currChar]->child->suffixIndex = suffixStartIndex;
            return;
        }

        Edge* edge = currNode->children[currChar];
        int edgeStart = edge->start;
        int edgeEnd = edge->end;

        int j = edgeStart;

        while (j<=edgeEnd && text[i]==text[j]){
            j++;
            i++;
        }   

        if (j<=edgeEnd){
            Node* splitNode = createNode();
            edge->end = j-1;
            Edge* newEdge = createEdge(splitNode,j,edgeEnd);
            newEdge->child = edge->child;

            splitNode->children[text[j]] = newEdge;
            splitNode->children[text[i]] = createEdge(splitNode,i,(tree->len_text)-1);
            splitNode->children[text[i]]->child->suffixIndex = suffixStartIndex;

            currNode->children[currChar] = createEdge(currNode,edge->start,j-1);
            currNode->children[currChar]->child = splitNode;

            return;
        }
    }
}

SuffixTree* buildSuffixTree(char *text){
    int len_text = strlen(text);
    SuffixTree* tree = (SuffixTree*)malloc(sizeof(SuffixTree));


    tree->text = text;
    tree->len_text = len_text;
    tree->root = createNode();

    for (int i=0;i<len_text;i++){
        insertSuffix(tree,text,i);
    }
    return tree;
}

void printSuffixTreeUtil(Node* node, char* text, int depth) {
    if (node == NULL){printf("Node become NULL");return;}

    for (int i = 0; i < MAX_CHAR; i++) {
        if (node->children[i] != NULL) {
            // printf("%d\n",i);
            Edge* edge = node->children[i];
            // printf("%d\n", depth);
            printf("%*s[%.*s] (start: %d, end: %d)\n", depth * 4, "", 
                   edge->end - edge->start + 1, text + edge->start, 
                   edge->start, edge->end);

            // Recursively print the child
            // printf("%d\n",edge->child  == NULL);
            printSuffixTreeUtil(edge->child, text, depth + 1);
        }
    }

    // Print suffix index if this is a leaf
    if (node->suffixIndex != -1) {
        printf("%*sSuffix Index: %d\n", depth * 4, "", node->suffixIndex);
    }
}

void printSuffixTree(SuffixTree* tree) {
    printf("Suffix Tree:\n");
    printSuffixTreeUtil(tree->root, tree->text, 0);
}

int main(){
    char text[] = "ababac";

    SuffixTree* tree = buildSuffixTree(text);

    printSuffixTree(tree);

    return 0;
}