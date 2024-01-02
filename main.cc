#include <cstddef>
#include <memory> // we'll need this one to allocate arrays.
#include <vector>

class Solution {
  public:
    // On these steps we've been taking, we've been making the algorithm worse
    // each time, so that we could analyze and align it.
    // Now that we're processing things in the correct order for caching,
    // let's use those caches!

    // Opcount: Since the "recurring" result is cached: O(1).
    // Space: No recursion so no frames need to be saved: O(1).
    int left_product(size_t excluded_index, std::vector<int> &nums,
                     int const left_products[]) {
        if (excluded_index == 0)
            return 1;
        return left_products[excluded_index - 1] * nums[excluded_index - 1];
    }

    // Opcount: Since the "recurring" result is cached: O(1).
    // Space: No recursion so no frames need to be saved: O(1).
    int right_product(size_t excluded_index, std::vector<int> &nums,
                      int const right_products[]) {
        if (excluded_index == nums.size() - 1)
            return 1;
        return right_products[excluded_index + 1] * nums[excluded_index + 1];
    }

    // Opcount: n lefts + n rights + n left*rights = 3n. O(n).
    // Space: n left products + n right products + n results = 3n. O(n).
    std::vector<int> productExceptSelf(std::vector<int> &nums) {

        auto left_products = std::make_unique<int[]>(nums.size());

        // left: we want to process i - 1 before i
        for (size_t i = 0; i < nums.size(); i++) {
            left_products[i] = left_product(i, nums, left_products.get());
        }

        auto right_products = std::make_unique<int[]>(nums.size());

        // right: we want to process i + 1 before i
        for (size_t i = nums.size(); i > 0;) {
            --i;
            right_products[i] = right_product(i, nums, right_products.get());
        }

        std::vector<int> result;

        for (size_t i = 0; i < nums.size(); ++i) {
            result.push_back(left_products[i] * right_products[i]);
        }

        return result;
    }
};
