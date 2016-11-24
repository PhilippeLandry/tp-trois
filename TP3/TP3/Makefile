# Makefile pour INF3105 / TP3
OPTIONS = -Wall
# Choisir l'une des deux configurations : -g -O0 pour débogage et -O2 pour la remise.
OPTIONS = -g -O0 -Wall
#OPTIONS = -O2 -Wall

# Syntaxe : cible : dépendance1 dépendance2 ...
# Ensuite, la ou les ligne(s) débutant par une tabulation (\t) donne les commandes pour construire une cible

tp3 :  tp3.cpp carte.o point.o iocarte.o
	g++ ${OPTIONS} -o tp3 tp3.cpp carte.o point.o iocarte.o

carte.o: carte.cpp carte.h point.h
	g++ ${OPTIONS} -c carte.cpp

iocarte.o: iocarte.cpp carte.h point.h
	g++ ${OPTIONS} -c iocarte.cpp

point.o: point.h point.cpp
	g++ ${OPTIONS} -c point.cpp

clean:
	rm -rf tp3 *.o

