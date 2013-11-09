encoder:
	gcc encoding/encode.c -o encoding/encode
trees:
	mpicc percolation/trees.c -o percolation/trees
gltrees:
	mpicc  -lGLU -lglut percolation/gl/glset.c -o percolation/gl/glset
execgl:
	mpirun -np 32 -machinefile hostlist.txt percolation/gl/glset
runtrees:
	mpirun -np 32 -machinefile hostlist.txt percolation/trees
clean:
	@rm -rf `find . -executable -type f`
