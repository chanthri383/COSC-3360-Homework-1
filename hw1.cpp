#include <iostream>
#include <string>
#include <queue>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;

char clockwiseDirection(char &currentDirection)
{
	if (currentDirection == 'N')
		return 'E';
	else if (currentDirection == 'E')
		return 'S';
	else if (currentDirection == 'S')
		return 'W';
	else if (currentDirection == 'W')
		return 'N';
}
void childDisplay(char curr, string license, int sleep)
{
	switch (curr)
	{
	case 'N':
	//	cout << "Current Direction: Northbound" << endl;
		cout << "Car " << license << " is using the intersection for " << sleep << " sec(s)" << endl;
		break;

	case 'E':
	//	cout << "Current Direction: Eastbound\n";
		cout << "Car " << license << " is using the intersection for " << sleep << " sec(s)\n";
		break;

	case 'S':
	//	cout << "Current Direction: Southbound\n";
		cout << "Car " << license << " is using the intersection for " << sleep << " sec(s)\n";
		break;

	case 'W':
	//	cout << "Current Direction: Westbound\n";
		cout << "Car " << license << " is using the intersection for " << sleep << " sec(s)\n";
		break;
	}
}
int main()
{
	int maxCars = 0;
	string wholeString = "";
	string license = "";
	char startingDirection;
	char currentDirection;
	int sleepTimer = 0;
	char c;
	int status;
	int childProcesses = 0;
	int carsSoFar = 0;
	bool carFound = false;
	queue<int> sleepTimeNorth;
	queue<int> sleepTimeEast;
	queue<int> sleepTimeSouth;
	queue<int> sleepTimeWest;
	queue<string> licensePlateNorth;
	queue<string> licensePlateEast;
	queue<string> licensePlateSouth;
	queue<string> licensePlateWest;
	cin >> startingDirection;
	cin >> maxCars;
	getline(cin, wholeString);
	while (getline(cin, wholeString))
	{

		if (wholeString[4] == 'N')
		{
			c = wholeString[6];
			sleepTimer = c - 48;
			sleepTimeNorth.push(sleepTimer);
			for (int i = 0; i <= wholeString.size() - 5; i++)
			{
				license += wholeString[i];
			}
			licensePlateNorth.push(license);
			license = "";
		}
		else if (wholeString[4] == 'E')
		{
			c = wholeString[6];
			sleepTimer = c - 48;
			sleepTimeEast.push(sleepTimer);
			for (int i = 0; i <= wholeString.size() - 5; i++)
			{
				license += wholeString[i];
			}
			licensePlateEast.push(license);
			license = "";
		}
		else if (wholeString[4] == 'S')
		{
			c = wholeString[6];
			sleepTimer = c - 48;
			sleepTimeSouth.push(sleepTimer);
			for (int i = 0; i <= wholeString.size() - 5; i++)
			{
				license += wholeString[i];
			}
			licensePlateSouth.push(license);
			license = "";
		}
		else if (wholeString[4] == 'W')
		{
			c = wholeString[6];
			sleepTimer = c - 48;
			sleepTimeWest.push(sleepTimer);
			for (int i = 0; i <= wholeString.size() - 5; i++)
			{
				license += wholeString[i];
			}
			licensePlateWest.push(license);
			license = "";
		}
		childProcesses++;
	}
	currentDirection = startingDirection;
	string currentWholeString = "";
	string licensePl = "";
	int sleeping;
	int i = 0;
	while (i < childProcesses)
	{
		if (currentDirection == 'N' && !licensePlateNorth.empty())
		{
			if (carsSoFar == 0)
				cout << "Current Direction: Northbound" << endl;
			licensePl = licensePlateNorth.front();
			sleeping = sleepTimeNorth.front();
			licensePlateNorth.pop();
			sleepTimeNorth.pop();
			i++;
		}
		else if (currentDirection == 'E' && !licensePlateEast.empty())
		{
			if (carsSoFar == 0)
				cout << "Current Direction: Eastbound\n";
			licensePl = licensePlateEast.front();
			sleeping = sleepTimeEast.front();
			licensePlateEast.pop();
			sleepTimeEast.pop();
			i++;
		}
		else if (currentDirection == 'S' && !licensePlateSouth.empty())
		{
			if (carsSoFar == 0)
				cout << "Current Direction: Southbound\n";
			licensePl = licensePlateSouth.front();
			sleeping = sleepTimeSouth.front();
			licensePlateSouth.pop();
			sleepTimeSouth.pop();
			i++;
		}
		else if (currentDirection == 'W' && !licensePlateWest.empty())
		{
			if (carsSoFar == 0)
				cout << "Current Direction: Westbound\n";
			licensePl = licensePlateWest.front();
			sleeping = sleepTimeWest.front();
			licensePlateWest.pop();
			sleepTimeWest.pop();
			i++;
		}
		else
		{
			carsSoFar = 0;
			currentDirection = clockwiseDirection(currentDirection);
			continue;
		}
		

		pid_t pid = fork();
		if (pid == 0)
		{
			childDisplay(currentDirection, licensePl, sleeping);
			sleep(sleeping);
			return 0;
		}
		wait(&status);

		carsSoFar++;
		if (carsSoFar == maxCars)
		{
			carsSoFar = 0;
			currentDirection = clockwiseDirection(currentDirection);
		}
	}
	return 0;
}
