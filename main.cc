#include <cstddef>
#include <memory> // we'll need this one to allocate arrays.
#include <vector>

class Solution {
  public:
    // Opcount: n lefts + n rights + n left*rights + memset(n, 0).
    // ≈ 3n + (n + 7)/8. O(n)
    // Space: n results + 1 accum (shared between two scopes) = n + 1. O(n).
    std::vector<int> productExceptSelf(std::vector<int> &nums) {

        // There's no need to create two new arrays and reduce them later, we
        // can do a couple of tricks to reuse the memory for results. We have to
        // make `results` (vector) act like an array. C++ doesn't provide us
        // with an easy way to initialize the values of the vector with custom
        // code, so we'll have to set a default value first and then write it
        // again.
        //
        // In practice, this will use memset(), which is fairly optimized on
        // machines that support avx2 (which nowadays is expected in a server
        // rack) to set values in blocks of 32,16,8,4, and 1 bytes. Since our
        // ints are 4 bytes, we'll have blocks of 8,4,2, and 1 ints. As n tends
        // to be large, most of the written blocks will be of 8 ints, so I'll
        // use that to approximate the opcount:
        //
        // memset_time(n) := (n + 7)/8 + (n % 8)/4 + (n % 4)/2 + n % 2
        // memset_time(n) ≈ (n + 7)/8, for n much larger than 8
        //
        // If that memset is too slow (n/8 is still too big), we could wrap the
        // left pass in a C++ iterator implementation, and use the std::vector
        // constructor that accepts a begin & end iterator so it writes the left
        // products on the first pass, removing the extra "set default" pass.
        // This can be pretty cumbersome and its effect is only good for pretty
        // huge inputs: we have GBps zero write speeds on our RAM, so we need
        // heaps of data to make that noticeable over our slower multiply loops.
        // So I've left it out as an exercise for the reader to find out if it's
        // worth it or not.

        // Choosing 0 since it's easy to load into an avx2 register, and a lot
        // of optimizations come around in hardware when writing & reading
        // zeroes. We'll overwrite them anyway.
        std::vector<int> result(/* length */ nums.size(), /* default */ 0);

        // left: we want to process i - 1 before i
        {
            int accum = 1;
            result[0] = 1;
            for (size_t i = 1; i < nums.size(); i++) {
                accum *= nums[i - 1];
                // This loop is the first pass, so it must overwrite the values.
                result[i] = accum;
            }
        }

        {
            // right: we want to process i + 1 before i
            int accum = 1;
            // Would be:
            // results[nums.size() - 1] *= 1;
            // Which obviously isn't needed.
            for (size_t i = nums.size() - 1; i > 0;) {
                --i;
                accum *= nums[i + 1];
                // This loop is the second pass, so it must multiply the values.
                // It calculates accum (right_products[i]). It knows the last
                // pass set result[i] = left_products[i], so we're doing:
                // result[i] = left_products[i] * right_products[i]
                result[i] *= accum;
            }
        }

        return result;
    }
};
