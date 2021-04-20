#include "String.h"
#include <iostream>
#include<algorithm>
#include <vector>
#include <string>


//MiHoYo 3/27 1
//数字序列

//string s("1807700018888800007");
void NumberSequence(const string& s)
{
	string s_sub("1807");

	//string s;
	//cin >> s;

	int i = 0;
	int len = 0;
	int len_max = 0;

	for (auto ch : s)
	{

		if (ch == s_sub[i])
		{
			++len;
		}
		else if (i < s_sub.size() - 1 && ch == s_sub[i + 1])
		{
			++i;
			++len;
		}
		else
		{
			if (i == s_sub.size() - 1) {  //不知道为何， 判定语句中有s.size(),会以unsigned int的方式进行判定， 如果i=-1永远不可能判中
				len_max = max(len_max, len);
			}
			len = 0;
			i = 0;

			if (ch == s_sub[i])
			{
				++len;
			}
		}
	}
	if (i == s_sub.size() - 1)
		len_max = max(len_max, len);

	cout << len_max << endl;

}

void ToLowerAndToUpper()
{
	cout << "请输入一个全部大写的字符串：";
	string str;
	cin >> str;
	///转小写
	transform(str.begin(), str.end(), str.begin(), tolower);
	///transform(wstr.begin(), wstr.end(), wstr.begin(), towlower);
	cout << "转化为小写后为：" << str << endl;

	///转大写
	cout << "请再输入一个全部小写的字符串：";
	string s;
	cin >> s;
	transform(s.begin(), s.end(), s.begin(), toupper);
	///transform(wstr.begin(), wstr.end(), wstr.begin(), towupper);
	cout << "转化为大写后为：" << s;
}


string addStrings(string num1, string num2) {
	if (num1.size() < num2.size())
		return addStrings(num2, num1);

	vector<int> arr1;
	vector<int> arr2;
	for (int i = arr1.size() - 1; i >= 0; --i)
		arr1.push_back(num1[i] - '0');
	for (int i = arr2.size() - 1; i >= 0; --i)
		arr2.push_back(num2[i] - '0');

	vector<int> arr3;
	int n = 0;
	for (int i = 0; i < arr1.size(); ++i)
	{
		n += arr1[i];
		if (i < arr2.size())
			n += arr2[i];
		arr3.push_back(n % 10);
		n /= 10;
	}

	if (n)
		arr3.push_back(n);

	string res;
	for (int i = arr3.size() - 1; i >= 0; --i)
		res += to_string(arr3[i]);

	return res;
}

//不是效率最高的方法
string multiply(string num1, string num2) {
	//vector<int> arr1;
	//vector<int> arr2;
	//for(int i = arr1.size() - 1; i >= 0; --i)
	//    arr1.push_back(num1[i] - '0');
	//for(int i = arr2.size() - 1; i >= 0; --i)
	//   arr2.push_back(num2[i] - '0');
	if (num1 == "0" || num2 == "0")
		return "0";
	int m = num1.size();
	int n = num2.size();
	vector<int> arr(m + n);
	for (int i = m - 1; i >= 0; --i)
		for (int j = n - 1; j >= 0; --j)
		{
			int bias = 0;
			int bit = m + n - i - j - 2;
			arr[bit] += (num1[i] -'0') * (num2[j] - '0');
			while (arr[bit + bias] >= 10) //如需进位则继续循环
			{
				arr[bit + 1 + bias] += arr[bit + bias] / 10;
				arr[bit + bias] %= 10;
				++bias;
			}
		}
	int i;
	for (i = n + m - 1; i >= 0; --i)
		if (arr[i] != 0)
			break;

	string ans;
	for (int j = i; j >= 0; --j)
		ans.push_back(arr[j] + '0');

	return ans;

}

void dfs(int dep, const string& input, const vector<string>& bottons, string& out, vector<string>& outs)
{
	if (dep > input.size() - 1) {
		outs.push_back(out);
		return;
	}
	int num = input[dep] - '0';
	for (int i = 0; i < bottons[num].size(); ++i)
	{
		out.push_back(bottons[num][i]);
		dfs(dep + 1, input, bottons, out, outs);
		out.erase(dep);
	}
}

vector<string> letterCombinations(string digits) {
	vector<string> ans;

	vector<string> bottons(10);
	bottons[2] = "abc";
	bottons[3] = "def";
	bottons[4] = "ghi";
	bottons[5] = "jkl";
	bottons[6] = "mno";
	bottons[7] = "pqrs";
	bottons[8] = "tuv";
	bottons[9] = "wxyz";

	string input;
	cin >> input;

	string out;

	dfs(0, input, bottons, out, ans);

	return ans;
}

bool IsEqual(const string& a, const string& b)
{
	int n = a.size();
	if (n % 2 == 1)
	{
		for (int i = 0; i < n; ++i)
		{
			if (a[i] != b[i])
			{
				return false;
			}
		}
		return true;
	}
	else if (n % 2 == 0)
	{
		string a_first(a, 0, n / 2);
		string a_second(a, n / 2, n / 2);
		string b_first(b, 0, n / 2);
		string b_second(b, n / 2, n / 2);
		return IsEqual(a_first, b_first) || IsEqual(a_second, b_second);
	}

	return true;
}

void EqualString()
{
	int t;
	cin >> t;
	while (t--)
	{
		string a, b;
		cin >> a;
		cin >> b;

		if (IsEqual(a, b))
			puts("YES");
		else
			puts("NO");
	}

}