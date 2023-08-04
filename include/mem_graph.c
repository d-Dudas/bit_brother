void print_mem_graph(long double *mem_usage, long double *total_mem)
{
    printf("\n");
    for(int i = 0; i < 10; i++)
    {
        printf("\t%ds ", 9 - i);
        for(int j = 0; j < mem_usage[i]; j++)
        {
            printf("|");
        }
        printf("\n");
    }
    printf("\t   ");
    for(int i = 0; i <= 100; i++)
    {
        if(i % 10 == 0)
        {
            printf("%d%%", i);
            if(i > 10)
                i += 2;
            else
                i += 1;

        }
        else
            printf(" ");
    }
    printf(" (%.2Lf GB)", *total_mem);
    printf("\n");
}