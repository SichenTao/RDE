# Results of version 1.1.0

Output of `python3 code/rde-cec2024/main.py` at version 1.1.0 (this repository, tag `v1.1.0`): D = 30, 25 independent runs, 300,000 function evaluations per run, 30 functions (function 2 is included in the run but is not part of the competition), default random seeds. Run on one core of an Apple-silicon Mac (macOS, Apple clang, `-O3 -std=c++14`); the full run took about 6 minutes.

Files: `RDE_CEC2024_D30_F<k>.txt` for k = 1-30. Each file has 1001 rows (checkpoints along the run) and 25 tab-separated columns (one per run); a value is the error of the best solution found so far, and errors of at most 1e-7 are written as 0.

Error after the last evaluation (last row), over the 25 runs:

| Function | Mean | Std |
| ---: | ---: | ---: |
| 1 | 0.0000e+00 | 0.0000e+00 |
| 2 | 0.0000e+00 | 0.0000e+00 |
| 3 | 0.0000e+00 | 0.0000e+00 |
| 4 | 5.8562e+01 | 0.0000e+00 |
| 5 | 7.1638e+00 | 2.3879e+00 |
| 6 | 0.0000e+00 | 0.0000e+00 |
| 7 | 3.8289e+01 | 2.0516e+00 |
| 8 | 7.2440e+00 | 1.7461e+00 |
| 9 | 0.0000e+00 | 0.0000e+00 |
| 10 | 1.4811e+03 | 3.9890e+02 |
| 11 | 5.2270e+00 | 1.1740e+01 |
| 12 | 2.3360e+02 | 1.7692e+02 |
| 13 | 1.2447e+01 | 6.8660e+00 |
| 14 | 1.9289e+01 | 6.8494e+00 |
| 15 | 1.2215e+00 | 8.6774e-01 |
| 16 | 3.6846e+01 | 5.4378e+01 |
| 17 | 3.6130e+01 | 9.3951e+00 |
| 18 | 2.0901e+01 | 4.8344e-01 |
| 19 | 3.4342e+00 | 1.1312e+00 |
| 20 | 3.0026e+01 | 5.6062e+00 |
| 21 | 2.0716e+02 | 1.8670e+00 |
| 22 | 1.0000e+02 | 0.0000e+00 |
| 23 | 3.5057e+02 | 3.1358e+00 |
| 24 | 4.2459e+02 | 2.4322e+00 |
| 25 | 3.8671e+02 | 1.6495e-02 |
| 26 | 9.0510e+02 | 3.6310e+01 |
| 27 | 4.9345e+02 | 5.4134e+00 |
| 28 | 3.0869e+02 | 2.9509e+01 |
| 29 | 4.3229e+02 | 1.8424e+01 |
| 30 | 1.9812e+03 | 3.6612e+01 |

Results of version 1.0.0 are not included here; the results of the 2024 competition are in the 2024 report ([arXiv:2404.16280](https://arxiv.org/abs/2404.16280)).
