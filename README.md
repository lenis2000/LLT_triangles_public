# Code for enumerating colored interlacing triangles

Colored interlacing triangles were introduced in (this paper)[https://arxiv.org/abs/2309.05970] by Aggarwal, Borodin, and Wheeler (2023).

The repository includes the following files, listed together with ways to run them:
- `LLT.py` is a Python file. The number of colors `n` is a parameter in the code; ran as 
    ```
    python3 LLT.py
    ```
    - The function `unique_permutations_two(n)` finds two-level colored interlacing triangles with `n` colors.
    - The function `unique_permutations_three(n)` finds three-level colored interlacing triangles with `n` colors, and outputs them into the file `depth3_colorsn.txt`, where `n` is the number of specified colors.
- `two_levels_fast_code.cpp` is a C++ file without threads; ran as
    ```
    g++ -std=c++11 -O3 two_levels_fast_code.cpp -o two_levels_fast_code.out
    ./two_levels_fast_code.out
    ```
    - Specify the number of colors `n` in the code before compilation. 
    - The program outputs second levels of all two-level colored interlacing triangles with `n` colors, given that on the first level the permutation is the identity.
- `three_openmp.cpp` is a C++ file with OpenMP threads; ran (on my computer) as
    ```
    /opt/homebrew/Cellar/llvm/17.0.6_1/bin/clang++ -fopenmp -O3 three_openmp.cpp    
    ./three_openmp.out
    ```
    - Specify the number of colors `n` in the code before compilation. 
    - The program counts the number of three-level colored interlacing triangles with `n` colors, given that the first level is the identity permutation.
    - The computation is done in parallel, but the total count is computed at the end.
    - The program does not output to file.
- `four_levels_fast_code.cpp` is a C++ file with mutex threads; ran as
    ```
    g++ -std=c++11 -O3 -pthread four_levels_fast_code.cpp -o four_levels_fast_code.out
    ./four_levels_fast_code.out
    ```
    - Specify the number of colors `n` in the code before compilation. 
    - The program first runs a three-level subroutine, then a four-level one.
    - Each subroutine is parallelized with mutex threads, and you can specify the number of threads in `threads_three.size() >= 8` or `threads_four.size() >= 8`.
    - The program outputs progress in the console but does not write to files.
