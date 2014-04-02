n-body:
	gcc -lm -lGL -lGLU -lglut nbody/demo_3d.c -o nbody/nbody
tracer:
	gcc raytracing/tracer.c -o raytracing/tracer -std=c99 -lm
error-lm:
	gcc -lm error/error.c -o error/error
conway-gl:
	mpicc -lGLU -lglut -lGL conway/conway.c -o conway/conway -std=c99
execconway:
	mpirun -np 32 -machinefile hostlist.txt conway/conway
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
