# RDE：IEEE WCCI/CEC 2024 数值优化竞赛有界约束单目标赛道亚军奖（[arXiv:2404.16280](https://arxiv.org/abs/2404.16280)）

<p align="center">
  <a href="README.md">English</a> |
  <strong>中文</strong> |
  <a href="README.ja.md">日本語</a>
</p>

RDE（Reconstructed Differential Evolution）是在 IEEE WCCI 2024 / IEEE CEC 2024 “兼顾精度与速度的数值优化竞赛”有界约束单目标赛道（BC-SOPs）获得亚军奖的差分进化求解器。本仓库包含它的 C++ 源码、CEC 2017 评价程序及数据，以及运行脚本。

1.0.0 版对应 2024 年报告中的结果；1.1.0 版修正了 Cauchy 扰动之后的边界处理（见 [CHANGELOG.md](CHANGELOG.md)）。

## 竞赛结果

| 项目 | 说明 |
| --- | --- |
| 成绩 | 亚军奖 |
| 竞赛 | IEEE WCCI 2024 / IEEE CEC 2024 数值优化精度与速度竞赛 |
| 赛道 | 有界约束单目标优化（BC-SOPs） |
| 基准 | CEC 2017 实参数单目标函数 |
| 运行次数 | 每个函数 25 次独立运行 |
| 预算 | 10000 x D 次函数评价 |
| 论文 | [arXiv:2404.16280](https://arxiv.org/abs/2404.16280) |

## 目录结构

| 路径 | 说明 |
| --- | --- |
| `code/rde-cec2024/main.py` | 编译并运行的脚本 |
| `code/rde-cec2024/RDE.cpp` | 求解器源码 |
| `code/rde-cec2024/cec17_test_func.cpp`、`malloc.h`、`input_data/` | CEC 2017 评价程序及其数据 |
| `benchmark/CEC2017_SOP/` | 同一份评价程序和数据的独立副本 |
| `results/v1.1.0/` | 1.1.0 版的结果（D = 30，25 次运行，30 个函数） |

## 环境要求与快速开始

需要 Python 3 和 C++14 编译器（默认 `g++`，可用 `--cxx` 更换）。不需要第三方 Python 包。

```bash
python3 code/rde-cec2024/main.py                  # D = 30，函数 1–30，每个函数 25 次
python3 code/rde-cec2024/main.py --compile-only   # 只编译
```

发布的代码在 `main()` 中用 `GNVarsIter` 设置维度（0、1、2、3 分别对应 D = 10、30、50、100），当前设为 D = 30。程序也会运行函数 2，它不属于竞赛函数。完整运行在 Apple 芯片 Mac 的单个核心上约需 6 分钟。结果写到 `code/rde-cec2024/outputs/`，每个函数一个文件 `RDE_CEC2024_D30_F<k>.txt`：1001 行（运行过程中的检查点），每次运行一列，记录到当前为止最优解的误差（不超过 1e-7 的误差写为 0）。

## 相关仓库

RDE 系列之后是 RDEx（2025）和 RDE26（2026），见[系列总览](https://github.com/SichenTao/reconstructed-differential-evolution)。

## 引用与许可证

请使用 “Cite this repository” 按钮（元数据见 [CITATION.cff](CITATION.cff)）；应引用的论文：

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

代码以 [MIT 许可证](LICENSE)发布。CEC 2017 评价程序和数据来自其他作者，见 [THIRD_PARTY_NOTICES.md](THIRD_PARTY_NOTICES.md)。
