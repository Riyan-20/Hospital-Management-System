#pragma once
#include <iostream>
#include "PatientRecord.h"
using namespace std;
class TNode {
public:
	PatientRecord data;
	TNode* left;
	TNode* right;
	TNode(const PatientRecord& obj)
	{
		data = obj;
		left = NULL;
		right = NULL;
	}

};

class HospitalData {
	TNode* root;
	int size;
	void count_nodes(TNode* ptr, int& count)
	{
		if (ptr)
		{
			count_nodes(ptr->left, count);
			count++;
			count_nodes(ptr->right, count);
		}
	}
	void wrapper_insert(TNode*& ptr, PatientRecord& obj)
	{
		if (ptr == NULL)
		{
			// PatientRecord temp
			ptr = new TNode(obj);
			size++;
			cout << "RECORD INSERTED ! " << endl;
			return;
		}
		else if (obj.getid() < ptr->data.getid())
		{
			wrapper_insert(ptr->left, obj);
			if (ptr != root && ptr->left->data.getadmitted() && ptr->left->data.getid() == obj.getid())
				rotateright(ptr);
		}
		else if (obj.getid() > ptr->data.getid())
		{
			wrapper_insert(ptr->right, obj);
			if (ptr != root && ptr->right->data.getadmitted() && ptr->right->data.getid() == obj.getid())
				rotateleft(ptr);
		}

	}
	bool wrapper_remove(TNode*& ptr, const int id)
	{
		if (ptr)
		{
			if (ptr->data.getid() == id)
			{
				if (ptr->left == nullptr && ptr->right == nullptr) // leaf node erasecase0
				{
					delete ptr;
					ptr = nullptr;
					cout << "erasecase0" << endl;
				}
				else if (ptr->left == nullptr && ptr->right != nullptr) // 1 right child erasecase1
				{
					TNode* temp = ptr;
					ptr = ptr->right;
					delete temp;
					cout << "erasecase1" << endl;
				}
				else if (ptr->left != nullptr && ptr->right == nullptr) // 1 left child erasecase1
				{
					TNode* temp = ptr;
					ptr = ptr->left;
					delete temp;
					cout << "erasecase1" << endl;
				}
				else // 2 childs erasecase2
				{
					cout << "erasecase2" << endl;
					TNode* temp = ptr->right;
					TNode* ptemp = ptr;
					while (temp->left != nullptr) // finding minimum value in right subtree of ptr
					{
						ptemp = temp;
						temp = temp->left;
					}
					swap(ptr->data, temp->data);
					if (ptemp->right == temp)
						ptemp->right = temp->right;
					else
						ptemp->left = temp->right;
					delete temp;
				}
				return 1;
			}
			else if (id < ptr->data.getid())
				return  wrapper_remove(ptr->left, id);
			else
				return wrapper_remove(ptr->right, id);
		}
		return 0;
	}

	TNode* wrapper_search(TNode*& ptr, int depth, const int id, int level)
	{
		if (ptr != NULL)
		{
			if (ptr->data.getid() == id)
			{
				return ptr;
			}
			else if (id < ptr->data.getid())
			{
				depth++;
				TNode* tptr = wrapper_search(ptr->left, depth, id, level);
				if (depth > level && tptr != nullptr)
				{
					rotateright(ptr);
				}
				return tptr;
			}
			else
			{
				depth++;
				TNode* tptr = wrapper_search(ptr->right, depth, id, level);
				if (depth > level && tptr != nullptr)
				{
					rotateleft(ptr);
				}
				return tptr;
			}
		}
		return 0;
	}
	void wrapper_output_addmitted(TNode* ptr)
	{
		if (ptr)
		{
			wrapper_output_addmitted(ptr->left);
			if (ptr->data.getadmitted())
				ptr->data.printrecord();
			wrapper_output_addmitted(ptr->right);
		}
	}
	void wrapper_output(TNode* ptr, const int id)
	{
		if (ptr != NULL)
		{
			if (ptr->data.getid() == id)
			{
				ptr->data.printrecord();
				return;
			}
			else if (id < ptr->data.getid())
			{
				wrapper_output(ptr->left, id);
			}
			else
			{
				wrapper_output(ptr->right, id);
			}
		}
		else
		{
			cout << "==================================" << endl;
			cout << "      PATIENT DOES NOT EXIST      " << endl;
			cout << "==================================" << endl;
		}
	}
	void print(TNode* ptr)
	{
		if (ptr)
		{
			/*cout << ptr->data.getid() << endl;
			cout << ptr->left->data.getid() << endl;
			cout << ptr->right->data.getid() << endl;*/
			print(ptr->left);
			cout << ptr->data.getid() << " ";
			print(ptr->right);
		}
	}
	bool wrapper_edit(TNode* ptr, const int id, string name, string date, string disease, bool ad)
	{
		if (ptr != NULL)
		{
			if (ptr->data.getid() == id)
			{
				ptr->data.editrecord(id, name, date, disease, ad);
				return 1;
			}
			else if (id < ptr->data.getid())
				return wrapper_edit(ptr->left, id, name, date, disease, ad);
			else
				return wrapper_edit(ptr->right, id, name, date, disease, ad);
		}
		return 0;
	}
	void wrapper_split(TNode*& ptr, int& count, int median, bool& found)
	{
		if (ptr)
		{
			if (ptr->left != nullptr)
			{
				if (!found)
				{
					wrapper_split(ptr->left, count, median, found);
					count++;
				}
			}
			if (median == count && !found)
			{
				found = true;
				return;
			}
			else if (found)
			{
				rotateright(ptr);
				return;

			}
			if (ptr->right != nullptr)
			{
				if (!found)
					wrapper_split(ptr->right, ++count, median, found);
				if (found)
					rotateleft(ptr);
			}
		}
	}

	// PUBLIC MEMBER FUNTIONS //
public:
	HospitalData()
	{
		root = nullptr;
		size = 0;
	}
	HospitalData(const HospitalData& obj) {
		this->root = nullptr;
		size = obj.size;
		this->copy(this->root, obj.root);
	}
	void Insert(PatientRecord& key)
	{
		wrapper_insert(root, key);
	}
	PatientRecord Search(const int id, int l)
	{
		/*TNode* ptr=NULL;
		if (id >0)
		{
			TNode* ptr = wrapper_search(root, 0, id, l);
			if (ptr)
			{
				cout << "=========================" << endl;
				cout << "      PATIENT FOUND      " << endl;
				cout << "=========================" << endl;
				ptr->data.printrecord();
			}
			else
			{
				cout << "==================================" << endl;
				cout << "      PATIENT DOES NOT EXIST      " << endl;
				cout << "==================================" << endl;
			}
			return;
		}
		cout << "==================================" << endl;
		cout << "      PATIENT DOES NOT EXIST      " << endl;
		cout << "==================================" << endl;*/
		return (wrapper_search(root, 0, id, 1)->data);
	}
	void Remove(const int id)
	{
		if (wrapper_remove(root, id))
		{
			cout << "==================================" << endl;
			cout << "          RECORD REMOVED          " << endl;
			cout << "==================================" << endl;
		}
		else
		{
			cout << "==================================" << endl;
			cout << "      RECORD DOES NOT EXIST       " << endl;
			cout << "==================================" << endl;
		}
	}
	void Edit(const int id, string name, string date, string disease, bool ad)
	{
		if (wrapper_edit(root, id, name, date, disease, ad))
		{
			cout << "==================================" << endl;
			cout << "       SUCCESSFULLY EDITED        " << endl;
			cout << "==================================" << endl;
		}
		else
		{
			cout << "==================================" << endl;
			cout << "	COULD NOT EDIT! ID NOT FOUND    " << endl;
			cout << "==================================" << endl;
		}
	}
	HospitalData Split()
	{
		bool found = 0;
		int count = 1;
		int mediannode = 0;
		if (this->size % 2 == 0) // even number of node
			mediannode = size / 2;
		else					// odd number of node
			mediannode = (size / 2) + 1;
		wrapper_split(root, count, mediannode, found);

		HospitalData t;
		t.root = this->root->right;
		t.size = wrapper_count();
		this->root->right = nullptr;
		return t;
	}
	void copy(TNode*& obj_r, TNode* r) {
		if (r != nullptr) {
			obj_r = new TNode(r->data);
			copy(obj_r->left, r->left);
			copy(obj_r->right, r->right);
		}
	}

	void Output(const int id)
	{
		wrapper_output(root, id);
	}
	void OutputAdmitted()
	{
		wrapper_output_addmitted(root);
	}
	void rotateleft(TNode*& x)
	{
		TNode* y = x->right;
		x->right = y->left;
		y->left = x;
		x = y;
	}
	void rotateright(TNode*& x)
	{
		TNode* y = x->left;
		x->left = y->right;
		y->right = x;
		x = y;
	}
	int wrapper_count()
	{
		int count = 0;
		count_nodes(root, count);
		return count;
	}
	int getsize()
	{
		return this->size;
	}
	void printTree()
	{
		print(root);
	}
	void DeleteAll(TNode*& t) {
		if (t != nullptr) {
			this->DeleteAll(t->left);
			this->DeleteAll(t->right);
			delete t;
		}
	}
	~HospitalData() {
		this->DeleteAll(root);
	}
};
