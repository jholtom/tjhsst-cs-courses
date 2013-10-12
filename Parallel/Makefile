encoder:
	gcc encode.c -o encode
trees:
	mpicc trees.c -o trees
runtrees:
	mpirun -machinefile hostlist.txt trees
clean:
	@rm -rf `find . -executable -type f`
