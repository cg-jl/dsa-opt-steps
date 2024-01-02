#include <cstddef>
#include <vector>

class Solution {
  public:
    int helper(int num, std::vector<int> &nums) {
        int product = 1;

        for (size_t i = 0; i < nums.size(); i++) {
            if (i != num)
                product *= nums[i];
        }
        return product;
    }

    // Opcount: n*(n - 1) multiplications. O(n^2)
    // Space: n ints for result. O(n).
    std::vector<int> productExceptSelf(std::vector<int> &nums) {
        std::vector<int> result;
        for (size_t i = 0; i < nums.size(); i++)
            result.push_back(helper(i, nums));
        return result;
    }
};
