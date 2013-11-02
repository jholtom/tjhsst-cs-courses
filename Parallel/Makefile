encoder:
	gcc encoding/encode.c -o encode
trees:
	mpicc percolation/trees.c -o trees
runtrees:
	mpirun -np 32 -machinefile hostlist.txt percolation/trees
clean:
	@rm -rf `find . -executable -type f`
