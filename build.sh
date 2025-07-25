# Copyright (c) 2025 David Ibehej
# 
# This software is released under the MIT License.
# https://opensource.org/licenses/MIT

#!/bin/bash

# Build script for Dynamic Programming C++ project
# Uses CMake presets for different build configurations

set -e  # Exit on any error

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Function to print colored output
print_info() {
    echo -e "${BLUE}[INFO]${NC} $1"
}

print_success() {
    echo -e "${GREEN}[SUCCESS]${NC} $1"
}

print_warning() {
    echo -e "${YELLOW}[WARNING]${NC} $1"
}

print_error() {
    echo -e "${RED}[ERROR]${NC} $1"
}

# Function to show help
show_help() {
    echo "Usage: $0 [PRESET|COMMAND]"
    echo ""
    echo "Available presets:"
    echo "  debug        - Debug build with Unix Makefiles"
    echo "  release      - Release build with Unix Makefiles"
    echo ""
    echo "Available commands:"
    echo "  clean        - Clean all build directories"
    echo "  test [preset]- Run tests for specified preset (default: debug)"
    echo "  help         - Show this help message"
    echo ""
    echo "Examples:"
    echo "  $0 debug         # Build debug version"
    echo "  $0 release       # Build release version"
    echo "  $0 test debug    # Run tests for debug build"
    echo "  $0 clean         # Clean all builds"
}

# Function to check if preset exists
check_preset() {
    local preset=$1
    local valid_presets=("debug" "release")
    
    for valid in "${valid_presets[@]}"; do
        if [[ "$preset" == "$valid" ]]; then
            return 0
        fi
    done
    return 1
}

# Function to clean build directories
clean_build() {
    print_info "Cleaning build directories..."
    rm -rf build/
    print_success "Build directories cleaned"
}

# Function to build with preset
build_preset() {
    local preset=$1
    
    if ! check_preset "$preset"; then
        print_error "Invalid preset: $preset"
        show_help
        exit 1
    fi
    
    print_info "Building with preset: $preset"
    
    # Configure
    print_info "Configuring..."
    if ! cmake --preset "$preset"; then
        print_error "Configuration failed for preset: $preset"
        exit 1
    fi
    
    # Build
    print_info "Building..."
    if ! cmake --build --preset "$preset"; then
        print_error "Build failed for preset: $preset"
        exit 1
    fi
    
    print_success "Build completed successfully for preset: $preset"
    
    # Show executable location
    case "$preset" in
        "debug")
            print_info "Executable: ./build/debug/bin/DynamicProgramming"
            ;;
        "release")
            print_info "Executable: ./build/release/bin/DynamicProgramming"
            ;;
    esac
}

# Function to run tests
run_tests() {
    local preset=${1:-debug}
    
    if ! check_preset "$preset"; then
        print_error "Invalid preset: $preset"
        show_help
        exit 1
    fi
    
    print_info "Running tests for preset: $preset"
    
    # Check if build exists
    local build_dir=""
    case "$preset" in
        "debug") build_dir="build/debug" ;;
        "release") build_dir="build/release" ;;
    esac
    
    if [[ ! -d "$build_dir" ]]; then
        print_warning "Build directory doesn't exist. Building first..."
        build_preset "$preset"
    fi
    
    # Run tests
    if ! ctest --preset "$preset"; then
        print_error "Tests failed for preset: $preset"
        exit 1
    fi
    
    print_success "Tests completed successfully for preset: $preset"
}

# Main script logic
main() {
    if [[ $# -eq 0 ]]; then
        print_error "No arguments provided"
        show_help
        exit 1
    fi
    
    case "$1" in
        "help"|"-h"|"--help")
            show_help
            ;;
        "clean")
            clean_build
            ;;
        "test")
            run_tests "$2"
            ;;
        "debug"|"release"|"ninja-debug"|"ninja-release")
            build_preset "$1"
            ;;
        *)
            print_error "Unknown command or preset: $1"
            show_help
            exit 1
            ;;
    esac
}

# Check if CMake is available
if ! command -v cmake &> /dev/null; then
    print_error "CMake is not installed or not in PATH"
    exit 1
fi

# Check CMake version
cmake_version=$(cmake --version | head -n1 | grep -o '[0-9]\+\.[0-9]\+\.[0-9]\+')
required_version="3.20.0"

if [[ "$(printf '%s\n' "$required_version" "$cmake_version" | sort -V | head -n1)" != "$required_version" ]]; then
    print_error "CMake version $cmake_version is too old. Required: $required_version or higher"
    exit 1
fi

# Run main function
main "$@"
