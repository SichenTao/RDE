# 🥈 RDE for IEEE WCCI / CEC 2024 Competition

![IEEE CEC 2024](https://img.shields.io/badge/IEEE%20CEC%202024-Runner--Up-silver)
![Track](https://img.shields.io/badge/Track-BC--SOPs-green)
![Language](https://img.shields.io/badge/Language-C%2B%2B%20%2B%20Python-lightgrey)

**RDE is the Runner-Up Award entry for the IEEE WCCI 2024 / IEEE CEC 2024 Competition on Numerical Optimization Considering Accuracy and Speed, bound-constrained single-objective track.**

This repository provides a clean open-source package in the same layout style as the RDE26-SOP competition repository.

## 🥈 Competition Result

| Item | Description |
| --- | --- |
| Achievement | Runner-Up Award |
| Competition | IEEE WCCI 2024 / IEEE CEC 2024 Competition on Numerical Optimization Considering Accuracy and Speed |
| Track | Bound-constrained single-objective optimization |
| Benchmark | CEC 2017 real-parameter numerical optimization problems |
| Runs | 25 independent runs per problem |
| Budget | 10000 x D function evaluations |
| Paper | [arXiv:2404.16280](https://arxiv.org/abs/2404.16280) |

## 🧭 RDE Research Line

| Year | Result | Track | Repository | Paper |
| --- | --- | --- | --- | --- |
| 2024 | 🥈 Runner-Up Award | IEEE CEC 2024 BC-SOPs | [RDE](https://github.com/SichenTao/IEEE-WCCI-CEC-2024-Competition-RDE) | [arXiv:2404.16280](https://arxiv.org/abs/2404.16280) |
| 2025 | 🥇 Rank 1 U-score | IEEE CEC 2025 RDEx Series | [RDEx Series](https://github.com/SichenTao/IEEE-CEC-2025-Competition-RDEx-Series) | [SOP](https://arxiv.org/abs/2603.27089), [CSOP](https://arxiv.org/abs/2603.27090), [MOP](https://arxiv.org/abs/2603.27092), [CMOP](https://arxiv.org/abs/2604.03708) |
| 2026 | 🏆 Champion / Rank 1 | IEEE WCCI 2026 / IEEE CEC 2026 RDE26 Series | [SOP](https://github.com/SichenTao/RDE26-SOP), [CSOP](https://github.com/SichenTao/RDE26-CSOP), [MOP](https://github.com/SichenTao/RDE26-MOP), [CMOP](https://github.com/SichenTao/RDE26-CMOP) | Competition release |

## Team

Sichen Tao, Ruihan Zhao, Kaiyu Wang, and Shangce Gao.

## Repository Layout

| Path | Description |
| --- | --- |
| `benchmark/` | Public benchmark materials |
| `code/rde-cec2024/main.py` | Run entry |
| `code/rde-cec2024/RDE.cpp` | Final algorithm source |
| `code/rde-cec2024/cec17_test_func.cpp` | Benchmark evaluator |
| `code/rde-cec2024/input_data/` | Required benchmark input data |

## Requirements

- Python 3
- C++14 compiler
- No third-party Python package is required

## Quick Start

```bash
python3 code/rde-cec2024/main.py
```

Generated outputs are written under `code/rde-cec2024/outputs/`.

## Citation

Sichen Tao, Ruihan Zhao, Kaiyu Wang, and Shangce Gao, "An Efficient Reconstructed Differential Evolution Variant by Some of the Current State-of-the-art Strategies for Solving Single Objective Bound Constrained Problems," arXiv:2404.16280, 2024.

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
