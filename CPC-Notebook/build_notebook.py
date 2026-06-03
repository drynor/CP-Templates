#!/usr/bin/env python3
import json, re, shutil, subprocess
from pathlib import Path
ROOT=Path(__file__).resolve().parent; GENERATED=ROOT/'generated'; CONFIG=ROOT/'notebook.yml'
SP={'\\':r'\textbackslash{}','&':r'\&','%':r'\%','$':r'\$','#':r'\#','_':r'\_','{':r'\{','}':r'\}','~':r'\textasciitilde{}','^':r'\textasciicircum{}'}
def esc(s): return ''.join(SP.get(c,c) for c in s)
def inline(s): return re.sub(r'`([^`]+)`',r'\\texttt{\1}',esc(s))
def md(path):
    if not path.exists(): return r'\textit{Missing notes file: '+esc(str(path))+'}\n'
    out=[]; inlist=False
    for raw in path.read_text(encoding='utf-8').splitlines():
        line=raw.rstrip()
        if not line:
            if inlist: out.append(r'\end{itemize}'); inlist=False
            out.append(''); continue
        if line.startswith('# '): continue
        if line.startswith('## '):
            if inlist: out.append(r'\end{itemize}'); inlist=False
            out.append(r'\subsubsection*{'+esc(line[3:].strip())+'}'); continue
        if line.startswith('- '):
            if not inlist: out.append(r'\begin{itemize}[leftmargin=*]'); inlist=True
            out.append(r'\item '+inline(line[2:].strip())); continue
        if inlist: out.append(r'\end{itemize}'); inlist=False
        out.append(inline(line)+r'\par')
    if inlist: out.append(r'\end{itemize}')
    return '\n'.join(out)
def texpath(p): return r'\detokenize{'+p.as_posix()+'}'
def pre(title):
    return r'''\documentclass[10pt,a4paper,landscape]{article}
\usepackage[margin=1.25cm]{geometry}
\usepackage{multicol,hyperref,xcolor,listings,fancyhdr,enumitem}
\usepackage[T1]{fontenc}
\usepackage[utf8]{inputenc}
\usepackage{lmodern}
\setlength{\columnsep}{0.75cm}\setlength{\parindent}{0pt}\setlength{\parskip}{0.35em}
\pagestyle{fancy}\fancyhf{}\lhead{'''+esc(title)+r'''}\rhead{\thepage}\cfoot{\thepage}
\definecolor{codebg}{RGB}{248,248,248}\definecolor{codekw}{RGB}{0,72,160}\definecolor{codestr}{RGB}{150,60,20}\definecolor{codecom}{RGB}{70,120,70}
\lstdefinestyle{cppstyle}{language=C++,basicstyle=\ttfamily\footnotesize,keywordstyle=\color{codekw}\bfseries,stringstyle=\color{codestr},commentstyle=\color{codecom}\itshape,numbers=left,numberstyle=\tiny\color{gray},stepnumber=1,numbersep=6pt,breaklines=true,columns=fullflexible,keepspaces=true,tabsize=2,frame=single,framerule=0.2pt,backgroundcolor=\color{codebg},showstringspaces=false}
\lstset{style=cppstyle}\hypersetup{colorlinks=true,linkcolor=blue,urlcolor=blue}
\begin{document}\begin{center}{\LARGE\bfseries '''+esc(title)+r'''}\\[0.5em]{\large Safe generated CPC/ICPC notebook}\end{center}
\tableofcontents\newpage\begin{multicols}{2}
'''
def build(cfg):
    parts=[pre(cfg.get('title','CPC Notebook'))]
    for sec in cfg['sections']:
        parts.append(r'\section{'+esc(sec['title'])+'}')
        for item in sec.get('items',[]):
            parts.append(r'\subsection{'+esc(item['title'])+'}')
            parts.append(md(ROOT/item['notes']))
            code=ROOT/item['code']
            if code.exists(): parts += [r'\subsubsection*{Code}', r'\lstinputlisting{'+texpath(Path('..')/code.relative_to(ROOT))+'}']
            else: parts.append(r'\textit{Missing code file: '+esc(str(code))+'}')
            parts.append(r'\vspace{0.8em}')
    parts += [r'\end{multicols}',r'\end{document}']
    return '\n'.join(parts)
def main():
    GENERATED.mkdir(parents=True,exist_ok=True); cfg=json.loads(CONFIG.read_text(encoding='utf-8'))
    tex=GENERATED/'notebook.tex'; tex.write_text(build(cfg),encoding='utf-8'); print('Generated LaTeX:',tex)
    exe=shutil.which('pdflatex')
    if not exe:
        print('pdflatex was not found. Generated notebook.tex only.')
        print('Manual build: cd CPC-Notebook/generated && pdflatex notebook.tex && pdflatex notebook.tex')
        return
    for _ in range(2):
        p=subprocess.run([exe,'-interaction=nonstopmode','-halt-on-error',tex.name],cwd=GENERATED,text=True,stdout=subprocess.PIPE,stderr=subprocess.STDOUT)
        if p.returncode:
            print(p.stdout); print('pdflatex failed; LaTeX remains at',tex); return
    print('Generated PDF:',GENERATED/'notebook.pdf')
if __name__=='__main__': main()
