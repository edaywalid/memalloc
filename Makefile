memalloc.o:
	gcc -c memalloc.c -o out/memalloc.o

linked_list.out: memalloc.o
	gcc out/memalloc.o examples/linked_list.c -o debug/linked_list
linked_list : linked_list.out
	./debug/linked_list


binary_search.out: memalloc.o
	gcc out/memalloc.o examples/binary_search.c -o debug/binary_search
binary_search: binary_search.out
	./debug/binary_search



directed_graph.out: memalloc.o
	gcc out/memalloc.o examples/directed_graph.c -o debug/directed_graph
directed_graph: directed_graph.out 
	./debug/directed_graph

