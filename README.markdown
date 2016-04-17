##Alpha trace
A raytracer written in C++ 

I am following the excellent tutorial and introduction to computer graphics by
Scratchapixel, [here](http://www.scratchapixel.com/).

##Directory structure

 - *build*: This folder contains all build files, and is removed on a clean. See
   **building** section for build instructions.
 - *doc*: Any notes and docs are here.
 - *src*: This includes all the source files which belong to the project,
 - *include*: Any headers included within the project
 - *spike*: Any small testcases, ideas or implementations live here
 - *thirdparty*: All third party headers, libs etc live here.
 - *cfg*: Custom config for the project.
 - *test*: All test code files.

##Building

####Requirements
 * CMake (version 2.6 or greater)
 * `make`
 * `C++11` compliant compiler set up with appropriate standard headers and
   libraries(tested with `g++-4.8` & `clang++-3.6`)

####Steps
From the project root... you know the deal.
1. `cd ./build`
2. `cmake ..`
3. `make`

All files resulting from the build are placed in `build` directory.
##Dev environment

The `ycm_extra_conf.py` is placed in the cfg folder. To automatically source this
file when in the project directory, add the following to your `vimrc`

    if filereadable("../cfg/ycm_extra_conf.py")
        let g:ycm_global_ycm_extra_conf = '../cfg/ycm_extra_conf.py'
    else
        let g:ycm_global_ycm_extra_conf = '~/.vim/.ycm_extra_conf.py'
    endif

This has one limitation, `vim` needs to be started from a directory one level
deeper than the `cfg` directory, ie. any subdirectory of the project root, for
proper YCM config.
##License
This project is distributed under the GNU GPL version 3.

This is free software; see the source for copying conditions.  There is NO
warranty; not even for MERCHANTIBILITY or FITNESS FOR A PARTICULAR PURPOSE.
