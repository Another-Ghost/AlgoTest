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
