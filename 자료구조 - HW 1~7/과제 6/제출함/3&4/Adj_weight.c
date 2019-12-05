#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

typedef enum {false, true} bool;

enum VisitMode {
	Visited,
	NotVisited
};

typedef char GraphElementType;

typedef struct tagVertex {
	GraphElementType data;
	int isVisited;
	int index;

	struct tagVertex* next;
	struct tagEdge* adjacencyList;
} Vertex;

typedef struct tagEdge {
	int weight;
	struct tagEdge* next;
	Vertex* from;
	Vertex* to;
} Edge;

typedef struct tagGraph {
	Vertex* vertices;
	int vertexCount;
} Graph;

Graph* createGraph();
void destroyGraph(Graph* g);

Vertex* createVertex(GraphElementType data);
void destroyVertex(Vertex* v);

Edge* createEdge(Vertex* from, Vertex* to, int weight);
void destroyEdge(Edge* e);

void addVertex(Graph* g, Vertex* v);
void addEdge(Vertex* v, Edge* e);

void printGraph(Graph* g);

Graph* createGraph() {
	Graph* g = (Graph*)malloc(sizeof(Graph));
	if (g == NULL) {
		return NULL;
	}

	g->vertexCount = 0;
	g->vertices = NULL;
	return g;
}

void destroyGraph(Graph* g) {
	if (g == NULL) {
		return;
	}

	while (g->vertices != NULL) {
		Vertex* next = g->vertices->next;
		destroyVertex(g->vertices);
		g->vertices = next;
	}

	free(g);
	g = NULL;
}

Vertex* createVertex(GraphElementType data) {
	Vertex* v = (Vertex*)malloc(sizeof(Vertex));
	if (v == NULL) {
		return NULL;
	}

	v->data = data;
	v->index = -1;
	v->isVisited = NotVisited;
	v->next = NULL;
	v->adjacencyList = NULL;
	return v;
}

void destroyVertex(Vertex* v) {
	if (v == NULL) {
		return;
	}

	while (v->adjacencyList != NULL) {
		Edge* next = v->adjacencyList->next;
		destroyEdge(v->adjacencyList);
		v->adjacencyList = next;
	}

	free(v);
	v = NULL;
}

Edge* createEdge(Vertex* from, Vertex* to, int weight) {
	Edge* e = (Edge*)malloc(sizeof(Edge));
	if (e == NULL) {
		return NULL;
	}

	e->weight = weight;
	e->from = from;
	e->to = to;
	e->next = NULL;
	return e;
}

void destroyEdge(Edge* e) {
	if (e == NULL) {
		return;
	}

	free(e);
	e = NULL;
}

void addVertex(Graph* g, Vertex* v) {
	if (g == NULL || v == NULL) {
		return;
	}

	Vertex* vList = g->vertices;
	if (vList == NULL) {
		g->vertices = v;
	}
	else {
		while (vList->next != NULL) {
			vList = vList->next;
		}
		vList->next = v;
	}

	v->index = g->vertexCount++;
}

void addEdge(Vertex* v, Edge* e) {
	if (v == NULL || e == NULL) {
		return;
	}

	Edge* eList = v->adjacencyList;
	if (eList == NULL) {
		v->adjacencyList = e;
	}
	else {
		while (eList->next != NULL) {
			eList = eList->next;
		}
		eList->next = e;
	}
}

void printGraph(Graph* g) {
	Vertex* v = NULL;
	Edge* e = NULL;

	v = g->vertices;
	if (v == NULL) {
		return;
	}

	while (v != NULL) {
		printf("\n %c ->", v->data);

		e = v->adjacencyList;
		while (e != NULL) {
			printf(" %c(%d) ->", e->to->data, e->weight);
			e = e->next;
		}

		printf(" NULL\n");
		v = v->next;
	}
	printf("\n");
}

char printed[100];
int printed_index = 0;

bool vaild(Graph* g, char data) {
	int i;

	for (i = 0; i < printed_index; i++) {
		if (data == printed[i]) {
			return false;
		}
	}
	printed[printed_index++] = data;
	return true;
}

void _dft(Graph* g, char data) {
	Vertex* v = NULL;
	Edge* e = NULL;
	v = g->vertices;


	while (1) {
		if (v == NULL) {
			break;
		}
		if (v->data == data) {

			if (vaild(g, v->data))
				printf("%c ", v->data);

			e = v->adjacencyList;
			while (e != NULL) {
				if (vaild(g, e->to->data))
					printf("%c ", e->to->data);
				_dft(g, e->to->data);
				e = e->next;
			}
		}
		v = v->next;
	}
}

void DFT(Graph* g) {
	Vertex* v = NULL;
	Edge* e = NULL;

	v = g->vertices;
	if (v == NULL) {
		return;
	}

	while (v != NULL) {
		if (vaild(g, v->data))
			printf("%c ", v->data);

		e = v->adjacencyList;
		while (e != NULL) {
			if (vaild(g, e->to->data))
				printf("%c ", e->to->data);
			_dft(g, e->to->data);
			e = e->next;
		}
		v = v->next;
	}
	printf("\n");
}

void BFT(Graph* g) {
	int i, j, k;
	int before_index = 0, before_index2 = 0;
	Edge* e = g->vertices->adjacencyList;
	Vertex* v = g->vertices;
	Vertex* v2 = g->vertices;
	char print_check[100];
	int print_check_index = 0;

	int oncePrinted = 0;

	print_check[print_check_index++] = g->vertices->data;
	printf("%c ", g->vertices->data);

	while (e != NULL) {
		printf("%c ", e->to->data);
		print_check[print_check_index++] = e->to->data;
		e = e->next;
	}
	before_index = 1;
	before_index2 = print_check_index;

	for (i = 1; i; i++) {
		oncePrinted = 0;
		for (j = before_index; j < before_index2; j++) {
			v2 = g->vertices;
			for (k = 0; k < g->vertexCount; k++) {
				if (print_check[j] == v2->data) {
					break;
				}
				v2 = v2->next;
			}

			e = v2->adjacencyList;

			while (e != NULL) {
				if (vaild(g, e->to->data)) {
					printf("%c ", e->to->data);
					print_check[print_check_index++] = e->to->data;
				}

				e = e->next;
				oncePrinted = 1;
			}
		}
		if (!oncePrinted) {
			printf("\n");
			return;
		}

		before_index = before_index2;
		before_index2 = print_check_index;
	}

	return;
}

// prim MST
void MST(Graph* g) {
	int i, j;
	int min, min_index = 0;
	char visited[100];
	int visited_index = 0;

	char from[100];
	char to[100];
	int from_to[100];
	int index = 0;

	Vertex* v = g->vertices;
	Edge* e = v->adjacencyList;

	visited[visited_index++] = v->data;

	while (visited_index != g->vertexCount) {
		from[index] = v->data;
		e = v->adjacencyList;
		while (e != NULL) {
			from[index] = v->data;
			to[index] = e->to->data;
			from_to[index++] = e->weight;
			e = e->next;
		}

		for (i = 0; i < index; i++) {
			for (j = 0; j < visited_index; j++) {
				if (to[i] == visited[j]) {
					from_to[i] = 10000; //big number
				}
			}
		}

		min = 10000;
		for (i = 0; i < index; i++) {
			if (from_to[i] < min) {
				min_index = i;
				min = from_to[i];
			}
		}

		visited[visited_index++] = to[min_index];
		printf("%c %c\n", from[min_index], to[min_index]);

		v = g->vertices;
		while (1) {
			if (to[min_index] == v->data) {
				break;
			}
			v = v->next;
		}

	}

}

int is_ALL_DONE(int isDone[], int length_max) {
	int i;
	for (i = 0; i < length_max; i++) {
		if (isDone[i] == 0) {
			return 0;
		}
	}
	return 1;
}

void D_al(Graph* g){
	int i, j;
	int min_index;
	int min;
	int length[100] = { 0, };
	int isDone[100] = { 0, };
	char name[100];
	int length_max = g->vertexCount;

	Vertex* v = g->vertices;
	Edge* e = v->adjacencyList;

	length[0] = 0;
	for (i = 1; i < length_max; i++) {
		length[i] = 10000;
	}


	for (i = 0; v != NULL; i++) {
		name[i] = v->data;
		v = v->next;
	}

	while (!is_ALL_DONE(isDone, length_max)) {
		min = 10000;
		min_index = -1;
		for (i = 0; i < length_max; i++) {
			if (length[i] != 10000 && isDone[i] == 0) {
				if (length[i] < min) {
					min = length[i];
					min_index = i;
				}
			}
		}
		i = min_index;
		v = g->vertices;
		while (1) {
			if (name[i] == v->data) {
				break;
			}
			v = v->next;
		}

		e = v->adjacencyList;
		while (e != NULL) {
			for (j = 0; j < length_max; j++) {
				if (name[j] == e->to->data) {
					break;
				}
			}

			if (!isDone[j] && length[j] > e->weight + length[i]) {
				length[j] = e->weight + length[i];
			}

			e = e->next;

		}
		isDone[i] = 1;
	}

	for (i = 1; i < length_max; i++) {
		printf("%c %c %d\n", g->vertices->data, name[i], length[i]);
	}
}

int main(void) {
	int i, j, vaild, menu;
	int weight;
	char standard, input1, input2, chars[100];
	int chars_index = 0;
	Vertex* v[100];
	int v_index = 0;

	Graph* g = createGraph();

	FILE* read_file = fopen("input.txt", "r");
	fscanf(read_file, "%c\n", &standard);

	chars[chars_index++] = standard;
	v[v_index] = createVertex(standard);
	addVertex(g, v[v_index++]);



	while (1) {
		vaild = fscanf(read_file, "%c %c %d\n", &input1, &input2, &weight);
		if (vaild == -1) {
			break;
		}

		vaild = 1;
		for (i = 0; i < chars_index; i++) {
			if (chars[i] == input1) {
				vaild = 0;
				break;
			}
		}
		if (vaild == 1) {
			v[v_index] = createVertex(input1);
			addVertex(g, v[v_index++]);
			chars[chars_index++] = input1;
		}


		vaild = 1;
		for (j = 0; j < chars_index; j++) {
			if (chars[j] == input2) {
				vaild = 0;
				break;
			}
		}
		if (vaild == 1) {
			v[v_index] = createVertex(input2);
			addVertex(g, v[v_index++]);
			chars[chars_index++] = input2;
		}
		addEdge(v[i], createEdge(v[i], v[j], weight));
	}

	while (1) {
		printf("1) adj list print 2) Shortest Path(MST) 3) Dijkstra's algorithm 4) Exit: ");
		scanf("%d", &menu);

		switch (menu) {
		case 1:
			printGraph(g);
			break;

		case 2:
			MST(g);
			break;

		case 3:
			D_al(g);
			break;

		case 4:
			destroyGraph(g);
			printf("program terminates.\n");
			return 0;

		default:
			printf("Wrong input.\n");
		}
	}

	return -1;
}
