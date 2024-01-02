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

        // These two loops use an if that only triggers in the first iteration,
        // and the rest always flow through the `else`s. Let's remove those
        // branches! We'll also propagate the initial value for `accum`, and
        // simplify `a = a * b` to `a *= b`.

        // left: we want to process i - 1 before i
        {
            int accum = 1;
            left_products[0] = 1;
            for (size_t i = 1; i < nums.size(); i++) {
                accum *= nums[i - 1];
                left_products[i] = accum;
            }
        }

        auto right_products = std::make_unique<int[]>(nums.size());

        {
            // right: we want to process i + 1 before i
            int accum = 1;
            right_products[nums.size() - 1] = 1;
            for (size_t i = nums.size() - 1; i > 0;) {
                --i;
                accum *= nums[i + 1];
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
