# wxInclude dependencies

|project|license [^_l]|description [dependencies]|version|source|diff [^_d]|
|-------|-------------|--------------------------|-------|------|----------|
|<a id='wxInclude' />[wxInclude](http://wiki.wxwidgets.org/Embedding_PNG_Images)|[wxWindows](http://wiki.wxwidgets.org/Embedding_PNG_Images 'assumed wxWindows license, since source can be downloaded from wxWiki')|embed resources into cross-platform code [pvt deps: _boost_]| | |  [intro]|
|<a id='boost' />[boost](http://www.boost.org/ 'Boost website')|[BSL-1.0](http://www.boost.org/users/license.html 'Boost Software License')|libraries that give C++ a boost [deps: _bzip2, zlib_]|[xpv1.92.0.3](https://github.com/externpro/boost/releases/tag/xpv1.92.0.3 'release')|[repo](https://github.com/externpro/boost 'github.com/externpro/boost') [upstream](https://github.com/boostorg/boost 'github.com/boostorg/boost')|[diff](https://github.com/externpro/boost/compare/boost-1.92.0...xpv1.92.0.3 'github.com/externpro/boost/compare/boost-1.92.0...xpv1.92.0.3') [native]|
|<a id='bzip2' />[bzip2](https://sourceware.org/bzip2/)|[bzip2-1.0.6](https://spdx.org/licenses/bzip2-1.0.6.html 'BSD-like, modified zlib license')|lossless block-sorting data compression library|[xpv1.0.8.5](https://github.com/externpro/bzip2/releases/tag/xpv1.0.8.5 'release')|[repo](https://github.com/externpro/bzip2 'github.com/externpro/bzip2') [upstream](https://github.com/opencor/bzip2 'github.com/opencor/bzip2')|[diff](https://github.com/externpro/bzip2/compare/bzip2-1.0.8...xpv1.0.8.5 'github.com/externpro/bzip2/compare/bzip2-1.0.8...xpv1.0.8.5') [intro]|
|<a id='zlib' />[zlib](https://zlib.net/ 'zlib website')|[Zlib](https://zlib.net/zlib_license.html 'zlib/libpng license, see https://en.wikipedia.org/wiki/Zlib_License')|a general-purpose lossless data-compression library|[xpv1.3.2.1](https://github.com/externpro/zlib/releases/tag/xpv1.3.2.1 'release')|[repo](https://github.com/externpro/zlib 'github.com/externpro/zlib') [upstream](https://github.com/madler/zlib 'github.com/madler/zlib')|[diff](https://github.com/externpro/zlib/compare/v1.3.2...xpv1.3.2.1 'github.com/externpro/zlib/compare/v1.3.2...xpv1.3.2.1') [patch]|

![deps](xprodeps.svg 'dependencies')

Dependency version check: all 3 parent-manifest versions match pinned versions.

|diff  |description|
|------|-----------|
|patch |diff modifies/patches existing cmake|
|intro |diff introduces cmake|
|auto  |diff adds cmake to replace autotools/configure/make|
|native|diff adds cmake but uses existing build system|
|bin   |diff adds cmake to repackage binaries built elsewhere|
|fetch |diff adds cmake and utilizes FetchContent|

[^_l]: see [SPDX License List](https://spdx.org/licenses/ '') for a list of commonly found licenses
[^_d]: see table above with description of diff
