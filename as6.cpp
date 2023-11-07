#include<bits/stdc++.h>
using namespace std;

void fifo()
{
    int i;
    int nof, nop;
    printf("\nEnter Number of Frames = ");
    scanf("%d", &nof);
    printf("\nEnter Number of Process = ");
    scanf("%d", &nop);

    vector<int>process_ref(nop);
    vector<int>frames(nof, -1);

    printf("\nEnter Process = ");
    for(int i=0;i<nop;i++)
    {
        scanf("%d", &process_ref[i]);
    }

    int fault = 0, hit = 0;
    int index = 0;

    for(int i=0;i<nop;i++)
    {
        int isHit = 0;
        printf("\n%d |", process_ref[i]);
        for(int j=0;j<nof;j++)
        {
            if(frames[j]==process_ref[i])
            {
                hit++;
                isHit = 1;
            }
        }

        if(isHit==0)
        {
            frames[index] = process_ref[i];
            fault++;
            index = (index+1)%nof;
        }

        for(int j=0;j<nof;j++)
        {
            printf(" %d |", frames[j]);
        }
        printf(" %c ", (isHit==1 ? 'H' : 'F'));
    }

    printf("\nTotal Page Fault = %d", fault);
    printf("\nTotal Page Hit = %d", hit);
}

void lru()
{
    map<int, int>mp;
    int nof, nop;
    printf("\nEnter Number of process = ");
    cin>>nop;
    cout<<"\nEnter number of frames = ";
    cin>>nof;
    vector<int>frames(nof, -1);
    vector<int>process_ref(nop);
    printf("\nEnter  Process reference = ");

    for(int i=0;i<nop;i++)
    {
        cin>>process_ref[i];
    }


    int hit = 0, fault = 0;
    int occupited = 0;
    for(int i=0;i<nop;i++)
    {
        int curr = process_ref[i];
        int isHit = 0;
        for(int j=0;j<nof;j++)
        {
            if(frames[j]==curr)
            {
                mp[curr] = i;
                hit++;
                isHit = 1;
                break;
            }
        }

        if(isHit==0 && occupited<nof)
        {  
            mp[curr] = i;
            frames[occupited++] = curr;
            fault++;
        }
        else if(isHit==0)
        {
            int index = 999;
            int val;
            for(auto it : mp)
            {
                if(it.second < index)
                {
                    index = it.second;
                    val = it.first;
                }
            }

            for(int j=0;j<nof;j++)
            {
                if(frames[j]==val)
                {
                    frames[j] = curr;
                    break;
                }
            }

            mp.erase(val);
            mp[curr] = i;
            fault++;
        }
        // cout<<"\n";
        // for(int j=0;j<nof;j++)
        // {
        //     cout<<frames[j]<<" ";
        // }
        // cout<<"\nPage = "<<(isHit==1 ? "Hit" : "Fault");
    }   

    cout<<"\nTotal Page Fault = "<<fault;
    cout<<"\nTotal Page Hit = "<<hit;  
}


void optimal()
{
    int nof, nop;
    cout<<"\nEnter Number of Process = ";
    cin>>nop;
    cout<<"\nEnter Number of frames = ";
    cin>>nof;

    int process[nop];
    cout<<"\nEnter Process = ";
    for(int i=0;i<nop;i++)
    {
        cin>>process[i];
    }

    vector<int>frames(nof, -1);
    vector<int>temp(nof);

    int fault = 0, hit = 0;

    for(int i=0;i<nop;i++)
    {
        int curr = process[i];
        int flag1 = 0, flag2 = 0;
        
        if(flag1==0 && flag2==0)
        {
            for(int j=0;j<nof;j++)
            {
                if(frames[j]==curr)
                {
                    hit++;
                    flag1 = 1;
                    flag2 = 1;
                    break;
                }
            }
        }

        if(flag1==0)
        {
            for(int j=0;j<nof;j++)
            {
                if(frames[j]==-1)
                {
                    fault++;
                    frames[j] = curr;
                    flag1 = 1;
                    flag2 = 1;
                    break;
                }
            }
        }

        if(flag2==0)
        {
            for(int j=0;j<nof;j++)
            {
                temp[j] = 9999;
                for(int k=i+1;k<nop;k++)
                {
                    if(frames[j]==process[k])
                    {
                        temp[j] = k;
                        break;
                    }
                }
            }

            int maxx = -1;
            int val;

            for(int j=0;j<nof;j++)
            {
                if(temp[j] > maxx)
                {
                    maxx = temp[j];
                    val = frames[j];
                }
            }

            for(int j=0;j<nof;j++)
            {
                if(frames[j]==val)
                {
                    frames[j] = curr;
                    break;
                }
            }

            fault++;
        }
    }

    // 7 0 1 2 0 3 0 4 2 3 0 3 2 1 2 0 1 7 0 1


    cout<<"\nTotal Page Fault = "<<fault;
    cout<<"\nTotal Page Hit = "<<hit;
}

int main()
{
    
    int choice;
    while(true)
    {
        printf("\nEnter : \n1) FIFO \n2) LRU \n3) Optimal \n4) EExit");
        cin>>choice;
        switch(choice)
        {
            case 1: 
                fifo();
                break;
            case 2:
                lru();
                break;
            case 3:
                optimal();
                break;
            case 4:
                exit(1);
            default:
                cout<<"\nInvalid Choice";
        }
    }
    return 0;
}