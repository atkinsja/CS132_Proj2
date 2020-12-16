/**************************************************************************************************
*
*   File name :			team.h
*
*	Programmer:  		Jeremy Atkins
*
*   Team struct which holds all of the information for each team
*
*   Date Written:		in the past
*
*   Date Last Revised:	11/08/2018
****************************************************************************************************/
#ifndef TEAM_H_
#define TEAM_H_
#define BUF 30			//maximum size of each team name
#include <string>
//record struct holding wins, losses, and ties
struct Record
{
	int wins;
	int losses;
	int ties;
};
struct Team
{
	char name[BUF];		//team name
	Record total;		//record of total wins, losses, and ties
	Record home;		//record of home wins, losses, and ties
	Record away;		//record of away wins, losses, and ties
	Record division;	//record of division wins, losses, and ties
	Record conference;	//record of conference wins, losses, and ties
	int divNum;			//division number
	double winPercent;	//win percentage
	char confName[BUF];	//name of the conference the team is in
	char divName[BUF];	//name of the division the team is in

	//overloaded < operator used in to sort each time by division number, win percentage, and then team name
	bool operator < (const Team& t) const
	{
		return ((divNum) < (t.divNum)) || 
			((divNum == t.divNum) && (winPercent > t.winPercent)) || 
			((divNum) == (t.divNum) && (winPercent == t.winPercent) && (strcmp(name, t.name) < 0));
		
	}
};
#endif // !TEAM_H_
