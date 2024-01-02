# DSA dynamic programming example

This is a quick repo where I explain the different stages that I could follow
when optimizing an algorithm. Thanks to this, caching has started clicking for
me! 

## How to traverse the changes

The file `main.cc` goes through a series of patches that can be viewed in each
commit. The full source files for each stage are in [`stages/`](./stages), and
the patch files that generate the diffs for [`main.cc`](./main.cc) are in
[`patches/`](./patches). You can go to a commit and then keep advancing commits
to see how `main.cc` changes, or instead follow the patches manually by first
copying `stages/1.initial.cc` to a different file and applying each patch from
[`patches`](./patches) in succession. 

Note that patches have the name of the stage the file ends up in, so applying
`7.cache.patch` to `stages/6.align_topological_order.cc` yields
`stages/7.cache.cc`.
