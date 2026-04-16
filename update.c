#include "inverted.h"

int update_database(M_node *HT[], F_node **head)
{ 
    char fname[20];
    printf("Enter the saved file name: ");
    scanf("%s", fname);
    FILE *fptr = fopen(fname, "r");
    if(fptr == NULL)
    {
        printf("INFO : Unable to open file\n");
        return FAILURE;
    }
    // Initialize HT
    for(int i = 0; i < 27; i++)
    {
        HT[i] = NULL;
    }
    int index;
    char word[25];
    int file_count;
    while(fscanf(fptr, "#%d;%[^;];%d;", &index, word, &file_count) != EOF)
    {
        // Create Main Node
        M_node *new_main = malloc(sizeof(M_node));
        strcpy(new_main->word, word);
        new_main->file_count = file_count;
        new_main->main_link = NULL;
        new_main->sub_link = NULL;

        S_node *last_sub = NULL;
        // Read sub nodes
        for(int i = 0; i < file_count; i++)
        {
            char filename[20];
            int word_count;

            fscanf(fptr, "%[^;];%d;", filename, &word_count);

            S_node *new_sub = malloc(sizeof(S_node));
            strcpy(new_sub->filename, filename);
            new_sub->word_count = word_count;
            new_sub->sub_link = NULL;

            if(new_main->sub_link == NULL)
            {
                new_main->sub_link = new_sub;
            }
            else
            {
                last_sub->sub_link = new_sub;
            }
            last_sub = new_sub;
        }
        // Insert into Hash Table
        if(HT[index] == NULL)
        {
            HT[index] = new_main;
        }
        else
        {
            M_node *temp = HT[index];
            while(temp->main_link != NULL)
            {
                temp = temp->main_link;
            }
            temp->main_link = new_main;
        }
    }
    fscanf(fptr, "#");  // consume ending #
    fclose(fptr);
    printf("INFO : Database updated successfully\n");
    return SUCCESS;
}
