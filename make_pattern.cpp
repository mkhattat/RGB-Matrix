/* This is a helper script for the game.
 * You do not need to complie this for the actuele game.
 *  This script is used in combination with pipe to build the patterns
 */


#include <iostream>
#include <string>


using namespace std;
int main(){

	string str_up, str_down;
	cin >> str_up;
	cin >> str_down;

	int size = 1000;
	uint8_t array[size];

	for (int i = 0; i<size; i++){
		array[i] = 0;
	}

	uint8_t tmp1, tmp2, up, down;

	cout << "uint8_t pattern[" << str_up.length() << "] = {\n";

	for (int i=0; i<str_up.length(); i++){
		tmp1 = str_up[i] - '0';
		tmp2 = str_down[i] - '0';	
		if (tmp1 == 1) up = 0b100;
	   	else if (tmp1 == 2) up = 0b110;
		else if (tmp1 == 3) up = 0b111;
		else up = 0;
		
		if (tmp2 == 1) down = 0b001;
		else if (tmp2 == 2) down = 0b011;
		else if (tmp2 == 3) down = 0b111;
		else down = 0;

		array[i] = (up + (down << 3));
	}

	for (int i=0; i<str_up.length(); i++){
		if (i == 0)
			printf("%d", array[i]);
		else
			printf(",\n%d", array[i]);
	}

	cout << "};";

}
