#pragma once

#include <vector>
#include <string>
#include <iostream>
using namespace std;

#define STOPITER 1
#define OK 0
#define NOTFOUND 404

int random_char()
{
	return random() % 200;
}

template <class tpk1, class tpd1>
class binaryTree;

template <class tpk2, class tpd2>
class btIterator;

//BRANCH CLASS
template <class tpk, class tpd>
class branch
{
	friend class binaryTree<tpk, tpd>;
	friend class btIterator<tpk, tpd>;
	//FIELDS
protected:
	tpk key;
	tpd data;
	unsigned short int weight;
	unsigned short int heigh;
	branch<tpk, tpd>* right;
	branch<tpk, tpd>* left;

	//PRIVATE FUNC
	void add(tpk in_key, tpd in_data, char mod)
	{
		branch<tpk, tpd>*  tmp = new branch<tpk, tpd>;
		tmp->init(in_key, in_data, heigh + 1); ++weight;
		switch (mod)
		{
		case 'r': right = tmp; break;
		case 'l': left = tmp; break;
		default: break;
		}
	}

	void add_bts_rec(tpk in_key, tpd in_data)
	{
		static vector<branch<tpk, tpd>*> stack;
		if (key>in_key) {
			if (left) {
				++weight;
				left->add_bts_rec(in_key, in_data);
			}
			else add(in_key, in_data, 'l');
		}
		else {
			if (right) { ++weight;  right->add_bts_rec(in_key, in_data); }
			else add(in_key, in_data, 'r');
		}
	}

	void init(tpk in_key, tpd in_data, unsigned short int in_heigh)
	{
		key = in_key; data = in_data; heigh = in_heigh;
	}

public:
	//CONSTRUCTORS
	branch()
	{
		weight = 0; right = nullptr; left = nullptr;
		heigh = 0;
	}
	~branch() {}

	//PUBLIC FUNC
	void print(bool all = false)
	{
		for (int i = 0; i <= heigh; ++i)
			cout << "  ";
		if (all) cout << "addr=" << this << "; key=" << key << "; data=" << data << "; weight=" << weight << "; heigh=" << heigh << "; r=" << right << "; l=" << left << endl;
		else cout << key << ": " << data << endl;
	}

	void set(tpd newData)
	{
		data = newData;
	}

	tpk get_key()
	{
		return key;
	}

	tpd get_data()
	{
		return data;
	}

	tpd replace(tpd newData)
	{
		tpd tmp = data; data = newData;
		return tmp;
	}
};

//BINARY TREE CLASS
template <class tpk1, class tpd1>
class binaryTree
{
	friend class btIterator<tpk1, tpd1>;
private:
	//FIELDS
	branch<tpk1, tpd1> root;
	bool isRootEmpty;

	//PRIVATE FUNC
	branch<tpk1, tpd1>* srch_bts(tpk1 key)
	{
		if (isRootEmpty) return NULL;
		branch<tpk1, tpd1>* br_ptr = &root;
		do {
			if (br_ptr->get_key() == key)
			{
				return br_ptr;
			}
			if ((br_ptr->key>key) && (br_ptr->left))
			{
				br_ptr = br_ptr->left;
			}
			else if ((br_ptr->key<key) && (br_ptr->right)) { br_ptr = br_ptr->right; }
			else break;
		} while (true);
		return NULL;
	}

public:
	//CONSTRUCTORS
	binaryTree() { isRootEmpty = true; }
	~binaryTree()
	{
		cout << "destructor report: undefined fail, deleting aborted\n";
		/*vector<branch<tpk1, tpd1>*> tmp;
		for (btIterator<tpk1, tpd1> bti(this); bti.isOK(); bti++) tmp.push_back(bti.get_ptr());
		for (branch<tpk1, tpd1>* br: tmp)
			{ cout << br <<  endl; delete br; } */
	}

	//PUBLIC FUNC
	void add(tpk1 newKey, tpd1 newData)
	{
		branch<tpk1, tpd1>* ptr = &root;
		if (isRootEmpty)
		{
			root.init(newKey, newData, 0); isRootEmpty = false; return;
		};
		while (ptr->weight>1)
		{
			if (!(ptr->right && ptr->left)) break;
			if (ptr->right->weight > ptr->left->weight) ptr = ptr->left;
			else ptr = ptr->right;
		}
		if (!ptr->right) ptr->add(newKey, newData, 'r');
		else ptr->add(newKey, newData, 'l');
	}

	void add_bts(tpk1 newKey, tpd1 newData) {
		if (isRootEmpty)
		{
			root.init(newKey, newData, 0); isRootEmpty = false; return;
		}
		root.add_bts_rec(newKey, newData);
	}

	void print(bool all = false)
	{
		for (btIterator<tpk1, tpd1> bti(this); bti.isOK(); bti++) bti.get_ptr()->print(all);
	}

	tpd1 search(tpk1 key)
	{
		for (btIterator<tpk1, tpd1> bti(this); bti.isOK(); bti++)
			if (bti.get_ptr()->get_key() == key) return bti.get_ptr()->get_data(); return NULL;
	}

	tpd1 search_bts(tpk1 key)
	{
		branch<tpk1, tpd1>* tmp = srch_bts(key);
		if (tmp) return tmp->get_data();
		else return NULL;
	}

	int del(tpk1 key)
	{
		branch<tpk1, tpd1>* tmp = srch_bts(key);
		if (tmp)
		{

		}
		else return NOTFOUND;
	}

};

//BINARY TREE ITERATOR CLASS
template <class tpk2, class tpd2>
class btIterator
{
private:
	//FIEDS
	branch<tpk2, tpd2>* ptr;
	binaryTree<tpk2, tpd2>* owner;
	vector<branch<tpk2, tpd2>*> stack;
	short int stat;

	//PRIVATE FUNC
	inline branch<tpk2, tpd2>* stack_pop()
	{
		branch<tpk2, tpd2>* tmp = stack.back();
		stack.pop_back();
		return tmp;
	}

	void next()
	{
		if (ptr->left)
			stack.push_back(ptr->left);
		if (ptr->right) ptr = ptr->right;
		else {
			if (stack.size()) ptr = stack_pop();
			else { stat = STOPITER; return; }
		}
		stat = OK;
		return;
	}

public:
	//CONSTRUCTORS
	btIterator() {}
	~btIterator() {}

	//PUBLIC FUNC
	btIterator(binaryTree<tpk2, tpd2>* bt)
	{
		owner = bt; ptr = &(owner->root); stat = OK;
	}

	inline void operator++(int n) { next(); }

	inline branch<tpk2, tpd2>* get_ptr()
	{
		return ptr;
	}

	inline short int isOK()
	{
		return stat == OK;
	}
};

