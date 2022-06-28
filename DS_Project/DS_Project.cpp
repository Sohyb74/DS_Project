#include <iostream>
#include"sqlite/sqlite3.h"
#include<string>
#include"Admin.h"
#include "Student.h"
#include"Course.h"
#include "DataBase.h"
#include "Menu.h"
using namespace std;
int main() {

	DataBase database;
	database.load_DB();

	Menu main_meue;
	main_meue.login();

	database.update_DB();
	
	return 0;
}