/**************************************************************************************************
*
*   File name :			standings.cpp
*
*	Programmer:  		Jeremy Atkins
*
*   Implementation of the functions defined in standings.h Contains the Standings class
*	which stores and updates a list of teams according to user input defined in the 
*	driver class
*
*   Date Written:		in the past
*
*   Date Last Revised:	11/08/2018
****************************************************************************************************/
#include "standings.h"
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;
/*******************************************************************************************
*	Function Name:			Standings() - the constructor
*	Purpose:				This constructor creates a Standings object and initilializes
*							a boolean determining whether the object is empty or not to true
*	Input Parameters:		none
*	Output Parameters:		none
*	Return value:			none
********************************************************************************************/
Standings::Standings()
{
	isEmpty = true;
}

/*******************************************************************************************
*	Function Name:			init
*	Purpose:				This function initializes a Standings object by reading input
*							from a file, parsing the data, and creating a doubly linked list 
*							containing the information as Team structs as defined in Team.h
*							and sorting the Teams using the standingsSort function
*							as defined below
*	Input Parameters:		ifstream& inFile	-	the file containing the Team data
*	Output Parameters:		ifstream&
*	Return value:			none
********************************************************************************************/
void Standings::init(ifstream& inFile)
{
	Team team;
	//if the list is not empty, delete it
	if (!isEmpty)
	{
		deleteList();
		isEmpty = true;
	}

	//parse data from inFile
	inFile.getline(team.name, BUF, '\t');
	while (inFile)
	{
		inFile >> team.total.wins;
		inFile >> team.total.losses;
		inFile >> team.total.ties;

		inFile >> team.home.wins;
		inFile.ignore();
		inFile >> team.home.losses;
		inFile.ignore();
		inFile >> team.home.ties;

		inFile >> team.away.wins;
		inFile.ignore();
		inFile >> team.away.losses;
		inFile.ignore();
		inFile >> team.away.ties;

		inFile >> team.division.wins;
		inFile.ignore();
		inFile >> team.division.losses;
		inFile.ignore();
		inFile >> team.division.ties;

		inFile >> team.conference.wins;
		inFile.ignore();
		inFile >> team.conference.losses;
		inFile.ignore();
		inFile >> team.conference.ties;

		inFile >> team.divNum;
		inFile.ignore(200, '\n');
		updateWinPercent(team);
		
		initDivision(team, team.divNum);

		li.push_back(team);
		inFile.getline(team.name, BUF, '\t');
	}
	isEmpty = false;		//list now has data in it
	standingsSort();		//sort the list
}

/*******************************************************************************************
*	Function Name:			deleteList
*	Purpose:				This function deletes every element in the list
*	Input Parameters:		none
*	Output Parameters:		none
*	Return value:			none
********************************************************************************************/
void Standings::deleteList()
{
	for (list<Team>::iterator it = li.begin(); it != li.end();)
	{
		li.erase(it++);
	}
}

/*******************************************************************************************
*	Function Name:			print
*	Purpose:				This function prints the list in order, as well as the division
*							and conference information for the Teams in the list
*	Input Parameters:		none
*	Output Parameters:		none
*	Return value:			none
********************************************************************************************/
void Standings::print()
{
	//if the list is empty, prompt user to add data to the list
	if (li.empty())
	{
		cout << "No standings exist." << endl;
		cout << "Enter a valid data file or add teams to create the standings." << endl;
		return;
	}

	int currentDiv = li.front().divNum;
	//int previousDiv = li.front().divNum;
	bool printedAFC = false;
	bool printedNFC = false;
	
	for (list<Team>::iterator it = li.begin(); it != li.end(); it++)
	{
		//prints the division each time the division changes
		if (currentDiv - (*it).divNum != 1 && currentDiv - (*it).divNum != 0)
			currentDiv = (*it).divNum;
		
		//prints the conference each time the conference changes
		if (currentDiv == (*it).divNum)
		{
			
			if (strcmp((*it).confName, "American Football Conference") == 0 && printedAFC == false)
			{
				cout << endl << (*it).confName << endl;
				printedAFC = true;
			}

			if (strcmp((*it).confName, "National Football Conference") == 0 && printedNFC == false)
			{
				cout << endl << (*it).confName << endl;
				printedNFC = true;
			}
			
			
			cout << endl << setw(30) << left << (*it).divName;
			cout << "W " << "L " << "T " << setw(10) << "  PCT " << setw(8) << "HOME " << setw(8) << "ROAD " << setw(8) << "DIV " << setw(8) << "CONF" << endl;
			currentDiv++;
			
		}
		
		//printing the Teams
		cout << fixed << setprecision(0);
		cout << setw(30) << (*it).name;
		cout << (*it).total.wins << " " << (*it).total.losses << " " << (*it).total.ties << setw(2) << " ";

		//print formatting
		if ((*it).winPercent == 1)
			cout << (*it).winPercent << setw(8) << ".000";
		else if ((*it).winPercent == 0)
			cout << setw(9) << ".000";
		else
			cout << "." << setw(8) << (*it).winPercent * 1000;

		cout << (*it).home.wins <<'-' << (*it).home.losses << '-' << (*it).home.ties << setw(3) << " ";
		cout << (*it).away.wins << '-' << (*it).away.losses << '-' << (*it).away.ties << setw(3) << " ";
		cout << (*it).division.wins << '-' << (*it).division.losses << '-' << (*it).division.ties << setw(3) << " ";
		cout << (*it).conference.wins << '-' << (*it).conference.losses << '-' << (*it).conference.ties;
		cout << endl;
		
	}
	cout << "\nGlossary" << endl;
	cout << "W: Wins" << endl;
	cout << "L: Losses" << endl;
	cout << "T: Ties" << endl;
	cout << "PCT: Win Percentage" << endl;
	cout << "\nHOME: home record" << endl;
	cout << "AWAY: away record" << endl;
	cout << "DIV: division record" << endl;
	cout << "HOME: home record" << endl;
}

/*******************************************************************************************
*	Function Name:			output
*	Purpose:				This function outputs the list in a tab seperated file which
*							is of a readable format by this program, so can be read back
*							into this program
*	Input Parameters:		string outFileName	-	the name of the output file to be written to
*	Output Parameters:		none
*	Return value:			none
********************************************************************************************/
void Standings::output(string outFileName)
{
	ofstream outFile;
	outFile.open(outFileName);
	
	for (list<Team>::iterator it = li.begin(); it != li.end(); it++)
	{
		outFile << (*it).name << '\t' << (*it).total.wins << '\t' << (*it).total.losses << '\t' << (*it).total.ties << '\t';
		outFile << (*it).home.wins << '-' << (*it).home.losses << '-' << (*it).home.ties << '\t';
		outFile << (*it).away.wins << '-' << (*it).away.losses << '-' << (*it).away.ties << '\t';
		outFile << (*it).division.wins << '-' << (*it).division.losses << '-' << (*it).division.ties << '\t';
		outFile << (*it).conference.wins << '-' << (*it).conference.losses << '-' << (*it).conference.ties << '\t';
		outFile << (*it).divNum << '\n';
	}
	outFile.close();
}

/*******************************************************************************************
*	Function Name:			standingsSort
*	Purpose:				This function uses the std::list sort function to sort the list
*							in decending order by division number, win percentage, and then 
*							team name as defined by the overloaded < operator in Team.h
*	Input Parameters:		none
*	Output Parameters:		none
*	Return value:			none
********************************************************************************************/
void Standings::standingsSort()
{

	//LAMBDA FUNCTION TO SORT ALSO WORKS
	/*li.sort([](const Team& first, const Team& sec) {
		return ((first.divNum) < (sec.divNum)) || ((first.divNum == sec.divNum) && (first.winPercent > sec.winPercent)) || ((first.divNum) == (sec.divNum) && (first.winPercent == sec.winPercent) && (strcmp(first.name, sec.name) < 0));
	});*/
	li.sort();
}

/*******************************************************************************************
*	Function Name:			addTeam
*	Purpose:				This function adds a Team to the bakc of the list, which is then
*							properly sorted
*	Input Parameters:		char [] teamName[]	-	the name of the team to add
*	Output Parameters:		none
*	Return value:			none
********************************************************************************************/
void Standings::addTeam(char teamName[])
{
	Team newTeam;
	bool noName = false;
	bool uniqueName = true;
	char recExists;
	
	//not a blank name
	if (strcmp(teamName, "") == 0)
	{
		noName = true;
	}
	else
		noName = false;

	//do not let the user input a name already on the list
	for (list<Team>::iterator it = li.begin(); it != li.end(); it++)
	{
		if (strcmp(teamName, (*it).name) == 0)
		{
			uniqueName = false;
		}
		
	}
	while (noName || !uniqueName)
	{
		if (noName)
			cout << "No team name entered.\nEnter the name of the team to add: ";
		else if (!uniqueName)
			cout << teamName << " already in the list. Enter a different team name: ";
		//cout << "Invalid team name, try again: ";
		cin.getline(teamName, BUF);

		if (strcmp(teamName, "") == 0)
		{
			noName = true;
		}
		else
			noName = false;

		for (list<Team>::iterator it = li.begin(); it != li.end(); it++)
		{
			if (strcmp(teamName, (*it).name) != 0)
			{
				uniqueName = true;
			}
			else
			{
				uniqueName = false;
				break;
			}
		}
	}
	
	if (strcmp(teamName, "-1") == 0)
	{
		cout << "Adding canceled." << endl;
		return;
	}
	
	
	//get the team's division from the user
	strcpy_s(newTeam.name, teamName);
	cout << "1. AFC East" << endl;
	cout << "2. AFC North" << endl;
	cout << "3. AFC South" << endl;
	cout << "4. AFC West" << endl;
	cout << "5. NFC East" << endl;
	cout << "6. NFC North" << endl;
	cout << "7. NFC South" << endl;
	cout << "8. NFC West" << endl;
	cout << "9. Cancel adding " << teamName << endl;

	validatedInput(newTeam.divNum, 1, 9, "the division the team is in: ");

	initDivision(newTeam, newTeam.divNum);
	if (newTeam.divNum == 9)		//cancel option
		return;

	cin.clear();
	cin.ignore(200, '\n');
	cout << "Does this team have en existing record you would like to enter? (y/n): ";
	cin >> recExists;
	
	while (cin.fail() || cin.peek() != '\n' && (recExists != 'n' || recExists != 'N' || recExists != 'y' || recExists != 'Y'))
	{
		cin.clear();
		cin.ignore(200, '\n');
		cout << "Enter y or n: ";
		cin >> recExists;
	}


	if (recExists == 'n' || recExists == 'N')
	{
		newTeam.total.wins = 0;
		newTeam.total.losses = 0;
		newTeam.total.ties = 0;

		newTeam.home.wins = 0;
		newTeam.home.losses = 0;
		newTeam.home.ties = 0;

		newTeam.away.wins = 0;
		newTeam.away.losses = 0;
		newTeam.away.ties = 0;

		newTeam.division.wins = 0;
		newTeam.division.losses = 0;
		newTeam.division.ties = 0;

		newTeam.conference.wins = 0;
		newTeam.conference.losses = 0;
		newTeam.conference.ties = 0;

		newTeam.winPercent = 0;
	}
	else if (recExists == 'y' || recExists == 'Y')
	{
		//adding data from the user to the team
		validatedInput(newTeam.total.wins, 0, "the total wins: ");
		validatedInput(newTeam.total.losses, 0, "the total losses: ");
		validatedInput(newTeam.total.ties, 0, "the total ties: ");

		validatedInput(newTeam.home.wins, 0, "the home wins: ");
		validatedInput(newTeam.home.losses, 0, "the home losses: ");
		validatedInput(newTeam.home.ties, 0, "the home ties: ");

		validatedInput(newTeam.away.wins, 0, "the away wins: ");
		validatedInput(newTeam.away.losses, 0, "the away losses: ");
		validatedInput(newTeam.away.ties, 0, "the away ties: ");

		validatedInput(newTeam.division.wins, 0, "the division wins: ");
		validatedInput(newTeam.division.losses, 0, "the division losses: ");
		validatedInput(newTeam.division.ties, 0, "the division ties: ");

		validatedInput(newTeam.conference.wins, 0, "the conference wins: ");
		validatedInput(newTeam.conference.losses, 0, "the conference losses: ");
		validatedInput(newTeam.conference.ties, 0, "the conference ties: ");

		updateWinPercent(newTeam);
	}
	li.push_back(newTeam);		//add team to the end of list
	
	standingsSort();			//sort the list

	cout << teamName << " added to the standings." << endl;
}

/*******************************************************************************************
*	Function Name:			initDivision
*	Purpose:				This function parses the division number of a team in order
*							to put the team in the correct division and conference
*	Input Parameters:		Team &t	-	the team to set the division and conference
*							int divNumber	-	the number of the division to set the team to
*	Output Parameters:		Team &t
*	Return value:			none
********************************************************************************************/
void Standings::initDivision(Team &t, int divNumber)
{
	switch(divNumber)
	{
	case 1:
		strcpy_s(t.confName, "American Football Conference");
		strcpy_s(t.divName, "AFC East");
		break;
	case 2:
		strcpy_s(t.confName, "American Football Conference");
		strcpy_s(t.divName, "AFC North");
		break;
	case 3:
		strcpy_s(t.confName, "American Football Conference");
		strcpy_s(t.divName, "AFC South");
		break;
	case 4:
		strcpy_s(t.confName, "American Football Conference");
		strcpy_s(t.divName, "AFC West");
		break;
	case 5:
		strcpy_s(t.confName, "National Football Conference");
		strcpy_s(t.divName, "NFC East");
		break;
	case 6:
		strcpy_s(t.confName, "National Football Conference");
		strcpy_s(t.divName, "NFC North");
		break;
	case 7:
		strcpy_s(t.confName, "National Football Conference");
		strcpy_s(t.divName, "NFC South");
		break;
	case 8:
		strcpy_s(t.confName, "National Football Conference");
		strcpy_s(t.divName, "NFC West");
		break;
	case 9:
		cout << "Adding canceled." << endl;
		break;
	default:
		strcpy_s(t.confName, "Invalid Conference");
		strcpy_s(t.divName, "Invalid Division");

	}
}

/*******************************************************************************************
*	Function Name:			deleteTeam
*	Purpose:				This function searches the list for a team and deletes it
*	Input Parameters:		char [] teamName	-	the name of the team to be deleted
*	Output Parameters:		none
*	Return value:			none
********************************************************************************************/
void Standings::deleteTeam(char teamName [])
{
	//not a blank name
	while (strcmp(teamName, "") == 0)
	{
		cout << "No team name entered.\nEnter the name of the team to delete: ";
		cin.getline(teamName, BUF);
	}

	//cancel
	if (strcmp(teamName, "-1") == 0)
	{
		cout << "Deleting cancelled." << endl;
		return;
	}
	bool found = false;
	for (list<Team>::iterator it = li.begin(); it != li.end(); it++)
	{
		if(strcmp((*it).name, teamName) == 0)
		{
			found = true;
			li.erase(it++);
		}
	}
	//if the team name is not found in the list
	if (!found)
		cout << teamName << " not found in the standings." << endl;
	else
		cout << teamName << " deleted from the standings." << endl;
}

/*******************************************************************************************
*	Function Name:			playGame
*	Purpose:				This function simulates a game between two teams according
*							to the users input and updates the list accordingly
*	Input Parameters:		char [] homeTeamName	-	the name of the home team
*							char [] awayTeamName	-	the name of the away team
*	Output Parameters:		none
*	Return value:			none
********************************************************************************************/
void Standings::playGame(char homeTeamName [], char awayTeamName [])
{
	Team homeTeam;
	Team awayTeam;
	bool homeInit = false;
	bool awayInit = false;
	int homeTeamScore, awayTeamScore;

	
	//copy the teams into local scope
	for (list<Team>::iterator it = li.begin(); it != li.end(); it++)
	{
		if (strcmp((*it).name, homeTeamName) == 0)
		{
			homeTeam = (*it);
			homeInit = true;
		}
		if (strcmp((*it).name, awayTeamName) == 0)
		{
			awayTeam = (*it);
			awayInit = true;
		}
	}

	//if either team name is not found in the list, return to the menu
	if (!homeInit)
	{
		cout << homeTeamName << " not found in the list." << endl;
		return;
	}

	if (!awayInit)
	{
		cout << awayTeamName << " not found in the list." << endl;
		return;
	}
	
	//get the scores from the user
	validatedInput(homeTeamScore, 0, "the home team score: ");
	if (homeTeamScore < 0)
	{
		cout << "Invalid score. Please enter the score as a positive integer: ";
		validatedInput(homeTeamScore, 0, "the home team score: ");
	}

	validatedInput(awayTeamScore, 0, "the away team score: ");
	if (awayTeamScore < 0)
	{
		cout << "Invalid score. Please enter the score as a positive integer: ";
		validatedInput(awayTeamScore, 0, "the away team score: ");
	}

	//home team wins
	if (homeTeamScore > awayTeamScore)
	{
		if (isConfGame(homeTeam, awayTeam))
		{
			homeTeam.conference.wins++;
			awayTeam.conference.losses++;
		}

		if (isDivGame(homeTeam, awayTeam))
		{
			homeTeam.division.wins++;
			awayTeam.division.losses++;
		}
		homeTeam.total.wins++;
		homeTeam.home.wins++;
		awayTeam.total.losses++;
		awayTeam.away.losses++;
		cout << homeTeam.name << " wins." << endl;
	}

	//away team wins
	else if (homeTeamScore < awayTeamScore)
	{
		if (isConfGame(homeTeam, awayTeam))
		{
			homeTeam.conference.losses++;
			awayTeam.conference.wins++;
		}
		if (isDivGame(homeTeam, awayTeam))
		{
			homeTeam.division.losses++;
			awayTeam.division.wins++;
		}
		homeTeam.total.losses++;
		homeTeam.home.losses++;

		awayTeam.total.wins++;
		awayTeam.away.wins++;
		cout << awayTeam.name << " wins." << endl;
	}

	//tie
	else
	{
		if (isConfGame(homeTeam, awayTeam))
		{
			homeTeam.conference.ties++;
			awayTeam.conference.ties++;
		}
		if (isDivGame(homeTeam, awayTeam))
		{
			homeTeam.division.ties++;
			awayTeam.division.ties++;
		}
		homeTeam.home.ties++;
		homeTeam.total.ties++;
		awayTeam.away.ties++;

		awayTeam.total.ties++;

		cout << homeTeam.name << " and " << awayTeam.name << " tied." << endl;

	}
	updateWinPercent(homeTeam);
	updateWinPercent(awayTeam);
	
	//copy the updated teams into the list
	for (list<Team>::iterator it = li.begin(); it != li.end(); it++)
	{
		if (strcmp((*it).name, homeTeamName) == 0)
			(*it) = homeTeam;
		if (strcmp((*it).name, awayTeamName) == 0)
			(*it) = awayTeam;
	}
	
	standingsSort();

}

/*******************************************************************************************
*	Function Name:			editTeam
*	Purpose:				This function allows the user to edit a team
*	Input Parameters:		char[] teamName	-	the name of the team to be editted
*	Output Parameters:		none
*	Return value:			none
********************************************************************************************/
void Standings::editTeam(char teamName [])
{
	//not a blank name
	while (strcmp(teamName, "") == 0)
	{
		cout << "No team name entered.\nEnter the name of the team to delete: ";
		cin.getline(teamName, BUF);
	}

	//cancel
	if (strcmp(teamName, "-1") == 0)
	{
		cout << "Editing cancelled." << endl;
		return;
	}
	bool found = false;
	for (list<Team>::iterator it = li.begin(); it != li.end(); it++)
	{
		if (strcmp((*it).name, teamName) == 0)
		{
			found = true;
			
			validatedInput((*it).total.wins, 0, "the total wins: ");
			validatedInput((*it).total.losses, 0, "the total losses: ");
			validatedInput((*it).total.ties, 0, "the total ties: ");

			validatedInput((*it).home.wins, 0, "the home wins: ");
			validatedInput((*it).home.losses, 0, "the home losses: ");
			validatedInput((*it).home.ties, 0, "the home ties: ");

			validatedInput((*it).away.wins, 0, "the away wins: ");
			validatedInput((*it).away.losses, 0, "the away losses: ");
			validatedInput((*it).away.ties, 0, "the away ties: ");

			validatedInput((*it).division.wins, 0, "the division wins: ");
			validatedInput((*it).division.losses, 0, "the division losses: ");
			validatedInput((*it).division.ties, 0, "the division ties: ");

			validatedInput((*it).conference.wins, 0, "the conference wins: ");
			validatedInput((*it).conference.losses, 0, "the conference losses: ");
			validatedInput((*it).conference.ties, 0, "the conference ties: ");

			updateWinPercent((*it));
			break;
		}
	}
	standingsSort();
	//if the team name is not in the list
	if (!found)
		cout << teamName << " not found in the standings." << endl;
	
}

/*******************************************************************************************
*	Function Name:			isConfGame
*	Purpose:				This function determines if a game played between two teams
*							is a conference game according to the division number of the
*							teams
*	Input Parameters:		Team first	-	first team to check
*							Team second	-	second team to check
*	Output Parameters:		none
*	Return value:			bool	-	true if the game is a conference game
*										false if the game is not a conference game
********************************************************************************************/
bool Standings::isConfGame(Team first, Team second)
{
	//if the difference in the division number is less than 4, the game is a conference game
	if (abs(first.divNum - second.divNum) < 4)
		return true;
	else
		return false;
}

/*******************************************************************************************
*	Function Name:			isDivGame
*	Purpose:				This function determines if a game played between two teams
*							is a division game according to the division number of the
*							teams
*	Input Parameters:		Team first	-	first team to check
*							Team second	-	second team to check
*	Output Parameters:		none
*	Return value:			bool	-	true if the game is a division game
*										false if the game is not a division game
********************************************************************************************/
bool Standings::isDivGame(Team first, Team second)
{
	//if the two division numbers are the same, the game is a division game
	if (first.divNum == second.divNum)
		return true;
	else
		return false;
}

/*******************************************************************************************
*	Function Name:			updateWinPercent
*	Purpose:				This function updates the win percentage of a team
*	Input Parameters:		Team &t	-	the team to update the win percentage of
*	Output Parameters:		Team &t
*	Return value:			none
********************************************************************************************/
void Standings::updateWinPercent(Team& t)
{
	t.winPercent = (double)t.total.wins / (t.total.wins + t.total.ties + t.total.losses);
	if ((t.total.wins + t.total.ties + t.total.losses) == 0)
		t.winPercent = 0;
}

/*******************************************************************************************
*	Function Name:			validatedInput
*	Purpose:				This function validates an integer input from the user by 
*							making sure it is an integer and is between a lower bound
*							and an upper bound
*	Input Parameters:		int &input	-	the integer to be validated
*							int lowerBound	-	the lower bound for valid input
*							int upperBound	-	the upper bound for valid input
*							string str	-	the prompt to the user
*	Output Parameters:		int& input
*	Return value:			none
********************************************************************************************/
void Standings::validatedInput(int& input, int lowerBound, int upperBound, string str)
{
	cout << "Please enter " << str;
	cin >> input;

	//prompt the user while the input is not an integer or is not in between the lower and upper bounds
	while (cin.fail() || cin.peek() != '\n' || input < lowerBound || input > upperBound)
	{
		cin.clear();
		cin.ignore(200, '\n');
		cout << "Incorrect input.\nPlease enter a valid integer " << lowerBound << " to " << upperBound << endl;

		cin >> input;
	}
}

/*******************************************************************************************
*	Function Name:			validatedInput
*	Purpose:				This function validates an integer input from the user by
*							making sure it is an integer and is above a lower bound
*	Input Parameters:		int &input	-	the integer to be validated
*							int lowerBound	-	the lower bound for valid input
*							string str	-	the prompt to the user
*	Output Parameters:		int& input
*	Return value:			none
********************************************************************************************/
void Standings::validatedInput(int& input, int lowerBound, string str)
{
	cout << "Please enter " << str;
	cin >> input;

	//prompt the user while the input is not an integer or is below the lower bound
	while (cin.fail() || cin.peek() != '\n' || input < lowerBound)
	{
		cin.clear();
		cin.ignore(200, '\n');
		cout << "Incorrect input.\nPlease enter a valid integer greater than or equal to " << lowerBound << endl;

		cin >> input;
	}
}