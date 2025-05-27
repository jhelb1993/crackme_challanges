all:	crackme_01 crackme_02 crackme_03 crackme_04

crackme_01:	crackme_01.c
	gcc crackme_01.c -o crackme_01

crackme_02:	crackme_02.c
	gcc crackme_02.c -o crackme_02

crackme_03:	crackme_03.c
	gcc crackme_03.c -o crackme_03

crackme_04:	crackme_04.c
	gcc crackme_04.c -o crackme_04

clean:
	rm -f crackme_01 crackme_02 crackme_03 crackme_04
