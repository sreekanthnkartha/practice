#include <stdio.h>
#include <stdlib.h>
int pg[100], n, f;

// PageReplacement Algorith

// FCFS

void fcfs()
{
    int frame[n];
    for (int i = 0; i < n; i++)
        frame[i] = -1;

    int i = 0, fault = 0;
    for (int j = 0; j < n; j++)
    {
        int check = 0;
        for (int ii = 0; ii < f; ii++)
        {
            if (frame[ii] == pg[j])
            {
                check = 1;
                break;
            }
        }
        if (!check)
        {
            frame[i] = pg[j];
            i = (i + 1) % f;
            fault++;
        }
    }
    printf("page fault : %i", fault);
}

// LRU

void lru()
{
    int frame[n];
    for (int i = 0; i < n; i++)
        frame[i] = -1;

    int p = 0;
    int i = 0, fault = 0;
    for (int j = 0; j < n; j++)
    {
        int check = 0;
        for (int ii = 0; ii < f; ii++)
        {
            if (frame[ii] == pg[j])
            {
                check = 1;
                break;
            }
        }
        if (!check)
        {
            frame[p++] = pg[j];
            fault++;
            if (p == f)
                break;
        }
    }

    for (int j = p; j < n; j++)
    {
        int check = 0;
        for (int ii = 0; ii < f; ii++)
        {
            if (frame[ii] == pg[j])
            {
                check = 1;
                break;
            }
        }
        if (!check)
        {
            int d = 0, td = 0, ind;
            for (int jj = 0; jj < f; jj++)
            {
                td = 0;
                int kk;
                for (kk = j - 1; kk >= 0; kk--)
                {
                    td++;
                    if (pg[kk] == frame[jj])
                    {
                        break;
                    }
                }
                if (kk == -1)
                    td++;
                if (td > d)
                {
                    ind = jj;
                    d = td;
                }
            }
            fault++;
            frame[ind] = pg[j];
        }
    }
    printf("page fault : %i", fault);
}

// LFU

void lfu()
{
    int count[100] = {0}, time[100] = {0};

    int frame[n];
    for (int i = 0; i < n; i++)
        frame[i] = -1;

    int p = 0;
    int i = 0, fault = 0;
    for (int j = 0; j < n; j++)
    {
        time[pg[j]]=j;
        count[frame[j]]++;
        int check = 0;
        for (int ii = 0; ii < f; ii++)
        {
            if (frame[ii] == pg[j])
            {
                // count[pg[j]]++;
                check = 1;
                break;
            }
        }
        if (!check)
        {
            if (p < f)
            {
                // count[pg[j]]++;
                // time[frame[leastind]]=j;
                time[pg[j]] = j;
                frame[p++] = pg[j];
                fault++;
                printf("i.\t");;
            }
            else
            {
                 fault++;
                int leastc=INT_MAX,timae=INT_MAX,leastind;
                for(int o=0;o<f;o++)
                {
                    if(leastc>count[frame[o]])
                    {
                        leastc=count[frame[o]];
                    }
                }
                for(int o=0;o<f;o++)
                {
                    if(leastc==count[frame[o]] && timae>time[frame[o]])
                    {
                        timae=time[frame[o]];
                        leastind=o;
                    }
                }
                printf("%i)%i.%i\t",j,frame[leastind],pg[j]);
                count[frame[leastind]]=0;
                frame[leastind] = pg[j];           
                
                
            }
        }
    }
    printf("page fault : %i", fault);
}

// Main

int main(int argc, char const *argv[])
{
    printf("Enter the no of pages and page and frames:\n");
    scanf("%i", &n);
    for (int i = 0; i < n; i++)
    {
        scanf("%i", &pg[i]);
    }
    scanf("%i", &f);
    fcfs();
    lru();
    lfu();
    return 0;
}

// END
