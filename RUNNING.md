# Submit on LeetCode

**No local compiler or installation is required to use these lessons.** LeetCode runs and judges the submitted code.

1. Open the problem using its lesson's LeetCode link.
2. Select **C**, **C++**, or **Python3** in the editor.
3. Copy exactly one approach file from that language directory into LeetCode.
4. Click **Run** to try examples or **Submit** to use LeetCode's judge.

The final `optimal` file is the recommended full-constraint submission. Every file uses the expected function or `Solution` method interface and contains no main function. LeetCode supplies `ListNode` and `TreeNode` where applicable.

The other approaches explain the learning progression. Exhaustive methods may exceed time limits, and recursive alternatives can exceed the available call stack. These limitations are explained in each lesson.

## Optional: validate the repository locally

The remaining instructions are for contributors checking the repository itself. They are not prerequisites for studying or submitting solutions on LeetCode.

### Local validation requirements

- Python 3.11 or newer; no pip dependencies.
- A C17 compiler and a C++17 compiler, such as GCC or Clang.
- Run commands from the repository root.

```sh
python tests/run.py
python tests/run.py --languages python
python tests/run.py --languages c cpp
```

By default the runner uses `gcc` for C and `g++` for C++. To select alternatives on Linux/macOS:

```sh
CC=clang CXX=clang++ python tests/run.py
```

In PowerShell:

```powershell
$env:CC = 'C:\path\to\clang.exe'
$env:CXX = 'C:\path\to\clang++.exe'
python tests/run.py
```

The compiler directory may also need to be on PATH so its runtime libraries can be found. The runner accepts an executable path with spaces. Build outputs stay in the ignored `.build` directory; Python caches are ignored too.

### Optional memory checks

```sh
python tests/run.py --languages c cpp --sanitize
```

On Linux, this enables AddressSanitizer, UndefinedBehaviorSanitizer, and leak detection. On Windows with a suitable Clang toolchain it enables AddressSanitizer; leak detection is disabled because that facility is platform dependent. The GitHub Actions workflow performs the Linux memory checks as well as regular tests. Sanitizer support and runtime availability depend on your compiler distribution.

### What the repository tests cover

Every approach uses the same fixed examples, edge cases, and small randomized inputs with seed 20261028. Independent reference routines compute expected results. Small inputs keep intentionally expensive baselines practical. The suite normalizes subset order, validates Two Sum indices, checks that linked-list outputs preserve every original node without cycles, and confirms promised input preservation.

The final `optimal` implementation for every problem also receives a larger case at the problem's size limit. These include a 5,000-node list, a 2,000-level tree, a 300×300 land grid, amount 10,000, 10,000 singleton lists, a 100,000-character string, and a 100,000-bar histogram. The checks validate lesson structure, difficulty counts, implementation coverage, and local Markdown links. LeetCode/source URLs were checked during authoring; tests do not depend on network access.

Recursive reversal, recursive tree traversal, and recursive Coin Change are teaching alternatives. A correct recurrence can still exceed Python's recursion limit or a native call stack on a large input. The iterative final versions avoid that issue. Binary Search's linear baseline intentionally fails the problem's requested logarithmic complexity. Exhaustive baselines may exceed time limits on large submissions.

### Notes for local test wrappers

Local test wrappers supply equivalents of LeetCode's node definitions. Python node annotations are postponed so the files can also be loaded by the test runner.

C functions returning arrays follow LeetCode's `returnSize` and `returnColumnSizes` conventions. The caller owns returned storage: free every nested row, the outer array, and column-size metadata. Minimum Window Substring returns a newly allocated null-terminated string even for an empty answer. Linked-list methods reuse input nodes; do not free the original nodes again through an obsolete head. Allocations are assumed to succeed within exercise limits; the lesson notes identify this teaching simplification.

## Repository layout

Each problem has one lesson README and `c`, `cpp`, and `python` folders. Each approach is a separate file, allowing direct submission without renaming methods or removing competing implementations. `catalog.json` records the 12 problems and the file names used by the test runner.
