/*
 * Engima Encryptor
 *
 * Angela Li                   ali520@mtroyal.ca
 * COMP1631-002                Assignment: 5
 * Due: November 26, 2018      Instructor: T.Kendon
 *
 * a5.1.cpp
 *
 * Purpose:
 *
 * Description:
 *
 * Assumptions/Limitations:
 *
 * Known Bugs:
 *
 */

#include <iostream>
#include <cmath>
#include <iomanip>
#include <cctype>
#include <fstream>
using namespace std;

int charToInt(int Letter);

char intToChar(int Num);

bool loadArray (int array[], const char filename[]);

void showTranslation(const int array[]);

void showTranslationDetails(const int arrray[]);

bool loadRotor(int rotor[], const char filename[]);

bool loadReflector(int reflector[], const char filename[]);

void encrypt(const char plainText[], const char cipher[]);

const int R_SIZE = 26;
const int NAME_SIZE = 80;
const char LETTERS_SIZE = 100;

int main(){

    int rotor1[R_SIZE] = {};
    int rotor2[R_SIZE] = {};
    int reflector[R_SIZE] = {};

    char rotorName1[NAME_SIZE] = {};
    char rotorName2[NAME_SIZE] = {};
    char reflectorName[NAME_SIZE] = {};

    char plainTextName[NAME_SIZE] = {};
    char cipherName[NAME_SIZE] = {};

    bool load = true;

    cout << "Enter a file name for Rotor 1: " << endl;
    cin >> rotorName1;
    if (loadRotor(rotor1, rotorName1)){
	showTranslation(rotor1);
    }

    else {

	cout << "Rotor 1 did not load" << endl;
	load = false;
    }

    if (load){
	cout << "Enter a file name for Rotor 2: ";
	cin >> rotorName2;
	if ((loadRotor(rotor2, rotorName2)) && load){
	    showTranslation(rotor2);
	}

	else {

	    cout << "Rotor 2 did not load" << endl;
	    load = false;
	}
    }
    if(load){
	cout << "Enter a file name for Reflector: ";
	cin >> reflectorName;

	if ((loadReflector(reflector, reflectorName)) && load){

	    cout << "Ready for encryption, reflector valid" << endl;

	}

	else {

	    cout << "Reflector did not load" << endl;
	    load = false;

	}
    }

    if (load){

	cout << "Enter a file name for plainText: ";
	cin >> plainTextName;

	cout << "Enter a file name for cipher: ";
	cin >> cipherName;

	encrypt(plainTextName, cipherName);
    }

}

int charToInt(char letter){

    return static_cast<int>(letter);
}

char intToChar(int Num){

    return static_cast<char>(Num);

}

/*
 * indexFor
 *
 * Purpose: Converts a letter to its integer equivalent order in the
 * alpahbet or "index".
 *
 * Description: Converts a letter to its ASCII number than subtracts the
 * ASCII value of the letter 'a', resulting in the integer value of the
 * order the original letter has in the alphabet.
 *
 * Assumptions:
 *
 * 1. Takes in 1 lowercase letter character.
 *
 * Input Parameters: char letter - 1 random lowercase letter in the
 * alphabet.
 *
 * Output: int - character equivalent of letter in the alphabet.
 *
 */

int indexFor(char letter){

    return (charToInt(letter) - charToInt('a'));
}

/*
 * fromIndex
 *
 * Purpose: Converts a integer to its character equivalent base on the
 * order of the alpahbet.
 *
 * Description: Takes an integer value then adds the ASCII value of 'a'
 * then integer converting the number to its letter based on its
 * alphebetical order.
 *
 * Assumptions:
 *
 * 1. The integer being passed is 25 or less.
 *
 * Input Parameters: int index - numerical value (that can represent a
 * the index).
 *
 * Output: char - corresponding lowercase letter based on the ASCII value.
 *
 */


char fromIndex(int index){

    return intToChar(('a') + (index));

}

/*
 * loadArray
 *
 * Purpose: Loads the offset between a letter and the letter that is
 * supposed to be in that spot into an array.
 *
 * Description: Takes a character from the file, which should be a
 * lowercase letter, then subtracts the ASCII
 *
 * Assumptions:
 *
 * 1. input file contains only lowercase letters.
 *
 * Input Parameters: const char filename[] - Name of file being opened
 * as input.
 *
 * Output: int array[] - array being loaded with the differences between
 * letters.
 *
 *         bool result - variable indicating if array was loaded.
 *
 */

bool loadArray (int array[], const char filename[]){

    int difference,
	i;

    char letter;

    bool result = false;

    ifstream inFile;
    ofstream outFile;

    inFile.open(filename);

    if (inFile.fail()){
	cout << "couldn't open " << filename
	     << " file." << endl;
    }

    else {

	for (i = 0; i < R_SIZE; i++){

	    inFile >> letter;

	    difference = ((charToInt(letter)) - charToInt(fromIndex(i)));

	    array[i] = difference;

	}

	if (i == R_SIZE){

	    result = true;
	    cout << "26 letters in this file" << endl;
	}

    }

    inFile.close();

    return result;

}

/*
 * showTranslation
 *
 * Purpose: Visually shows how the characters map to the orginal
 * characters alphebetical order.
 *
 * Description: Prints out all the letters in alphabet then prints
 * out the corresponding letters to show their position.
 *
 * Assumptions:
 *
 * 1. Every index has an offset value.
 *
 * Input Parameters: const int array[] - contains the offset between the
 *                                       26 letters in the file.
 *
 * Output: None.
 *
 */

void showTranslation(const int array[]){

    for (int i = 0; i < R_SIZE; i++){

	cout << fromIndex(i) << " ";
    }

    cout << endl;

    for (int i  = 0; i < R_SIZE; i++){

	cout << "| ";

    }

    cout << endl;

    for (int i = 0; i < R_SIZE; i++){

	cout << intToChar(charToInt((fromIndex(i))) + (array[i])) << " ";

    }

    cout << endl;

    return;

    }

/*
 * showTranslationsDetails
 *
 * Purpose: Shows the details of the translations of the letters.
 *
 * Description: Prints out the offset value in the corresponding index
 * then shows how the offset produces the letter.
 *
 * Assumptions:
 *
 * 1. Every index has an offset value.
 *
 * Input Parameters: const int array[] - contains the offset between the 26
 *                                       letters in the file.
 *
 * Output: None.
 *
 *
 */

void showTranslationDetails(const int array[]){

    int i;

    for (i = 0; i < R_SIZE; i++){

	cout << "array [" << fromIndex(i) << "] = " << array[i] << " | "
	     << array[i] << " + " << fromIndex(i) << " ==> "
	     << intToChar(fromIndex(i) + array[i]) << endl;

    }

    return;

}

bool loadRotor(int rotor[], const char filename[]){

    bool result = false;

    if (loadArray(rotor, filename)){

	result = true;


    }

    return result;

}

/*
 * loadReflector
 *
 * Purpose: Loads an array then checks if the letters mapped properly
 * to each other.
 *
 * Description: Loads an array and then checks if ‘interchanges’ a pair of
 * characters meaning each (lower case alphabetic) character α, whenever
 * the αth element of the array has value β, the βth element of the array
 * has value α.
 *
 * Assumptions:
 *
 * 1. Reflector will not be valid after the first incorrect letter mapping.
 *
 * 2. Only the first incorrect letter mapping will be printed.
 *
 * Input Parameters: const char reflectorName[] - Name of reflector.
 *
 * Output: bool result - variable indicating if the reflector was valid.
 *
 */

bool loadReflector(int reflector[], const char reflectorName[]){

    bool result;
    int i, j;

    if (loadArray(reflector, reflectorName)){

	for (i = 0; i < R_SIZE; i++){

	    j = reflector[i] + i;

	    if ((reflector[i] == -(reflector[j])) && (reflector[i] != 0)){

		result = true;

	    }

	    else { // error message details the first specific error in
                   // reflector file of mismatched letters.

		cout << fromIndex(reflector[i]) << " translates to "
		     << fromIndex(reflector[j] + 32) << " but "
		     << fromIndex(reflector[i])
		     << " does not translate to "
		     << fromIndex(reflector[j] + 32) << endl;

		result = false;

		i = R_SIZE;
	    }
	}

	if (result){

	    showTranslation(reflector);
	}
    }

    else {

	cout << "Reflector was not valid." << endl
	     << "Details could not be shown." << endl;

    }

    return result;

}

/*
 * encrypt
 *
 * Purpose: Turns a regular text file's A-Z letters into '*' then inputs
 * it into another text file.
 *
 * Description: Takes plain text and turns the lowercase alphabet letters
 * into '*' and just directly outputs anything else to the cipher file
 *
 * Assumptions:
 *
 * 1. The only the lowercase letters will be "encrypted" in plain text
 * file; uppercase letters will be simply moved over.
 *
 * 2. The cipher text is empty.
 *
 * Input Parameters: const char plainTextName[] - Name of the plain text
 *                                                file needed to be
 *                                                encrypted.
 *
 * Output: const char cipherName[] - Name of cipher file where the
 *                                   encrypted text is being moved.
 *
 */

void encrypt(const char plainTextName[], const char cipherName[]){

    char character;

    ifstream inFile;
    ofstream outFile;

    inFile.open(plainTextName); // input file.

    outFile.open(cipherName); // output file.

    inFile.get(character);

    while (!inFile.eof()){

	if (character >= 'a' && character <= 'z'){ // checking for
                                                   // lowercase letters.

	    character = '*';

	    outFile.put(character);

	}

	else {

	    outFile.put(character);

	}

	inFile.get(character);

    }

    inFile.close();
    outFile.close();

    cout << "File was encrypted" << endl;

    return;

}
