#include "avl.h"

int main(){
	AVL < int, string > map;
	
	map[1] = "This";
	map[2] = "is";
	map[3] = "Awesome!";
	
	cout << map[1] << " " << map[2] << " " << map[3] << endl;
	
	return 0;
}