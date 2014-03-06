#include <string>
#include <vector>
#include <iostream>

using namespace std;


class Solution {
public:
    int longestValidParentheses(string s) {
		//todo:1. convert the "s" to a integration curve
		//todo:2. find the summit value and peak position
        int len = s.size();
		int res = 0;
		integ.clear();
		integ.push_back(res);
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
		if (len < 2)
			return 0;
		else
			return getValidLength(0,len);

    }
	int getValidLength(int start,int end)
	{
		if ((end-start) < 2)
			return 0;
		vector<int> temp = findSummit(start,end);
		if (temp.front()==start && temp.back()==end)
			return end-start;
		int ll,lr,ml,mr,rl,rr;
		if(temp.size() == 2)
		{
			ll = start;    lr = temp.front() - 1;
			ml = temp.front();  mr = temp.back();
			rl = temp.back()+1;rr = end;
		}
		else
			return -1;
		int ls = 0,ms = 0,rs = 0;
		if ((lr-ll) >= 2)	
			ls = getValidLength(ll,lr);
		if ((mr-ml) >= 2)  
			ms = getValidLength(ml,mr);
		if ((rr-rl) >= 2)  
			rs = getValidLength(rl,rr);
		int max = ls;
		if(ms > max) max = ms;
		if(rs > max) max = rs;
		return max;
	}
	vector<int> findSummit(int start,int end)
	{
		int left = start,right = start;
		vector<int> temp;
		int max = integ[left];
		for (int i=start+1;i<=end;i++)
		{
			if(integ[i] < max)
				continue;
			else if(integ[i] == max)
				right = i;
			else
			{
				left = right = i;
				max = integ[i];
			}
		}
		temp.push_back(left);
		temp.push_back(right);
		return temp;
	}
private:
	vector<int> integ;
};