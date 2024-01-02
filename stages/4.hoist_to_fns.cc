#include <cstddef>
#include <vector>

class Solution {
  public:

    // We know these are distinct operations, so we can move these to separate
    // functions for easier analysis:

    int left_product(size_t excluded_index, std::vector<int> &nums) {
        int left_product = 1;
        for (size_t i = 0; i < excluded_index; ++i) {
            left_product *= nums[i];
        }
        return left_product;
    }

    int right_product(size_t excluded_index, std::vector<int> &nums) {
        int right_product = 1;
        for (size_t i = excluded_index + 1; i < nums.size(); ++i) {
            right_product *= nums[i];
        }
        return right_product;
    }

    int helper(size_t excluded_index, std::vector<int> &nums) {
        return left_product(excluded_index, nums) *
               right_product(excluded_index, nums);
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
