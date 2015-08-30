/**
 * Given an array of integers, find two numbers such that they add up to 
 * a specific target number.
 *
 * The function twoSum should return indices of the two numbers such that
 * they add up to the target, where index1 must be less than index2. Please
 * note that your returned answers (both index1 and index2) are not zero-based.
 * 
 * You may assume that each input would have exactly one solution.

 * Input: numbers={2, 7, 11, 15}, target=9
 * Output: index1=1, index2=2
 */


/**
 * 最简单的办法，两层循环，时间复杂度是O(n^2)
 * 用unordered_map, 查找的时间复杂度是O(1), 所以整体的时间复杂度是O(n)
 * 另外需要注意的是
 * 1. nums中的元素可能有重复，所以要用undered_multimap
 * 2. 找到的第二个数不能是第一个数自己
 */
#include <unordered_map>

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        vector<int> vec;
        unordered_multimap<int, int> mymap;
        for(size_t i = 0; i < nums.size(); ++i) {
            mymap.insert(make_pair(nums[i], i));
        }
        
        for (auto it = mymap.begin(); it != mymap.end(); ++it) {
            int b = target - it->first;
            auto range = mymap.equal_range(b);
            if (range.first != mymap.end()) {
                auto it2 = range.first;
                if (it == it2) { ++it2; }
                if (it2 == range.second) { continue; }
                
                size_t index = it->second;
                size_t index2 = it2->second;
                if (index < index2) {
                    vec.push_back(index + 1);
                    vec.push_back(index2 + 1);
                } else {
                    vec.push_back(index2 + 1);
                    vec.push_back(index + 1);
                }
                break;
            } 
        }

        return vec;
    }
};

