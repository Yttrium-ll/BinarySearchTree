// bst.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "binaryTree.h"

int main()
{
	cout << "hi" << endl;
	binaryTree<int, char> yggdrassil;
	int tmp;
	char ch;
	string input;
	for (int i = 0; i<5; ++i)
	{
		tmp = random_char();
		yggdrassil.add_bts(tmp, char(tmp));
	}
	yggdrassil.print();
	do {
		cout << "& ";
		cin >> input;
		if (input == "add")
		{
			cin >> tmp >> ch;
			yggdrassil.add_bts(tmp, ch);
			cout << "----- tree after changing -----\n";
			yggdrassil.print();
		}
		else if (input == "search")
		{
			cin >> tmp;
			ch = yggdrassil.search_bts(tmp);
			if (ch) cout << "res: " << ch << endl;
			else cout << "no such elem\n";
		}
		else if (input == "print")
			yggdrassil.print(true);
		else if (input == "exit") break;
		else cout << "no such command\n";
		cout << endl;
	} while (input != "exit");
	cout << "end\n";
    return 0;
}

