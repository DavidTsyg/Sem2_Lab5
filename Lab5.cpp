// Lab5Test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <conio.h>
using namespace std;
template <class T>
class binarytree
{
protected:
	//структура узла	
	struct node
	{
		T key_value;
		//		unsigned int height;
		node* left;
		node* right;
		node(T k) { key_value = k; left = right = 0; /*height = 1;*/ }
	};

	//инициализируем корень дерева	
	node* root = NULL;
	//вспомогательная функция вставки
	node* insert_serve(node*& leaf, T key)
	{
		if (leaf == NULL)
			leaf = new node(key);
		else if (key < leaf->key_value)
			insert_serve(leaf->left, key);
		else if (key > leaf->key_value)
			insert_serve(leaf->right, key);
		return leaf;
	}
	//вспомогательная функция поиска ключа
	virtual node* search_serve(T key, node* leaf)
	{
		if (leaf != NULL)
		{
			if (key == leaf->key_value) return leaf;
			else if (key < leaf->key_value)//если заданный ключ меньше ключа в узле то идем влево
				return search_serve(key, leaf->left);//рекурсивно идем к следующему узлу
			else if (key > leaf->key_value)//иначе идем вправо
				return search_serve(key, leaf->right);//рекурсивно идем к следующему узлу
		}
		else return NULL;//если ничего не нашли то возвращеам NULL
	}
	//вспомогательная функция уничтожения дерева
	void destroytree_serve(node* leaf)
	{
		if (leaf != NULL)//проверка
		{
			destroytree_serve(leaf->left);//рекурсивно идем к следующему узлу
			destroytree_serve(leaf->right);//рекурсивно идем к следующему узлу
			delete leaf;//уничтожаем узел
		}
	}
	//вспомогательная функция нахождения пути к узлу
	void printpath_serve(T key, node *leaf)
	{
		if (key == leaf->key_value) cout << leaf->key_value << endl;
		else if (key < leaf->key_value)//если заданный ключ меньше ключа в узле то идем влево
		{
			cout << leaf->key_value << endl;
			printpath_serve(key, leaf->left);//рекурсивно идем к следующему узлу
		}
		else if (key > leaf->key_value)//иначе идем вправо
		{
			cout << leaf->key_value << endl;
			printpath_serve(key, leaf->right);//рекурсивно идем к следующему узлу
		}
	}

	//вспомогательная функция находящая минимальный ключ в "под-ветке" заданного ключа 
	node* findmin(node* leaf)
	{
		if (leaf->left != NULL)//проверка на существование меньшего значения
			findmin(leaf->left);//рекурсивно идем к следующему узлу
		else return leaf;
	}
	//вспомогательная функция уничтожающая узел 
	node* destroynode_serve(node* leaf, T key)
	{
		if (leaf == NULL)
			return leaf;
		if (key < leaf->key_value)
			leaf->left = destroynode_serve(leaf->left, key);
		else if (key > leaf->key_value)
			leaf->right = destroynode_serve(leaf->right, key);
		else
		{
			if ((leaf->left == NULL) || (leaf->right == NULL))
			{
				node* temp = leaf->left ? leaf->left :
					leaf->right;

				// нет детей
				if (temp == NULL)
				{
					temp = leaf;
					leaf = NULL;
				}
				else // один ребенок
					*leaf = *temp;
				delete temp;
			}
			else
			{
				//два ребенка
				node* temp = findmin(leaf->right);
				leaf->key_value = temp->key_value;
				leaf->right = destroynode_serve(leaf->right, temp->key_value);
			}
		}
		if (leaf == NULL)
			return leaf;
		return leaf;
	}
	//вспомогательная функция вывода дерева
	void print_tree(node* leaf, int level)
	{
		if (leaf != NULL) {
			print_tree(leaf->left, level + 1);     // вывод левого "под-дерева"
			for (int i = 0; i < level; i++) cout << "   ";
			cout << leaf->key_value << endl;               // вывод корня поддерева
			print_tree(leaf->right, level + 1);    // вывод правого "под-дерева"
		}
	}

public:
	binarytree() {}
	~binarytree() { destroytree(); }
	//основная функция для вставки ключа	
	void insert(T key)
	{
		if (search_serve(key, root) == NULL)
		{
			if (root == NULL) {
				root = new node(key);
			}
			else
				insert_serve(root, key);
		}
		else cout << "Key " << key << " already exists !" << endl;
	}
	//основная функция для нахождения ключа
	void search(T key)
	{
		if (search_serve(key, root) != NULL) cout << "Key " << key << " exists" << endl;//используем вспомогательную функцию
		else cout << "Key doesn't exist" << endl;
	}
	//основная функция для удаления дерева
	void destroytree()
	{
		destroytree_serve(root);//используем вспомогательную функцию
	}
	//основная функция для удаления узла
	void destroynode(T key)
	{
		//находим узел для вспомогательной функции
		if (search_serve(key, root) != NULL)
			destroynode_serve(root, key);//используем вспомогательную функцию
		else cout << "Key " << key << " doesn't exist !" << endl;
	}
	//основная функция вывода пути к узлу
	void printpath(T key)
	{
		if (search_serve(key, root) != NULL)//проверка
		{
			cout << endl << endl << endl;
			printpath_serve(key, root);//используем вспомогательную функцию
			cout << endl << endl << endl;
		}
		else
			cout << "Key " << key << " doesn't exist" << endl;
	}
	//основная функция вывода дерева
	void print()
	{
		cout << endl << endl << endl << endl;
		print_tree(root, 0);
		cout << endl << endl << endl << endl;
	}

};


int main()
{
	binarytree <int> tree;
	char ch;
	int key;
	while (1)
	{
		cout << endl << endl;
		cout << " Binary Search Tree Operations " << endl;
		cout << " ----------------------------- " << endl;
		cout << " 1. Insertion/Creation " << endl;
		cout << " 2. Print Tree " << endl;
		cout << " 3. Removal " << endl;
		cout << " 4. Search " << endl;
		cout << " 5. Exit " << endl;
		cout << " Enter your choice : ";


		cin >> ch;
		switch (ch)
		{
		case '1': cout << " Enter data to be inserted : ";
			cin.ignore(1);
			cin >> key;
			tree.insert(key);
			break;
		case '2': cout << endl;
			cout << " Print Tree" << endl;
			cout << " -------------------" << endl;
			tree.print();
			break;
		
		case '3': cout << " Enter data to be deleted : ";
			cin.clear();
			cin.ignore(1);
			cin >> key;
			tree.destroynode(key);
			break;
		case '4': cout << " Enter data to be searched : ";
			cin.ignore(1);
			cin >> key;
			tree.search(key);
			break;
		case '5': system("pause");
			return 0;
			break;
		default: cout << "Invalid input. Ending the session." << endl;
			system("pause");
			return 0;
			break;
		}

	}
	return 0;
}

