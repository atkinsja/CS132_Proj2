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
	void standingSort();
	void init(string);
	void addTeam();
	void deleteTeam(char[]);
private:
	Team team;
	list<Team> li;
	void initDivision(Team &, int);
	int numTeams;
};
#endif // !STANDINGS_H_
