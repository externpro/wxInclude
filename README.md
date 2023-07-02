# wxInclude

Embed resources into cross-platform code.

https://wiki.wxwidgets.org/Embedding_PNG_Images

## Build

<details>
<summary><b>Linux</b></summary>

```bash
# Get and set up vcpkg
git clone https://github.com/microsoft/vcpkg.git
export VCPKG_ROOT=$(realpath ./vcpkg)
$VCPKG_ROOT/bootstrap-vcpkg.sh

# Get wxInclude
git clone https://github.com/Werni2A/wxInclude.git
cd wxInclude
git checkout modernization

# Build application
cmake \
    -B build \
    -S . \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_TOOLCHAIN_FILE=$VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake
cmake --build build

# Install application
cmake --install build --prefix /usr/local --config Release
```

</details>

<details>
<summary><b>MacOS</b></summary>

```bash
brew install pkg-config

# Get and set up vcpkg
git clone https://github.com/microsoft/vcpkg.git
export VCPKG_ROOT=$(realpath ./vcpkg)
$VCPKG_ROOT/bootstrap-vcpkg.sh

# Get wxInclude
git clone https://github.com/Werni2A/wxInclude.git
cd wxInclude
git checkout modernization

# Build application
cmake \
    -B build \
    -S . \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_TOOLCHAIN_FILE=$VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake
cmake --build build

# Install application
cmake --install build --prefix /usr/local --config Release
```

</details>

<details>
<summary><b>Windows</b></summary>

```powershell
# Get and set up vcpkg
git clone https://github.com/microsoft/vcpkg.git
$Env:VCPKG_ROOT = Resolve-Path ./vcpkg
& "$Env:VCPKG_ROOT\bootstrap-vcpkg.bat"

# Get wxInclude
git clone https://github.com/Werni2A/wxInclude.git
cd wxInclude
git checkout modernization

# Build application
cmake `
    -B build `
    -S . `
    -DCMAKE_BUILD_TYPE=Debug `
    -DCMAKE_TOOLCHAIN_FILE="$Env:VCPKG_ROOT\scripts\buildsystems\vcpkg.cmake"
cmake --build build

# Install application
cmake --install build --prefix "$Env:ProgramFiles\wxInclude" --config Debug
```

</details>
