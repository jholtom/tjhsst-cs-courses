encoder:
	gcc encode.c -o encode
trees:
	mpicc trees.c -o trees
runtrees:
	mpirun -np 32 -machinefile hostlist.txt trees
clean:
	@rm -rf `find . -executable -type f`
