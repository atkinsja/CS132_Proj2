/**************************************************************************************************
*
*   File name :			driver.cpp
*
*	Programmer:  		Jeremy Atkins
*
*   Driver file initializing a Standings object and allowing for user input in order to 
*	change the list
*
*   Date Written:		in the past
*
*   Date Last Revised:	11/08/2018
****************************************************************************************************/
#define BUF 30			//maximum size of each team name
#include "standings.h"
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;
void printMenu();			//printing the menu
void makeSelection();		//main menu functionality
void validateName(char name[], int);		//name validation
void printTitle();

//main function
int main()
{
	makeSelection();
	return 0;
}

/*******************************************************************************************
*	Function Name:			printMenu
*	Purpose:				This function prints the menu showing the user which options are
*							available to them
*	Input Parameters:		none
*	Output Parameters:		none
*	Return value:			none
********************************************************************************************/
void printMenu()
{
	cout << endl << endl;
	cout << "1. View the list of teams." << endl;
	cout << "2. Add a team." << endl;
	cout << "3. Delete a team." << endl;
	cout << "4. Play a game." << endl;
	cout << "5. Edit a team." << endl;
	cout << "6. Output results." << endl;
	cout << "7. Read in a different file." << endl;
	cout << "8. Print the title." << endl;
	cout << "9. Exit." << endl;
}

/*******************************************************************************************
*	Function Name:			makeSelection
*	Purpose:				This function contains the primary functionality, including
*							the functionality for the main menu which makes calls to the
*							Standings class in order to perform operations
*	Input Parameters:		none
*	Output Parameters:		none
*	Return value:			none
********************************************************************************************/
void makeSelection()
{
	string inFileName;
	string outFileName;
	string dateStr;
	Standings standings;
	ifstream inFile;
	int input;

	printTitle();
	
	//file input
	cout << "Enter the file with the teams information: ";
	cin >> inFileName;
	inFile.open(inFileName);
	if (!inFile)
	{
		cout << "Error opening " << inFileName << endl;
	}
	else
	{
		standings.init(inFile);
		inFile.close();
		cout << inFileName << " successfully loaded." << endl;
	}
	
	//main menu
	printMenu();
	do
	{
		cout << "Make a selection:";
		cin >> input;
		while (cin.fail() || cin.peek() != '\n')
		{
			cin.clear();
			cin.ignore(200, '\n');
			printMenu();
			cout << "Incorrect input.\nPlease enter the number of a menu option.\n";
			cout << "Make selection: ";
			cin >> input;
		}
		cout << endl << endl;
		switch (input)
		{
		//print the menu
		case 1:
			standings.print();
			printMenu();
			break;

		//add a team
		case 2:
			char addTeam[BUF];
			cin.clear();
			cin.ignore();
			cout << "Enter the name of the team to add (-1 to cancel): ";
			cin.getline(addTeam, BUF);
			if (strcmp(addTeam, "-1") == 0)
			{
				cout << "Adding cancelled." << endl;
				printMenu();
				break;
			}
			validateName(addTeam, BUF);
			standings.addTeam(addTeam);
			printMenu();
			break;

		//delete a team
		case 3:
			char deleteTeam[BUF];
			cout << "Enter the name of the team to delete (-1 to cancel): ";
			cin.ignore();
			cin.clear();
			cin.getline(deleteTeam, BUF);
			if (strcmp(deleteTeam, "-1") == 0)
			{
				cout << "Deleting cancelled." << endl;
				printMenu();
				break;
			}
			validateName(deleteTeam, BUF);
			standings.deleteTeam(deleteTeam);
			printMenu();
			break;

		//simulate a game
		case 4:
			char homeTeamName[BUF];
			char awayTeamName[BUF];
			cout << "Enter the name of the home team (-1 to cancel): ";
			
			cin.ignore();
			cin.clear();

			//home team input
			cin.getline(homeTeamName, BUF);

			//not a blank name
			while (strcmp(homeTeamName, "") == 0)
			{
				cout << "No home team name entered.\nEnter the name of the home team: ";
				cin.getline(homeTeamName, BUF);
			}

			//cancel
			if (strcmp(homeTeamName, "-1") == 0)
			{
				cout << "Game cancelled." << endl;
				printMenu();
				break;
			}

			validateName(homeTeamName, BUF);
			
			cout << "Enter the name of the away team (-1 to cancel): ";

			//away team input
			cin.getline(awayTeamName, BUF);

			//not a blank name
			while (strcmp(awayTeamName, "") == 0)
			{
				cout << "No away team name entered.\nEnter the name of the away team: ";
				cin.getline(awayTeamName, BUF);
			}

			//cancel
			if (strcmp(awayTeamName, "-1") == 0)
			{
				cout << "Game cancelled." << endl;
				printMenu();
				break;
			}

			validateName(awayTeamName, BUF);

			//team names are not the same
			while (strcmp(homeTeamName, awayTeamName) == 0)
			{
				cout << "Please enter two different team names." << endl;
				cout << "Enter the name of the home team (-1 to cancel): ";
				cin.getline(homeTeamName, BUF);

				while (strcmp(homeTeamName, "") == 0)
				{
					cout << "No home team name entered.\nEnter the name of the home team: ";
					cin.getline(homeTeamName, BUF);
				}

				if (strcmp(homeTeamName, "-1") == 0)
				{
					cout << "Game cancelled." << endl;
					break;
				}

				validateName(homeTeamName, BUF);

				cout << "Enter the name of the away team (-1 to cancel): ";
				cin.getline(awayTeamName, BUF);

				while (strcmp(awayTeamName, "") == 0)
				{
					cout << "No away team name entered.\nEnter the name of the away team: ";
					cin.getline(awayTeamName, BUF);
				}

				if (strcmp(awayTeamName, "-1") == 0)
				{
					cout << "Game cancelled." << endl;
					break;
				}

				validateName(awayTeamName, BUF);
			}

			standings.playGame(homeTeamName, awayTeamName);
			printMenu();
			break;

		//edit a team
		case 5:
			char teamName[BUF];
			cout << "Enter the name of the team to edit (-1 to cancel): ";
			cin.clear();
			cin.ignore();
			cin.getline(teamName, BUF);
			if (strcmp(teamName, "-1") == 0)
			{
				cout << "Editing cancelled." << endl;
				printMenu();
				break;
			}
			validateName(teamName, BUF);
			standings.editTeam(teamName);
			printMenu();
			break;

		//output to a readable file
		case 6:
			cin.clear();
			cin.ignore();
			cout << "Enter the date: ";
			cin >> dateStr;
			outFileName = "NFL_standings_" + dateStr + ".tsv";
			standings.output(outFileName);
			cout << "Results written to " << outFileName << endl;
			printMenu();
			break;

		//read in a different file
		case 7:
			cin.clear();
			cin.ignore();
			cout << "Enter the name of the file with the teams information: ";
			cin >> inFileName;
			inFile.open(inFileName);
			if (!inFile)
			{
				cout << "Error opening " << inFileName << endl;
				printMenu();
				break;
			}
			else
				cout << inFileName << " successfully loaded." << endl;
			
			standings.init(inFile);
			inFile.close();
			printMenu();
			break;

		//print out the title
		case 8:
			printTitle();
			printMenu();
			break;

		//exit the program
		case 9:
			break;

		default:
			cout << "Incorrect input.\nPlease enter the number of a menu option.\n";
			printMenu();
		}
	} while (input != 9);
}

/*******************************************************************************************
*	Function Name:			validateName
*	Purpose:				This function validates the name of a team, ensuring it does
*							not overflow the buffer
*	Input Parameters:		char [] name	-	the name to be validated
*							int buffer		-	the maximum size of name
*	Output Parameters:		none
*	Return value:			none
********************************************************************************************/
void validateName(char name[], int buffer)
{
	
	while (strlen(name) == (buffer - 1) && cin.peek() != '\n')
	{
		cin.clear();
		cin.ignore(200, '\n');
		cout << "Team name too long.\nPlease input a name with less than " << buffer << " characters: ";
		cin.getline(name, buffer);
	}
}

/*******************************************************************************************
*	Function Name:			printTitle
*	Purpose:				This function prints some ASCII art for a title
*	Input Parameters:		none
*	Output Parameters:		none
*	Return value:			none
********************************************************************************************/
void printTitle()
{
	cout << " ______  ______   ______   ______  ______   ______   __       __        " << endl;
	cout << "/\\  ___\\/\\  __ \\ /\\  __ \\ /\\__  _\\/\\  == \\ /\\  __ \\ /\\ \\     /\\ \\       " << endl;
	cout << "\\ \\  __\\\\ \\ \\/\\ \\\\ \\ \\/\\ \\\\/_/\\ \\/\\ \\  __< \\ \\  __ \\\\ \\ \\____\\ \\ \\____  " << endl;
	cout << " \\ \\_\\   \\ \\_____\\\\ \\_____\\  \\ \\_\\ \\ \\_____\\\\ \\_\\ \\_\\\\ \\_____\\\\ \\_____\\ " << endl;
	cout << "  \\/_/    \\/_____/ \\/_____/   \\/_/  \\/_____/ \\/_/\\/_/ \\/_____/ \\/_____/ " << endl;
	cout << endl;
	cout << " ______  ______   ______   __   __   ______   __  __                    " << endl;
	cout << "/\\  ___\\/\\  == \\ /\\  ___\\ /\\ \"-.\\ \\ / \\___ \\ /\\ \\_\\ \\                   " << endl;
	cout << "\\ \\  __\\\\ \\  __< \\ \\  __\\ \\ \\ \\-.  \\\\/_/  /__\\ \\____ \\                  " << endl;
	cout << " \\ \\_\\   \\ \\_\\ \\_\\\\ \\_____\\\\ \\_\\\\\"\\_\\ /\\_____\\\\/\\_____\\                 " << endl;
	cout << "  \\/_/    \\/_/ /_/ \\/_____/ \\/_/ \\/_/ \\/_____/ \\/_____/                 " << endl;
	cout << endl;

	cout << "                 __" << endl;
	cout << "              .-'||'-." << endl;
	cout << "            .'   ||   '." << endl;
	cout << "           /   __||__   \\" << endl;
	cout << "           | /`-    -`\\ |" << endl;
	cout << "           | | 6    6 | |" << endl;
	cout << "           \\/\\____7___/\\/" << endl;
	cout << "   .--------:\\:I:II:I:/;--------." << endl;
	cout << "  /          \\`:I::I:`/          \\" << endl;
	cout << " |            `------'            |" << endl;
	cout << " |             \\____/             |" << endl;
	cout << " |      ,    __     ___    ,      |" << endl;
	cout << " |======|   /  |   / _ \\   |======|" << endl;
	cout << " |======|   ^| |  | | | |  |======|" << endl;
	cout << " |~~~~~|     | |  | |_| |   |~~~~~|" << endl;
	cout << " |     |\\   [___]  \\___/   /|     |" << endl;
	cout << "  \\    \\|                  |/    /" << endl;
	cout << "  `\\    \\  _ _.-=\"\"=-._ _  /    /'" << endl;
	cout << "    `\\   '`_)\\\\-++++-//(_`'   /'" << endl;
	cout << "      ;   (__||      ||__)   ;" << endl;
	cout << "       ;   ___\\      /___   ;" << endl;
	cout << "        '. ---/-=..=-\\--- .'" << endl;
	cout << "          `\"\"`        `\"\"`" << endl;
}

