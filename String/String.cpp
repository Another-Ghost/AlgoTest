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
