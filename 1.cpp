#include <vector>
#include <unordered_map>
#include <utility>

using namespace std;

typedef std::pair<int, int> indexAndTimes;

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        std::unordered_map<int, int> mapNums;
        for (size_t i = 0; i < nums.size(); i++)
        {
            mapNums[nums[i]] = i;
        }
        
        for (int i = 0; i < nums.size(); i++)
        {
            int base = nums[i];
            int reciprocal = target - nums[i];
            if(mapNums.contains(reciprocal) && mapNums.at(reciprocal) != i)
            {
                return std::vector<int>({i, mapNums.at(reciprocal)});
            }
        }
        return std::vector<int>({0,0});
    }
};

int main(int argc, char const *argv[])
{
    Solution sol;

    vector<int> nums = {3,2,4};
    int target = 6;

    std::vector<int> solution = sol.twoSum(nums, target);


    return 0;
}
