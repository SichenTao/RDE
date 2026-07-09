# 🥈 IEEE WCCI / CEC 2024 竞赛 RDE

![IEEE CEC 2024](https://img.shields.io/badge/IEEE%20CEC%202024-Runner--Up-silver)
![Track](https://img.shields.io/badge/Track-BC--SOPs-green)
![Language](https://img.shields.io/badge/Language-C%2B%2B%20%2B%20Python-lightgrey)

<p align="center">
  <a href="README.md">English</a> |
  <strong>中文</strong> |
  <a href="README.ja.md">日本語</a>
</p>

**RDE 是 IEEE WCCI 2024 / IEEE CEC 2024 数值优化精度与速度竞赛有界约束单目标赛道的亚军奖参赛方案。**

本仓库按与 RDE26-SOP 竞赛仓库一致的结构，提供整洁的开源算法包。

## 🥈 竞赛结果

| 项目 | 说明 |
| --- | --- |
| 成绩 | 亚军奖 |
| 竞赛 | IEEE WCCI 2024 / IEEE CEC 2024 数值优化精度与速度竞赛 |
| 赛道 | 有界约束单目标优化 |
| 基准 | CEC 2017 实参数值优化问题 |
| 运行次数 | 每个问题 25 次独立运行 |
| 预算 | 10000 x D 次函数评价 |
| 论文 | [arXiv:2404.16280](https://arxiv.org/abs/2404.16280) |

## 🧭 RDE 研究线

| 年份 | 结果 | 赛道 | 仓库 | 论文 |
| --- | --- | --- | --- | --- |
| 2024 | 🥈 亚军奖 | IEEE CEC 2024 BC-SOPs | [RDE](https://github.com/SichenTao/IEEE-WCCI-CEC-2024-Competition-RDE) | [arXiv:2404.16280](https://arxiv.org/abs/2404.16280) |
| 2025 | 🥇 U-score 第 1 名 | IEEE CEC 2025 RDEx 系列 | [RDEx Series](https://github.com/SichenTao/IEEE-CEC-2025-Competition-RDEx-Series) | [SOP](https://arxiv.org/abs/2603.27089), [CSOP](https://arxiv.org/abs/2603.27090), [MOP](https://arxiv.org/abs/2603.27092), [CMOP](https://arxiv.org/abs/2604.03708) |
| 2026 | 🏆 冠军 / 第 1 名 | IEEE WCCI 2026 / IEEE CEC 2026 RDE26 系列 | [SOP](https://github.com/SichenTao/RDE26-SOP), [CSOP](https://github.com/SichenTao/RDE26-CSOP), [MOP](https://github.com/SichenTao/RDE26-MOP), [CMOP](https://github.com/SichenTao/RDE26-CMOP) | 竞赛公开版本 |

## 团队

Sichen Tao, Ruihan Zhao, Kaiyu Wang, and Shangce Gao.

## 仓库结构

| 路径 | 说明 |
| --- | --- |
| `benchmark/` | 公开基准材料 |
| `code/rde-cec2024/main.py` | 运行入口 |
| `code/rde-cec2024/RDE.cpp` | 最终算法源代码 |
| `code/rde-cec2024/cec17_test_func.cpp` | 基准评价器 |
| `code/rde-cec2024/input_data/` | 必要的基准输入数据 |

## 运行需求

- Python 3
- C++14 编译器
- 不需要第三方 Python 包

## 快速开始

```bash
python3 code/rde-cec2024/main.py
```

生成结果会写入 `code/rde-cec2024/outputs/`。

## 引用

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
