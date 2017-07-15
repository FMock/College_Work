#!/bin/sh
#
# $RCSfile$-- Test test/00/t0012a.sh
#
#
# Test of block comments
#
work=${TMPDIR:-/tmp}/$$
PAGER=cat
export PAGER
umask 022
here=`pwd`
if test $? -ne 0 ; then exit 2; fi
SHELL=/bin/sh
export SHELL

bin="$here/${1-.}"

pass()
{
	set +x
	cd $here
	rm -rf $work
	exit 0
}
fail()
{
	set +x
	echo "FAILED test of block comments" 1>&2
	cd $here
	rm -rf $work
	exit 1
}
no_result()
{
	set +x
	echo "NO RESULT for test of block comments" 1>&2
	cd $here
	rm -rf $work
	exit 2
}
trap \"no_result\" 1 2 3 15

mkdir $work
if test $? -ne 0 ; then no_result; fi
cd $work
if test $? -ne 0 ; then no_result; fi

#
# test block comments
#

cat > test.w <<"EOF"
\documentclass{article}
\begin{document}
@c Here is a block comment which is long enough to need line
breaking. (And a bit extra.)
Here is a block comment which is long enough to need line
breaking.
Here is a block comment which is long enough to need line
breaking. (Some more extra.)
Here is a block comment which is long enough to need line
breaking.

Here is more of the block comment. It is also long enough to
need line-breaking.

@o test.c -cc
@{Here is some stuff.
   @c
Here is the end of the stuff.
Here (@c) is a block comment in code.
@}

@c This is another block comment that shouldn't end in a
newline. (So long as its length is right.
@o test.c -cc
@{This --@c-- is where it is used.
@}
\end{document}
EOF

cat > test.expected.tex <<"EOF"
\newcommand{\NWtarget}[2]{#2}
\newcommand{\NWlink}[2]{#2}
\newcommand{\NWtxtMacroDefBy}{Fragment defined by}
\newcommand{\NWtxtMacroRefIn}{Fragment referenced in}
\newcommand{\NWtxtMacroNoRef}{Fragment never referenced}
\newcommand{\NWtxtDefBy}{Defined by}
\newcommand{\NWtxtRefIn}{Referenced in}
\newcommand{\NWtxtNoRef}{Not referenced}
\newcommand{\NWtxtFileDefBy}{File defined by}
\newcommand{\NWtxtIdentsUsed}{Uses:}
\newcommand{\NWtxtIdentsNotUsed}{Never used}
\newcommand{\NWtxtIdentsDefed}{Defines:}
\newcommand{\NWsep}{${\diamond}$}
\newcommand{\NWnotglobal}{(not defined globally)}
\newcommand{\NWuseHyperlinks}{}
\documentclass{article}
\begin{document}
\begin{flushleft} \small
\begin{minipage}{\linewidth} Here is a block comment which is long enough to need line
breaking. (And a bit extra.)
Here is a block comment which is long enough to need line
breaking.
Here is a block comment which is long enough to need line
breaking. (Some more extra.)
Here is a block comment which is long enough to need line
breaking.

Here is more of the block comment. It is also long enough to
need line-breaking.

\par\vspace{\baselineskip}
\label{scrap1}\raggedright\small
\NWtarget{nuweb?}{} \verb@"test.c"@\nobreak\ {\footnotesize {?}}$\equiv$
\vspace{-1ex}
\begin{list}{}{} \item
\mbox{}\verb@Here is some stuff.@\\
\mbox{}\verb@   @\hbox{\sffamily\slshape (Comment)}\verb@@\\
\mbox{}\verb@Here is the end of the stuff.@\\
\mbox{}\verb@Here (@\hbox{\sffamily\slshape (Comment)}\verb@) is a block comment in code.@\\
\mbox{}\verb@@{\NWsep}
\end{list}
\vspace{-1.5ex}
\footnotesize
\begin{list}{}{\setlength{\itemsep}{-\parsep}\setlength{\itemindent}{-\leftmargin}}
\item \NWtxtFileDefBy\ \NWlink{nuweb?}{?}\NWlink{nuweb?}{, ?}.

\item{}
\end{list}
\end{minipage}\vspace{4ex}
\end{flushleft}
\begin{flushleft} \small
\begin{minipage}{\linewidth} This is another block comment that shouldn't end in a
newline. (So long as its length is right.
\par\vspace{\baselineskip}
\label{scrap2}\raggedright\small
\NWtarget{nuweb?}{} \verb@"test.c"@\nobreak\ {\footnotesize {?}}$\equiv$
\vspace{-1ex}
\begin{list}{}{} \item
\mbox{}\verb@This --@\hbox{\sffamily\slshape (Comment)}\verb@-- is where it is used.@\\
\mbox{}\verb@@{\NWsep}
\end{list}
\vspace{-1.5ex}
\footnotesize
\begin{list}{}{\setlength{\itemsep}{-\parsep}\setlength{\itemindent}{-\leftmargin}}
\item \NWtxtFileDefBy\ \NWlink{nuweb?}{?}\NWlink{nuweb?}{, ?}.

\item{}
\end{list}
\end{minipage}\vspace{4ex}
\end{flushleft}
\end{document}
EOF

cat > test.expected.c <<"EOF"
Here is some stuff.
   /* Here is a block comment which is long enough to need line
    * breaking. (And a bit extra.) Here is a block comment which
    * is long enough to need line breaking. Here is a block comment
    * which is long enough to need line breaking. (Some more extra.)
    * Here is a block comment which is long enough to need line
    * breaking.
    * Here is more of the block comment. It is also long enough
    * to need line-breaking.
    */
Here is the end of the stuff.
Here (/* Here is a block comment which is long enough to need
       * line breaking. (And a bit extra.) Here is a block comment
       * which is long enough to need line breaking. Here is a
       * block comment which is long enough to need line breaking.
       * (Some more extra.) Here is a block comment which is long
       * enough to need line breaking.
       * Here is more of the block comment. It is also long enough
       * to need line-breaking.
       */) is a block comment in code.
This --/* This is another block comment that shouldn't end in
        * a newline. (So long as its length is right.  */-- is where it is used.
EOF

# [Add other files here.  Avoid any extra processing such as
# decompression until after demo has run.  If demo fails this script
# can save time by not decompressing. ]

$bin/nuweb test.w
if test $? -ne 0 ; then fail; fi

diff -a --context test.expected.tex test.tex
if test $? -ne 0 ; then fail; fi

diff -a --context test.expected.c test.c
if test $? -ne 0 ; then fail; fi

# [Add other sub-tests that might be failed here.  If they need files
# created above to be decompressed, decompress them here ; this saves
# time if demo fails or the text-based sub-test fails.]

#
# Only definite negatives are possible.
# The functionality exercised by this test appears to work,
# no other guarantees are made.
#
pass
