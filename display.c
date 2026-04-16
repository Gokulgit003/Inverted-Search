#include "inverted.h"

void display_database(M_node *HT[])
{
    int flag=0;
    for(int i=0;i<27;i++)
    {
        M_node *mtemp=HT[i];
        while(mtemp)
        {
            flag=1;
            printf("[Index:%2d] [Word:%-10s] [Files:%d] ",i, mtemp->word, mtemp->file_count);
            S_node *stemp=mtemp->sub_link;
            while(stemp)
            {
                printf("[File:%s Count:%d] ",stemp->filename, stemp->word_count);
                stemp = stemp->sub_link;
            }
            printf("\n");
            mtemp=mtemp->main_link;
        }
    }
    if(flag == 0)
    {
        printf("INFO : Database is empty\n");
    }
}
