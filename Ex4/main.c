#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


typedef struct Edge {
    int dest;
    int weight;
}Edge;

typedef struct Node {
    int id;
    int priority;
    int visited;
    int numOfEdges;
    Edge** edges;
}Node ;

typedef struct Graph {
    int numOfNodes;
    Node** nodes;
} Graph;

typedef struct Element {
    Node* node;
    struct Element* next;
} Element;

typedef struct PriorityQueue {
    Element* head;
}PriorityQueue;


typedef struct Permutaion {

    int size;
    int currentIndex;
    int** allPermutation;
}Permutaion;


void deleteGraph(Graph* graph)
{
    for (int i = 0; i < graph->numOfNodes; i++)
    {
        if (graph->nodes[i] != NULL)
        {

            Node* node = graph->nodes[i];
            for (int j = 0; j < node->numOfEdges; j++)
            {
                free(node->edges[j]);
            }
            free(node->edges);
           
        }
        free(graph->nodes[i]);
    }
    free(graph->nodes);


}

void setNewArray(Permutaion* pr, int* arr, int size)
{
    for (int i = 0; i < size; i++)
    {
        pr->allPermutation[pr->currentIndex][i] = arr[i];
        //printf("%d ", arr[i]);
    }
    pr->currentIndex++;
    // printf("\n");
}

//function to swap the variables
void swap(int* a, int* b)
{
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

//permutation function
void permutation(Permutaion* per, int* arr, int start, int end)
{
    if (start == end)
    {
        setNewArray(per, arr, end + 1);
        return;
    }
    int i;
    for (i = start; i <= end; i++)
    {
        swap((arr + i), (arr + start));
        permutation(per, arr, start + 1, end);
        swap((arr + i), (arr + start));
    }
}

int calculateAzheret(int number)
{
    int res = 1;
    for (int i = 1; i <= number; i++)
    {
        res *= i;
    }
    return res;
}


Permutaion* generatrePermutation(int size)
{
    int azheret = calculateAzheret(size);
    Permutaion* per = (Permutaion*)calloc(1, sizeof(Permutaion));
    per->size = azheret;
    per->allPermutation = (int**)calloc(azheret, sizeof(int*));
    for (int i = 0; i < per->size; i++)
    {
        per->allPermutation[i] = (int*)calloc(size, sizeof(int));
    }
    return per;
}





PriorityQueue* createPriorityQueue()
{
    return (PriorityQueue*)calloc(1, sizeof(PriorityQueue));
}

Node* peek(PriorityQueue* queue) {
    if (queue->head != NULL)
    {
        return queue->head->node;
    }
    return NULL;
}

Node* pop(PriorityQueue* queue) {
    Element* result = queue->head;
    if (result != NULL)
    {
        queue->head = result->next;
    }
    Node* p = result->node;
    free(result);
    return p;
}

int isEmpty(PriorityQueue* queue) {
    return queue->head == NULL;
}

Element* createElement(Node* node)
{
    Element* res = (Element*)calloc(1, sizeof(Element));
    res->node = node;
    res->next = NULL;
    return res;
}

void push(PriorityQueue* queue,Node* node) {
    Node* nodeToAdd = node;
    if (queue->head == NULL) {
        queue->head = createElement(nodeToAdd);
        return;
    }
    if (nodeToAdd->priority <= queue->head->node->priority) {
        Element* first = createElement(nodeToAdd);
        first->next = queue->head;
        queue->head = first;
    }
    else {
        Element* start = queue->head;
        while (start->next != NULL && start->next->node->priority < nodeToAdd->priority) {
            start = start->next;
        }
        Element* in = createElement(nodeToAdd);
        in->next = start->next;
        start->next = in;
    }
}

Node* getNode(Graph* graph, int nodeNumber)
{
    for (int i = 0; i < graph->numOfNodes; i++) {
        if (graph->nodes[i] != NULL && graph->nodes[i]->id == nodeNumber)
        {
            return graph->nodes[i];
        }
    }
    return NULL;

}

Graph* createGraph(int numOfNodes) {
    Graph* graph = (Graph*)calloc(1,sizeof(Graph));
    graph->numOfNodes = numOfNodes;
    graph->nodes = (Node**)calloc(numOfNodes,sizeof(Node*));
    for (int i = 0; i < numOfNodes; i++) {
        graph->nodes[i] =NULL;
       
    }
    return graph;
}

void addEdge(Graph* graph, int srcNode, int destNode, int w) {

    for (int i = 0; i < graph->numOfNodes; i++)
    {
        if (graph->nodes[i] != NULL && graph->nodes[i]->id == srcNode)
        {
            Node* node = graph->nodes[i];
            node->numOfEdges++;
            node->edges = (Edge**)realloc(node->edges, sizeof(Edge*) * node->numOfEdges);
            node->edges[node->numOfEdges - 1] = (Edge*)calloc(1, sizeof(Edge));
            node->edges[node->numOfEdges - 1]->dest = destNode;
            node->edges[node->numOfEdges - 1]->weight = w;
            //printf("Add edge src %d , dest %d , w %d \n", srcNode, destNode, w);
            break;
        }
    }
}

void freeAllEdges(Node* node)
{
    for (int i = 0; i < node->numOfEdges; i++)
    {
        free(node->edges[i]);
    }
    node->numOfEdges = 0;
    free(node->edges);
    node->edges = NULL;
}

void addNode(Graph* graph, int nodeNumber,int shouldOverride) {
    int isNodeExists = 0;
    for (int i = 0; i < graph->numOfNodes; i++)
    {
        if (shouldOverride == 0)
        {
            if (graph->nodes[i] == NULL)
            {
                graph->nodes[i] = (Node*)calloc(1, sizeof(Node));
                graph->nodes[i]->id = nodeNumber;
                //printf("Add node number #%d\n", nodeNumber);
                break;
            }
        }
        else {
            if (graph->nodes[i] != NULL && graph->nodes[i]->id == nodeNumber)
            {
                Node* node = graph->nodes[i];
                freeAllEdges(node);
                isNodeExists = 1;
                break;
            }
        }
    }
    if (shouldOverride == 1 && isNodeExists == 0)
    {
        graph->numOfNodes++;
        graph->nodes = (Node**)realloc(graph->nodes, sizeof(Node*) * graph->numOfNodes);
        graph->nodes[graph->numOfNodes - 1] = NULL;
        addNode(graph, nodeNumber, 0);
    }
}

void removeEdgeFromNode(Node* node, int numOfNode)
{
    if (node != NULL)
    {
        for (int i = 0; i < node->numOfEdges; i++)
        {
            if (node->edges[i]->dest == numOfNode)
            {
                free(node->edges[i]);
                for (int j = i; j < node->numOfEdges - 1; j++)
                {
                    node->edges[j] = node->edges[j + 1];
                }
                node->numOfEdges--;
           
           

                node->edges = (Edge**)realloc(node->edges, sizeof(Edge*) * node->numOfEdges);
               // printf("Remove edge from %d to %d\n", node->id, numOfNode);
                break;
            }
        }
    }
}

void deleteNode(Graph* graph, int nodeNumber)
{
    for (int i = 0; i < graph->numOfNodes; i++)
    {
        if (graph->nodes[i] != NULL && graph->nodes[i]->id == nodeNumber)
        {
            freeAllEdges(graph->nodes[i]);
            free(graph->nodes[i]);
            for (int j = i; j < graph->numOfNodes - 1; j++)
            {
                graph->nodes[j] = graph->nodes[j + 1];
            }
            graph->numOfNodes--;   
            graph->nodes = (Node**)realloc(graph->nodes, sizeof(Node*) * graph->numOfNodes);
           // printf("Node deleted - %d\n", nodeNumber);

            for (int i = 0; i < graph->numOfNodes; i++)
            {
                removeEdgeFromNode(graph->nodes[i], nodeNumber);
            }
            break;
        }
    }
}

void freeList(Element* head)
{
   Element* tmp;

    while (head != NULL)
    {
        tmp = head;
        head = head->next;
        free(tmp);
    }

}



void resetGraphPriority(Graph* graph)
{
    for (int i = 0; i < graph->numOfNodes; i++)
    {
        if (graph->nodes[i] != NULL)
        {
            graph->nodes[i]->visited = 0;
            graph->nodes[i]->priority = INT_MAX;
        }
    }
}

int Dijkstra(Graph* graph, int src, int dest) {
    Node* srcNode = getNode(graph, src);
    Node* destNode = getNode(graph, dest);
    if (srcNode == NULL || destNode == NULL) {
        return -1;
    }
   resetGraphPriority(graph);
   
    srcNode->priority = 0;
    PriorityQueue* queue = createPriorityQueue();
    Node* curr = srcNode;

    curr->priority = 0;
    push(queue, curr);
    curr->visited = 1;
    while (!isEmpty(queue)) {
        curr = pop(queue);
        curr->visited = 1;
        if (curr->numOfEdges == 0) {
            continue;
        }
        else {
            for (int i = 0; i < curr->numOfEdges; i++)
            {
                Node* node = getNode(graph, curr->edges[i]->dest);
                double totalWeight = curr->priority + curr->edges[i]->weight;
                if (totalWeight <node->priority ) {
                    node->priority = totalWeight;
                }
                if (node->visited == 0)
                {
                    push(queue, node);
                }
            }
            if (curr->id == dest)
            {
                freeList(queue->head);
                free(queue);
                return curr->priority;
            }
        
        }
    }
    free(curr);
    freeList(queue->head);
    free(queue);
    return -1;
}

int isCommand(char ch)
{
    if (ch != 'D' && ch != 'A' && ch != 'B' && ch != 'S' && ch != 'T')
    {
        return 0;
    }
    return 1;

}

int getWeightSrcToDest(Graph* graph, int from, int dest)
{
    Node* node = getNode(graph, from);
    if (node == NULL)
    {
        return -1;
    }
    else {
        for (int i = 0; i < node->numOfEdges; i++)
        {
            if (node->edges[i] != NULL && node->edges[i]->dest == dest)
            {
                return node->edges[i]->weight;
            }
        }
    }
    return -1;

}

int getCostOfPath(Graph* graph, int* arr, int size)
{
    int result = 0;
    for (int i = 1; i < size; i++)
    {
        int tempRes = getWeightSrcToDest(graph, arr[i - 1], arr[i]);
        if (tempRes == -1)
        {
            return -1;
        }
        else {
            result += tempRes;
        }

    }

    return result;

}

int* getBiggerArrayWithNodeThatDosentExistsInCurrentArray(Graph* graph, int* arr,int *size)
{
    for (int i = 0; i < graph->numOfNodes; i++)
    {
        if (graph->nodes[i] != NULL)
        {
            int nodeToCheck = graph->nodes[i]->id;
            int isExists = 0;
            for (int j = 0; j < *size; j++)
            {
                if (arr[j] == nodeToCheck)
                {
                    isExists = 1;
                    break;
                }
            }
            if (isExists == 0)
            {
                *size = *size + 1;
                int* result = (int*)calloc(sizeof(int), *size);
                for (int i = 0; i < *size - 1; i++)
                {
                    result[i] = arr[i];
                }
                result[*size - 1] = nodeToCheck;
                return result;
            }
        }
    }
    return NULL;
}


int tsp(Graph* graph ,int *arr,int size)
{
    int minPath = INT_MAX; 
    int* arrToCheck = arr;
    int  arrToCheckSize = size;
    do{
        Permutaion* per = generatrePermutation(arrToCheckSize);
        permutation(per, arrToCheck, 0, arrToCheckSize - 1);
        for (int i = 0; i < per->size; i++)
        {
            int pathCost = getCostOfPath(graph, per->allPermutation[i], arrToCheckSize);
            if (pathCost != -1 && pathCost < minPath)
            {
                minPath = pathCost;
            }
        }
        if (arrToCheckSize != graph->numOfNodes) {
            int* prev = arrToCheck;
            arrToCheck = getBiggerArrayWithNodeThatDosentExistsInCurrentArray(graph, prev,&arrToCheckSize);
            free(prev);
        }
        else {
            for (int i = 0; i < per->size; i++)
            {
                free(per->allPermutation[i]);
            }
            free(per->allPermutation);
            free(per);
            break;
        }
        for (int i = 0; i < per->size; i++)
        {
            free(per->allPermutation[i]);
        }
        free(per->allPermutation);
        free(per);
   } while (arrToCheckSize <= graph->numOfNodes);
   if (arrToCheck != NULL) {
       free(arrToCheck);
   }

    if (minPath == INT_MAX)
    {
        return -1;
    }
    else {
        return minPath;
    }

}

void printGraph(Graph* graph)
{
    printf("====================================================================\n");
    printf("Number of nodes - %d\n", graph->numOfNodes);
    for (int i = 0; i < graph->numOfNodes; i++)
    {
        printf("Node number %d has %d edges:\n", graph->nodes[i]->id, graph->nodes[i]->numOfEdges);
        for (int j = 0; j < graph->nodes[i]->numOfEdges; j++)
        {
            printf("Edge { %d -> %d }, weight %d\n", graph->nodes[i]->id, graph->nodes[i]->edges[j]->dest, graph->nodes[i]->edges[j]->weight);
        }
    }
    printf("====================================================================\n");
    printf("\n");
    printf("\n");
}




int main() {
    Graph* graph = NULL;
    char input[255] = { 0 };
    scanf("%[^\n]s", input);
    char* ptr = input;
    while (*ptr != '\0' && *ptr != 48) {
        switch (*ptr)
        {
        case 'A': {
            ptr += 2;
            int numOfNodes = *ptr - '0';
            if (graph != NULL)
            {
                deleteGraph(graph);
                free(graph);
            }
            graph = createGraph(numOfNodes);
            ptr += 2;
            while (!isCommand(*ptr) && *ptr != '\0')
            {
                if (*ptr == 'n')
                {
                    ptr += 2;
                    int srcNode = *ptr - '0';
                    addNode(graph, srcNode, 0);
                    ptr += 2;
                    while (*ptr != 'n' && !isCommand(*ptr) && *ptr != '\0')
                    {
                        int destNode = *ptr - '0';
                        ptr += 2;
                        int weight = *ptr - '0';
                        ptr += 2;
                        addEdge(graph, srcNode, destNode, weight);
                    }
                }
            }
            break;
        }
        case 'B': {
            ptr += 2;
            int srcNode = *ptr - '0';
            ptr += 2;
            addNode(graph, srcNode, 1);
            while (!isCommand(*ptr) && *ptr != '\0')
            {
                int destNode = *ptr - '0';
                ptr += 2;
                int weight = *ptr - '0';
                ptr += 2;
                addEdge(graph, srcNode, destNode, weight);
            }

            break;
        }
        case 'D': {
            ptr += 2;
            int nodeToDelete = *ptr - '0';
            deleteNode(graph, nodeToDelete);
            ptr += 2;
            break;
        }
        case 'S': {
            ptr += 2;
            int fromNode = *ptr - '0';
            ptr += 2;
            int toNode = *ptr - '0';
            int result = Dijkstra(graph, fromNode, toNode);
            printf("Dijsktra shortest path: %d \n", result);
            break;
        }
        case 'T': {
            //printGraph(graph);
            int* cities = (int*)calloc(6, sizeof(int));
            ptr += 2;
            int numOfCities = *ptr - '0';
            ptr += 2;
            int index = 0;
            for (int i = 0; i < numOfCities; i++)
            {
                cities[index++] = *ptr - '0';
                ptr += 2;
            }
            int res = tsp(graph, cities, index);
            printf("TSP shortest path: %d \n", res);
            break;
        }
        }
    }
    if (graph != NULL) {
        deleteGraph(graph);
        free(graph);
    }
}