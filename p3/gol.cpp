/*
 * CSc103 Project 3: Game of Life
 * See readme.html for details.
 * Please list all references you made use of in order to complete the
 * assignment: your classmates, websites, etc.  Aside from the lecture notes
 * and the book, please list everything.  And remember- citing a source does
 * NOT mean it is okay to COPY THAT SOURCE.  What you submit here **MUST BE
 * YOUR OWN WORK**.
 * References:
 * Dawen, Azwad, Matt, Kyle, readme.html
 *
 * Finally, please indicate approximately how many hours you spent on this:
 * #hours: INT_MAX
 */

#include <iostream>
#include <cstdio>
#include <stdlib.h> // for exit();
#include <getopt.h> // to parse long arguments.
#include <unistd.h> // sleep
#include <vector>
using std::vector;
#include <string>
using std::string;
using namespace std;

static const char* usage =
"Usage: %s [OPTIONS]...\n"
"Text-based version of Conway's game of life.\n\n"
"   --seed,-s     FILE     read start state from FILE.\n"
"   --world,-w    FILE     store current world in FILE.\n"
"   --fast-fw,-f  NUM      evolve system for NUM generations and quit.\n"
"   --help,-h              show this message and exit.\n";

size_t max_gen = 0; /* if > 0, fast forward to this generation. */
string wfilename =  "/tmp/gol-world-current"; /* write state here */
FILE* fworld = 0; /* handle to file wfilename. */
string initfilename = "/tmp/gol-world-current"; /* read initial state from here. */
vector<vector<bool> > W ;
size_t nbrCount(size_t i, size_t j, const vector<vector<bool> >& g);
void update();
void initFromFile(const string fname); /* read initial state into vectors. */
void mainLoop();
void dumpState(FILE* f);

/* NOTE: you can use a *boolean* as an index into the following array
 * to translate from bool to the right characters: */
char text[3] = ".O";

int main(int argc, char *argv[]) {
	// define long options
	static struct option long_opts[] = {
		{"seed",    required_argument, 0, 's'},
		{"world",   required_argument, 0, 'w'},
		{"fast-fw", required_argument, 0, 'f'},
		{"help",    no_argument,       0, 'h'},
		{0,0,0,0}
	};
	// process options:
	char c;
	int opt_index = 0;
	while ((c = getopt_long(argc, argv, "hs:w:f:", long_opts, &opt_index)) != -1) {
		switch (c) {
			case 'h':
				printf(usage,argv[0]);
				return 0;
			case 's':
				initfilename = optarg;
				break;
			case 'w':
				wfilename = optarg;
				break;
			case 'f':
				max_gen = atoi(optarg);
				break;
			case '?':
				printf(usage,argv[0]);
				return 1;
		}
	}

	/* TODO: comment out 3 lines above once you see what's in them. */
	/* NOTE: if wfilename == "-" you should write to stdout, not a file
	 * named "-"! */

	initFromFile(initfilename);
	mainLoop();

	return 0;
}

size_t nbrCount(size_t i, size_t j, const vector<vector<bool> >& g)
{
	size_t counter = 0;
	int r = g.size();
	int c = g[0].size();
	for (int x = -1; x <= 1; x++)
	{
		for (int y = -1; y <= 1; y++)
		{
			if ((g[(i + x + r)%r][(j + y + c)%c] == 1))
			{
				counter++;
			}
		}
	}
	if ((g[i][j]) == 1){
		counter--;
	}
	return counter;
}

void update(){
	vector<vector<bool> > newGen = W;
	size_t r = W.size();
	size_t c = W[0].size();
	for (size_t i = 0; i < r; i++){
		for (size_t j = 0; j < c; j++){
			int alive = nbrCount(i, j, W);
			if ((W[i][j] == 1) && (alive < 2 || alive > 3)){
				newGen[i][j] = 0;
			}
			else if ((W[i][j] == 0) && (alive == 3)){
				newGen[i][j] = 1;
			}
		}
	}
	W = newGen;
}

void initFromFile(const string fname) {
    //Initializes board from a file
    FILE* f = fopen(fname.c_str(),"rb");
    if (!f) {
        exit(1);
    }
    //Reinitialiaze world
    W.clear();
    W.push_back(vector<bool>());
    size_t rows = 0;
    //Read character by character and input into world
    char c;
    while (fread(&c,1,1,f)) {
    if (c == '\n') {
				//New line, increment row
        rows++;
        W.push_back(vector<bool>());
    } else if (c == '.') {
        W[rows].push_back(false); /* dead x_x */
    } else {
        W[rows].push_back(true); /* alive 8D */
    }
    }
    fclose(f);
    //Remove last row (if empty?)
    W.pop_back();
}

void mainLoop() {
	FILE* f;
	if (wfilename == "-"){
		f = stdout;
	}
	else {
		f = fopen(wfilename.c_str(), "wb");
	}

	if (max_gen == 0) {
		while(true){
			sleep(1);
			update();
			dumpState(f);
		}
	}
	else {
		for (size_t x = 0; x < max_gen; x++)
		{
			update();
		}
		dumpState(f);
	}
	fclose(f);
}

void dumpState(FILE* f)
{
	rewind(f);
	size_t r = W.size();
	size_t c = W[0].size();
	char ch;
	for (size_t x = 0; x < r; x++){
		for (size_t y = 0; y < c; y++){
			if (W[x][y] == 0){
				ch = '.';
				fwrite(&ch,1,1,f);
			}
			else if (W[x][y] == 1){
				ch = 'O';
				fwrite(&ch,1,1,f);
			}
		}
		ch = '\n';
		fwrite(&ch,1,1,f);
	}
}





