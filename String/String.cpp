#include <iostream>
#include <string>
#include <vector>

using namespace std;

//MiHoYo 3/27 1
//��������
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
        else if (i<s_sub.size()-1 && ch == s_sub[i + 1])
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

void NumberSequence2(const string& s)
{
    for (int i = 0; i < s.size(); ++i)
    {
        
    }
}


int main()
{
    string s("1807700018888800007");

    NumberSequence(s);

    return 0;
}

