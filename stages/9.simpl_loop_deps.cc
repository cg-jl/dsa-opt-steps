#include <cstddef>
#include <memory> // we'll need this one to allocate arrays.
#include <vector>

class Solution {
  public:
    // Opcount: n lefts + n rights + n left*rights = 3n. O(n).
    // Space: n left products + n right products + n results + 1 accum (shared
    // between two scopes) = 3n + 1. O(n).
    std::vector<int> productExceptSelf(std::vector<int> &nums) {

        auto left_products = std::make_unique<int[]>(nums.size());

        // We already know how many loop iterations apart is the last value. To
        // help the CPU and the compiler, we'll use a local variable to track
        // it, instead of using memory references. This way we avoid changing
        // the memory locations we're fetching from, which boosts our cache
        // usage.

        // left: we want to process i - 1 before i
        {
            int accum;
            for (size_t i = 0; i < nums.size(); i++) {
                if (i == 0) {
                    accum = 1;
                } else {
                    accum = accum * nums[i - 1];
                }
                left_products[i] = accum;
            }
        }

        auto right_products = std::make_unique<int[]>(nums.size());

        {
            // right: we want to process i + 1 before i
            int accum;
            for (size_t i = nums.size(); i > 0;) {
                --i;
                if (i == nums.size() - 1) {
                    accum = 1;
                } else {
                    accum = accum * nums[i + 1];
                }
                right_products[i] = accum;
            }
        }

        std::vector<int> result;

        for (size_t i = 0; i < nums.size(); ++i) {
            result.push_back(left_products[i] * right_products[i]);
        }

        return result;
    }
};
