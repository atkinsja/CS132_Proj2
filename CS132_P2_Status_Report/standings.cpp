#include "standings.h"
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

Standings::Standings()
{
	numTeams = 0;
}


void Standings::init(string inFileName)
{
	
	ifstream inFile;
	inFile.open(inFileName);
	cout << "opened " << inFileName << endl;
	if (!inFile)
	{
		cout << "Error opening " << inFileName << endl;
	}
	inFile.getline(team.name, 30, '\t');
	while (inFile)
	{
		inFile >> team.wins;
		inFile >> team.losses;
		inFile >> team.ties;

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
		inFile.ignore();
		team.winPercent = (double)team.wins / (team.wins + team.losses + team.ties);
		numTeams++;
		
		
		initDivision(team, team.divNum);

		li.push_back(team);
		inFile.getline(team.name, 30, '\t');
	}
	inFile.close();
}

void Standings::print()
{
	cout << "print called " << endl;
	int currentDiv = 1;
	int numPrinted = 0;
	for each (Team t in li)
	{
		
		if (currentDiv == t.divNum)
		{
			if(currentDiv == 1 || currentDiv == 5)
				cout << endl << t.confName << endl;

			cout << endl << setw(25) << left << t.divName;
			cout << "W " << "L " << "T " << setw(6) << "PCT " << setw(6) << "HOME " << setw(6) << "ROAD " << setw(6) << "DIV " << setw(6) << "CONF" << endl;
			currentDiv++;
		}
		

		cout << fixed << setprecision(3);

		cout << setw(25) << t.name;
		cout << t.wins << " " << t.losses << " " << t.ties << " " << t.winPercent << " ";
		cout << t.home.wins << '-' << t.home.losses << '-' << t.home.ties << " ";
		cout << t.away.wins << '-' << t.away.losses << '-' << t.away.ties << " ";
		cout << t.division.wins << '-' << t.division.losses << '-' << t.division.ties << " ";
		cout << t.conference.wins << '-' << t.conference.losses << '-' << t.conference.ties;
		//cout << " DivNum: " << t.divNum;
		cout << endl;
		numPrinted++;
	}
}

void Standings::standingSort()
{
	//TO DO
	//CHANGE BEFORE TURN IN
	li.sort([](const Team& first, const Team& sec) {
		return ((first.divNum) < (sec.divNum))||((first.divNum == sec.divNum) && (first.winPercent > sec.winPercent)); 
	});
}

void Standings::addTeam()
{
	Team newTeam;
	
	
	cout << "Enter the team name:";
	cin.ignore();
	cin.getline(newTeam.name, 30, '\n');
	cout << "1. AFC East" << endl;
	cout << "2. AFC North" << endl;
	cout << "3. AFC South" << endl;
	cout << "4. AFC West" << endl;
	cout << "5. NFC East" << endl;
	cout << "6. NFC North" << endl;
	cout << "7. NFC South" << endl;
	cout << "8. NFC West" << endl;
	cout << "Enter the number of the division the team is in: ";
	cin >> newTeam.divNum;
	initDivision(newTeam, newTeam.divNum);

	cout << "Enter their overall record in the order wins, losses, then ties: ";
	cin >> newTeam.wins;
	cin >> newTeam.losses;
	cin >> newTeam.ties;

	cout << "Enter their home record: ";
	cin >> newTeam.home.wins;
	cin >> newTeam.home.losses;
	cin >> newTeam.home.ties;

	cout << "Enter their away record: ";
	cin >> newTeam.away.wins;
	cin >> newTeam.away.losses;
	cin >> newTeam.away.ties;

	
	cout << "Enter their division record in the order wins, losses, then ties: ";
	cin >> newTeam.division.wins;
	cin >> newTeam.division.losses;
	cin >> newTeam.division.ties;

	cout << "Enter their conference record in the order wins, losses, then ties: ";
	cin >> newTeam.conference.wins;
	cin >> newTeam.conference.losses;
	cin >> newTeam.conference.ties;

	newTeam.winPercent = (double)newTeam.wins / (newTeam.wins + newTeam.losses + newTeam.ties);
	numTeams++;
	li.push_back(newTeam);
	
	standingSort();

}


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
		strcpy_s(t.confName, "American Football Conference");
		strcpy_s(t.divName, "NFC North");
		break;
	case 7:
		strcpy_s(t.confName, "American Football Conference");
		strcpy_s(t.divName, "NFC South");
		break;
	case 8:
		strcpy_s(t.confName, "American Football Conference");
		strcpy_s(t.divName, "NFC West");
		break;
	default:
		strcpy_s(t.confName, "Invalid Conference");
		strcpy_s(t.divName, "Invalid Division");

	}
}



void Standings::deleteTeam(char teamName [])
{

	for (list<Team>::iterator it = li.begin(); it != li.end(); it++)
	{
		if(strcmp((*it).name, teamName) == 0)
		{
			cout << "Equal: " << (*it).name << endl;
			li.erase(it++);
		}
	}

}