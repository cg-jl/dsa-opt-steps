#include <cstddef>
#include <vector>

class Solution {
  public:
    int helper(int num, std::vector<int> &nums) {
        int product = 1;

        // By separating the loops, now we know there are two
        // distinct operations: multiplications before and multiplications
        // after the skipped index.

        for (size_t i = 0; i < num; ++i) {
            product *= nums[i];
        }

        for (size_t i = num + 1; i < nums.size(); ++i) {
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
