// Project 1 For CS454
// Created By: Nick Flouty & Joey Robinson
#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>
#include "BigIntegerLibrary.hh"

using namespace std;



// Part 1 Functions:
void copyMatrix(BigInteger a[38][38], BigInteger b[38][38], int order)
{
	for (int i = 0; i< order; i++)
		for (int j = 0; j < order; j++)
			b[i][j] = a[i][j];
}

void multMatrix(BigInteger a[38][38], BigInteger b[38][38], BigInteger c[38][38], int order)
{
	BigInteger sum = 0;
	for (int i = 0; i < order; ++i)
	{
		for (int j = 0; j < order; ++j)
		{
			for (int k = 0; k < order; ++k)
			{
				sum += a[i][k] * b[k][j];

			}
			c[i][j] = sum;
			sum = 0;
		}
	}
}

void problem1(int n)
{
	int A[38][3] =
	{
		{ 1,2,3 },
	{ 4,5,6 },
	{ 7,8,9 },
	{ 10,11,12 },
	{ 37,13,14 },
	{ 15,16,17 },
	{ 18,19,20 },
	{ 21,22,23 },
	{ 24,37,25 },
	{ 26,27,28 },
	{ 29,30,31 },
	{ 32,33,34 },
	{ 35,36,37 },
	{ 37,37,17 },
	{ 37,19,37 },
	{ 37,37,23 },
	{ 37,37,25 },
	{ 26,27,28 },
	{ 37,30,37 },
	{ 32,33,34 },
	{ 37,36,37 },
	{ 37,37,14 },
	{ 37,37,17 },
	{ 18,19,20 },
	{ 37,37,23 },
	{ 26,37,37 },
	{ 29,30,31 },
	{ 32,37,37 },
	{ 35,37,37 },
	{ 37,13,37 },
	{ 15,16,17 },
	{ 37,19,37 },
	{ 21,22,23 },
	{ 24,37,37 },
	{ 26,37,37 },
	{ 37,30,37 },
	{ 32,37,37 },
	{ 37,37,37 }
	};


	BigInteger M[38][38];

	for (int i = 0; i <= 37; i++)
	{
		for (int j = 0; j <= 37; j++)
		{
			M[i][j] = 0;
		}

	}

	for (int j = 0; j <= 37; j++)
	{
		for (int k = 0; k <= 2; k++)
		{
			M[j][A[j][k]]++;
		}
	}



	BigInteger result[38][38];
	BigInteger result2[38][38];


	for (int i = 0; i <= 37; i++)
	{
		for (int j = 0; j <= 37; j++)
		{
			result[i][j] = 0;
		}

	}
	for (int i = 0; i <= 37; i++)
	{
		for (int j = 0; j <= 37; j++)
		{
			result2[i][j] = 0;
		}

	}


	copyMatrix(M, result, 38);
	for (int i = 0; i < n - 1; i++)
	{
		multMatrix(M, result, result2, 38);
		copyMatrix(result2, result, 38);
	}



	BigInteger sum = 0;
	for (int j = 0; j < 37; j++)
	{
		sum += result2[0][j];
	}
	cout << sum;

}

// Part 2 Functions: 
int remove(queue<int> &Q)
{
	int temp;
	temp = Q.front();
	Q.pop();
	return temp;
}

int delta(int current, int next, int n)
{
	if (n == 0)
		return 0;
	return((current * 10 + next) % n);
}

string MinString(int n, string input)
{
	queue<int> Q;					//Step 1. Initialize a queue Q to empty queue.

	vector<int> VISITED;
	for (int i = 0; i < n; i++)		//Step 2. initialize VISITED, a Boolean array of length n to false.
		VISITED.push_back(0);

	Q.push(0);						//Step 3: insert start state into Q.

	bool found = false;
	vector<int> PARENT;
	for (int i = 0; i < n; i++)
		PARENT.push_back(0);

	vector<int> LABEL;
	for (int i = 0; i < n; i++)
		LABEL.push_back(0);

	vector<int>FINAL;
	for (int i = 0; i < n; i++)
		FINAL.push_back(0);
	FINAL[0] = 1;

	int size = (input.length() / 2) + 1;				//number of integers in input without connting commas.

	vector<int> Dpermitted;
	for (int i = 0; i < input.length(); i++)			//puts digits permiited input into a vector int without the commas.
		if (isdigit(input[i]))
			Dpermitted.push_back(input[i] - '0');

	vector<vector<int>> Delta;
	Delta.resize(n);									//DFA Delta[n][size]

	for (int i = 0; i < n; i++)
	{
		Delta[i].resize(size);
		for (int j = 0; j < size; j++)
		{
			Delta[i][j] = (delta(i, Dpermitted[j], n));	//Filling Delta Transition Matri
		}
	}

	while (!Q.empty())
	{
		int current = remove(Q);
		for (int k = 0; k < size; k++)
		{
			int next = Delta[current][k];

			if (FINAL[next] == 1)
			{
				LABEL[next] = Dpermitted[k];
				PARENT[next] = current;
				found = true;
				break;
			}
			else
			{
				if (VISITED[next] == 0)
				{
					PARENT[next] = current;
					VISITED[next] = 1;
					LABEL[next] = Dpermitted[k];
					Q.push(next);
				}
			}
		}
		if (found)
			break;
	}

	if (!found)
		return "No Solution.";
	else								//use PARENT pointers and LABL to find the shortest string accepted
	{
		string out;
		int i = 0;
		if (PARENT[i] == 0)
			return (to_string(n));
		while (PARENT[i] != 0)
		{
			out += to_string(LABEL[PARENT[i]]);
			i = PARENT[i];
		}
		reverse(out.begin(), out.end());
		out += to_string(LABEL[PARENT[i]]);
		return out;
	}
}

string smallestMultiple(int k, string input)
{
	int size = (input.length() / 2) + 1; //number of integers in input without connting commas.

	vector<int> Dpermitted;
	Dpermitted.resize(size);
	int j = 0;
	for (int i = 0; i < size; i++) //puts digits permiited input into a vector int without the commas.
	{
		if (isdigit(input[i]))
		{
			Dpermitted[j] = input[i];
			j++;
		}
	}

	string str = MinString(k, input);
	return(str);
}

// Main:
int main()
{
	int user;
	cout << "Which problem do you want to solve?" << endl
		<< "1: Problem 1" << endl
		<< "2: Problem 2" << endl
		<< "3: Quit" << endl << ">>";
	cin >> user;

	while (user != 3 && user == 1 || user == 2)
	{
		if (user == 1)
		{
			int n;
			cout << "Input n = ";
			cin >> n;
			problem1(n);
		}
		else if (user == 2)
		{
			int n;
			cout << "Enter the number n = ";
			cin >> n;
			string input;
			cout << "Enter the Digits Permitted (seperated by a comma, no space. ex. 1,2,3): ";
			cin >> input;

			cout << "The smallest multiple is: " << smallestMultiple(n, input) << endl << endl;

		}
		cout << endl;
		cout << "Which problem do you want to solve?" << endl
			<< "1: Problem 1" << endl
			<< "2: Problem 2" << endl
			<< "3: Quit" << endl << ">>";
		cin >> user;
		cout << endl;
	}


	return 0;
}
