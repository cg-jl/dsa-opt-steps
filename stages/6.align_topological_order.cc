#include <cstddef>
#include <memory> // we'll need this one to allocate arrays.
#include <vector>

class Solution {
  public:
    // left_product(0) <- [] (no dependencies)
    // left_product(i) <- left_product(i - 1), nums(i - 1)

    int left_product(size_t excluded_index, std::vector<int> &nums) {
        if (excluded_index == 0)
            return 1;
        return left_product(excluded_index - 1, nums) *
               nums[excluded_index - 1];
    }

    // right_product(n) <- [] (no dependencies)
    // right_product(i) <- right_product(i + 1), nums(i + 1)

    int right_product(size_t excluded_index, std::vector<int> &nums) {
        if (excluded_index == nums.size())
            return 1;
        return right_product(excluded_index + 1, nums) *
               nums[excluded_index + 1];
    }

    // Opcount: n*(n - 1) multiplications. O(n^2)
    // Space: 
    //  - n frames for left_product, then reuse n for right_product.
    //  - n left products, n right products.
    //  - n results:
    //  Total: n + 2n + n = 4n. O(n)
    std::vector<int> productExceptSelf(std::vector<int> &nums) {

        // Since the topological ordering of the operations for each product is
        // different, we have to split our algorithm in two loops, so that we
        // can have the last result for  both products.
        //
        // Here it means distributing the multiplication of left and right
        // values. Since we have to keep all the left multiplications before we
        // do the right multiplications, we need n variables to store those
        // intermediate values.

        // Note that since multiplication is commutative, it doesn't matter if
        // we start by defining the left values or if we start by defining the
        // right values. We have to choose the ordering here because we're
        // single threaded, so we have to do one task first and then the other.

        // To avoid ordering shenanigans by having to push in order, we'll
        // pre-allocate both arrays so that we can set them with our running
        // index.
        auto left_products = std::make_unique<int[]>(nums.size());

        // left: we want to process i - 1 before i
        for (size_t i = 0; i < nums.size(); i++) {
            left_products[i] = left_product(i, nums);
        }

        auto right_products = std::make_unique<int[]>(nums.size());

        // right: we want to process i + 1 before i
        for (size_t i = nums.size(); i > 0;) {
            --i;
            right_products[i] = right_product(i, nums);
        }

        std::vector<int> result;

        for (size_t i = 0; i < nums.size(); ++i) {
            result.push_back(left_products[i] * right_products[i]);
        }

        return result;
    }
};
