#include<stdio.h>
#include<stdlib.h>
#include<math.h>


void sort(int * request, int n)
{
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n-i-1;j++)
        {
            if(request[j] > request[j+1])
            {
                int temp = request[j];
                request[j] = request[j+1];
                request[j+1] = temp;
            }
        }
    }
}

void sstf()
{
    int track, head, head1;
    track = 200;
    int n;
    printf("\nEnter Number of request = ");
    scanf("%d", &n);

    int request[n];
    printf("\nEnter Request = ");
    for(int i=0;i<n;i++)
    {
        scanf("%d", &request[i]);
    }

    printf("\nEnter intital head = ");
    scanf("%d", &head1);

    head = head1;
    printf("%d",head);

    int visited[n];
    for(int i=0;i<n;i++)
    {
        visited[i] = 0;
    }

    int pending = n;
    int distance = 0;

    while(pending>0)
    {
        int index = -1;
        int diff = 9999;
        
        for(int i=0;i<n;i++)
        {
            if(visited[i]==0 && abs(head-request[i]) < diff)
            {
                diff = abs(head - request[i]);
                index = i; 
            }
        }

        if(index!=-1)
        {
            printf(" -> %d", request[index]);
            distance += abs(head - request[index]);
            visited[index] = 1;
            head = request[index];
            pending--;
        }
    }

    printf("\nTotal Time in SSTF is : %d", distance);
}


void scan()
{
        int size;
    printf("\nEnter Total Track on Disk = ");
    scanf("%d", &size);

    int n;
    printf("\nEnter Number of Requests = ");
    scanf("%d", &n);

    int request[n];
    printf("\nEnter Request in sequence = ");
    for(int i=0;i<n;i++)
    {
        scanf("%d", &request[i]);
    }

    int head;
    printf("\nEnter Intial postion of head = ");
    scanf("%d", &head);

    int dir;
    int distance = 0;

    sort(request, n);

    int index = -1;
    int i = 0;
    while(i<n && request[i] <= head)
    {
        index = i;
        i++;
    }

    printf("\nEnter : \n1) Moment towards Up(right) \n2) moment towards down(left) \n");
    scanf("%d", &dir);
    printf("\n%d", head);
    if(dir==1)
    {
        for(i=index+1;i<n;i++)
        {
            printf(" -> %d", request[i]);
            distance += abs(head - request[i]);
            head = request[i];
        }

        printf("-> %d", (size-1));
        distance += abs(head - (size-1));
        head = size-1;

        for(i=index;i>=0;i--)
        {
            printf(" -> %d", request[i]);
            distance += abs(head - request[i]);
            head = request[i];
        }
    }
    else if(dir==2)
    {
        for(i=index;i>=0;i--)
        {
            printf(" -> %d", request[i]);
            distance += abs(head - request[i]);
            head = request[i];
        }

        printf(" -> %d", 0);
        distance += abs(head - 0);
        head = 0;

        for(i = index+1;i<n;i++)
        {
            printf(" -> %d", request[i]);
            distance += abs(head - request[i]);
            head = request[i];
        }
    }
    else{
        printf("\nInvalid Input");
    }

    printf("\nTotal Distance Covered By disk arm = %d", distance);
}

void c_look()
{
    int track;
    printf("\nEnter Total Size of Track = ");
    scanf("%d", &track);

    int n;
    printf("\nEnter total number of request = ");
    scanf("%d", &n);

    int request[n];
    printf("\nEnter request in  sequence = ");
    for(int i=0;i<n;i++)
    {
        scanf("%d", &request[i]);
    }

    int head;
    printf("\nEnter intial position of head = ");
    scanf("%d", &head);

    sort(request, n);
    int index = -1;
    int i = 0;
    while(i<n && request[i]<=head)
    {
        index = i;
        i++;
    }

    int distance = 0;
    int dire;
    printf("\nEnter : \n1) Move to right \n2) Move to left \n");
    scanf("%d", &dire);
    printf("\n%d", head);
    if(dire==1)
    {
        for(i=index+1;i<n;i++)
        {
            printf(" -> %d", request[i]);
            distance += abs(head - request[i]);
            head = request[i];
        }

        for(i=0;i<=index;i++)
        {
            printf(" -> %d", request[i]);
            distance += abs(head - request[i]);
            head = request[i];
        }
    }
    else if(dire==2)
    {
        for(i=index;i>=0;i--)
        {
            printf(" -> %d", request[i]);
            distance += abs(head - request[i]);
            head = request[i];
        }

        for(i=n-1;i>index;i--)
        {
            printf(" -> %d", request[i]);
            distance += abs(head - request[i]);
            head = request[i];
        }
    }
    else{
        printf("\nInvalid Choice");
    }

    printf("\nTotal Distance Covered by head = %d", distance);


}

int main()
{
    int choice;
    while(1)
    {
        printf("\nEnter : \n1) SSFT \n2) SCAN \n3) C-LOOK \n4) Exit");
        scanf("%d", &choice);
        
        printf("\nchoice = %d", choice);
        switch(choice)
        {
            case 1:
                sstf();
                break;
            case 2:
                scan();
                break;
            case 3:
                c_look();
                break;
            case 4:
                exit(1);
            default :
                printf("\nInvalid Input");
        }
    }


    return 0;
}