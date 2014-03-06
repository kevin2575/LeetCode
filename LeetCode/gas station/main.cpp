#include <vector>
#include <iostream>
using namespace std;

int canCompleteCircuit(vector<int> &gas, vector<int> &cost) ;

int main() {
	vector<int> gas ;
	vector<int> cost;
	gas.push_back(2);
	gas.push_back(4);
	cost.push_back(3);
	cost.push_back(4);
	int k = canCompleteCircuit(gas,cost);
	cout<<k<<endl;
	system("pause");
	return 0;
}

int canCompleteCircuit(vector<int> &gas, vector<int> &cost) 
{
	int len = gas.size();
	int remain = 0;
	vector<int> dif;
	for (int i=0;i<len;i++)
	{
		dif.push_back(gas[i] - cost[i]);
	}
	for(int i=0;i<len;i++)
	{
		remain = 0;
		int j = 0;
		for(j=0;j<len;j++)
		{
			remain += dif[(i+j)%len];
			if(remain < 0)
			{
				i += j;
				break;
			}
		}
		if(j==len) 
		{
			return i;
		}
	}
	return -1;
}