#include "inverted.h"

void save_database(M_node *HT[])
{
    char fname[20];
    int flag = 0;

    printf("Enter file name to save database: ");
    scanf("%s", fname);

    FILE *fptr = fopen(fname, "w");
    if(fptr == NULL)
    {
        printf("INFO : Unable to create file\n");
        return;
    }

    for(int i = 0; i < 27; i++)
    {
        if(HT[i] != NULL)
        {
            M_node *main_temp = HT[i];

            while(main_temp != NULL)
            {
                flag = 1;

                // Write index, word, file_count
                fprintf(fptr, "#%d;%s;%d;",
                        i,
                        main_temp->word,
                        main_temp->file_count);

                S_node *sub_temp = main_temp->sub_link;

                // Write filename and word_count
                while(sub_temp != NULL)
                {
                    fprintf(fptr, "%s;%d;",
                            sub_temp->filename,
                            sub_temp->word_count);

                    sub_temp = sub_temp->sub_link;
                }

                fprintf(fptr, "#\n");

                main_temp = main_temp->main_link;
            }
        }
    }

    fclose(fptr);

    if(flag == 0)
    {
        printf("INFO : Database is empty. Nothing saved\n");
    }
    else
    {
        printf("INFO : Database saved successfully\n");
    }
}   
