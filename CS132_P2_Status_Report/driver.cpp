//#include "list.h"
//#include "team.h"
#define BUF 30
#include "standings.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;
void printMenu();
void makeSelection();
int main()
{
	/*Standings standings;
	cout << "Before sorting:" << endl;
	standings.print();
	cout << "---------------After sorting------------------------" << endl;
	standings.sort();
	standings.print();*/
	printMenu();
	makeSelection();

	
	return 0;
}

void printMenu()
{
	cout << "1. Read file to put into the team list." << endl;
	cout << "2. View the list of teams." << endl;
	cout << "3. Add a team." << endl;
	cout << "4. Delete a team." << endl;
	
	

}

void makeSelection()
{
	string filename = "NFL_standings_10162018.tsv";	//testing purposes
	Standings standings;
	int input;
	char teamName [BUF];
	do
	{
		cout << "Make a selection:";
		cin >> input;
		
		switch (input)
		{
		case 1:
			cout << "Enter the file with the teams information:" << endl;
			cout << "Default file provided for development purposes" << endl;
			//cin >> filename;
			standings.init(filename);
			standings.standingSort();
			printMenu();
			break;
		case 2:
			standings.print();
			printMenu();
			break;
		case 3:
			standings.addTeam();
			//standings.standingSort();
			printMenu();
			break;
		case 4:
			cout << "Enter the name of the team to delete: " << endl;
			cin.ignore();
			cin.clear();
			cin.getline(teamName, BUF);
			standings.deleteTeam(teamName);
			printMenu();
			break;
		case 9:
			break;
		}
	} while (input != 9);
}