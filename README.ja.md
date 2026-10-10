# RDE：IEEE WCCI/CEC 2024 数値最適化コンペティション 有界制約付き単目的トラックで Runner-Up Award（[arXiv:2404.16280](https://arxiv.org/abs/2404.16280)）

<p align="center">
  <a href="README.md">English</a> |
  <a href="README.zh-CN.md">中文</a> |
  <strong>日本語</strong>
</p>

RDE（Reconstructed Differential Evolution）は、IEEE WCCI 2024 / IEEE CEC 2024「精度と速度を考慮した数値最適化コンペティション」の有界制約付き単目的トラック（BC-SOPs）で Runner-Up Award を受けた差分進化ソルバーです。このリポジトリには、C++ のソース、CEC 2017 の評価プログラムとそのデータ、実行スクリプトが入っています。

バージョン 1.0.0 は 2024 年の報告書の結果に対応します。バージョン 1.1.0 は Cauchy 摂動後の境界処理を修正したものです（[CHANGELOG.md](CHANGELOG.md) を参照）。

## コンペティション結果

| 項目 | 説明 |
| --- | --- |
| 成績 | Runner-Up Award |
| コンペティション | IEEE WCCI 2024 / IEEE CEC 2024 Competition on Numerical Optimization Considering Accuracy and Speed |
| トラック | 有界制約付き単目的最適化（BC-SOPs） |
| ベンチマーク | CEC 2017 実数値単目的関数 |
| 試行回数 | 関数ごとに独立 25 試行 |
| 予算 | 10000 x D 回の関数評価 |
| 論文 | [arXiv:2404.16280](https://arxiv.org/abs/2404.16280) |

## ディレクトリ構成

| パス | 説明 |
| --- | --- |
| `code/rde-cec2024/main.py` | ビルド・実行スクリプト |
| `code/rde-cec2024/RDE.cpp` | ソルバーのソース |
| `code/rde-cec2024/cec17_test_func.cpp`、`malloc.h`、`input_data/` | CEC 2017 の評価プログラムとデータ |
| `benchmark/CEC2017_SOP/` | 同じ評価プログラムとデータの独立したコピー |
| `results/v1.1.0/` | バージョン 1.1.0 の結果（D = 30、25 試行、30 関数） |

## 必要環境とクイックスタート

Python 3 と C++14 コンパイラが必要です（既定は `g++`、`--cxx` で変更できます）。サードパーティの Python パッケージは不要です。

```bash
python3 code/rde-cec2024/main.py                  # D = 30、関数 1～30、各 25 試行
python3 code/rde-cec2024/main.py --compile-only   # ビルドのみ
```

公開コードでは、次元は `main()` 内の `GNVarsIter` で決まります（0、1、2、3 が D = 10、30、50、100 に対応）。現在は D = 30 です。プログラムは関数 2 も実行しますが、これはコンペティションの対象外です。完全な実行は Apple シリコンの Mac の 1 コアで約 6 分でした。結果は `code/rde-cec2024/outputs/` に、関数ごとに 1 ファイル `RDE_CEC2024_D30_F<k>.txt` として書き出されます。1001 行（実行途中のチェックポイント）、試行ごとに 1 列で、それまでの最良解の誤差を記録します（1e-7 以下の誤差は 0 と書かれます）。

## 関連リポジトリ

RDE シリーズは RDEx（2025）と RDE26（2026）に続きます。[シリーズ概要](https://github.com/SichenTao/reconstructed-differential-evolution)を参照してください。

## 引用とライセンス

「Cite this repository」ボタンを使ってください（メタデータは [CITATION.cff](CITATION.cff)）。引用すべき論文：

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

コードは [MIT ライセンス](LICENSE)で公開しています。CEC 2017 の評価プログラムとデータは他の著者のものです。[THIRD_PARTY_NOTICES.md](THIRD_PARTY_NOTICES.md) を参照してください。
