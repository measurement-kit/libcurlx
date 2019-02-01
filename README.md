# Measurement Kit cURL wrappers library

[![GitHub license](https://img.shields.io/github/license/measurement-kit/mkcurl.svg)](https://raw.githubusercontent.com/measurement-kit/mkcurl/master/LICENSE) [![Github Releases](https://img.shields.io/github/release/measurement-kit/mkcurl.svg)](https://github.com/measurement-kit/mkcurl/releases) [![Build Status](https://img.shields.io/travis/measurement-kit/mkcurl/master.svg?label=travis)](https://travis-ci.org/measurement-kit/mkcurl) [![codecov](https://codecov.io/gh/measurement-kit/mkcurl/branch/master/graph/badge.svg)](https://codecov.io/gh/measurement-kit/mkcurl) [![Build status](https://img.shields.io/appveyor/ci/bassosimone/mkcurl/master.svg?label=appveyor)](https://ci.appveyor.com/project/bassosimone/mkcurl/branch/master)

This header-only library contains Measurement Kit cURL wrappers. Its main
use case is vendoring of a specific tag inside Measurement Kit. Because this
is just a basic building block, we do not provide any stable API guarantee
for this library. For this reason, we'll never release `v1.0.0`.

To build and test:

```
go get -v github.com/bassosimone/mkbuild
cmake .
cmake --build .
ctest -a
```

See `.travis.yml` and `.appveyor.yml` for more options.
