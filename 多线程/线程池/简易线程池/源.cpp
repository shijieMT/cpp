
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>

using namespace std;

//class Solution {
//public:
//    /**
//     * Note: 类名、方法名、参数名已经指定，请勿修改
//     *
//     *
//     * 根据价格列表和当前点券数，计算出能买到的最多英雄
//     * @param costs int整型 vector 英雄点券价格列表
//     * @param coins int整型  拥有的点券
//     * @return int整型vector
//     */
//    vector<int> solution(vector<int>& costs, int coins) {
//        // write code here
//        int n = costs.size();
//        vector<vector<int>> dp(n + 1, vector<int>(coins + 1, 0));
//        vector<vector<int>> buy(n + 1, vector<int>(coins + 1, 0));
//        vector<vector<int>> prev(n + 1, vector<int>(coins + 1, -1));
//        for (int i = 1; i <= n; i++)
//        {
//            int cur_cost = costs[i - 1];
//            for (int j = 0; j <= coins; j++) {
//                // 买
//                int num1 = -1;
//                if (j >= cur_cost) {
//                    num1 = dp[i - 1][j - cur_cost] + 1;
//                }
//                // 不买
//                int num2 = 0;
//                num2 = dp[i - 1][j];
//                if (num1 > num2) {
//                    buy[i][j] = 1;
//                    prev[i][j] = j - cur_cost;
//                    dp[i][j] = num1;
//                }
//                else {
//                    buy[i][j] = 0;
//                    prev[i][j] = j;
//                    dp[i][j] = num2;
//                }
//            }
//        }
//        vector<int> ans;
//        int cur_index = coins;
//        for (int i = n; i > 0; i--) {
//            if (buy[i][cur_index] == 1) {
//                ans.push_back(costs[i - 1]);
//                cur_index = prev[i][cur_index];
//            }
//            else {
//                cur_index = prev[i][cur_index];
//            }
//        }
//        reverse(ans.begin(), ans.end());
//        return ans;
//    }
//};



//class Solution {
//   /* bool cmp(string s1, string s2)const
//    {
//        int len = min(s1.size(), s2.size());
//        for (int i = 0; i < len; i++)
//        {
//            char& c1 = s1[i];
//            char& c2 = s2[i];
//            if (c1 < c2)return false;
//            else if (c1 > c2)return true;
//            else {
//                continue;
//            }
//        }
//        if (s1.size() < s2.size())
//            return false;
//        else {
//            return true;
//        }
//    }*/
//public:
//    /**
//     * Note: 类名、方法名、参数名已经指定，请勿修改
//     *
//     *
//     *
//     * @param nums int整型 vector
//     * @return string字符串
//     */
//    string LargestNum(vector<int>& nums) {
//        vector<string> arr;
//        for (auto& e : nums) {
//            arr.push_back(to_string(e));
//        }
//        sort(arr.begin(), arr.end(), [](string s1, string s2) {
//            int len = min(s1.size(), s2.size());
//            for (int i = 0; i < len; i++)
//            {
//                char& c1 = s1[i];
//                char& c2 = s2[i];
//                if (c1 < c2)return false;
//                else if (c1 > c2)return true;
//                else {
//                    continue;
//                }
//            }
//            if (s1.size() < s2.size())
//                return true;
//            else {
//                return false;
//            }
//            });
//
//        string ans;
//        for (auto& e : arr) {
//            ans += e;
//        }
//        return ans;
//    }
//};

//int main()
//{
//    vector<int> v = { 0,1, 98, 989, 898 };//98 + 989 +898 + 1 + 0
//    //                                                         989 + 98
//    Solution s;
//   cout << s.LargestNum(v);
//
//    ;
//}


#include"ThreadPool.hpp"

int main()
{


	TaskQueue taskqueue;
	auto task1 = []() {
		cout << "hello word" << endl;
		cout << this_thread::get_id << " :ehkllo" << endl; 
	};
	auto task2 = []() {
		cout << this_thread::get_id << " :helloe" << endl;
	};
	ThreadPool pool(1);
	int a = 3;
	pool.addTask(task1);
	pool.addTask(task1);
	pool.addTask(task2);
	pool.addTask(task2);
}