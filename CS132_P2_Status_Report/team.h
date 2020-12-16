#ifndef TEAM_H_
#define TEAM_H_
#define BUF 30
#include <string>
struct Record
{
	int wins;
	int losses;
	int ties;
	
};
struct Team
{
	char name[BUF];
	int wins;
	int losses;
	int ties;
	int league;
	double winPercent;
	Record home;
	Record away;
	Record division;
	Record conference;
	int divNum;
	char confName[BUF];
	char divName[BUF];
};
#endif // !TEAM_H_
