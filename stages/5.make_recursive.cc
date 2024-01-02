#include <cstddef>
#include <vector>

class Solution {
  public:
    // We notice that on each excluded_index, `left_product` is doing all of the
    // multiplications of the last iteration, then doing just one more. We can
    // define a recursive solution for it like this:
    // left_product(0) := 1
    // left_product(i) := left_product(i - 1) * nums[i - 1]
    // In terms of dependencies:
    // left_product(i) <- ("depends on") left_product(i - 1), nums(i - 1)

    // Opcount: i multiplications. O(n)
    // Space: One int (nums[i + 1) per reducing frame. O(n)
    int left_product(size_t excluded_index, std::vector<int> &nums) {
        if (excluded_index == 0)
            return 1;
        return left_product(excluded_index - 1, nums) *
               nums[excluded_index - 1];
    }

    // `right_product` is also doing duplicate work by multiplying the same
    // tail. We can re-define the current right_product as:
    // right_product(n - 1) := 1
    // right_product(i) := right_product(i + 1) * nums[i + 1]
    // There is another definition we could use, which uses the last iteration
    // instead of the next:
    // right_product(0) := prod(nums[1:])
    // right_product(i) := right_product(i - 1) / nums[i - 1]
    // But this one uses division, which is forbidden in the problem. We'll keep
    // the former.
    // As for dependencies:
    // right_product(i) <- right_product(i + 1), nums(i + 1)

    // Note that by making these recursive, we're dropping performance (the
    // constants that are removed from O notation) from the last one. Due to how
    // I've implemented it, we also have dropped in efficiency in space, since
    // now we're taking O(n) space too!. We still have the  efficiency in time
    // (O notation).
    // But now we know how we can relate one iteration to another
    // iteration that could potentially be done before, which is what enables us
    // to re-use already computed results.

    // Opcount: n - i multiplications. O(n)
    // Space: One int (nums[i + 1) per reducing frame. O(n)
    int right_product(size_t excluded_index, std::vector<int> &nums) {
        if (excluded_index == nums.size() - 1)
            return 1;
        return right_product(excluded_index + 1, nums) *
               nums[excluded_index + 1];
    }

    // Opcount: (i - 1) + (n - i) multiplications = n - 1. O(n)
    // Space: n for left_product, n for right_product. Since each returns before
    // the multiplication, we re-use the frames: n ints. O(n).
    int helper(size_t excluded_index, std::vector<int> &nums) {
        return left_product(excluded_index, nums) *
               right_product(excluded_index, nums);
    }

    // Opcount: n*(n - 1) multiplications. O(n^2)
    // Space: We re-use `helper`'s frame each iteration: n ints + n results: 2n. O(n)
    std::vector<int> productExceptSelf(std::vector<int> &nums) {
        std::vector<int> result;
        for (size_t i = 0; i < nums.size(); i++)
            result.push_back(helper(i, nums));
        return result;
    }
};
