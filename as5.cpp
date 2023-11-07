#include<iostream>

#include<vector>

using namespace std;



int allocation[10][10],max_res[10][10],need[10][10];

vector<int> available(10,0);

int avail[10][10];

vector<int> total(10,0);

int process,resource;



void input()

{

    cout<<"Enter No. of Processes: ";

    cin>>process;

    cout<<"Enter No. of Resources: ";

    cin>>resource;

    

    for(int i=0;i<process;i++)

    {

        cout<<"Enter for Process: "<<(i+1);

        cout<<"\nAllocation Resources: ";

        for(int j=0;j<resource;j++)

        {

            cin>>allocation[i][j];

        }

        

        cout<<"\nMaximum Requirements: ";

        for(int j=0;j<resource;j++)

        {

            cin>>max_res[i][j];

        }

        

    }

    

    for(int i=0;i<process;i++)

    {

        for(int j=0;j<resource;j++)

        {

            need[i][j] = max_res[i][j] - allocation[i][j];

        }

    }

    

    cout<<"Enter Total Resources: ";

    for(int j=0;j<resource;j++)

    {

        cin>>total[j];

    }

    

    

    for(int i=0;i<resource;i++)

    {

        for(int j=0;j<process;j++)

        {

            available[i] += allocation[j][i];

        }

    }

    

    for(int t = 0;t<resource;t++)

    {

        available[t] = total[t] - available[t];

        avail[0][t] = available[t];

    }

    

}



void banker()

{

    int flag = 0;

    vector<int> finished(process,0);

    vector<int> safe_seq(process,0);

    int k = 0;

    

    for(int l=0;l<5;l++)

    {

        for(int i=0;i<process;i++)

        {

            if(finished[i] == 0)

            {

                flag = 0;

                

                for(int j=0;j<resource;j++)

                {

                    if(need[i][j] > available[j])

                    {

                        flag = 1;

                        break;

                    }

                }

                

                if(flag == 0)

                {

                    finished[i] = 1;

                    safe_seq[k] = i;

                    k++;

                    

                    for(int j=0;j<resource;j++)

                    {

                        available[j] += allocation[i][j];

                        avail[k][j] = available[j];

                    }

                    

                }

            }

        }

    }

    

    flag = 0;

    for(int i=0;i<process;i++)

    {

        if(finished[i] == 0)

        {

            flag = 1;

            break;

        }

    }

    

    if(flag)    cout<<"\nDeadlock Detected";

    else

    {

        cout<<"\nSafe Sequence: ";

        for(int i=0;i<safe_seq.size();i++)

        {

            cout<<"P"<<safe_seq[i]<<" | ";

        }

    }

}



void print_matrix()

{

    cout<<"\n\n----------------Banker's Algorithm ----------------"<<endl<<endl;

    

    cout<<"Process"<<" "<<"Allocation"<<"  "<<"Max"<<"  "<<"Available"<<"  "<<"Need"<<endl;

    

    

    for(int i=0;i<process;i++)

    {

        cout<<"P"<<i<<"  ";

        for(int j=0;j<resource;j++)

        {

            cout<<allocation[i][j]<<" ";

        }

        cout<<"     ";

        for(int j=0;j<resource;j++)

        {

            cout<<max_res[i][j]<<" ";

        }

        cout<<"     ";

        for(int j=0;j<resource;j++)

        {

            cout<<avail[i][j]<<" ";

        }

        cout<<"     ";

        for(int j=0;j<resource;j++)

        {

            cout<<need[i][j]<<" ";

        }

        cout<<endl;

    }

    

}



int main()

{

    cout<<"----------------Banker's Algorithm----------------"<<endl;

    

    input();

    banker();

    print_matrix();

    

    return 0;

}