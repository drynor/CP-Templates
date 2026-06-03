# CPC Notebook

This folder is a safe, separate competitive programming notebook built from the existing template repository. The old template folders are source material only; notebook copies live under `CPC-Notebook/sections/`, so edits here do not rewrite the original algorithms.

## Build

```bash
cd CPC-Notebook
python build_notebook.py
```

The script always writes `generated/notebook.tex`. If `pdflatex` is installed, it also builds `generated/notebook.pdf`. Manual build later:

```bash
cd CPC-Notebook/generated
pdflatex notebook.tex
pdflatex notebook.tex
```

Dependencies: Python 3 and, for PDF output, a LaTeX distribution with `pdflatex`, `geometry`, `multicol`, `hyperref`, `xcolor`, `listings`, `fancyhdr`, and `enumitem`.

## Adding Templates

Each entry is normally paired as `AlgorithmName.md` notes plus `AlgorithmName.cpp` code. Notes should include when to use it, core idea, API, complexity, common bugs, variants, small example, and tested problems. C++ files start with a short contest safety header.

Edit `notebook.yml` to control order. It is JSON-compatible YAML so the builder works without extra Python packages. Paths are relative to `CPC-Notebook/` and may contain spaces.

## Printing

Print `generated/notebook.pdf` on A4 landscape. The notebook uses two columns, page numbers, a table of contents, C++ syntax highlighting, and line numbers, prioritizing readability over compression.
