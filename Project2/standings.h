/**************************************************************************************************
*
*   File name :			standings.h
*
*	Programmer:  		Jeremy Atkins
*
*   Header file for the Standings class, implemented in Standings.cpp
*
*   Date Written:		in the past
*
*   Date Last Revised:	11/8/2018
*
*	Class Name:		Standings
*
*	Private data members:
*		list<Team> li	-	the doubly linked stl::list holding the teams
*		bool isEmpty	-	determines if the Standings object is empty
*
*	Private member function:
*		initDivision	-	parses the division number of a team in order to put the team 
*							in the correct division and conference
*		isConfGame		-	determines if a game played between two teams is a conference game 
*							according to the division number of the teams
*		isDivGame		-	determines if a game played between two teams is a division game 
*							according to the division number of the teams
*		updateWinPercent	-	updates the win percentage of a team
*		standingsSort	-	uses the std::list sort function to sort the list in decending 
*							order by division number, win percentage, and then 
*							team name as defined by the overloaded < operator in Team.h
*		deleteList		-	deletes every element in the list
*		validatedInput	-	validates an integer input from the user by making 
*							sure it is an integer and is between a lower bound and an upper bound
*		validatedInput	-	validates an integer input from the user by making 
*							sure it is an integer and is above a lower bound
*
*	Public member functions:
*		Standings		-	constructor for a Standings object
*		print			-	prints the list in order, as well as the division
*							and conference information for the Teams in the list
*		init			-	initializes a Standings object by reading input
*							from a file, parsing the data, and creating a doubly linked list 
*							containing the information as Team structs as defined in Team.h
*							and sorting the Teams using the standingsSort function
*		addTeam			-	adds a Team to the bakc of the list, which is then
*							properly sorted
*		deleteTeam		-	searches the list for a team and deletes it
*		playGame		-	simulates a game between two teams according
*							to the users input and updates the list accordingly
*		output			-	outputs the list in a tab seperated file which
*							is of a readable format by this program, so can be read back
*							into this program
*		editTeam		-	allows the user to edit a team
****************************************************************************************************/
#ifndef STANDINGS_H_
#define STANDINGS_H_
#include "team.h"
#include <list>
using namespace std;
class Standings
{
public:
	Standings();
	void print();
	void init(ifstream&);
	void addTeam(char[]);
	void deleteTeam(char[]);
	void playGame(char[], char[]);
	void output(string);
	void editTeam(char[]);
private:
	//Team team;
	list<Team> li;
	bool isEmpty;
	void initDivision(Team&, int);
	bool isConfGame(Team, Team);
	bool isDivGame(Team, Team);
	void updateWinPercent(Team&);
	void standingsSort();
	void deleteList();
	void validatedInput(int&, int, int, string);
	void validatedInput(int&, int, string);

};
#endif // !STANDINGS_H_
