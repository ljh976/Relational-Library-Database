//#pragma once

#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include <stack>
#include <vector>
#include <iostream>
#include <sstream>
#include <tuple>
#include <queue>
using namespace std;


class Record {

	//Data Structure
	vector <string> info;

public:
	//Constructors/Destructor
	Record();
	Record(int info_size);
	~Record();

	//Utility Functions
	int size();
	void set(int k, string str);
	string getAttributeStat(int);
	void deleteAttribute(int loc);
	string& operator[] (int index);
	void resize(int);


};

class Table {

	//Data Structures
	vector<string> table;
	vector<Record> record;
	vector<bool> keys;

public:
	//Constructors/Destructor
	Table();
	Table(string attributeName);
	Table(string firstAttribute, string secondAttribute);
	Table(string firstAttribute, string secondAttribute, string thirdAttribute);
	~Table();

	//Utility Functions
	void addAttribute(string newAttribute);
	void deleteAttribute(string tobeDeleted);
	void insertRecord(Record newRecord);
	void makeKey(string keyAttribute);

	Table joinTables(Table firstTable, Table secondTable);
	Table keyjoinTables(Table firstTable, Table secondTable);

	//Accesor Functions

	vector <string> getAttributes();
	int getRecordSize();
	Record getRecord(int iterator);
	int getCount(string attribute);
	string getMin(string attribute);
	string getMax(string attribute);

};

class Database {

	//Data Structures
	vector<string> nameofDatabase;
	vector<Table> tables;


public:
	//Constructor/Destrcutor
	Database();
	~Database();

	//Utililty Functions
	void addTable(Table t, string name);
	void dropTable(string name);
	//vector<string> q_parser(string parse);
	stack<char*> q_parser(char par[]);
	Table find_it(string);

	//Accesor Functions
	int getWeight(string s);
	vector<string> getTablenames();
	vector<Table> getTables();
	Table query(string SELECT, string FROM, string WHERE);

	queue<string> yardAlgorithm(string WHERE);
};

#endif