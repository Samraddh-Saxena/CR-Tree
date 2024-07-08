output: Data.o RList.o PQueue.o RTree.o Data_Sampling.o Test_RTree.o Main_RTree.o
	gcc -o output Data.o PQueue.o RList.o RTree.o Data_Sampling.o Test_RTree.o Main_RTree.o -lm  

Main_RTree.o: Main_RTree.c
	gcc -c -g Main_RTree.c -lm

Data.o: Data.c
	gcc -c -g Data.c -lm
	
RList.o: RList.c
	gcc -c -g RList.c -lm 

RTree.o: RTree.c
	gcc -c -g RTree.c -lm

Test_RTree.o: Test_RTree.c
	gcc -c -g Test_RTree.c -lm

PQueue.o: PQueue.c 
	gcc -c -g PQueue.c -lm

Data_Sampling.o: Data_Sampling.c
	gcc -c -g Data_Sampling.c -lm
	
clean:
	rm *.o
	rm output
