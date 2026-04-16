#include "inverted.h"

void create_database(M_node *HT[], F_node *head)
{
     char word[25];

    // Initialize Hash Table
    for(int i = 0; i < 27; i++)
    {
        HT[i] = NULL;
    }

    // Traverse through each file
    while(head != NULL)
    {
        FILE *fptr = fopen(head->f_name, "r");
        if(fptr == NULL)
        {
            head = head->link;
            continue;
        }

        // Read each word
        while(fscanf(fptr, "%s", word) != EOF)
        {
            int index = get_index(word);

            M_node *temp = HT[index];
            M_node *prev = NULL;

            // Search if word already exists
            while(temp != NULL)
            {
                if(strcmp(temp->word, word) == 0)
                    break;

                prev = temp;
                temp = temp->main_link;
            }

            // Word not found → Create Main node
            if(temp == NULL)
            {
                M_node *new_main = malloc(sizeof(M_node));
                strcpy(new_main->word, word);
                new_main->file_count = 1;
                new_main->main_link = NULL;

                // Create sub node
                S_node *new_sub = malloc(sizeof(S_node));
                strcpy(new_sub->filename, head->f_name);
                new_sub->word_count = 1;
                new_sub->sub_link = NULL;

                new_main->sub_link = new_sub;

                // Insert into HT
                if(prev == NULL)
                    HT[index] = new_main;
                else
                    prev->main_link = new_main;
            }
            else
            {
                // Word already exists
                S_node *sub_temp = temp->sub_link;
                S_node *sub_prev = NULL;

                while(sub_temp != NULL)
                {
                    if(strcmp(sub_temp->filename, head->f_name) == 0)
                        break;

                    sub_prev = sub_temp;
                    sub_temp = sub_temp->sub_link;
                }

                // File already exists → increment word count
                if(sub_temp != NULL)
                {
                    sub_temp->word_count++;
                }
                else
                {
                    // New file for existing word
                    S_node *new_sub = malloc(sizeof(S_node));
                    strcpy(new_sub->filename, head->f_name);
                    new_sub->word_count = 1;
                    new_sub->sub_link = NULL;

                    sub_prev->sub_link = new_sub;
                    temp->file_count++;
                }
            }
        }

        fclose(fptr);
        head = head->link;
    }

    printf("INFO : Database created successfully\n");
}
