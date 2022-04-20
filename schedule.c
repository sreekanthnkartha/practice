#include <stdio.h>
#include <stdlib.h>
struct process
{
    int name;
    int ari;
    int bur;
    int prio;
    int comp;
    int turn;
    int wait;
    int vis;
    int rem;
} p[100];
int n;

void sort()
{
    for (int i = 0; i < n; i++)
    {
        struct process temp = p[i];
        int index = i;
        for (int j = i; j < n; j++)
        {
            if (p[j].ari < temp.ari)
            {
                temp = p[j];
                index = j;
            }
        }
        temp = p[index];
        p[index] = p[i];
        p[i] = temp;
    }
}

void cal()
{
    for (int i = 0; i < n; i++)
    {
        p[i].turn = p[i].comp - p[i].ari;
        p[i].wait = p[i].turn - p[i].bur;
    }
}

void display()
{
    cal();
    printf("Process\tAt\tBt\tCT\twt\ttat\n");
    for (int i = 0; i < n; i++)
    {
        printf("%i\t%i\t%i\t%i\t%i\t%i\t\n", p[i].name, p[i].ari, p[i].bur, p[i].comp, p[i].wait, p[i].turn);
    }
}

void input()
{
    printf("no of process : ");
    scanf("%i", &n);
    printf("At Bt Prio\n");
    for (int i = 0; i < n; i++)
    {
        scanf("%i %i %i", &p[i].ari, &p[i].bur, &p[i].prio);
        p[i].name = i + 1;
        p[i].rem = p[i].bur;
        p[i].comp = 0;
        p[i].wait = 0;
        p[i].turn = 0;
        p[i].vis = 0;
    }
}

void fcfs()
{
    sort();
    int co = 0;
    for (int i = 0; i < n; i++)
    {
        if (co < p[i].ari)
        {
            co = p[i].ari;
        }
        co += p[i].bur;
        p[i].comp = co;
    }
}

void sjf()
{
    sort();
    int co = p[0].ari;
    int si = 0;
    for (int i = 0; i < n;)
    {
        if (p[i].vis == 0)
        {
            if (p[i].ari <= co)
            {
                si = i;
                for (int j = 0; j < n; j++)
                {
                    if (p[j].vis == 0 && p[j].ari <= co && p[si].bur > p[j].bur)
                    {
                        si = j;
                    }
                }
                co += p[si].bur;
                p[si].comp = co;
                p[si].vis = 1;
            }
            else
                co++;
        }
        else
            i++;
    }
}
void srtf()
{
    sort();
    int co = p[0].ari;
    int si = 0;
    for (int i = 0; i < n;)
    {
        if (p[i].vis == 0)
        {
            if (p[i].ari <= co)
            {
                si = i;
                for (int j = 0; j < n; j++)
                {
                    if (p[j].vis == 0 && p[j].ari <= co && p[si].rem > p[j].rem)
                    {
                        si = j;
                    }
                }
                int tt = p[si].rem;
                int check = 0;
                int time;
                for (time = 1; time <= tt; time++)
                {
                    for (int k = 0; k < n; k++)
                    {
                        if (p[k].vis == 0 && p[k].ari <= co + time && p[si].rem - time > p[k].rem)
                        {
                            p[si].rem -= time;
                            si = k;
                            check = 1;
                            break;
                        }
                    }
                    if (check)
                        break;
                }
                if (check == 0)
                {
                    co += p[si].rem;
                    p[si].comp = co;
                    p[si].vis = 1;
                    p[si].rem = 0;
                }
                else
                {
                    co += time;
                }
            }
            else
                co++;
        }
        else
            i++;
    }
}

void rr()
{
    int tq;
    scanf("%i", &tq);
    sort();
    int co = p[0].ari;
    int req[100];
    for (int i = 0; i < 100; i++)
    {
        req[i] = -1;
    }
    int ptr1 = 0, ptr2 = 0;
    req[ptr2++] = 0;
    while (req[ptr1] != -1)
    {
        int ind = req[ptr1];
        printf("%i ",p[ind].name);
        p[ind].vis = 1;
        int k;
        if (p[ind].rem >= tq)
        {
            k = tq;
        }
        else
        {
            k = p[ind].rem;
        }
        for (int kk = co; kk <= co + k; kk++)
        {
            for (int j = 0; j < n; j++)
            {
                if(kk>=p[j].ari && p[j].vis!=1)
                {
                    p[j].vis=1;
                    req[ptr2++]=j;
                }
            }
        }
        co+=k;
        p[ind].rem -= k;
        if (p[ind].rem == 0)
        {
            p[ind].comp = co;
        }
        else
        {
            req[ptr2] = ind;
            ptr2++;
        }
        ptr1++;
    }
}

int main(int argc, char const *argv[])
{
    input();
    // fcfs();
    // sjf();
    // srtf();
    rr();
    display();
    return 0;
}
