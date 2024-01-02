#include <cstddef>
#include <vector>

class Solution {
  public:
    int helper(int num, std::vector<int> &nums) {
        // Now that we know there are two distinct operations,
        // we can separate them further:

        int left_product = 1;
        for (size_t i = 0; i < num; ++i) {
            left_product *= nums[i];
        }

        int right_product = 1;
        for (size_t i = num + 1; i < nums.size(); ++i) {
            right_product *= nums[i];
        }

        return left_product * right_product;
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
