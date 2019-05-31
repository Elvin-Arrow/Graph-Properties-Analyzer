#include <iostream>
using namespace std;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
struct Node{
	char data;
	Node *next;
};
int degree(Node * vertex){
	int count = -1;
	while(vertex != NULL){
		count ++;
		vertex = vertex->next;
	}
	return count;
}
int Edges(Node * Graph[],int verteces){
	int sum_of_degrees = 0;
	for(int i = 0; i < verteces; i++){
		sum_of_degrees = sum_of_degrees + degree(Graph[i]);
	}
	
	return sum_of_degrees/2;
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
bool connected(Node * Graph[], int ver ){
	bool result = true;
	int count = 0;
	int count2 = 0;
	char closure[ver];
	closure[0] = Graph[0]->data;
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
	int vertices;
	cout << "How many vertices are there in your graph?" << endl;
	cin >> vertices;
	Node * Graph1[vertices];
	Node * Graph2[vertices];
	//naming the vertices of Graph 1
	cout << "Enter the names of the vertices of graph 1: " << endl;
	for(int i = 0; i < vertices; i++){
		Graph1[i] = new Node;
		cout << "Vertex " << i+1 << ": ";
		cin >> Graph1[i]->data;
	}
	//naming the vertices of graph 2
	cout << "Enter the names of the vertices of graph 2: " << endl;
	for(int i = 0; i < vertices; i++){
		Graph2[i] = new Node;
		cout << "Vertex " << i+1 << ": ";
		cin >> Graph2[i]->data;
	}
	
	//Getting the vertices connected to each of the vertices of Graph 1
	cout << "Graph 1:" << endl;
	for(int i = 0; i < vertices; i++){
		Node * temp2 = Graph1[i];
		Node * start_G1 = temp2;
		Node * end_G1 = temp2;
		end_G1->next = NULL;
		cout << "Vertex " << Graph1[i]->data << " is connected to how many vertices?: ";
		int to_how_many;
		cin >> to_how_many;
		cout << "Enter the name of those vertices: " << endl;
		for(int j = 0; j < to_how_many; j++){
			Node *temp = new Node;
			cout << "Vertex " << j+1 << ": ";
			cin >> temp->data;
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
				
		}
	}
	//Getting the vertices connected to each of the vertices of Graph 2
	cout << "Graph2: " << endl;
	for(int i = 0; i < vertices; i++){
	Node * temp1 = Graph2[i];
	Node * start_G2 = temp1;
	Node * end_G2 = temp1;
	end_G2->next = NULL;
		cout << "Vertex " << Graph2[i]->data << " is connected to how many vertices?: ";
		int to_how_many;
		cin >> to_how_many;
		cout << "Enter the name of those vertices: " << endl;
		for(int j = 0; j < to_how_many; j++){
			Node *temp = new Node;
			cout << "Vertex " << j+1 << ": ";
			cin >> temp->data;
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
				
		}
	}
	cout << "*****************************************" << endl;
	
	//counting the edges of both the graphs
	int edges1 = Edges(Graph1,vertices);
	int edges2 = Edges(Graph2,vertices);
	
	if(edges1 == edges2)
		cout << "Graph 1 and Graph 2 contain equal  " << edges1 << " edges!" << endl;
	else
		cout << "Graph 1 and Graph 2 dont contain equal edges!" << endl;
	
	if(connected(Graph2,vertices) && connected(Graph1,vertices) ){
		cout << "The Graphs are connected!" << endl;
	}
	else
	 	cout << "The Graphs are not connected!" << endl;
	
	return 0;
}
