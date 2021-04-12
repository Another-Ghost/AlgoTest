#include "String.h"
#include <iostream>
#include<algorithm>
#include <vector>
#include <string>


//MiHoYo 3/27 1
//��������

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
			if (i == s_sub.size() - 1) {  //��֪��Ϊ�Σ� �ж��������s.size(),����unsigned int�ķ�ʽ�����ж��� ���i=-1��Զ����������
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
	cout << "������һ��ȫ����д���ַ�����";
	string str;
	cin >> str;
	///תСд
	transform(str.begin(), str.end(), str.begin(), tolower);
	///transform(wstr.begin(), wstr.end(), wstr.begin(), towlower);
	cout << "ת��ΪСд��Ϊ��" << str << endl;

	///ת��д
	cout << "��������һ��ȫ��Сд���ַ�����";
	string s;
	cin >> s;
	transform(s.begin(), s.end(), s.begin(), toupper);
	///transform(wstr.begin(), wstr.end(), wstr.begin(), towupper);
	cout << "ת��Ϊ��д��Ϊ��" << s;
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
			while (arr[bit + bias] >= 10) //�����λ�����ѭ��
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