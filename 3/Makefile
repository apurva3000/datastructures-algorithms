# Makefile - tiraka, uds
# 12.10.2005 HJ - initial revision
# 27.10.2006 HJ - removed -O2 from eff and added rm in clean
# 24.06.2009 SK - added *~ in clean (removes now emacs' backup files)
# 26.04.2010 SK - added rule to run style with correct config
# 16.06.2011 SK - added -w in style and -Wextra for compiling with g++
# 17.06.2011 SK - allows only datastructure.cc, .hh and main.cc to be compiled

.PHONY: all

SRC=main.cc tietorakenne.cc
HDR=tietorakenne.hh

all: prog eff

prog: $(SRC) $(HDR)
	tutg++ -O2 -o tirakaprog $(SRC)

eff: $(SRC) $(HDR)
	g++ -O2 -std=c++11 -Wall -Wextra -pedantic -Werror $(SRC) -o tirakaeff

clean:
	rm -f tirakaprog tirakaeff *~

style:
	/home/style/style -c /home/boss/style/tiraka -w tietorakenne.cc
