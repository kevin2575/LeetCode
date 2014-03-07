#include "solution.h"

int main() {
	Solution s;
	int len = s.longestValidParentheses("(((()))))((()))");
	cout<<len<<endl;
	system("pause");
	return 0;
}