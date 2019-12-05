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
			printf(" %c ->", e->to->data);
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

int main(void) {
	int i, j, vaild, menu;
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
		vaild = fscanf(read_file, "%c %c\n", &input1, &input2);
		if (vaild != 2) {
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
		addEdge(v[i], createEdge(v[i], v[j], 0));
	}

	while (1) {
		printf("1) adj list print 2) DFT print 3) BFT print 4) Exit: ");
		scanf("%d", &menu);

		switch (menu) {
		case 1:
			printGraph(g);
			break;
		case 2:
			printed_index = 0;
			DFT(g);
			break;
		case 3:
			printed_index = 0;
			BFT(g);
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
