#include <iostream>
#include <fstream>

using namespace std;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
struct Node{
	char data;
	Node *next;
};

struct edges{
	char initial;
	char terminal;
	edges * next;
};

int degree(Node * vertex){
	int count = -1;
	while(vertex != NULL){
		count ++;
		vertex = vertex->next;
	}
	return count;
}

int sum_of_degrees(Node * graph[], int ver){
	int sum = 0;
	for(int i = 0; i < ver; i++){
		sum = sum + degree(graph[i]);
	}
	return sum;
}

bool edgeExists(edges * start, char a, char b){
	edges * trav = start;
	bool exists = false;
	while(trav != NULL){
		if(trav->initial == a && trav->terminal == b){
			exists = true;
			break;
		}
		trav = trav->next;
	}
	return exists;
}

bool is_directed(edges * e, Node * graph[], int vertices){
	bool directed = false;
	for(int i = 0; i<vertices; i++){
		Node * start = graph[i];
		Node * trav = graph[i];
		while(trav->next != NULL){
			if(edgeExists(e,trav->next->data,start->data)){
				trav = trav->next;
			}
			else{
				directed = true;
				break;
			}
		}
		if(! directed)
			break;
	}
	return directed;
}

int Edges(Node * Graph[],int verteces){

	int sum = sum_of_degrees(Graph,verteces);
	return sum/2;
}

bool already_present(char array[], char ch, int len){
	bool present = false;
	for(int i = 0; i < len; i++){
		if(array[i] == ch)
		present = true;
	}
	return present;
}

bool taken(int array[], int x, int c){
	bool result = false;
	for(int i = 0; i < c; i++){
		if(x == array[i])
			result = true;
	}
	return result;
}

bool connected(Node * Graph[], int ver, int start){
	bool result = true;
	int count = 0;
	int count2 = 0;
	char closure[ver];
	closure[0] = Graph[start]->data;
	int i = 0;
	int added[ver];
	while(i < ver){
		Node * trav = NULL;
		for(int j = 0; j < ver; j++){
			if(already_present(closure,Graph[j]->data,count+1) && !taken(added,j,count2)){
				added[count2] = j;
				count2++;
				trav = Graph[j];
			}
		}
		if(trav == NULL && count < ver){
			result = false;
			break;
		}
		else
		while(trav != NULL){
			if(!already_present(closure,trav->data,count+1)){
				count++;
				closure[count] = trav->data;
			}
			trav = trav->next;
		}
		i++;
	}
	if(count == ver-1){
		result = true;
	}

return result;
}

int main(int argc, char** argv) {

  //Declaration area
	ifstream inFile;
	string x; //Variable to receive input from the file
  int counter;

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

  inFile.close();
	int vertices = counter;
	Node * Graph1[vertices];


	edges * Eg1 = NULL;
	edges * Eg2 = NULL;

	edges * start_Eg1 = Eg1;
	edges * end_Eg1 = Eg1;

	edges * start_Eg2 = Eg1;
	edges * end_Eg2 = Eg1;
	//naming the vertices of Graph 1
	cout << "Enter the names of the vertices of graph 1: " << endl;
  //Opening the file
  inFile.open("C:\\Users\\mtalh\\source\\repos\\Data Structure Project\\Vertices G1.txt");
  if (inFile) {
    //Loop through the file contents
    for(int i = 0; i < vertices; i++){
      inFile >> x;
  		Graph1[i] = new Node;
  		cout << "Vertex " << i+1 << ": ";
  		Graph1[i]->data = x[0];
  	}
  }
  else{
    cout << "\nError: Unable to open the file Vertices.txt\n";
		exit(1);
  }
  inFile.close();

  //Open the vertices file
  inFile.open("C:\\Users\\mtalh\\source\\repos\\Data Structure Project\\Vertices G1.txt");
  //Getting the vertices connected to each of the vertices of Graph 1
	cout << "Graph 1:" << endl;
	for(int i = 0; i < vertices; i++){
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

  vertices = counter;

  //Declare the graph
  Node * Graph2[vertices];

  //Open the file
  inFile.open("C:\\Users\\mtalh\\source\\repos\\Data Structure Project\\Vertices G2.txt");

  if (inFile) {
    //Loop through the contents and store root vertices
    for(int i = 0; i < vertices; i++){
      inFile >> x;
  		Graph2[i] = new Node;
  		cout << "Vertex " << i+1 << ": ";
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
	cout << "Graph2: " << endl;
	for(int i = 0; i < vertices; i++){
  	Node * temp1 = Graph2[i];
  	Node * start_G2 = temp1;
  	Node * end_G2 = temp1;
  	end_G2->next = NULL;

    //Get input
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
	if(! is_directed(start_Eg1,Graph1,vertices))
		edges1 = Edges(Graph1,vertices);
	else
		edges1 = sum_of_degrees(Graph1,vertices);

	if(! is_directed(start_Eg2,Graph2,vertices))
		edges2 = Edges(Graph2,vertices);
	else
		edges2 = sum_of_degrees(Graph2,vertices);

	if(edges1 == edges2)
		cout << "Graph 1 and Graph 2 contain equal  " << edges1 << " edges!" << endl;
	else
		cout << "Graph 1 and Graph 2 dont contain equal edges!" << endl;

	//if(connected(Graph2,vertices) && connected(Graph1,vertices) ){
	//	cout << "The Graphs are connected!" << endl;
	//}

	bool conn = true;
	for(int i = 0; i < vertices; i++){
		if(! connected(Graph1,vertices,i)){
			cout << "The Graphs are not connected!" << endl;
			conn = false;
			break;
		}
	}
	if(conn)
	for(int i = 0; i < vertices; i++){
		if(! connected(Graph2,vertices,i)){
			cout << "The Graphs are not connected!" << endl;
			conn = false;
			break;
		}
	}

	if(conn){
		cout << "The Graphs are connected!" << endl;
	}

	return 0;
}
