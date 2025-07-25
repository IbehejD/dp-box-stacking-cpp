<!--
 Copyright (c) 2025 David Ibehej
 
 This software is released under the MIT License.
 https://opensource.org/licenses/MIT
-->

# Dynamic Programming in C++

A comprehensive C++ project for implementing and exploring dynamic programming algorithms and solutions.

## Project Structure

```
DynamicPrograming-CPP/
├── CMakeLists.txt          # Main CMake configuration
├── CMakePresets.json       # CMake presets for different build configurations
├── README.md              # This file
├── build.sh               # Build script using CMake presets
├── include/               # Header files
├── src/                   # Source files
├── tests/                 # Test files
└── build/                 # Build output directory (generated)
```

## Prerequisites

- CMake 3.20 or higher
- C++17 compatible compiler (GCC 7+, Clang 5+, MSVC 2017+)
- Make or Ninja build system

## Building the Project

### Using the Build Script (Recommended)

The project includes a `build.sh` script that uses CMake presets for easy building:

```bash
# Build debug version
./build.sh debug

# Build release version
./build.sh release

# Clean build directory
./build.sh clean

# Show help
./build.sh help
```

### Manual CMake Commands

You can also build manually using CMake presets:

```bash
# Configure and build debug
cmake --preset debug
cmake --build --preset debug

# Configure and build release
cmake --preset release
cmake --build --preset release
```

### Traditional CMake (without presets)

```bash
# Debug build
mkdir -p build/debug
cd build/debug
cmake -DCMAKE_BUILD_TYPE=Debug ../..
make -j4

# Release build
mkdir -p build/release
cd build/release
cmake -DCMAKE_BUILD_TYPE=Release ../..
make -j4
```

## Running the Program

After building, the executable will be located in the build directory:

```bash
# Debug build
./build/debug/bin/DynamicProgramming

# Release build
./build/release/bin/DynamicProgramming
```

## Testing

Run tests using CTest:

```bash
# Using presets
cmake --build --preset debug
ctest --preset debug

# Manual
cd build/debug
ctest --output-on-failure
```

## Development

### Adding New Source Files

1. Add `.cpp` files to the `src/` directory
2. Add corresponding header files to the `include/` directory
3. CMake will automatically detect and include them in the build

### Code Style

- Use C++17 features
- Follow modern C++ best practices
- Include appropriate headers
- Use meaningful variable and function names

## Available CMake Presets

- **debug**: Debug build with Unix Makefiles
- **release**: Release build with Unix Makefiles

## Common Dynamic Programming Problems

This project can be used to implement various DP algorithms such as:

- Fibonacci sequence
- Knapsack problems
- Longest Common Subsequence (LCS)
- Edit Distance
- Coin Change
- Maximum Subarray Sum
- And many more...

## License

This software is released under the MIT License.
