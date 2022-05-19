#include <iostream>
#include <algorithm>
#include <vector>
#include <climits>
#include <variant>
using namespace std;
#define ABS(a) ((a) >= 0 ? (a) : -(a))

class Solution
{
public:
    string licenseKeyFormatting(string s, int k)
    {
        int len = 0;
        string tem;
        for (int i = 0; i < s.length(); i++)
        {
            if (s[i] != '-')
            {
                if (s[i] >= 'a' && s[i] <= 'z')
                    s[i] -= 32;
                tem += s[i];
                len++;
            }
        }
        int a = len % k;
        if (a == 0)
            a = k;

        cout << len << "\n"
             << a;
        string o;
        for (int i = 0; i < tem.length(); i++)
        {
            if (a <= 0)
            {
                o += '-';
                a = k;
            }
            a--;
            o += tem[i];
        }
        return o;
    }
    int xorOperation(int n, int start)
    {
        int out = start;
        for (int i = 0; i < n; i++)
            out ^= (start + 2 * i);
        return out;
    }
    bool wordBreak(string s, vector<string> &wordDict)
    {
        int a = s.length() + 1;
        vector<bool> dp(a);
        dp[0] = 1;
        for (int i = 0; i < a; i++)
        {
            if (dp[i])
            {
                for (int j = 0; j < wordDict.size(); j++)
                {
                    int p = wordDict[j].length();
                    if (i + p >= a)
                        continue;
                    if (s.substr(i, p) == wordDict[j])
                        dp[i + p] = 1;
                }
            }
        }
        return dp[a - 1];
    }

    int GetCost(vector<int> a, vector<int> b)
    {
        return ABS(a[0] - b[0]) + ABS(a[1] - b[1]);
    }

    int minCostConnectPoints(vector<vector<int>> &points)
    {
        /*int cost = 0;
        int size = points.size();
        long long middx = 0, middy = 0;
        for (int i = 0; i < size; i++)
        {
            middx += points[i][0];
            middy += points[i][1];
        }
        vector<int> mid(2);

        mid[0] = middx / size;
        mid[1] = middy / size;
        int index = -1, dis = 0x3f3f3f3f;
        for (int i = 0; i < size; i++)
        {
            int tem = GetCost(mid, points[i]);
            if (tem < dis)
            {
                dis = tem;
                index = i;
            }
        }
        */
        int size = points.size();
        int cost = 0;
        for (int i = 0; i < size; i++)
        {
            vector<bool> iscon(size, 0);
            int co = GetWay(points, i, iscon);
            if (co < cost)
                cost = co;
        }
        return cost;
    }

    int GetWay(vector<vector<int>> &points, int p, vector<bool> &con)
    {
        int dis = 0x3f3f3f3f, index = -1;
        for (int i = 0; con[i] == false && i != p && i < points.size(); i++)
        {
            int tem = GetCost(points[p], points[i]);
            if (tem < dis)
            {
                index = i;
                dis = tem;
            }
        }
        if (index != -1)
        {
            con[index] = true;
            return dis + GetWay(points, index, con);
        }
        return 0;
    }
};

union int2float
{
    int a;
    float b;
    int2float(int v) : a(v) {}
    int2float(float v) : b(v) {}
};

int main()
{
    // vector<int> p1(2), p2(2);
    // p1[0] = 0;
    // p1[1] = 0;
    // p2[0] = 2;
    // p2[1] = 2;
    // Solution so;
    // cout << so.GetCost(p1, p2);

    // system("Pause");
    // return 0;
    int2float m = 3.1f;
    std::cout << m.a << std::endl;
    std::cout << m.b << std::endl;
    std::variant<int, float> v = 3.1f;
    std::cout << std::get<int>(v) << std::endl;
    std::cout << std::get<float>(v) << std::endl;

    system("Pause");
    return 0;
}
