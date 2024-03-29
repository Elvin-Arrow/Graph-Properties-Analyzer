#include <iostream>
#include <fstream>
#include "windows.h"

using namespace std;

struct Node{
	char data;
	Node *next;
};

struct edges{
	char initial;
	char terminal;
	edges * next;
};

struct degree_count{
	int degree;
	int count;
	degree_count* next;
};

class Stack {
  Node *topOfStackPointer;
	Node* bottomOfStackPointer;

  public:
  //Attributes

  //Method declaration

  Stack () {
    topOfStackPointer = NULL;
  }

  void push(char item) {
    //Declaration area
    Node *newNodePointer;

    //Working area
    newNodePointer = new Node;
    if (newNodePointer != NULL) {
      //Populate the new node
      newNodePointer->data = item;
      newNodePointer->next = NULL;

      //Adjust the new node
      if (topOfStackPointer == NULL) {
        topOfStackPointer = newNodePointer;
				bottomOfStackPointer = newNodePointer;
      }
      else {
        newNodePointer->next = topOfStackPointer;
        topOfStackPointer = newNodePointer;
      }
    }
    else {
      cout << "\nStack is full :)\n";
    }
  }

  char pop() {
    //Declaration area
    Node *deleteNode;
    char popItem;

    //Working area
    if (topOfStackPointer != NULL) {
      popItem = topOfStackPointer->data;
      deleteNode = topOfStackPointer;
      topOfStackPointer = topOfStackPointer->next;
      free(deleteNode);
    }
    return popItem;
  }

  char peek() {
    if (topOfStackPointer != NULL)
      return topOfStackPointer->data;
    else
      return ' ';
  }

  bool isEmpty() {
    if (topOfStackPointer == NULL)
      return true;
    else
      return false;
  }

  void displayStack() {
    //Declaration area
    Node *traverse;

    //Working area
    traverse = topOfStackPointer;
    cout << "\nAddress\t\tItems\tNext Address\n";
    while (traverse != NULL) {
      cout << traverse << "\t" <<traverse->data << "\t" << traverse->next <<endl;
      traverse = traverse->next; //Go to next node
    }
  }

	void itemCount() {
		//Declaration area
		int count;
		Node* traverse;

		//Working area
		count = 0;
		traverse = bottomOfStackPointer;
		while (traverse != NULL) {
			count++;
			traverse = traverse->next;
		}
	}
};

//Fnction declaration
void printDots();
void degreeCount(Node* graph1[], Node* graph2[] , int verticesG1, int verticesG2);
bool lookUp(int value, Node* startOfListPointer);
int listItemCount (Node* startOfListPointer);
int iDFS (Node* graph[], int vertex, int vertices);
int getVertexNumber(char vertex, Node* graph[], int vertices);
bool euilarExists(edges* edge, Node** graph, int vertices);
int inDegree(char a,Node * graph[],int vertices);


//Function returns the degree count of the vertex
int degree (Node * vertex) {
	int count = -1;
	while(vertex != NULL){
		count ++;
		vertex = vertex->next;
	}
	return count;
}

//Function returns the sum of degrees
int sum_of_degrees (Node * graph[], int ver) {
	int sum = 0;
	for(int i = 0; i < ver; i++) {
		sum = sum + degree(graph[i]);
	}
	return sum;
}

//Function checks whether an edge exists between two points or not
bool edgeExists (edges * start, char a, char b) {
	edges * trav = start;
	bool exists = false;
	while(trav != NULL) {
		if(trav->initial == a && trav->terminal == b) {
			exists = true;
			break;
		}
		trav = trav->next;
	}
	return exists;
}

//Function checks whether the graph is directed or not
bool is_directed (edges * e, Node * graph[], int vertices) {
	bool directed = false;
	for (int i = 0; i < vertices; i++) {
		Node * start = graph[i];
		Node * trav = graph[i];
		while (trav->next != NULL) {
			//Check for undirected
			if (edgeExists(e, trav->next->data, start->data)) {
				trav = trav->next;
			}
			else {
				directed = true;
				break;
			}
		}
		if (! directed)
			break;
	}
	return directed;
}

//Function return the number of edges in the graph
int Edges (Node * Graph[], int vertices) {

	int sum = sum_of_degrees(Graph, vertices);
	return sum/2;
}


bool already_present (char array[], char ch, int len) {
	bool present = false;
	for(int i = 0; i < len; i++){
		if(array[i] == ch)
		present = true;
	}
	return present;
}

bool taken(int array[], int x, int c) {
	bool result = false;
	for (int i = 0; i < c; i++) {
		if (x == array[i])
			result = true;
	}
	return result;
}

bool connected(Node * Graph[], int ver, int start) {
	bool result = true;
	int count = 0;
	int count2 = 0;
	char closure[ver];
	closure[0] = Graph[start]->data;
	int i = 0;
	int added[ver];
	while (i < ver) {
		Node * trav = NULL;
		for (int j = 0; j < ver; j++) {
			if (already_present(closure,Graph[j]->data,count+1) && !taken(added,j,count2)) {
				added[count2] = j;
				count2++;
				trav = Graph[j];
				break;
			}
		}
		if (trav == NULL && count < ver) {
			result = false;
			break;
		}
		else
		while(trav != NULL) {
			if(!already_present(closure,trav->data,count+1)) {
				count++;
				closure[count] = trav->data;
			}
			trav = trav->next;
		}
		i++;
	}
	if(count == ver-1) {
		result = true;
	}

return result;
}

degree_count * countOfAllDegrees(Node * graph[], int ver){
	int deg;

	degree_count * dc1_start = NULL;
	degree_count * dc1_end = NULL;

	for(int i = 0; i < ver; i++){
		deg = degree(graph[i]);
		degree_count * trav = dc1_start;
		bool exists = false;
		while(trav != NULL){
			if(trav->degree == deg){
				trav->count++;
				exists = true;
				break;
			}
			trav = trav->next;
		}
		if(! exists){
			degree_count * temp = new degree_count;
			temp->degree = deg;
			temp->count = 1;

			if(dc1_start == NULL){
				dc1_start = temp;
				dc1_end = temp;
				dc1_end->next = NULL;
			}
			else{
				dc1_end->next = temp;
				dc1_end = temp;
				dc1_end->next = NULL;
			}
		}

	}

	return dc1_start;
}

int length(degree_count * t){
	int l = 0;
	degree_count * trav = t;
	while(trav != NULL){
		l++;
		trav = trav->next;
	}
	return l;
}

bool equalCountOfEqualDegrees(degree_count * dc1, degree_count * dc2){
	int len_dc1 = length(dc1);
	int len_dc2 = length(dc2);
	bool result;
	if(len_dc1 == len_dc2){
		degree_count * trav1 = dc1;
		while(trav1 != NULL){
			int degri = trav1->degree;
			int cnt = trav1->count;

			degree_count * trav2 = dc2;
			bool found = false;
			while(dc2 != NULL){
				if(trav2->degree == degri && trav2->count == cnt){
					found = true;
					break;
				}
				trav2 = trav2->next;
			}
			if(found)
				trav1 = trav1->next;
			else
				break;
		}

		if(trav1 == NULL)
			result = true;
		else
			result = false;
	}
	return result;
}

int main(int argc, char** argv) {

  //Declaration area
	ifstream inFile;
	string x; //Variable to receive input from the file
  int counter, verticesG1, verticesG2;

	//Working area
  counter = 0;
  //Open the file
	inFile.open("C:\\Users\\mtalh\\source\\repos\\Data Structure Project\\Vertices G1.txt");
	if (inFile) { //If file opens
    //Loop through the contents
		while (inFile >> x) {
      counter++;
		}
	}
	else {
		cout << "\nError: Unable to open the file Vertices G1.txt\n";
		exit(1);
	}
	//Close the file
  inFile.close();

	verticesG1 = counter;
	Node * Graph1[verticesG1];

	edges * Eg1 = NULL;
	edges * Eg2 = NULL;

	edges * start_Eg1 = Eg1;
	edges * end_Eg1 = Eg1;

	edges * start_Eg2 = Eg1;
	edges * end_Eg2 = Eg1;

	//naming the vertices of Graph 1
  //Opening the file
  inFile.open("C:\\Users\\mtalh\\source\\repos\\Data Structure Project\\Vertices G1.txt");
  if (inFile) {
    //Loop through the file contents
    for(int i = 0; i < verticesG1; i++){
      inFile >> x;
  		Graph1[i] = new Node;
  		Graph1[i]->data = x[0];
  	}
  }
  else{
    cout << "\nError: Unable to open the file Vertices.txt\n";
		exit(1);
  }
	//Close the file
  inFile.close();

  //Open the vertices file
  inFile.open("C:\\Users\\mtalh\\source\\repos\\Data Structure Project\\Vertices G1.txt");

	//Getting the vertices connected to each of the vertices of Graph 1
	for(int i = 0; i < verticesG1; i++) {
		Node * temp2 = Graph1[i];
		Node * start_G1 = temp2;
		Node * end_G1 = temp2;
		end_G1->next = NULL;

    //Get input from the file
    inFile >> x;

		//Loop through the items to get the terminal vertices
		for(int j = 2; j < x.size(); j+=2){
			Node *temp = new Node;
      temp->data = x[j];
			if(start_G1 == NULL){
				start_G1 = temp;
				end_G1 = temp;
				end_G1->next = NULL;
			}
			else{
				end_G1->next = temp;
				end_G1 = temp;
				end_G1->next = NULL;
			}

			edges * e = new edges;
			e->initial = Graph1[i]->data;
			e->terminal = temp->data;

			if(start_Eg1 == NULL){
				start_Eg1 = e;
				end_Eg1 = e;
				end_Eg1->next = NULL;
			}

			else{
				end_Eg1->next = e;
				end_Eg1 = e;
				end_Eg1->next = NULL;
			}

		}
	}

  //Close the file
  inFile.close();

	//naming the vertices of graph 2
  //Open the file
  inFile.open("C:\\Users\\mtalh\\source\\repos\\Data Structure Project\\Vertices G2.txt");

  //Get the vertex count
  counter = 0;
  if (inFile) {
		while (inFile >> x) {
      counter++;
		}
	}
	else {
		cout << "\nError: Unable to open the file Vertices.txt\n";
		exit(1);
	}
  //Close the file
  inFile.close();

  verticesG2 = counter;

  //Declare the graph
  Node * Graph2[verticesG2];

  //Open the file
  inFile.open("C:\\Users\\mtalh\\source\\repos\\Data Structure Project\\Vertices G2.txt");

  if (inFile) {
    //Loop through the contents and store root vertices
    for(int i = 0; i < verticesG2; i++){
      inFile >> x;
  		Graph2[i] = new Node;
  		Graph2[i]->data = x[0];
  	}
  }
  else {
    cout << "\nError: Unable to open the file Vertices.txt\n";
		exit(1);
  }
  inFile.close();

  //Open the file
  inFile.open("C:\\Users\\mtalh\\source\\repos\\Data Structure Project\\Vertices G2.txt");

	//Getting the vertices connected to each of the vertices of Graph 2
	for(int i = 0; i < verticesG2; i++){
  	Node * temp1 = Graph2[i];
  	Node * start_G2 = temp1;
  	Node * end_G2 = temp1;
  	end_G2->next = NULL;

    //Get input from the file
    inFile >> x;

  	for(int j = 2; j < x.size(); j+=2){
  		Node *temp = new Node;
      temp->data = x[j];

  		if(start_G2 == NULL){
  			start_G2 = temp;
  			end_G2 = temp;
  			end_G2->next = NULL;
  		}
  		else{
  			end_G2->next = temp;
  			end_G2 = temp;
  			end_G2->next = NULL;
  		}

  		edges * e2 = new edges;
  		e2->initial = Graph2[i]->data;
  		e2->terminal = temp->data;

  		if(start_Eg2 == NULL){
  			start_Eg2 = e2;
  			end_Eg2 = e2;
  			end_Eg2->next = NULL;
  		}

  		else{
  			end_Eg2->next = e2;
  			end_Eg2 = e2;
  			end_Eg2->next = NULL;
  		}

  	}
  }
  //Close the file
  inFile.close();

	cout << "*****************************************" << endl;
	//Check for graph edges
	cout << "Checking graphs edges";
	printDots();
	//counting the edges of both the graphs
	int edges1;
	int edges2;
	if(! is_directed(start_Eg1,Graph1,verticesG1))
		edges1 = Edges(Graph1,verticesG1);
	else
		edges1 = sum_of_degrees(Graph1,verticesG1);

	if(! is_directed(start_Eg2,Graph2,verticesG2))
		edges2 = Edges(Graph2,verticesG2);
	else
		edges2 = sum_of_degrees(Graph2,verticesG2);

	if(edges1 == edges2)
		cout << "Graph 1 and Graph 2 contain equal " << edges1 << " edges!" << endl;
	else
		cout << "Graph 1 and Graph 2 dont contain equal edges!" << endl;

	//if(connected(Graph2,vertices) && connected(Graph1,vertices) ){
	//	cout << "The Graphs are connected!" << endl;
	//}

	//Check whether graphs are connected
	Sleep(500);
	cout << "\nChecking for whether graphs are connected";
	printDots();
	bool conn = true; //Boolean variable holding connected status
	for(int i = 0; i < verticesG1; i++){
		if(! connected(Graph1,verticesG1,i)){
			cout << "The Graphs are not connected!" << endl;
			conn = false;
			break;
		}
	}
	if(conn)
	for(int i = 0; i < verticesG2; i++){
		if(! connected(Graph2, verticesG2, i)){
			cout << "The Graphs are not connected!" << endl;
			conn = false;
			break;
		}
	}

	if(conn){
		cout << "The Graphs are connected!" << endl;
	}

	//Check whether both graphs have a vertex of degree k
	Sleep(500);
	cout << "\nChecking whether both graphs have a vertex of degree k";
	printDots();
	degreeCount(Graph1, Graph2, verticesG1, verticesG2);

	// Checking if graphs have m vertices with degree k

	Sleep(500);
	cout << "\nChecking if graphs have m vertices with degree k";
	printDots();
	degree_count * dc1 = countOfAllDegrees(Graph1,verticesG1);
	degree_count * dc2 = countOfAllDegrees(Graph2,verticesG2);
	if(equalCountOfEqualDegrees(dc1,dc2)){
		cout << "The graphs contain equal vertices with equal degrees!" << endl;
	}
	else
		cout << "The graphs dont have equal vertices with equal degrees!" << endl;

	//Check for cycles in the graphs
	Sleep(500);
	cout << "\nAnalysing graphs for cycles";
	printDots();
  int g1, g2;
  g1 = iDFS(Graph1, 0, verticesG1);
	g2 = iDFS(Graph2, 0, verticesG2);

  g2 = iDFS(Graph2, 0, verticesG2);
	if (g1 == g2) {
    cout << "Both graphs contain " << g1 << " cycles" << endl;
  }
  else {
		cout << "Both graphs do not have similar amount of cycles\n";
    cout << "Graph 1 has " << g1 << " cycles\n";
		cout << "Graph 2 has " << g2 << " cycles\n";
  }

	//checking if the graphs contain an Euilar Circuit
	Sleep(500);
	cout << "\nAnalyzing graphs for Euler circuit";
	printDots();
	if(euilarExists(start_Eg1,Graph1,verticesG1) && (start_Eg2,Graph2,verticesG2) )
		cout << "An Euilar ciruit exists in both graphs!" << endl;
	else
		cout << "Euilar circuit do not exist in both graphs!" << endl;

	return 0;
}

void printDots() {
	for (int i = 0; i < 3; i++) {
		cout << " . ";
		Sleep(750);
	}
	cout << endl;
}

void degreeCount(Node* graph1[], Node* graph2[] , int verticesG1, int verticesG2) {
	//Declaration area
  bool degreeStatus;
	Node* startG1 = NULL;
	Node* startG2 = NULL;
	Node* endG1 = NULL;
	Node* endG2 = NULL;

	//Working area
	for (int i = 0; i < verticesG1; i++) {
		bool exists = false;
		int d = degree(graph1[i]);
		Node* traverse = startG1;

		while (traverse != NULL) {
			if ((int)traverse->data == d) {
				exists = true;
				break;
			}
			traverse = traverse->next;
		}

		if (!exists) {
			Node* node = new Node;
			node->data = d;
			node->next = NULL;

			if (startG1 == NULL) {
				startG1 = node;
				endG1 = node;
			}
			else {
				endG1->next = node;
				endG1 = node;
			}
		}

	}

	for (int i = 0; i < verticesG2; i++) {
		bool exists = false;
		int d = degree(graph2[i]);
		Node* traverse = startG2;

		while (traverse != NULL) {
			if (traverse->data == d) {
				exists = true;
				break;
			}
			traverse = traverse->next;
		}

		if (!exists) {
			Node* node = new Node;
			node->data = d;
			node->next = NULL;

			if (startG2 == NULL) {
				startG2 = node;
				endG2 = node;
			}
			else {
				endG2->next = node;
				endG2 = node;
			}
		}

	}

	if (listItemCount(startG1) == listItemCount(startG2)) {
		Node* traverse = startG1;
		int d;
		while (traverse != NULL) {
			d = (int)traverse -> data;
			if (lookUp(d, startG2)) {
				cout << "Both graphs have a vertex of degree " << d << endl;
			}
			else {
				cout << "One graphs has a vertex of degree " << d;
				cout << " the other does not\n";
			}
			traverse = traverse->next;
		}
	}
	else if (listItemCount(startG1) > listItemCount(startG2)) {
		Node* traverse = startG1;
		int d;
		while (traverse != NULL) {
			d = (int)traverse -> data;
			if (lookUp(d, startG2)) {
				cout << "\nBoth graphs have a vertex of degree " << d << endl;
			}
			else {
				cout << "\nOne graphs has a vertex of degree " << d;
				cout << " the other does not\n";
			}
			traverse = traverse->next;
		}

		traverse = startG2;
		while (traverse != NULL) {
			d = (int)traverse -> data;
			if (lookUp(d, startG1)) {
				cout << "\nBoth graphs have a vertex of degree " << d << endl;
			}
			else {
				cout << "\nOne graphs has a vertex of degree " << d;
				cout << " the other does not\n";
			}
			traverse = traverse->next;
		}
	}
	else {
		Node* traverse = startG2;
		int d;
		while (traverse != NULL) {
			d = (int)traverse -> data;
			if (lookUp(d, startG1)) {
				cout << "\nBoth graphs have a vertex of degree " << d << endl;
			}
			else {
				cout << "\nOne graphs has a vertex of degree " << d;
				cout << " the other does not\n";
			}
			traverse = traverse->next;
		}
		traverse = startG1;
		while (traverse != NULL) {
			d = (int)traverse -> data;
			if (lookUp(d, startG2)) {
				cout << "\nBoth graphs have a vertex of degree " << d << endl;
			}
			else {
				cout << "\nOne graphs has a vertex of degree " << d;
				cout << " the other does not\n";
			}
			traverse = traverse->next;
		}
	}

}

bool lookUp(int value, Node* startOfListPointer) {
	//Declaration area
	Node* traverse;

	//Working area
	traverse = startOfListPointer;
	while (traverse != NULL) {
		if ((int)traverse->data == value) {
			return true;
		}
		traverse = traverse->next;
	}
	return false;
}

int listItemCount (Node* startOfListPointer) {
	//Declaration area
	int itemCount;
	Node* traverse;

	//Working area
	itemCount = 0;
	traverse = startOfListPointer;
	while (traverse != NULL) {
		itemCount++;
		traverse = traverse->next;
	}
	return itemCount;
}

//Version 1
int iDFS (Node* graph[], int vertex, int vertices) {
	//Declaration area
	Stack itemStack;
	char ver, previous;
	int dg, cycle;
	Node* n;
  bool* visited = new bool[vertices];
  bool* inStack = new bool[vertices];
	bool change;

	//Working area
	change = true;
  for (int i = 0; i < vertices; i++) {
    visited[i] = false;
    inStack[i] = false;
  }

  cycle = 0;
  previous = ' ';
  ver = ' ';
	itemStack.push(graph[vertex]->data);
	visited[vertex] = true;
  inStack[vertex] = true;

	while (!itemStack.isEmpty()) {
		if (change)
    	previous = ver;
		change = false;
		ver = itemStack.pop(); //Get the vertex
		//cout << ver << endl;
		vertex = getVertexNumber(ver, graph, vertices);
    visited[vertex] = true;

		n = graph[vertex]->next;
		dg = degree(graph[vertex]);
		char neighbour[dg];

    //Populate the neighbour array
		for (int i = 0; i < dg; i++) {
			neighbour[i] = n->data;
			n = n->next;
		}

		for (char ng : neighbour) {
      if (!inStack[getVertexNumber(ng, graph, vertices)]) {
        itemStack.push(ng);
        inStack[getVertexNumber(ng, graph, vertices)] = true;
				change = true;
      }
      else if (previous != ng && visited[getVertexNumber(ng, graph, vertices)]) {
        //Cycle found
        cycle++;
				change = true;
      }
		}

	}

  return cycle;
}

int getVertexNumber(char vertex, Node* graph[], int vertices) {
	for (int i = 0; i < vertices; i++) {
		if (vertex == graph[i]->data) {
			return i;
		}
	}
	return -1;
}


bool euilarExists(edges* edge, Node** graph, int vertices) {

	if(! is_directed(edge, graph, vertices)){
		for(int i = 0; i < vertices; i++){
			int j = degree(graph[i]);
			if(j%2 != 0)
				return false;
		}
	}
	else{
		for(int i = 0; i < vertices; i++){
			int j = degree(graph[i]);
			int k = inDegree(graph[i]->data, graph, vertices);
			if(j != k)
				return false;
		}
	}
	return true;
}


int inDegree(char a,Node * graph[],int vertices) {
	//Declaration area
	int degree;

	//Working area
	degree = 0;
	for(int i = 0; i < vertices; i++){
		Node * traverse = graph[i];
		if(traverse != NULL)
		while(traverse->next != NULL){

			if(traverse->next->data == a)
				degree++;
			traverse = traverse->next;
		}

	}
	return degree;
}
