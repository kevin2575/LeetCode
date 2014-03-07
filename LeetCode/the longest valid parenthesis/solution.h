#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:
    int longestValidParentheses(string s) {
		//todo:1. convert the "s" to a integration curve
		//todo:2. find the summit value and peak position
		int mm = 0,len = s.size();
		while(mm<=len-1 && s[mm]==')') mm++;
		s.erase(0,mm);
		len = s.size();
		mm = len-1;
		while(mm>=0 && s[mm]=='(') mm--;
		s.erase(mm+1,len-1-mm);

		if(s.size()<2)
			return 0;

		int res = 0;
		integ.clear();
		integ.push_back(res);
		len = s.size();
		for(int i=0;i<len;i++)
		{
			if(s[i]=='(')
				res -= 1;
			else if(s[i] == ')')
				res += 1;
			else
				return 0;
			integ.push_back(res);
		}
		findPeaks();
		if (len < 2)
			return 0;
		vector<int> temp = findSummit(0,integ.size()-1);
		if(temp.size()==1)
		{
			if(temp[0]==0)
				return rightLength(0,integ.size()-1);
			else if(temp[0]==integ.size()-1)
				return leftLength(0,integ.size()-1);
			else
			{
				int a = leftLength(0,temp[0]-1);
				int b = rightLength(temp[0]+1,integ.size()-1);
				return a>b?a:b;
			}
		}
		else if(temp.size()==2)
		{
			int a = leftLength(0,temp[0]-1);
			int b = temp[1] - temp[0];
			int c = rightLength(temp[0]+1,integ.size()-1);
			int max = a;
			if(b>max) max = b;
			if(c>max) max = c;
			return max;
		}
    }
	int leftLength(int start,int end)
	{
		if((end-start)<2)
			return 0;
		int k = findLeftSummit(start,end);//ignore the last summit;
		int a = leftLength(0,k-1);
		int b = end - k - (integ[end] - integ[k]);
		return a>b?a:b;
	}
	int rightLength(int start,int end)
	{
		if((end-start)<2)
			return 0;
		int k = findRightSummit(start,end);
		int a = k-start-(integ[start]-integ[k]);
		int b = rightLength(k+1,end);
		return a>b?a:b;
	}
	int findRightSummit(int start,int end)
	{
		int max = -100000;
		int res = -1;
		for(int i=peaks.size()-1;i>=0;i--)
		{
			if(peaks[i]<start)
				break;
			if(integ[peaks[i]]>max)
			{
				max = integ[peaks[i]];
				res = peaks[i];
			}
		}
		return res;
	}
	int findLeftSummit(int start,int end)
	{
		int max = -100000;
		int res = -1;
		for (int i= 0;i<peaks.size();i++)
		{
			if(peaks[i]>end)
				break;
			if(integ[peaks[i]]>max)
			{
				max = integ[peaks[i]];
				res = peaks[i];
			}
		}
		return res;
	}
	vector<int> findSummit(int start,int end)
	{
		int left,right,ldown,lup;
		vector<int> temp;
		for(int i=0;i<peaks.size();i++)
		{
			if(peaks[i]==start)
				left = i;
			if(peaks[i] == end)
				right = i;
		}
		ldown = lup = peaks[left];
		int max = integ[ldown];
		for(int i=left+1;i<=right;i++)
		{
			if(integ[peaks[i]]<max)
				continue;
			else if(integ[peaks[i]]==max)
				lup = peaks[i];
			else
			{
				ldown = lup = peaks[i];
				max = integ[peaks[i]];
			}				
		}
		if(ldown==lup)
			temp.push_back(ldown);
		else
		{
			temp.push_back(ldown);
			temp.push_back(lup);
		}
		return temp;
	}
	void findPeaks()
	{
		peaks.push_back(0);
		for(int i=1;i<integ.size()-1;i++)
		{
			if(integ[i]>integ[i-1]&&integ[i]>integ[i+1])
				peaks.push_back(i);
		}
		peaks.push_back(integ.size()-1);
	}
private:
	vector<int> integ;
	vector<int> peaks;
};
