#!/bin/sed -f
# usage: ./ti84pce.sed ti84pce.inc > ti84pceg.inc
/^[#.]/d
s/^Ld/Lsmalld/
s/	equ /	= /
s/|/ or /g
s/&/ and /g
s/\^/ xor /g
s/<</ shl /g
s/>>/ shr /g
