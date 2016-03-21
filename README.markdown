##Alpha trace

A raytracer written in C++

##Directory structure

 - *build*: This folder contains all build files, and is removed on a clean.
            Executables live in build/bin, compiled libs in build/lib.
 - *doc*: Any notes, like my assembly notes, are here.
 - *src*: This includes all the source files which belong to the project,
   headers live in the inlcude subdir.
 - *spike*: Any small testcases, ideas or implementations live here
 - *thirdparty*: All thirdparty headers, libs etc live here.
 - *cfg*: Custom config for the project.
 - *test*: All test code files.

##Building

####Requirements
 * CMake (version 2.6 or greater)
 * make
 * C++11 compliant compiler(tested with g++ & clang)

####Steps
1. `cd build`
2. `cmake ..`
3. `make`

The executables are placed in `build/bin`, the libraries are placed in
`build/lib`.

##Dev environment

The ycm_extra_conf.py is placed in the cfg folder. To automatically source this
file when in the project directory, add the following to your `vimrc`

    if filereadable("../cfg/ycm_extra_conf.py")
        let g:ycm_global_ycm_extra_conf = '../cfg/ycm_extra_conf.py'
    else
        let g:ycm_global_ycm_extra_conf = '~/.vim/.ycm_extra_conf.py'
    endif

