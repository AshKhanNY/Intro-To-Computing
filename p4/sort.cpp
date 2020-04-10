/*
 * CSc103 Project 4: Sorting with lists
 * See readme.html for details.
 * Please list all references you made use of in order to complete the
 * assignment: your classmates, websites, etc.  Aside from the lecture notes
 * and the book, please list everything.  And remember- citing a source does
 * NOT mean it is okay to COPY THAT SOURCE.  What you submit here **MUST BE
 * YOUR OWN WORK**.
 * References: Dawen, Azwad, Kyle, cplusplus.com (for swap function)
 *
 *
 * Finally, please indicate approximately how many hours you spent on this:
 * #hours: 8
 */

#include <iostream>
using std::cin;
using std::cout;
using std::endl;
#include <getopt.h> // to parse long arguments.
#include <string>
using std::string;

/* doubly linked list node: */
struct node {
	string data;
	node* prev;
	node* next;
	node(string s="", node* p=NULL, node* n=NULL) : data(s),prev(p),next(n) {}
};

void sort(node*& x);
void forwPrint(node* x);
void revPrint(node* x);
void input(node*& x, string y);
bool uni(node* x, string y);

int main(int argc, char *argv[]) {
	/* define long options */
	static int unique=0, reverse=0;
	static struct option long_opts[] = {
		{"unique",   no_argument,       &unique,   'u'},
		{"reverse",  no_argument,       &reverse,  'r'},
		{0,0,0,0} // this denotes the end of our options.
	};
	/* process options */
	char c; /* holds an option */
	int opt_index = 0;
	while ((c = getopt_long(argc, argv, "ur", long_opts, &opt_index)) != -1) {
		switch (c) {
			case 'u':
				unique = 1;
				break;
			case 'r':
				reverse = 1;
				break;
			case '?': /* this will catch unknown options. */
				return 1;
		}
	}

	node* curr = NULL;
	node* start = NULL;
	node* end = NULL;
	string line;

	//Very first node
	if (getline(cin,line)){
		curr = new node;
		curr->data = line;
		start = curr; //Marker for beginning list
	}

	//Following nodes
	while(getline(cin,line)){
		if (line == "end") break; //terminator (for testing only)
		if (unique == 1){
			if (uni(start, line) == true) //determines if current word is unique
				input(curr, line);
		}
		else{
			input(curr, line);
		}
	}
	end = curr; //Marker for end of list

	//checks if elligible for sorting
	sort(start);

	//checks what order you want to print in
	if (reverse == 1)
		revPrint(end);
	else
		forwPrint(start);

	return 0;
}

void sort(node*& x){ //sorts nodes by values, x = start
	for (node* i = x; i != NULL; i = i->next){
		for (node* k = x; k != NULL; k = k->next){
			if (k->data > i->data)
				swap(i->data, k->data);
		}
	}
}

void input(node*& x, string y){ //sets up new node, updates
	x->next = new node; //sets up new node
	x->next->prev = x;
	x = x->next;
	x->data = y;
}

bool uni(node* x, string y){ //checks if line is unique
	for (node* i = x; i != NULL; i = i->next){
		if (y == (*i).data)
			return false; //meaning it is not unique
	}
	return true; //meaning it is unique
}

void forwPrint(node* x){ //Forward printer, x = start
	for (node* i = x; i != NULL; i = i->next){
		cout << ((*i).data) << endl;
	}
}

void revPrint(node* x){ //Reverse printer, x = end
	for (node* i = x; i != NULL; i = i->prev){
		cout << ((*i).data) << endl;
	}
}










