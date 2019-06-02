#include <iostream>
#include <fstream>

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

class Stack {
  Node *topOfStackPointer;

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

  bool isStackEmpty() {
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


};

//Fnction declaration
void degreeCount(Node* graph1[], Node* graph2[] , int verticesG1, int verticesG2);
void simpleDFS(Node* graph[], int vertices);
void sDFS(bool* visited, int vertex, Node* graph[], int vertices);
bool dfs(bool* visited, Node* vertex, char parent, Node* graph[], int vertices);
int getNeighbouringVertexIndex(Node* vertex, Node* graph[], int vertices);
int getVertexNumber(char vertex, Node* graph[], int vertices);
bool simpleCircuit(Node* graph[], int vertices);

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

	degreeCount(Graph1, Graph2, verticesG1, verticesG2);
	cout << endl;
	//cout << simpleCircuit(Graph1, verticesG1) << endl;
	simpleDFS(Graph2, verticesG2);
	return 0;
}

void degreeCount(Node* graph1[], Node* graph2[] , int verticesG1, int verticesG2) {
	//Declaration area

	//Working area
	cout << "\nGraph 1\n";
	for (int i = 0; i < verticesG1; i++) {
		cout << "Degree of " << graph1[i]->data  << " is: "<< degree(graph1[i]) << endl;
	}

	cout << "\nGraph 2\n";
	for (int i = 0; i < verticesG2; i++) {
		cout << "Degree of " << graph2[i]->data  << " is: "<< degree(graph2[i]) << endl;
	}

}

void simpleDFS(Node* graph[], int vertices) {
	//Declaration area
	bool* visited = new bool[vertices];

	//Working area
	for (int i = 0; i < vertices; i++) {
		visited[i] = false;
	}

	for (int i = 0; i < vertices; i++) {
		if (visited[i] == false) {
			sDFS(visited, i, graph, vertices);
		}
	}
}

void sDFS(bool* visited, int vertex, Node* graph[], int vertices) {
	//Declaration area
	int d;
	Node* temp = graph[vertex];

	//Working area
	visited[vertex] = true;
	cout << graph[vertex]->data << endl;

	d = degree(graph[vertex]);

	for (int i = 0; i < d; i++) {
		temp = graph[vertex];
		for (int j = 0; j < i; j++) {
			temp = temp->next;
		}
		vertex = getVertexNumber(temp->data, graph, vertices);
		if (!visited[vertex])
			sDFS(visited, vertex, graph, vertices);

	}
}

bool dfs(bool* visited, Node* vertex, char parent, Node* graph[], int vertices) {
	//Declaration area
	int d, p, vn;

	//Working area
	//Mark the vertex as visited
	visited[getVertexNumber(vertex->data, graph, vertices)];

	d = degree(vertex);
	for (int i = 0; i < d; i++) {
		//Set parent for the next recursion
		p = graph[getVertexNumber(vertex->data, graph, vertices)]->data;
		//Goto the next vertex
		vertex = vertex->next;
		//Get vertex number and check visit status
		vn = getVertexNumber(vertex->data, graph, vertices);
		if (!visited[vn]){
			if (dfs(visited, vertex, p, graph, vertices))
				return true;
			else if (vertex->data != p) {
				return true;
			}
		}
	}
	return false;
}

int getNeighbouringVertexIndex(Node* vertex, Node* graph[], int vertices) {

	for (int i = 0; i < vertices; i++) {
		if (graph[i]->data == vertex->data) {
			return i;
		}
	}
	return -1;
}

int getVertexNumber(char vertex, Node* graph[], int vertices) {
	for (int i = 0; i < vertices; i++) {
		if (vertex == graph[i]->data) {
			return i;
		}
	}
	return -1;
}

bool simpleCircuit(Node* graph[], int vertices) {
	//Declaration area
	bool* visited = new bool[vertices];

	//Working area
	for (int i = 0; i < vertices; i++) {
		visited[i] = false;
	}

	for (int i = 0; i < vertices; i++) {
		if (!visited[i]) {
			if (dfs(visited, graph[i]->next, ' ', graph, vertices)) {
				return true;
			}
		}
	}
	return false;
}
