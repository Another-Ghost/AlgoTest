#include <iostream>
#include <vector>
#include <algorithm>
#include "Math.h"
#include "Sort.h"

using namespace std;


class Solution {
public:
    /**
     * �����е����������������������Ѿ�ָ���������޸ģ�ֱ�ӷ��ط����涨��ֵ����
     *
     *
     * @param intervals int����vector<vector<>>
     * @return int����vector<vector<>>
     */
    static bool Comp(vector<int> a, vector<int> b)
    {
        return a[0] <= b[0];
    }

    vector<vector<int> > split(vector<vector<int> >& intervals) {
        // write code here
        sort(intervals.begin(), intervals.end(), Comp);
        vector<vector<int>> ans;
        //ans.push_back(*intervals.begin());
        vector<int> tmp = *intervals.begin();
        if (tmp[0] > 0)
        {
            ans.push_back({ 1, tmp[0] });
        }
        for (int i = 1; i < intervals.size(); ++i)
        {
            if (intervals[i][0] > tmp[1])
            {
                tmp = intervals[i];
            }
            else
            {
                if (intervals[i][0] > tmp[0] + 1)
                {
                    if (intervals[i][1] > tmp[1])
                    {
                        ans.push_back({ tmp[0] + 1, intervals[i][0] });
                    }

                    if (intervals[i][1] > tmp[1])
                    {
                        tmp[0] = tmp[1] + 1;
                        tmp[1] = intervals[i][1];
                    }
                    else
                    {
                        //tmp[1] = [i][1];
                        tmp[0] = intervals[i][1];

                    }
                    //else
                    //{
                    //    tmp = intervals[++i];
                    //}
                }
                else
                {

                }
            }


        }
        return ans;
    }
};

int main()
{
    Solution solution;
    vector<vector<int>> intervals = { {1, 3},{9, 13},{2, 6},{13, 18} };

    solution.split(intervals);
	return 0;
}

