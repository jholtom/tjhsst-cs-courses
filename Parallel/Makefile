error-lm:
	gcc -lm error/error.c -o error/error
encoder:
	gcc encoding/encode.c -o encoding/encode
trees:
	mpicc percolation/trees.c -o percolation/trees
mpiglset:
	mpicc  -lGLU -lglut percolation/gl/glset.c -o percolation/gl/glset
glset:
	gcc -lGLU -lglut percolation/gl/glset.c -o percolation/gl/glset
execmpigl:
	mpirun -np 32 -machinefile hostlist.txt percolation/gl/glset
runtrees:
	mpirun -np 32 -machinefile hostlist.txt percolation/trees
clean:
	@rm -rf `find . -executable -type f`
