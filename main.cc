#include <cstddef>
#include <memory> // we'll need this one to allocate arrays.
#include <vector>

class Solution {
  public:
    // We've already reached the target efficiency: O(n).
    // From here we'll be reducing & simplifying the code so that we get more
    // performance, which means reducing the constants that come before the
    // `n`s. Some of these can be automatically done by compilers, others
    // require human intervention since they're about changing data structures,
    // not just reordering code.

    // Our first step will be inlining our helper functions to understand how
    // our loops behave. This way we can understand better direct dependencies
    // between variables.

    // Opcount: n lefts + n rights + n left*rights = 3n. O(n).
    // Space: n left products + n right products + n results = 3n. O(n).
    std::vector<int> productExceptSelf(std::vector<int> &nums) {

        auto left_products = std::make_unique<int[]>(nums.size());

        // left: we want to process i - 1 before i
        for (size_t i = 0; i < nums.size(); i++) {
            if (i == 0) {
                left_products[i] = 1;
            } else {
                left_products[i] = left_products[i - 1] * nums[i - 1];
            }
        }

        auto right_products = std::make_unique<int[]>(nums.size());

        // right: we want to process i + 1 before i
        for (size_t i = nums.size(); i > 0;) {
            --i;
            if (i == nums.size() - 1) {
                right_products[i] = 1;
            } else {
                right_products[i] = right_products[i + 1] * nums[i + 1];
            }
        }

        std::vector<int> result;

        for (size_t i = 0; i < nums.size(); ++i) {
            result.push_back(left_products[i] * right_products[i]);
        }

        return result;
    }
};
