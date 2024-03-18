# Code for enumerating colored interlacing triangles

Colored interlacing triangles were introduced in (this paper)[https://arxiv.org/abs/2309.05970] by Aggarwal, Borodin, and Wheeler (2023).

The repository includes the following files, listed together with ways to run them:
- `LLT.py` is a Python file. The number of colors `n` is a parameter in the code; ran as 
    ```
    python3 LLT.py
    ```
    - The function `unique_permutations_two(n)` finds two-level colored interlacing triangles with `n` colors.
    - The function `unique_permutations_three(n)` finds three-level colored interlacing triangles with `n` colors, and outputs them into the file `depth3_colorsn.txt`, where `n` is the number of specified colors. The file for `n=3` is already included in the repository as an example.
-
