#include<iostream>

#include<vector>

#include<algorithm>

using namespace std;



struct Process{

    

    int pname,at,bt,wt,tat,ct;

};



void scandata(vector<Process> &p,int n)

{

    for(int i=0;i<n;i++)

    {

        p[i].pname = i+1;

        cout<<"Enter data for Process "<<i+1<<": "<<endl;

        cout<<"Enter Arrival Time : ";

        cin>>p[i].at;

        cout<<"\nEnter Burst Time : ";

        cin>>p[i].bt;        

    }

}



void printdata(vector<Process> &p,int n)

{

    cout<<"\nPid"<<"   "<<"AT"<<"   "<<"BT"<<"   "<<"WT"<<"   "<<"TAT"<<"   "<<endl;

    for(int i=0;i<n;i++)

    {

        cout<<p[i].pname<<"   "<<p[i].at<<"   "<<p[i].bt<<"   "<<p[i].wt<<"   "<<p[i].tat<<endl;

    }

}



void roundrobin(vector<Process> &p,int n)

{

    int tq;

    cout<<"Enter Time Quantum: ";

    cin>>tq;

    

    int time = 0;

    int count = 0;

    int pending = n;

    

    vector<int> fin(n),rem_bt(n);

    

    for(int i=0;i<n;i++)

    {

        fin[i] = 0;

        rem_bt[i] = p[i].bt;

        p[i].wt = 0;

    }

    

    while(pending > 0)

    {

        if(fin[count] != 1 && p[count].at <= time && rem_bt[count] <= tq)

        {

            time += rem_bt[count];

            fin[count] = 1;

            pending--;

            

            p[count].wt -= p[count].at;

            p[count].tat = p[count].wt + p[count].bt;

            

            //Printing Gantt Chart

            

            for(int i=0;i<rem_bt[count];i++)

            {

                cout<<p[count].pname<<" ";

            }

            

            for(int i=0;i<n;i++)

            {

                if(i == count || fin[i] == 1)

                {

                    continue;

                }

                

                p[i].wt += rem_bt[count];

            }

            rem_bt[count] = 0;

        }

        else if(fin[count] != 1 && p[count].at <= time && rem_bt[count] > tq)

        {

            time += tq;

            rem_bt[count] -= tq;

            

            //Printing Gantt Chart

            

            for(int i=0;i<tq;i++)

            {

                cout<<p[count].pname<<" ";

            }

            

            for(int i=0;i<n;i++)

            {

                if(i == count || fin[i] == 1)

                {

                    continue;

                }

                

                p[i].wt += tq;

            }

            

        }

        count = (count+1) % n;

    }

    

    double avg_wait_time = 0;

    double avg_tat_time = 0;

    

    for(int i=0;i<n;i++)

    {

        avg_wait_time += p[i].wt;

        avg_tat_time += p[i].tat;

    }

    

    cout<<"\nAverage Wait Time: "<< (avg_wait_time / (double) n);

    cout<<"\nAverage TurnAround Time: "<< (avg_tat_time / (double) n);

    

}



static bool compare(Process &a, Process &b)

{

	if(a.at == b.at)

		return a.bt < b.bt;

	

	return a.at < b.at;

}



void sjf_prem(vector<Process>& p,int n)

{

	vector<int> visited(n);

	vector<int> rem_bt(n);



	for(int i=0;i<n;i++)

	{

		visited[i] = 0;

		rem_bt[i] = p[i].bt;

		p[i].ct = 0; 

	}



	int process = 0;

	int time = 0;



	time = p[0].at;

	rem_bt[0] -= 1;



	if(rem_bt[0] == 0)

	{

		process++;

		visited[0] = 1;

	}



	time++;



	cout<<"Printing Gantt Chart: ";

	cout<<"P"<<p[0].pname<<" | ";



	p[0].ct = time;



	while(process < n)

	{

		int min_id = -1;

		int mintime = 9999;



		for(int i=0;i<n;i++)

		{

			if(visited[i] != 1 && p[i].at <= time && rem_bt[i] < mintime)

			{

				min_id = i;

				mintime = rem_bt[i];

			}

		}



		cout<<"P"<<p[min_id].pname<<" | ";



		time++;		// It will continue on its own, it does not depend on other.



		if(min_id != -1 && visited[min_id] != 1)

		{

			p[min_id].ct = time;

			rem_bt[min_id] -= 1;

			if(rem_bt[min_id] == 0)

			{

				process++;

				visited[min_id] = 1;

			}

		}

	}



	double avg_wt = 0,avg_tat = 0;



	for(int i=0;i<n;i++)

	{

		p[i].tat = p[i].ct - p[i].at;

		p[i].wt = p[i].tat - p[i].bt;



		avg_tat += p[i].tat;

		avg_wt += p[i].wt;

	}



	cout<<"\nAverage Waiting Time: "<<(avg_wt / (double) n);

	cout<<"\nAverage Turn Around Time: "<<(avg_tat / (double) n);

}





int main()

{

    int n;

    cout<<"Enter no. of Processes: ";

    cin>>n;

    

    vector<Process> p(n);

    scandata(p,n);

    //roundrobin(p,n);

    sort(p.begin(),p.end(),compare);

    sjf_prem(p,n);

    printdata(p,n);

    

    return 0;

}