# DraygonTensor 

[![Built with Spacemacs](https://cdn.rawgit.com/syl20bnr/spacemacs/442d025779da2f62fc86c2082703697714db6514/assets/spacemacs-badge.svg)](http://github.com/syl20bnr/spacemacs)

## Prerequisites 

### Windows

- CMake 2.8 or greater
- Git

The included build scripts assume that `cmake.exe` can be found in the path, edit them to reflect the location of your cmake binary.

### OSX

- CMake 2.8 or greater
- Git
- SDL2-2.0.4 or greater

### Linux

- CMake 2.8 or greater
- Git
- SDL2-2.0.4 or greater

## Getting the repo 

- Make a fork of this repository

- Clone your fork

```
git clone <your_fork_url>
cd <your_fork_dir>
```

- Setup local branches to track remote branches

```
git branch develop origin/develop
```

- Repeat for each branch you want to track locally

- OR grab all remote branches for local tracking:

```
for b in `git branch -r | grep -v -- '->'`; do git branch --track ${b##origin/} $b; done
```

## Building

### Windows:
Execute one of the `generate_project_*.bat` files in the root directory

### Other:
From root directory:
```
mkdir build
cd build
mkdir superbuild
cd superbuild
cmake ../../cmake/superbuild -DCMAKE_BUILD_TYPE=Debug -G<Generator of your choice>
cmake --build ./ --config Debug
```

In both cases can delete build folder and repeat to do a clean build.

## Contributing

Before contributing, consult the [contribution guidelines](https://github.com/samdelion/DraygonTensor/blob/master/CONTRIBUTING.md).
    
## API

API can be found [here](https://samdelion.github.io/DraygonTensor-api/).
