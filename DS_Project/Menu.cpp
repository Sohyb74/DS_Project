#include "Menu.h"
#include <iostream>
#include <fstream>
#include "Admin.h"
#include "Student.h"
#include"Course.h"
#include"sqlite/sqlite3.h"
#include <vector>
#include <algorithm>
#include "DataBase.h"
using namespace std;
string Menu::name;
string Menu::name2;
int Menu::id;
string  pass;
void Menu::login() {
	system("cls");
	system("Color 74");
	cout << "\n";
	cout << "                        ************           * Student Ums *           *************\n ";
	cout << endl;
	cout << "                                           **********************\n";
	cout << "                                           *     login page     *\n";
	cout << "                                           **********************\n";
	cout << "Enter your First & Second Name: ";
	cin >> name;
	cin >> name2;
	transform(name.begin(), name.end(), name.begin(), ::tolower);
	transform(name2.begin(), name2.end(), name2.begin(), ::tolower);
	cout << "\n\n";
	cout << "Enter your password: ";
	cin >> pass;
	transform(pass.begin(), pass.end(), pass.begin(), ::tolower);
	cout << "\n\n";
	if (Check_Admin_Data(pass)) {
		adminmenu();
	}
	else if (Check_Stud_Data(pass)) {
		studmenu();
	}
	else {
		cout << "Your Username Or Password is Wrong !  \n";
		system("pause 0");
		system("cls");
		login();
	}
}
//////////////////////////////////////////////////////////////////////////
void Menu::adminmenu() {
	Admin admin;
	char choice;
	system("cls");
	cout << "\n";
	cout << "                        ************           * Student Ums *           *************\n ";
	cout << endl;
	cout << "                                           **********************\n";
	cout << "                                           *      Admin Page    *\n";
	cout << "                                           **********************\n";
	cout << " Welcome, " << name << "\n";
	cout << "**********************\n";
	cout << "1-Add New Course\n";
	cout << "2-Add New Student\n";
	cout << "3-Update/Delete Course\n";
	cout << "4-View List OF Students in Specific Course\n";
	cout << "5-View List OF Courses of Specific Student\n";
	cout << "6-Fill prerequisite of Specific Course\n";
	cout << "7-Add finished Courses and progressed Courses To Specific Student\n";
	cout << "8-Exit\n";
	cout << "9-Go Back To Loign Menu\n";
	cout << "Enter your choice : ";
	cin >> choice;

	string course_name;
	switch (choice)
	{
	case '1':
		system("cls");
		course_name = admin.Addcourse();
		cout << "If you want to add course prerequisite press 1\nfor get to admin menu press 0\n";
		int p;
		cin >> p;
		if (p == 1) {
			system("cls");
			view_all_courses();
			admin.fill_prerequisite_list(course_name);
			system("pause");
			adminmenu();
		}
		else {
			system("pause");
			adminmenu();
		}
		break;
	case '2':
		system("cls");
		admin.add_stud();
		system("pause");
		adminmenu();
		break;
	case '3':
		system("cls");
		admin.ModifyCourses();
		break;
	case '4':
		system("cls");
		view_all_courses();
		admin.view_studs_of_course();
		system("pause");
		adminmenu();
		break;
	case '5':
		system("cls");
		admin.view_courses_of_stud();
		system("pause");
		adminmenu();
		break;
	case '6':
		system("cls");
		view_all_courses();
		cout << "Enter Course name\n";
		cin >> course_name;
		admin.fill_prerequisite_list(course_name);
		adminmenu();
		break;
	case '7':
		system("cls");
		admin.add_f_course_in_p_course();
		system("pause");
		adminmenu();
		break;
	case '8':
		system("cls");
		cout << "                                                                      \n\n\n";
		cout << "                                  ______________________________________\n\n";
		cout << "                                  ************ See You Soon ************\n";
		cout << "                                  ______________________________________\n\n\n\n";
		break;
	case '9':
		login();
	default:
		cout << "Sorry Wrong Choice....!\n";
		system("pause");
	then:adminmenu();
	}
}
//////////////////////////////////////////////////////////////////////////
void Menu::studmenu() {
	Student stud;
	for (auto x : DataBase::students_map) {
		if (name == x.second.get_f_name() && name2 == x.second.get_s_name()) {
			id = stoi(x.first);
			break;
		}
	}
	char choice;
	system("cls");
	cout << "\n";
	cout << "                        ************           * Student Ums *           *************\n ";
	cout << endl;
	cout << "                                           **********************\n";
	cout << "                                           *     Student Page   *\n";
	cout << "                                           **********************\n";
	cout << " Welcome, " << name << "\n";
	cout << "**********************\n";
	cout << "1-View List of Available Courses\n";
	cout << "2-View Details of specific Course\n";
	cout << "3-Regisiter for A Course\n";
	cout << "4-View My Courses\n";
	cout << "5-Edit My data\n";
	cout << "6-Exist \n";
	cout << "7-Go Back To Loign Menu \n";
	cout << "Enter your choice : ";
	cin >> choice;
	char p;
	string s;
	switch (choice)
	{
	case '1':
		system("cls");
		cout << "\t\t\t\t\tYour Available COURSES\n\t\t\t\t\t-----------------------\n";
		stud.view_available_courses(id);
		system("pause");
		studmenu();
		break;
	case '2':system("cls");
		cout << "\t\t\t\t\tYour Available COURSES\n\t\t\t\t\t-----------------------\n";
		stud.view_available_courses(id);
		cout << endl;
		stud.View_CoursesDetails();
		system("pause");
		studmenu();
		break;
	case '3':system("cls");
		cout << "\t\t\t\t\tYour Available COURSES\n\t\t\t\t\t-----------------------\n";
		stud.view_available_courses(id);
		cout << "press 1 to view details of specific Course...press 2 to register for a course: ";
		cin >> p;
		if (p == '1') {
			s = stud.View_CoursesDetails();
			if (s == "")
				break;
			cout << "If you want to regisiter for this course press 1...OR press 0 to go back\n";
			cin >> p;
			if (p == '1') {
				stud.Request_course(s, id);
			}
			else if (p == '0') {
				studmenu();
			}
			else {
				cout << "invalid choice\n";
				system("pause");
				studmenu();
			}
		}
		else if (p == '2') {
			cout << "\nEnter Course Came\n";
			cin >> s;
			transform(s.begin(), s.end(), s.begin(), ::tolower);
			stud.Request_course(s, id);
		}
		else {
			cout << "invalid choice\n";
			studmenu();
		}
		system("pause");
		studmenu();
		break;

	case '4':
		system("cls");
		stud.view_stud_courses(id);
		system("pause");
		studmenu();
		break;
	case '5':
		system("cls");
		stud.edit_stud_data(id);
		system("pause");
		studmenu();
		break;
	case '6':
		system("cls");
		cout << "                                                                      \n\n\n";
		cout << "                                  ______________________________________\n\n";
		cout << "                                  ************ See You Soon ************\n";
		cout << "                                  ______________________________________\n\n\n\n";
		break;
	case '7':
		login();
	default:
		cout << "Sorry Wrong Choice....!\n";
		system("pause");
		then:studmenu();
	}
}
//////////////////////////////////////////////////////////////////////////
bool Menu::Check_Stud_Data(string password) {
	for (auto x : DataBase::students_map) {
		if (x.second.get_f_name() == name && x.second.get_s_name() == name2 && x.second.get_student_password() == pass) {
			return true;
		}
	}
	return false;
}
//////////////////////////////////////////////////////////////////////////
bool Menu::Check_Admin_Data(string password) {
	for (auto x : DataBase::admins_map) {
		if (x.second.get_fname() == name && x.second.get_lname() == name2 && x.second.get_admin_pass() == pass) {
			return true;
		}
	}
	return false;
}
//////////////////////////////////////////////////////////////////////////
void Menu::view_all_courses() {
	int c = 1;
	cout << "\t\t\t\t\tAll Courses...\n";
	for (auto x : DataBase::courses_map) {
		cout << c << "- " << x.second.get_Course_name() << endl;
		c++;
	}
	cout << "\n\n\n";
}