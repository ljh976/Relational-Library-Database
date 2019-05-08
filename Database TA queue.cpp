#define _CRT_SECURE_NO_WARNINGS 
#include <string>
#include <stack>
#include <vector>
#include <iostream>
#include <sstream>
#include <queue>
#include<map>
#include "Database.h"
//#include "stdafx.h"
#include <string.h>


using namespace std;

vector <string> keys;

Record::Record() {
	info;
}

Record::Record(int info_size) {

	info.resize(info_size);

}

Record::~Record() {
	info.clear();
}

int Record::size() {
	return info.size();
}

void Record::resize(int size) {
	info.resize(size);
}

void Record::set(int k, string str) {
	info[k] = str;
}

string Record::getAttributeStat(int index) {
	return info[index];
}

void Record::deleteAttribute(int index) {
	info.erase(info.begin() + index);
}

string& Record::operator [] (int index) {
	return info[index];
}


Table::Table() {
	table;
	record;
	keys;
}
Table::Table(string attributeName) {
	table.push_back(attributeName);
	vector<Record> record;
	vector<bool> keys(1);
}

Table::Table(string firstAttribute, string secondAttribute) {
	table.push_back(firstAttribute);
	table.push_back(secondAttribute);
	vector<Record> record;
	vector<bool> keys(2);
}

Table::Table(string firstAttribute, string secondAttribute, string thirdAttribute) {
	table.push_back(firstAttribute);
	table.push_back(secondAttribute);
	table.push_back(thirdAttribute);
	vector<Record> record;
	vector<bool> keys(3);
}

Table::~Table() {
	table.clear();
	record.clear();
	keys.clear();
}

void Table::addAttribute(string newAttribute) {
	table.push_back(newAttribute);
	keys.resize(keys.size() + 1);
}

void Table::deleteAttribute(string tobeDeleted) {
	for (int i = 0; i < table.size(); ++i) {
		if (table[i] == tobeDeleted) {
			table.erase(table.begin() + i);
			for (int j = 0; j < record.size(); ++j)
				record[j].deleteAttribute(i);
		}


		else {
			cerr << "No attribute found matching: " << tobeDeleted << endl;
		}
	}
}

void Table::insertRecord(Record newRecord) {
	record.push_back(newRecord);
}

void Table::makeKey(string keyAttribute) {
	for (int i = 0; i < table.size(); ++i) {
		if (table[i] == keyAttribute)
			keys[i] = true;
	}
}

Table Table::joinTables(Table firstTable, Table secondTable) {
	for (int i = 0; i<secondTable.table.size(); i++) {
		firstTable.table.push_back(secondTable.table.at(i));
	}

	return firstTable;
}

Table Table::keyjoinTables(Table firstTable, Table secondTable) {
	string keyname;
	for (int i = 0; i < secondTable.keys.size(); i++) {
		if (secondTable.keys[i]) {
			keyname = secondTable.table[i];
			break;
		}
	}

	for (int j = 0; j < firstTable.table.size(); j++) {
		if (firstTable.table[j] == keyname)
			secondTable.deleteAttribute(keyname);
	}

	vector<string> stattr = secondTable.getAttributes();
	for (int k = 0; k < stattr.size(); k++)
		firstTable.addAttribute(stattr[k]);

	for (int l = 0; l < firstTable.record.size(); l++) {
		int index = firstTable.record.size() + 1;
		firstTable.record[l].resize(firstTable.table.size());
		for (; index < firstTable.table.size(); index++) {
			for (int m = 0; m < secondTable.record.size(); m++)
				firstTable.record[l].set(index, secondTable.record[l][m]);
		}
	}

	Table keyTable = firstTable;
	return keyTable;
}

vector<string> Table::getAttributes() {

	vector<string> allAttributes;
	for (int i = 0; i < table.size(); i++) {
		allAttributes.push_back(table[i]);
	}

	return allAttributes;
}

int Table::getRecordSize() {
	return record.size();
}

Record Table::getRecord(int iterator) {
	return record[iterator];
}

int Table::getCount(string attribute) {
	return record.size();
}

string Table::getMin(string attribute) {
	vector<int> minVector;
	for (int i = 0; i < table.size(); i++) {
		if (table[i] == attribute) {
			for (int j = 0; j < record.size(); j++) {
				minVector.push_back(stoi(record[j].getAttributeStat(i)));
			}
		}
	}

	int newMin = minVector[0];

	for (int k = 0; k < minVector.size(); k++) {
		if (minVector[k] < newMin)
			newMin = minVector[k];
	}
	string min = to_string(newMin);
	cout << "mn: " << newMin << endl;
	return min;
}

string Table::getMax(string attribute) {
	vector<int> maxVector;
	for (int i = 0; i < table.size(); i++) {
		if (table[i] == attribute) {
			for (int j = 0; j < record.size(); j++)
				maxVector.push_back(stoi(record[j].getAttributeStat(i)));
		}
	}
	int newMax = maxVector[0];

	for (int k = 0; k < maxVector.size(); k++) {
		if (maxVector[k] > newMax)
			newMax = maxVector[k];
	}
	string max = to_string(newMax);
	cout << "mx: " << newMax << endl;
	return max;
}

Database::Database() {
	vector <string> nameofDatabase;
	vector<Table> table;
}

Database::~Database() {
	nameofDatabase.clear();
	tables.clear();
}

void Database::addTable(Table t, string name) {
	tables.push_back(t);
	nameofDatabase.push_back(name);
}

void Database::dropTable(string name) {
	for (int i = 0; i < nameofDatabase.size(); ++i) {
		if (nameofDatabase[i] == name) {
			nameofDatabase.erase(nameofDatabase.begin() + i);
			tables.erase(tables.begin() + i);
		}
	}
}

vector<string> Database::getTablenames() {
	vector<string> names;
	if (nameofDatabase.empty()) {
		return names;
	}

	else {

		for (int i = 0; i < nameofDatabase.size(); i++)
			names.push_back(nameofDatabase[i]);

		return names;
	}
}


vector<Table> Database::getTables() {
	vector<Table> alltables;

	if (tables.empty())
		return alltables;

	for (int i = 0; i < tables.size(); ++i)
		alltables.push_back(tables[i]);

	return alltables;
}

int Database::getWeight(string s) {
	if (s == "NOT") {
		return 2;
	}
	else if (s == "=" || s == "<>" || s == ">" || s == "<" || s == ">=" || s == "<=" || s == "AND" || s == "OR") {
		return 1;
	}
	else {
		return 0;
	}
}


stack<char*> Database::q_parser(char par[]) {
	stack<char*> v;
	char* delimiter;
	delimiter = " ,=,<>,>,<,>=,<=,AND,OR,NOT";
	char *ptr = strtok(par, delimiter);

	//cout << ptr << endl;
	while (ptr != NULL) {
		printf("%s\n", ptr);
		v.push(ptr);
		//ptr = strtok(NULL, ">=");
		ptr = strtok(NULL, " ,=,<>,>,<,>=,<=,AND,OR,NOT");
		//cout << ptr << endl;
	}

	char* x = ">";
	cout<<*x<<endl;
	//v.push(x);

	//cout<<"stack size: "<< v.size()<<endl;

	//for (int i = 0; i <= v.size(); i++) {
	//cout << v.top() << endl;
	//v.pop();
	//}

	return v;
}

Table Database::find_it(string x) {
	Table new_table;
	for (int i = 0; i < nameofDatabase.size(); i++) {
		if (nameofDatabase.at(i) == x) {
			new_table = tables.at(i);
			break;
		}
	}
	return new_table;
}
bool isOperator(char * op) {
	if (strcmp(op,">")==0 || strcmp(op,"<") == 0 || strcmp(op,">=") == 0 || strcmp(op,"<=") == 0 ||
		strcmp(op, "==") == 0 || strcmp(op,"<>") == 0 || strcmp(op,"AND") == 0 || strcmp(op,"OR") == 0 || strcmp(op,"NOT") == 0 || strcmp(op,"(") == 0 || strcmp(op, ")") == 0)
			return true;
	return false;
}

void printQueue(queue<string> queueWhere) {
	while (!queueWhere.empty()) {
		cout << queueWhere.front() << endl;
		queueWhere.pop();
	}
}

queue<string> Database::yardAlgorithm(string WHERE) {
	map<string, int> priority;
	priority.insert(pair<string, int>(">", 10));
	priority.insert(pair<string, int>("<", 9));
	priority.insert(pair<string, int>(">=", 8));
	priority.insert(pair<string, int>("<=", 7));
	priority.insert(pair<string, int>("==", 6));
	priority.insert(pair<string, int>("<>", 5));
	priority.insert(pair<string, int>("AND", 4));
	priority.insert(pair<string, int>("OR", 3));
	priority.insert(pair<string, int>("NOT", 2));
	priority.insert(pair<string, int>("(", 1));
	priority.insert(pair<string, int>(")", 0));

	queue<string> parsedWhere;
	stack<string> operators;
	//( age > 0 AND age < 5 ) OR age > 20
	char*  aux = new char[WHERE.length() + 1];
	strcpy(aux, WHERE.c_str());
	char *ptr = strtok(aux, " ");
	while (ptr != NULL) {
		if (isOperator(ptr)) {
			if (!operators.empty()) {
				 string lastOp = operators.top();
				 if (priority.at(lastOp) > priority.at(ptr)) {
					 operators.pop();
					 parsedWhere.push(lastOp);
				 }
					 
			}
			operators.push(ptr);

		}
		else {
			parsedWhere.push(ptr);

		}
		ptr = strtok(NULL, " ");
	}
	while (!operators.empty()) {
		parsedWhere.push(operators.top());
		operators.pop();
	}
	printQueue(parsedWhere);
	return parsedWhere;
}

Table Database::query(string SELECT, string FROM, string WHERE) {
	Table old_t = find_it(FROM);

	Table new_t;
	stack<char*> par_query;

	vector <string> temp_atti;

	if (SELECT == "*") {
		temp_atti = old_t.getAttributes();
		for (int i = 0; i<temp_atti.size(); i++) {
			new_t.addAttribute(temp_atti[i]);
		}
	}

	else {
		for (auto i : SELECT) {
			new_t.addAttribute(FROM);
		}
	}

	queue<string> queryString = yardAlgorithm(WHERE);
	int and_ = WHERE.find("AND");
	int or_ = WHERE.find("OR");
	int not_ = WHERE.find("NOT");

	int x = WHERE.find(">");
	int y = WHERE.find("<");
	int z = WHERE.find("=");
	char* str = new char[WHERE.length() + 1];
	strcpy(str, WHERE.c_str());
	par_query = q_parser(str);
	string right;
	string left;

	right = par_query.top();
	par_query.pop();
	left = par_query.top();
	par_query.pop();

	

	vector <string> str_v = old_t.getAttributes();
	Record r;

	/////////////////////////////////Greater than////////////////////////////////////////////////////////
	if (x > 0 && z < 0) {
		int k = 0;

		for (int i = 0; i<str_v.size(); i++) {
			if (str_v[i] == left) {
				k = i;
			}
		}
		vector <Record> r_v;
		for (int i = 0; i<old_t.getRecordSize(); i++) {
			r_v.push_back(old_t.getRecord(i));
		}

		for (int i = 0; i < r_v.size(); i++) {
			if (stoi(r_v[i].getAttributeStat(k)) < stoi(right))
				r_v.erase(r_v.begin() + i);
		}

		for (int i = 0; i < r_v.size(); i++) {
			new_t.insertRecord(r_v[i]);
		}
		cout << "Greater than worked" << endl;

	}

	////////////////////////////////////Less than///////////////////////////////////////////////////////
	if (y > 0 && z < 0) {
		int k = 0;

		for (int i = 0; i<str_v.size(); i++) {
			if (str_v[i] == left) {
				k = i;
			}
		}
		vector <Record> r_v;

		for (int i = 0; i<old_t.getRecordSize(); i++) {
			r_v.push_back(old_t.getRecord(i));
		}

		for (int i = 0; i < r_v.size(); i++) {
			if (stoi(r_v[i].getAttributeStat(k)) > stoi(right))
				r_v.erase(r_v.begin() + i);
		}

		for (int i = 0; i < r_v.size(); i++) {
			new_t.insertRecord(r_v[i]);
		}


		vector <int> info_v1;

		for (int j = 0; j<r_v.size(); j++) {
			info_v1.push_back(stoi(r_v[j].getAttributeStat(k)));
			cout << "YAHOOO: " << info_v1[j] << endl;
		}
		cout << "less than worked" << endl;
	}

	/////////////////////////////////Greater than or equal too////////////////////////////////////////////////
	if (x > 0 && z > 0) {
		int k = 0;

		for (int i = 0; i<str_v.size(); i++) {
			if (str_v[i] == left) {
				k = i;
			}
		}
		vector <Record> r_v;
		for (int i = 0; i<old_t.getRecordSize(); i++) {
			r_v.push_back(old_t.getRecord(i));
		}

		for (int i = 0; i < r_v.size(); i++) {
			if (stoi(r_v[i].getAttributeStat(k)) <= stoi(right))
				r_v.erase(r_v.begin() + i);
		}

		for (int i = 0; i < r_v.size(); i++) {
			new_t.insertRecord(r_v[i]);
		}

		cout << " Greater than or equal worked" << endl;

	}

	////////////////////////////////Less than or equal too////////////////////////////////////////////////////	

	if (y > 0 && z > 0) {
		int k = 0;

		for (int i = 0; i<str_v.size(); i++) {
			if (str_v[i] == left) {
				k = i;
			}
		}
		vector <Record> r_v;
		for (int i = 0; i<old_t.getRecordSize(); i++) {
			r_v.push_back(old_t.getRecord(i));
		}

		for (int i = 0; i < r_v.size(); i++) {
			if (stoi(r_v[i].getAttributeStat(k)) >= stoi(right))
				r_v.erase(r_v.begin() + i);
		}

		for (int i = 0; i < r_v.size(); i++) {
			new_t.insertRecord(r_v[i]);
		}

		cout << "less than or equal worked" << endl;
	}

	if (and_ > 0) {
		vector <string> str_v;
		int k;
		str_v = old_t.getAttributes();
		// finding two attributes
		for (int i = 0; i<str_v.size(); i++) {
			if (str_v[i] == left) {
				k = i;
			}
		}

		for (int i = 0; i<str_v.size(); i++) {
			if (str_v[i] == left) {
				k = i;
			}
		}
		//finding contents from two records in conditions. 
		vector <Record> r_v1;
		for (int i = 0; i<old_t.getRecordSize(); i++) {
			r_v1.push_back(old_t.getRecord(i));
		}

		vector <Record> r_v2;
		for (int i = 0; i<old_t.getRecordSize(); i++) {
			r_v2.push_back(old_t.getRecord(i));
		}


	}
	return new_t;
}