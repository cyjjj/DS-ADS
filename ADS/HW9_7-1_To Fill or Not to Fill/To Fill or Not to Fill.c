/* Greedy
Gas stations are sorted increasingly by distance
At each station,look for the first station within the maximum distance that is cheaper than the current station
If there is no cheaper one than current station, look for the cheapest
If found,check if there is enough gas to drive there,skip if enough; if not enough, buy just enough
If not found,buy until the tank is full
*/
#include <stdio.h>
#include <stdlib.h>

struct node {
	double price; //the unit gas price
	double distance; //the distance between this station and Hangzhou
};

int cmp(const void *a, const void *b)//qsort
{
	struct node *na = (struct node*)a;
    struct node *nb = (struct node*)b;
    if(na->distance != nb->distance)
        return na->distance - nb->distance;//distance increasingly
}

int main()
{
	double Cmax; //the maximum capacity of the tank
	double D; //the distance between Hangzhou and the destination city
	double Davg; //the average distance per unit gas that the car can run
	int N; //the total number of gas stations
	int i;
	
	scanf("%lf %lf %lf %d", &Cmax, &D, &Davg, &N);
	struct node station[N + 1];
	for (i = 0; i < N; i++)
		scanf("%lf %lf", &station[i].price, &station[i].distance);
	station[N].price = 0;
	station[N].distance = D;//destination
	qsort(station, N + 1, sizeof(struct node), cmp);
	
	double MaxDis = 0.0, CurrentTank = 0.0, TotalPrice = 0.0;
	    int position = 0;
	if(station[0].distance != 0)
	{
	    //no gas at the beginning point
		printf("The maximum travel distance = 0.00");
	} 
	else 
	{
		while(station[position].distance < D)//not arrive 
		{
			MaxDis = station[position].distance + Cmax * Davg; //maximum distance
			double MinPrice = station[position + 1].price;
			int NextNode = -1, flag = 0;
			for(i = position + 1; i < N + 1 && station[i].distance <= MaxDis && !flag; i++) 
			{
				if(station[i].price <= MinPrice) 
				{
					MinPrice = station[i].price;
					NextNode = i; //look for the cheapest
					if(station[i].price < station[position].price)
					   flag = 1; //found the first station cheaper than current station within maximum distance 
				}
			}
			
			if(NextNode != -1) //can reach the next station
			{
				double NeedTank = (station[NextNode].distance - station[position].distance) / Davg;
                if(flag) //check if there is enough gas to drive there
				{
					if(NeedTank <= CurrentTank) //already enough
						CurrentTank = CurrentTank - NeedTank;
					else //not enough
					{
						TotalPrice +=  (NeedTank - CurrentTank) * station[position].price;
                        CurrentTank = 0.0;
					}
                }
				else //buy gas until the tank is full
				{
                    TotalPrice += (Cmax - CurrentTank) * station[position].price;
                    CurrentTank = Cmax - NeedTank;
                }
			}
			else //cannot reach the next station
			{
				printf("The maximum travel distance = %.2lf", MaxDis);
				return 0;
			}
			
			position = NextNode;
		}
		
		//arrive at the destination
		printf("%.2lf", TotalPrice);
	}
	return 0;
}
