# RDE: Runner-Up Award in the bound-constrained single-objective track of the IEEE WCCI/CEC 2024 numerical optimization competition ([arXiv:2404.16280](https://arxiv.org/abs/2404.16280))

<p align="center">
  <strong>English</strong> |
  <a href="README.zh-CN.md">中文</a> |
  <a href="README.ja.md">日本語</a>
</p>

RDE (Reconstructed Differential Evolution) is the differential evolution solver that received the Runner-Up Award in the bound-constrained single-objective track (BC-SOPs) of the IEEE WCCI 2024 / IEEE CEC 2024 Competition on Numerical Optimization Considering Accuracy and Speed. This repository contains its C++ source, the CEC 2017 evaluator with its data, and a run script.

Version 1.0.0 corresponds to the results in the 2024 report; version 1.1.0 corrects the boundary handling after the Cauchy perturbation (see [CHANGELOG.md](CHANGELOG.md)).

## Competition result

| Item | Description |
| --- | --- |
| Achievement | Runner-Up Award |
| Competition | IEEE WCCI 2024 / IEEE CEC 2024 Competition on Numerical Optimization Considering Accuracy and Speed |
| Track | Bound-constrained single-objective optimization (BC-SOPs) |
| Benchmark | CEC 2017 real-parameter single-objective functions |
| Runs | 25 independent runs per function |
| Budget | 10000 x D function evaluations |
| Paper | [arXiv:2404.16280](https://arxiv.org/abs/2404.16280) |

## Repository layout

| Path | Description |
| --- | --- |
| `code/rde-cec2024/main.py` | Build and run script |
| `code/rde-cec2024/RDE.cpp` | Solver source |
| `code/rde-cec2024/cec17_test_func.cpp`, `malloc.h`, `input_data/` | CEC 2017 evaluator and its data |
| `benchmark/CEC2017_SOP/` | The same evaluator and data as a stand-alone copy |
| `results/v1.1.0/` | Results of version 1.1.0 (D = 30, 25 runs, 30 functions) |

## Requirements and quick start

Python 3 and a C++14 compiler (`g++` by default; `--cxx` selects another one). No third-party Python package is needed.

```bash
python3 code/rde-cec2024/main.py                  # D = 30, functions 1-30, 25 runs each
python3 code/rde-cec2024/main.py --compile-only   # build only
```

In the released code the dimension is set in `main()` by `GNVarsIter` (0, 1, 2, 3 select D = 10, 30, 50, 100); it is set to D = 30. The program also runs function 2, which is not part of the competition. A full run took about 6 minutes on one core of an Apple-silicon Mac. Results go to `code/rde-cec2024/outputs/`, one file `RDE_CEC2024_D30_F<k>.txt` per function: 1001 rows (checkpoints along the run) and one column per run, holding the error of the best solution found so far (errors of at most 1e-7 are written as 0).

## Related repositories

The RDE line continues with RDEx (2025) and RDE26 (2026); see the [series overview](https://github.com/SichenTao/reconstructed-differential-evolution).

## Citation and license

Use the "Cite this repository" button (metadata in [CITATION.cff](CITATION.cff)); the paper to cite is:

```bibtex
@misc{tao2024efficient,
  title = {An Efficient Reconstructed Differential Evolution Variant by Some of the Current State-of-the-art Strategies for Solving Single Objective Bound Constrained Problems},
  author = {Tao, Sichen and Zhao, Ruihan and Wang, Kaiyu and Gao, Shangce},
  year = {2024},
  eprint = {2404.16280},
  archivePrefix = {arXiv},
  primaryClass = {cs.NE},
  doi = {10.48550/arXiv.2404.16280}
}
```

The code is released under the [MIT License](LICENSE). The CEC 2017 evaluator and data come from other authors; see [THIRD_PARTY_NOTICES.md](THIRD_PARTY_NOTICES.md).
