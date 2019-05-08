
//#include "stdafx.h"
#include "Database.h"
#include <iostream>
#include <string>
#include <vector>
#include <ostream>
#include <tuple>
#include <stdio.h>
//#include <tchar.h>
bool test_record() {

	//new records
	Record new_record1(10);
	Record new_record2(10);

	//making new test records to push into table
	new_record1.set(0, "Jake");
	new_record1.set(1, "19");
	new_record1.set(2, "09/13/1998");
	new_record1.set(3, "193");
	new_record1.set(4, "9:30");

	new_record2.set(0, "Jake");
	new_record2.set(1, "19");
	new_record2.set(2, "09/13/1998");
	new_record2.set(3, "193");
	new_record2.set(4, "9:30");


	if (new_record1.size() != 5) {
		cout << "Error with size method of record" << endl;
		return true;
	}
	//if (new_record1.set == new_record2.set) {

	//}
	else {
		cout << "error with overloaded == operator on record" << endl;
		return true;
	}

	cout << "Testing getAttribute method on Record class : --------" << endl;
	cout << new_record1.getAttributeStat(0) << endl;
	cout << new_record1.getAttributeStat(1) << endl;
	cout << new_record1.getAttributeStat(2) << endl;
	cout << new_record1.getAttributeStat(3) << endl;
	cout << new_record1.getAttributeStat(4) << endl;
	cout << "-----------------------------" << endl;
	cout << "Deleting Attriibute Time" << endl;
	new_record1.deleteAttribute(4);
	cout << "New record size = " << new_record1.size() << endl;

	cout << "Testing [] operator on Record" << endl;
	if (new_record1[2] != "09/13/1998") {
		cout << "error using [] operator on Record class" << endl;
		return true;
	}

	return false;
}

bool test_database() {

	//creating Table
	Table test_table("Full_Name", "Age", "Birthdate");
	test_table.addAttribute("Weight");
	test_table.addAttribute("Time");
	test_table.makeKey("Full_Name");


	//new records
	Record new_record1(10);
	Record new_record2(10);
	Record new_record3(10);
	Record new_record4(10);

	//making new test records to push into table
	new_record1.set(0, "Jake");
	new_record1.set(1, "19");
	new_record1.set(2, "09/13/1998");
	new_record1.set(3, "193");
	new_record1.set(4, "9:30");


	new_record2.set(0, "Paul");
	new_record2.set(1, "34");
	new_record2.set(2, "03/01/1983");
	new_record2.set(3, "154");
	new_record2.set(4, "14:52");


	new_record3.set(0, "Ashley");
	new_record3.set(1, "25");
	new_record3.set(2, "11/23/1992");
	new_record3.set(3, "123");
	new_record3.set(4, "00:30");


	new_record4.set(0, "Dillon");
	new_record4.set(1, "12");
	new_record4.set(2, "08/27/2005");
	new_record4.set(3, "98");
	new_record4.set(4, "21:45");

	//new records
	Record new_record5(10);
	Record new_record6(10);
	Record new_record7(10);
	Record new_record8(10);

	new_record5.set(0, "Bob");
	new_record5.set(1, "19");
	new_record5.set(2, "09/13/1998");
	new_record5.set(3, "143");
	new_record5.set(4, "2:30");

	new_record6.set(0, "Billy");
	new_record6.set(1, "34");
	new_record6.set(2, "03/01/1983");
	new_record6.set(3, "154");
	new_record6.set(4, "10:52");

	new_record7.set(0, "Babester");
	new_record7.set(1, "24");
	new_record7.set(2, "11/23/1992");
	new_record7.set(3, "123");
	new_record7.set(4, "00:30");

	new_record8.set(0, "Cinnamon");
	new_record8.set(1, "91");
	new_record8.set(2, "08/27/2005");
	new_record8.set(3, "78");
	new_record8.set(4, "21:45");

	//inserting record into testtable 2
	Table test_table2;
	test_table2.insertRecord(new_record5);
	test_table2.insertRecord(new_record6);
	test_table2.insertRecord(new_record7);
	test_table2.insertRecord(new_record8);

	//add table to database
	Database test_database;
	test_database.addTable(test_table, "New Table 1");
	test_database.addTable(test_table2, "New Table 2");
	std::vector<std::string> table_names;
	table_names = test_database.getTablenames();
	vector <Table> all_tables;
	all_tables = test_database.getTables();
	if (table_names.size() != 1) {
		cout << "Error with size of all tables" << endl;
		return true;
	}

	Table query_table;
	query_table = test_database.query("*", "New Table 1", "Name=Paul");
	query_table = test_database.query("*", "New Table 1", "Name=Paul AND Weight>99");
	query_table = test_database.query("*", "New Table 1", "Age>15");
	query_table = test_database.query("*", "New Table 1", "Age>15 OR Weight > 150");
	query_table = test_database.query("*", "New Table 1", "(Age NOT 12) AND (Weight < 150)");


	query_table = test_database.query("*", "New Table 2", "Name=Paul");
	query_table = test_database.query("*", "New Table 2", "Name=Paul AND Weight>99");
	query_table = test_database.query("*", "New Table 2", "Age>15");
	query_table = test_database.query("*", "New Table 2", "Age>15 OR Weight > 150");
	query_table = test_database.query("*", "New Table 2", "(Age NOT 12) AND (Weight < 150)");

	test_database.dropTable("New Table 1");

	//should return no table
	query_table = test_database.query("*", "New Table 1", "(Age NOT 12) AND (Weight < 150)");

	return false;
}

bool test_table() {
	Table test_table("Full_Name", "Age", "Birthdate");
	test_table.addAttribute("Weight");
	test_table.addAttribute("Time");
	test_table.makeKey("Full_Name");


	//new records
	Record new_record1(10);
	Record new_record2(10);
	Record new_record3(10);
	Record new_record4(10);

	//making new test records to push into table
	vector < tuple <int, string> > tuples;
	new_record1.set(0, "Jake");
	new_record1.set(1, "19");
	new_record1.set(2, "09/13/1998");
	new_record1.set(3, "193");
	new_record1.set(4, "9:30");

	new_record2.set(0, "Paul");
	new_record2.set(1, "34");
	new_record2.set(2, "03/01/1983");
	new_record2.set(3, "154");
	new_record2.set(4, "14:52");

	new_record3.set(0, "Ashley");
	new_record3.set(1, "25");
	new_record3.set(2, "11/23/1992");
	new_record3.set(3, "123");
	new_record3.set(4, "00:30");

	new_record4.set(0, "Dillon");
	new_record4.set(1, "12");
	new_record4.set(2, "08/27/2005");
	new_record4.set(3, "98");
	new_record4.set(4, "21:45");

	//testing insert record
	test_table.insertRecord(new_record1);
	test_table.insertRecord(new_record2);
	test_table.insertRecord(new_record3);
	test_table.insertRecord(new_record4);

	if (test_table.getRecordSize() != 4) {
		cout << "Error in getSize() function! " << endl;
		return true;
	}

	Record get_record_tester(10);
	get_record_tester = test_table.getRecord(1);
	if (get_record_tester.getAttributeStat(0) != "Jake") {
		cout << "Error when getting record from table: Jake not found" << endl;
		return true;
	}

	vector <string> get_attributes_tester;
	get_attributes_tester = test_table.getAttributes();
	cout << "Output of getAttributes() method is as follows " << endl;
	for (int i = 0; i < get_attributes_tester.size(); i++) {
		cout << get_attributes_tester[i] << endl << "-----------------------" << endl;
		cout << "Now deleting the Attribute 'Time' " << endl;
		cout << "Output of the getAttributes method after deleting Time : -------" << endl;
		cout << test_table.getAttributes()[i] << endl;
	}

	//Testing join tables and key Join Tables method
	Table test_table2("Full_Name", "Age", "Birthdate");
	test_table2.addAttribute("Weight");
	test_table2.addAttribute("Time");
	test_table2.makeKey("Full_Name");


	//new records
	Record new_record5(10);
	Record new_record6(10);
	Record new_record7(10);
	Record new_record8(10);

	new_record5.set(0, "Bob");
	new_record5.set(1, "19");
	new_record5.set(2, "09/13/1998");
	new_record5.set(3, "143");
	new_record5.set(4, "2:30");

	new_record6.set(0, "Billy");
	new_record6.set(1, "34");
	new_record6.set(2, "03/01/1983");
	new_record6.set(3, "154");
	new_record6.set(4, "10:52");

	new_record7.set(0, "Babester");
	new_record7.set(1, "24");
	new_record7.set(2, "11/23/1992");
	new_record7.set(3, "123");
	new_record7.set(4, "00:30");

	new_record8.set(0, "Cinnamon");
	new_record8.set(1, "91");
	new_record8.set(2, "08/27/2005");
	new_record8.set(3, "78");
	new_record8.set(4, "21:45");
	//inserting record into testtable 2
	test_table2.insertRecord(new_record5);
	test_table2.insertRecord(new_record6);
	test_table2.insertRecord(new_record7);
	test_table2.insertRecord(new_record8);

	Table result_table1;
	Table result_table2;
	result_table1 = test_table2.joinTables(test_table2, test_table);
	result_table2 = test_table2.keyjoinTables(test_table2, test_table);

	if (test_table.getMin("Age") != "12") {
		cout << "Error with getMin method of Table Class" << endl;
		return true;
	}
	if (test_table.getMax("Weight") != "193") {
		cout << "Error with getMax method of Table Class" << endl;
		return true;
	}
	if (test_table.getCount("Weight") != 4) {
		cout << "Error with getCount method of Table Class, exepected 4" << endl;
		return true;
	}
	if (test_table.getRecordSize() != 4) {
		cout << "Error with getSize method of Table Class, exepected 4" << endl;
		return true;
	}

	return false;
}


int OtherTests() {

	std::cout << "Testing has begun" << std::endl;
	if (test_record()) {
		std::cout << "Error while testing Record class" << std::endl;
	}
	if (test_table()) {
		std::cout << "Error while testing Table class" << std::endl;
	}
	if (test_database()) {
		std::cout << "Error while testing DataBase class" << std::endl;
	}

	return 0;
}