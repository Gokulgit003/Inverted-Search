#include "inverted.h"

/* Function definitions */
int validate_files(int argc, char *argv[], F_node **head)
{
    if(argc<2)
    { 
        printf("Error: invalid arguments, arguments should contain atleast one file\n"); 
        printf("INFO: ./a.out <file.txt>\n");
        return FAILURE; 
    } 
    for(int i=1;i<argc;i++) 
    { 
        if(strstr(argv[i],".txt")==NULL) 
        { 
            printf("INFO: %s file is not a .txt file\n",argv[i]); 
            continue; 
        } 
        FILE *fptr=fopen(argv[i],"r"); 
        if(fptr==NULL) 
        { 
            printf("INFO: Unable to open file %s",argv[i]); 
            continue; 
        } 
        fseek(fptr,0,SEEK_END); 
        if(ftell(fptr)==0) 
        { 
            printf("INFO: %s file is empty\n",argv[i]); 
            continue; 
        } 
        if(check_duplicates(*head,argv[i])==SUCCESS) 
        { 
            printf("INFO: %s file is repeated, so it will not store into the linked list\n",argv[i]); 
            continue; 
        } 
        if(insert_last(head,argv[i])==SUCCESS) 
        { 
            printf("INFO: Successfull: inserting file name %s into file linked list\n",argv[i]); 
        } 
    } 
    return SUCCESS; 
}

int check_duplicates(F_node *head, char *f_name) 
{ 
    while(head!=NULL) 
    { 
        if(strcmp(head->f_name, f_name)==0) 
        { 
            return SUCCESS; 
        } 
        head=head->link; 
    } 
    return FAILURE; 
}

int insert_last(F_node **head, char *f_name) 
{ 
    F_node *new=malloc(sizeof(F_node)); 
    if(new==NULL) 
    { 
        printf("INFO: Node not created\n"); 
        return FAILURE; 
    } 
    strcpy(new->f_name,f_name); 
    new->link=NULL; 
    if(*head==NULL) 
    { 
        *head=new; 
        return SUCCESS; 
    } 
    F_node *temp=*head; 
    while(temp->link!=NULL) 
    { 
        temp=temp->link; 
    } 
    temp->link=new; 
    return SUCCESS; 
}

int get_index(char *word)
{
    if(word[0] >= 'a' && word[0] <= 'z')
        return word[0] - 'a';

    if(word[0] >= 'A' && word[0] <= 'Z')
        return word[0] - 'A';

    return 26;  
}
