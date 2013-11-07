encoder:
	gcc encoding/encode.c -o encoding/encode
trees:
	mpicc percolation/trees.c -o percolation/trees
gltrees:
	mpicc  -lGLU -lglut percolation/gl/gltrees.c -o percolation/gl/gltrees
execgl:
	mpirun -np 32 -machinefile hostlist.txt percolation/gl/gltrees
runtrees:
	mpirun -np 32 -machinefile hostlist.txt percolation/trees
clean:
	@rm -rf `find . -executable -type f`
