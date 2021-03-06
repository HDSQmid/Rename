/* Rename - For when spelling matters

This application recieves input from the user and provides better spellings

It gets a line from the console, and first checks if the entire sentence can be replaced, 
if a replacement is found then it returns that input
otherwise it splits it into individual words and checks for replacements for those words 
and concatenates those words into a string
any words that dont have replacements are split into syllables and the syllbles
checked for replacements then compiled into words

*/

// Rename.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#define sentencesFile "sentences.txt"
#define wordsFile "words.txt"
#define numParses 10

std::string checkSentenceReplacement(std::string test);
std::string checkWordreplacement(std::string test);
void loadReplacements();
void loadSentenceReplacements();
void loadWordReplacements();

std::map<std::string, std::string> sentences;
std::map<std::string, std::string> words;

/***************************************************************************/

int main() {
	//initialise application
	loadReplacements();


	std::string in = "";
	std::string out = "";
	std::getline(std::cin, in);
	for (int i = 0; i < numParses; i++) {

		if (out != "") in = out;

		out = checkSentenceReplacement(in);
		if (out == "") {

			std::string currentWord, replacement;
			std::stringstream ss(in);
			// split into individual words
			while (true) {

				ss >> currentWord;
				replacement = checkWordreplacement(currentWord);
				if (replacement == "") {
					// split into syllables

					//for now
					replacement = currentWord;
				}
				if (out == "") out = replacement;
				else out = out + " " + replacement;
				if (ss.eof()) break;
			}

		}
	}
	std::cout << out << std::endl;

	system("PAUSE");
    return 0;
}

/******************************************************************************/

std::string checkSentenceReplacement(std::string test)
{
	std::string str = sentences[test];
	return str;
}

std::string checkWordreplacement(std::string test)
{
	std::string str = words[test];
	return str;
}

/*****************************************************************************/

void loadReplacements() {

	loadSentenceReplacements();
	loadWordReplacements();

}

void loadSentenceReplacements() {

	// attempt to import file
	std::ifstream input;
	// import file
	input.open(sentencesFile, std::ios::in);
	if (input.is_open()) {
		
		std::string id;
		std::string val;
		

		while (!input.eof()) {

			do {
				std::getline(input, id); // get line from file
				if (id == "") continue; // if line is blank skip that line
			} while (id[0] == '#');
			
			do {
				std::getline(input, val); // get line from file
				if (val == "") continue; // if line is blank skip that line
			} while (val[0] == '#');

			sentences.insert(std::pair<std::string, std::string>(id, val));

		}
		input.close();
	}

	else {

		std::cout << "Failed to load sentence replacements" << std::endl;

	}





}

void loadWordReplacements() {

	// attempt to import file
	std::ifstream input;
	// import file
	input.open(wordsFile, std::ios::in);
	if (input.is_open()) {

		std::string in;
		std::string id;
		std::string val;

		while (!input.eof()) {

			std::getline(input, in); // get line from file
			if (in == "") continue; // if line is blank skip that line
			if (id[0] == '#') continue; // if line is a comment (indicated by '#') skip it
			std::stringstream iss(in); // create stringstream
			iss >> id; // get id as first word of stringstream
			std::stringstream oss;
			oss << iss.rdbuf(); // transfer buffer to other stringstream
			val = oss.str(); // set remainder of string as final value of translation
			val = val.substr(1);

										   //add some error handling here

			words.insert(std::pair<std::string, std::string>(id, val));

		}
		input.close();
	}

	else {

		std::cout << "Failed to load word replacements" << std::endl;

	}




}

