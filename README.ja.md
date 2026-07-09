# 🥈 IEEE WCCI / CEC 2024 コンペティション RDE

![IEEE CEC 2024](https://img.shields.io/badge/IEEE%20CEC%202024-Runner--Up-silver)
![Track](https://img.shields.io/badge/Track-BC--SOPs-green)
![Language](https://img.shields.io/badge/Language-C%2B%2B%20%2B%20Python-lightgrey)

<p align="center">
  <a href="README.md">English</a> |
  <a href="README.zh-CN.md">中文</a> |
  <strong>日本語</strong>
</p>

**RDE は、IEEE WCCI 2024 / IEEE CEC 2024 の「精度と速度を考慮した数値最適化コンペティション」における有界制約単目的トラックの Runner-Up Award エントリです。**

本リポジトリは、RDE26-SOP コンペティションリポジトリと同じ構成方針に基づく、整理済みのオープンソースパッケージを提供します。

## 🥈 コンペティション結果

| 項目 | 説明 |
| --- | --- |
| 成績 | Runner-Up Award |
| コンペティション | IEEE WCCI 2024 / IEEE CEC 2024 Competition on Numerical Optimization Considering Accuracy and Speed |
| トラック | 有界制約単目的最適化 |
| ベンチマーク | CEC 2017 実数値数値最適化問題 |
| 実行回数 | 各問題につき 25 回の独立実行 |
| 評価予算 | 10000 x D 回の関数評価 |
| 論文 | [arXiv:2404.16280](https://arxiv.org/abs/2404.16280) |

## 🧭 RDE 研究ライン

| 年 | 結果 | トラック | リポジトリ | 論文 |
| --- | --- | --- | --- | --- |
| 2024 | 🥈 Runner-Up Award | IEEE CEC 2024 BC-SOPs | [RDE](https://github.com/SichenTao/IEEE-WCCI-CEC-2024-Competition-RDE) | [arXiv:2404.16280](https://arxiv.org/abs/2404.16280) |
| 2025 | 🥇 Rank 1 U-score | IEEE CEC 2025 RDEx シリーズ | [RDEx Series](https://github.com/SichenTao/IEEE-CEC-2025-Competition-RDEx-Series) | [SOP](https://arxiv.org/abs/2603.27089), [CSOP](https://arxiv.org/abs/2603.27090), [MOP](https://arxiv.org/abs/2603.27092), [CMOP](https://arxiv.org/abs/2604.03708) |
| 2026 | 🏆 優勝 / 第 1 位 | IEEE WCCI 2026 / IEEE CEC 2026 RDE26 シリーズ | [SOP](https://github.com/SichenTao/RDE26-SOP), [CSOP](https://github.com/SichenTao/RDE26-CSOP), [MOP](https://github.com/SichenTao/RDE26-MOP), [CMOP](https://github.com/SichenTao/RDE26-CMOP) | コンペティション公開版 |

## チーム

Sichen Tao, Ruihan Zhao, Kaiyu Wang, and Shangce Gao.

## リポジトリ構成

| パス | 説明 |
| --- | --- |
| `benchmark/` | 公開ベンチマーク資料 |
| `code/rde-cec2024/main.py` | 実行エントリ |
| `code/rde-cec2024/RDE.cpp` | 最終アルゴリズムのソースコード |
| `code/rde-cec2024/cec17_test_func.cpp` | ベンチマーク評価器 |
| `code/rde-cec2024/input_data/` | 必要なベンチマーク入力データ |

## 要件

- Python 3
- C++14 コンパイラ
- サードパーティ製 Python パッケージは不要です

## クイックスタート

```bash
python3 code/rde-cec2024/main.py
```

生成された出力は `code/rde-cec2024/outputs/` に書き込まれます。

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
