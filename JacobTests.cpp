// JacobTests.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"
#include "Database.h"
#include <iostream>
#include <stdio.h>
//#include <tchar.h>
int errors = 0;

#define error(expected, actual, message) \
	if(!(expected == actual) && ++errors)	 \
		cout << __FILE__ << ": " << __LINE__ << ": " << message << endl;

int OtherTests();

int main() {
	Database db;
	vector<string> names = db.getTablenames();
	error(names.size(), 0, "Database should be empty");
	Table people1("name");
	people1.addAttribute("age");

	error(people1.getRecordSize(), 0, "Table should have size zero!");

	Table people2("name", "age");

	Record rec1(2);
	Record rec2(2);
	Record rec3(2);

	rec1.set(0, "Smith");
	rec1.set(1, "29");
	rec2.set(0, "Jiminy Cricket");
	rec2.set(1, "-18");
	rec3.set(0, "Smithyson");
	rec3.set(1, "219817");


	error(rec1.size(), 2, "Record size should be 2...");
	//error(rec1 == rec2, false, "Two non equal records tested equal");
	
	error(rec1[0], "Smith", "Incorrect item at index 0");
	error(rec1.getAttributeStat(0), "Smith", "Incorrect item at index 0");

	people1.insertRecord(rec1);
	people1.insertRecord(rec2);
	people1.makeKey("name");
	people2.insertRecord(rec3);

	error(people1.getRecordSize(), 2, "people table has incorrect size");

	error(people1.getMin("age"), "-18", "Returned incorrect minimum");
	error(people1.getMax("age"), "29", "Returned incorrect maximum");
	//cout << "is eg" << endl;
	db.addTable(people1, "people1");
	//out of range error handling
	vector<string>tablename;

	tablename = db.getTablenames(); //STUCK HERE
	error(tablename.size(), 1, "Incorrect number of tables");
	error(tablename[0], "people1", "Incorrect table name");

	db.addTable(people2, "people2");

	db.yardAlgorithm("age > 0 AND age < 10");

	Table table = db.query("*", "people1", "age<20"); //changed

	error(table.getRecordSize(), 1, "query returned table of wrong size");

	table = db.query("*", "people1", "name=Smith AND age=29");
	error(table.getRecordSize(), 1, "query returned table of wrong size");

	table = db.query("*", "people1", "name=jkdls OR age<0");
	error(table.getRecordSize(), 1, "query returned table of wrong size");

	table = db.query("*", "people1", "name=jkdls AND age<0");
	error(table.getRecordSize(), 0, "query returned table of wrong size");

	table = db.query("name", "people1", "name=jkdls OR age<0");
	error(table.getRecordSize(), 1, "query returned table of wrong size");

	OtherTests();
	cout << "Test ended." << endl;


	cout << "testing area//////////////////////////////////////" << endl;

	
	cout << rec1[0] << endl;// printing rec;

	
	//cout << v2[0] << endl;
	//cout << v2[1] << endl;
	cout << "Testing query" << endl;
	db.query("name", "people2", "age>0 AND age<10");


	

	//cout << "testing area//////////////////////////////////////" << endl;
	////////////////////////////////////////////////////////
	//system("PAUSE");
	return 0;
}
