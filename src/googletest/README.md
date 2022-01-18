# Usage of Google Test in Module "Testen"

This is branch `testen/fused` of our modification of [Google Test][].
In this branch, we have replaced the original `cmake` build
configuration by project files to be used with `qmake`, which we are
using in other projects, and we have 'fused' the multiple source files
into only three files: `gtest/gtest.h`, `gmock/gmock.h` and
`gmock-gtest-all.cc`.

[Google Test]: https://github.com/google/googletest.git

We maintain the following branches in our repository:

* branch `master` which will follow the original [Google Test][]
  repository
* branch `testen/master` which only replaces `cmake` by `qmake`
* branch `testen/fused` which provides a minimal file set top copy into
  other projects

If you want to use googletest for your own projects, you should consider
using the original [Google Test][] with `cmake`, as it is much more
tested - unless you use `qmake` already and want to take our `qmake`
project files, but then it's at your own risk.

If you want to use this fused version, you should consider to copy just
the necessary files into your project, instead of using a (more complex)
`git submodule` approach.

## Where it comes from

The original git repository is available via

```
git clone https://github.com/google/googletest.git
```

We cloned and modified this repository to use it in the module "Testen"
of the study course "Angewandte Informatik" at Worms University of Applied
Sciences.

## Documentation

The original documentaion is available at [Google Test][].

You may use
[our copy](https://atlas.ai.it.hs-worms.de/bitbucket/projects/TST/repos/googletest/browse)
of the repository. Don't miss the
* [Google Test Primer](https://atlas.ai.it.hs-worms.de/bitbucket/projects/TST/repos/googletest/browse/googletest/docs/Primer.md)
* [Google Mock Documentation](https://atlas.ai.it.hs-worms.de/bitbucket/projects/TST/repos/googletest/browse/googlemock/README.md)

