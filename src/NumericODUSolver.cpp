#include "../includes/NumericMethodsFODU.h"

using namespace std;

void NumericODUSolver::printSolver() {
	cout << "t0 = " << t0 << endl;
	cout << "t = " << t << endl;
	cout << "n = " << n << endl;
	cout << "method = " << method << endl;
	cout << "outputFile = " << outputFile << endl;
}

NumericODUSolver::NumericODUSolver(string inputFile) {
	ifstream fin(inputFile);
	if (!fin.is_open()) {
		cout << "File doesn't open!!!";
		exit(0);
	}
	string word, value;
	while (fin >> word) {
		if (word != "initCond:")
			fin >> value;
		else
			getline(fin, value);
		if (word == "t0:")
			t0 = stoi(value);
		else if (word == "t1:")
			t = stoi(value);
		else if (word == "equation:") {
			if (value == "test1") {
				equations.push_back(test1Equation1);
				equations.push_back(test1Equation2);
			}
			else if (value == "myTest1") {
				equations.push_back(myTest1Equation1);
				equations.push_back(myTest1Equation2);
				functions.push_back(myTest1ExactSol1);
				functions.push_back(myTest1ExactSol2);
			}
			else {
				cout << "No such test as: \" " << value << "\"";
				exit(0);
			}
			test = value;
		}
		else if (word == "numberOfStep:")
			n = stoi(value);
		else if (word == "initCond:")
		{
			vector <string> buffer;
			boost::split(buffer, value, boost::is_any_of(" "));
			for (auto i : buffer) {
				if (i != "") {
					initialCond.push_back(stoi(i));
				}
			}
		}
		else if (word == "method:")
		{
			method = value;
		}
		else if (word == "outputFile:")
			outputFile = value;
		else if (word == "defaultStep:")
			step = stod(value);
		else {
			cout << "I don't now such paramert as: \" " << word << "\"";
			fin.close();
			exit(0);
		}
	}
	fin.close();
};