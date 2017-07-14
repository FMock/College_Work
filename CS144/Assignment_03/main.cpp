#include<iostream>
#include<vector>

using namespace std;
/*
	Frank Mock CS144
	Assignment 3

	This program will print out the permutations of any number n. I used the
	Exercise P6.11 instructions as a guide.
*/


/**
   Removes an element from an ordered vector.
   @param values a vector
   @param pos the position of the element to erase
*/
void erase(vector<int>& values, int pos)
{ 
   for (unsigned int i = pos; i < values.size() - 1; i++)
      values[i] = values[i + 1];
   values.pop_back();
}

/*
	Prints the permutations of the sequence of integers in an
	array.
	@param to_permute the array which holds the integers to permute
	@param prefix array that holds the permutations
*/

void permutation_helper(vector<int>& to_permute, vector<int>& prefix)
{
	//if to_permute has no elements, print elements in prefix
	if(to_permute.empty())
	{
		for(unsigned i = 0; i < prefix.size(); i++)
		{
			if(prefix[i] != 0)
				cout << prefix[i] << " ";
		}
		cout << endl;

		return;
	}

	for(unsigned int j = 0; j < to_permute.size(); j++)
	{
		/*
		  foreach element j in to_permute, make an array
		  to_permute2 that is equal to permute except for
		  the value at position j.
		*/
		vector<int> to_permute2 = to_permute;
		erase(to_permute2, j);
		/*
		  make an array prefix2 consisting of prefix and
		  the value at position j.
		*/
		vector<int> prefix2 = prefix;
		prefix2.push_back(to_permute[j]);

		//recursively call permutaion_helper
		permutation_helper(to_permute2, prefix2);
	}

}



int main()
{
	cout << "Enter a  number n and I will print all permutations" << endl;
	cout << "of the squence of numbers 1,2,3,...n. For example if" << endl;
	cout << "n is 3, the program will print:" << endl;
	cout << endl;
	cout << "1 2 3" << endl;
	cout << "1 3 2" << endl;
	cout << "2 1 3" << endl;
	cout << "2 3 1" << endl;
	cout << "3 1 2" << endl;
	cout << "3 2 1" << endl;
	cout << endl;
	cout << "Keep in mind that the number of permutations of any" << endl;
	cout << "number n is n factorial. So make your choice of n" << endl;
	cout << "reasonable." << endl;
	cout << "Enter a number: ";
	int n;
	cin >> n;
	vector<int> prefix(n);
	vector<int> to_permute;
	for(int i = 1; i <= n; i++)
		to_permute.push_back(i);

	permutation_helper(to_permute, prefix);

	//Keep command window open
	cout << "Press any key and then enter to end" << endl;
	int end;
	cin >> end;
	return 0;
}