#include "inverted.h"

void search_database(M_node *HT[])
{
    char word[25];

    printf("Enter the word to search: ");
    scanf("%s", word);

    int index = get_index(word);

    M_node *temp = HT[index];

    if(temp == NULL)
    {
        printf("INFO : Word not found in database\n");
        return;
    }

    while(temp != NULL)
    {
        if(strcmp(temp->word, word) == 0)
        {
            printf("Word found!\n");
            printf("Word : %s\n", temp->word);
            printf("File Count : %d\n", temp->file_count);

            S_node *sub_temp = temp->sub_link;

            while(sub_temp != NULL)
            {
                printf("File : %s | Word Count : %d\n",
                        sub_temp->filename,
                        sub_temp->word_count);

                sub_temp = sub_temp->sub_link;
            }

            return;
        }

        temp = temp->main_link;
    }

    printf("INFO : Word not found in database\n");
}
