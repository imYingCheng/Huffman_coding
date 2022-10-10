#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
typedef struct treeNode *Node;
struct treeNode{
    char data;
    int num;
    Node llink, rlink, parent;
};
Node record[256];
FILE *input_file;
FILE *output_file;
int len;                            //the final answer
void count_len(Node *,int);
Node build_tree(int);
int read_line(int);
int main(){
    input_file = fopen("input_2.txt", "r");
    output_file = fopen("output_2.txt", "w");
    int m,index;
    Node head;
    while(1){
        fscanf(input_file,"%d\n", &m);
        if(m==0)
            break;
        index=read_line(m);
        head=build_tree(index);
        len = 0;
        count_len(&head,0);
        fprintf(output_file, "%d\n\n", len);
    }
    fclose(input_file);
    fclose(output_file);
    return 0;
}
int read_line(int m){
    for (int i = 0; i < 256;i++){       //initialize the record array
        record[i] = (Node)malloc(sizeof(struct treeNode));
        record[i]->parent = NULL;
        record[i]->data = '\0';
        record[i]->num = 0;
        record[i]->llink = NULL;
        record[i]->rlink = NULL;
    }
    int index = 0,j;
    char c;
    for (int i = 0; i < m;i++){
        while(1){                       //store input data in th array
            fscanf(input_file,"%c", &c);
            if(c=='\n')
                break;
            for (j = 0; j < index;j++){
                if(record[j]->data==c){
                    record[j]->num++;
                    break;
                }
                else if(record[j]->data=='\0')
                    break;
            }
            if(j==index||record[j]->data=='\0'){
                record[index]->data = c;
                record[index]->num = 1;
                index++;
            }
        }
    }
    return index;
}
Node build_tree(int index){         //build tree from the leaf until the root_num reduce to 1
    int root_num;
    Node s1, s2;
    int num1, num2;
    while(1){
        root_num = 0;
        num1 = INT_MAX;
        num2 = INT_MAX;
        for (int i = 0; i < index;i++){
            if(record[i]->parent)
                continue;
            root_num++;
            if(record[i]->num<num1){
                if(record[i]->num<num2){
                    num2 = num1;
                    s2 = s1;
                    num1 = record[i]->num;
                    s1 = record[i];
                }
            }
            else if(record[i]->num<num2){
                num2 = record[i]->num;
                s2 = record[i];
            }   
        }
        if(root_num==1)
            return s1;
        record[index]->parent = NULL;
        record[index]->llink = s1;
        record[index]->rlink = s2;
        record[index]->num = num1 + num2;
        s1->parent = record[index];
        s2->parent = record[index];
        index++;
    }
}
void count_len(Node *tmp,int depth){
    if((*tmp)->data!='\0'){
        len += ((*tmp)->num) * depth;
        return;
    }
    else{
        count_len(&((*tmp)->llink), depth + 1);
        count_len(&((*tmp)->rlink), depth + 1);
    }
}