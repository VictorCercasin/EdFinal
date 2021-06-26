CFLAGS = -g -std=c99 -fstack-protector-all -lm
 
siguel: main.o lista.o svg.o learq.o leqry.o pathment.o txt.o circulo.o info.o retangulo.o texto.o ponto.o regiao.o casa.o sort.o poligono.o quadtree.o hashTable.o pessoa.o morador.o str.o estabComerc.o quadra.o grafo.o
	gcc -o siguel main.o lista.o svg.o learq.o leqry.o pathment.o txt.o circulo.o info.o retangulo.o texto.o ponto.o regiao.o casa.o sort.o poligono.o quadtree.o hashTable.o pessoa.o morador.o str.o estabComerc.o quadra.o grafo.o $(CFLAGS)
	rm -rf *.o *~

main.o: main.c lista.h svg.h learq.h leqry.h pathment.h txt.h 
	gcc -o main.o -c main.c $(CFLAGS)
 
lista.o: lista.c lista.h txt.h circulo.h retangulo.h texto.h info.h ponto.h regiao.h casa.h poligono.h
	gcc -o lista.o -c lista.c $(CFLAGS)
 
svg.o: svg.c svg.h lista.h
	gcc -o svg.o -c svg.c $(CFLAGS)

learq.o: learq.c learq.h lista.h
	gcc -o learq.o -c learq.c $(CFLAGS)

leqry.o: leqry.c leqry.h lista.h svg.h sort.h poligono.h
	gcc -o leqry.o -c leqry.c $(CFLAGS)

pathment.o: pathment.c pathment.h
	gcc -o pathment.o -c pathment.c $(CFLAGS)

txt.o: txt.c txt.h lista.h
	gcc -o txt.o -c txt.c $(CFLAGS)

circulo.o: circulo.c circulo.h	
	gcc -o circulo.o -c circulo.c $(CFLAGS)

info.o: info.c info.h
	gcc -o info.o -c info.c $(CFLAGS)

retangulo.o: retangulo.c retangulo.h
	gcc -o retangulo.o -c retangulo.c $(CFLAGS)

texto.o: texto.c texto.h
	gcc -o texto.o -c texto.c $(CFLAGS)	 

ponto.o: ponto.c ponto.h 
	gcc -o ponto.o -c ponto.c $(CFLAGS)

regiao.o: regiao.c regiao.h
	gcc -o regiao.o -c regiao.c $(CFLAGS)

casa.o: casa.c casa.h 
	gcc -o casa.o -c casa.c $(CFLAGS)

sort.o: sort.c sort.h ponto.h	
	gcc -o sort.o -c sort.c $(CFLAGS)
	
poligono.o: poligono.c poligono.h ponto.h
	gcc -o poligono.o -c poligono.c $(CFLAGS)	

quadtree.o: quadtree.c quadtree.h
	gcc -o quadtree.o -c quadtree.c $(CFLAGS)

hashTable.o: hashTable.c hashTable.h
	gcc -o hashTable.o -c hashTable.c $(CFLAGS)	

estabComerc.o: estabComerc.c estabComerc.h
	gcc -o estabComerc.o -c estabComerc.c $(CFLAGS)	

morador.o: morador.c morador.h
	gcc -o morador.o -c morador.c $(CFLAGS)	

pessoa.o: pessoa.c pessoa.h
	gcc -o pessoa.o -c pessoa.c $(CFLAGS)	

str.o: str.c str.h
	gcc -o str.o -c str.c $(CFLAGS)	

quadra.o: quadra.c quadra.h
	gcc -o quadra.o -c quadra.c $(CFLAGS)	

grafo.o: grafo.c grafo.h
	gcc -o grafo.o -c grafo.c $(CFLAGS)

clean:
	rm -rf *.o *~ siguel