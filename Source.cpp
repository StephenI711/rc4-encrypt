#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;
void flip(int&, int&);
int main()
{
	
	//vector<int> encryption;

	ifstream in;
	in.open("ciphertxt.txt");
	string plaintext;
	getline(in, plaintext); // get text
	in.close();
	//cout << plaintext;
	string key;
	cout << "Enter a key in range 5 - 32 bytes:" << endl;
	getline(cin, key);

	int keySize = key.size();
	//input validate
	while (keySize < 5 || keySize > 32)
	{
		if (keySize < 5)
		{
			cout << "Too short. Try again: " << endl;
		}
		else
		{
			cout << "Too long. Try again: " << endl;
		}
		getline(cin, key);
		keySize = key.size();
	}
	vector<int> S(256);
	vector<int> T(256);
	//key scheduling algorithm
	for (int l = 0; l < 256; l++)
	{
		S[l] = l;
		T[l] = key[(l % (sizeof(key) / sizeof(key)))];
	}


	//permutation algorithm
	int k = 0;
	for (int i = 0; i < 256; i++)
	{
		k = (k + S[i] + T[i]) % 256;
		flip(S[i], S[k]);
	}
	
	int x = 0, y = 0, z = 0, q, d, temp;

	string tempstr;
	string ciphertxt;
	cout << "Decryption: " << endl;
	for (int r = 0; r < plaintext.size(); r++)
	{
		x = (x + 1) % 256;
		y = (y + S[x]) % 256;
		flip(S[x], S[y]);
		temp = (S[x] + S[y]) % 256;
		z = S[temp];
		d = ((int)plaintext[r] ^ z);
	
		ciphertxt += char(d);

	}

	cout << ciphertxt;


	return 0;
}

void flip(int& p, int& q)
{
	int temp = p;
	p = q;
	q = temp;
}