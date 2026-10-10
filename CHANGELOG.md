# Changelog

## 1.1.0

### Fixed

- **Trial vector outside the search range.** After the Cauchy perturbation, a component of the trial vector could lie outside [-100, 100] and was evaluated as it was. The trial vector is now repaired with `FindLimits` (the midpoint between the violated bound and the parent value), the repair that was already applied to the donor vector, before it is evaluated. The change is one line in `code/rde-cec2024/RDE.cpp`, just before the evaluation.
- Because points outside the range are no longer evaluated, the final errors change on some functions; the change is largest on F4, F25, F27 and F30.

### Added

- `results/v1.1.0/`: results of this version (D = 30, 25 runs, 30 functions).
- `CITATION.cff`, `THIRD_PARTY_NOTICES.md`, this file; the authors of the paper are named in `LICENSE`; READMEs rewritten.

## 1.0.0

The code of the first public release (2026-07-06), the algorithm entered in the 2024 competition. It corresponds to the results in the 2024 report ([arXiv:2404.16280](https://arxiv.org/abs/2404.16280)).
