#include<iostream>
#include "sqlite/sqlite3.h"
#include<string>
#include <vector>
#include <algorithm>
#include"Student.h"
#include"DataBase.h"
using namespace std;
sqlite3* DB;
//VECTORS FOR prerequisite COURSES
vector<string> finishedCourses_forStud_vec;
vector<string> preList_forStud_vec;
vector<string> remainCrs_vec;
vector<string> AvailabeCrs_vec;
//FLAGS TO UBDATE DATA OF STUDENT AND PROGRESSED COURSES IN DB
bool Student::STUDENT_CHANGED = false;
bool Student::PROG_CHANGED = false;
//CONSTRUCTOR
Student::Student(int idd, string fnam, string snam, string thnam, string pass, string aca) {
	id = idd;
	f_name = fnam;
	s_name = snam;
	th_name = thnam;
	password = pass;
}
Student::Student() {}
/*******************************************************************************************************************/
//GETTER FOR STUDANT DATA.....
string Student::get_f_name() {
	return  f_name;
}
string Student::get_s_name() {
	return s_name;
}
string Student::get_th_name() {
	return th_name;
}
string Student::get_student_password() {
	return  password;
}
string Student::get_acadamic_year() {
	return  acadamic_year;
}
string Student::get_student_id() {
	return   to_string(id);
}
//SETTER FOR STUDANT DATA.....
void Student::set_student_id(int idd) {
	id = idd;
}
void Student::set_f_name(string f) {
	f_name = f;
}
void Student::set_s_name(string s) {
	s_name = s;
}
void Student::set_th_name(string th) {
	th_name = th;
}
void Student::set_student_password(string pass) {
	password = pass;
}
void Student::set_acadamic_year(string aca) {
	acadamic_year = aca;
}
/******************************************************************************************************************/
/*THIS FUNCTION COULD CHANGE ONLY PASSWORD*/
void Student::edit_stud_data(int id)
{
	/*int  p, clk1;*/
	string password1, new_password;
	cout << "Enter Your Old password" << endl;
	cin >> password1;
	transform(password1.begin(), password1.end(), password1.begin(), ::tolower);
	if (password1 == DataBase::students_map[to_string(id)].get_student_password()) {
		cout << "Enter the new Password" << endl;
		cin >> new_password;
		transform(new_password.begin(), new_password.end(), new_password.begin(), ::tolower);
		DataBase::students_map[to_string(id)].set_student_password(new_password);
		STUDENT_CHANGED = true;
	}
	else {
		cout << "Your Password Is Incorrect" << endl;
	}
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Student::edit_f_and_p_course()
{
	Student stud1;
	int id, num_of_finished_c, num_of_in_p;
	char p;
	string password;
	string f_course_name, new_f_course, new_p_course, in_p_name;
	int clk;
	cout << "enter the password of student you want to edit " << endl;
	cin >> password;
	stud1.set_student_password(password);
	cout << "enter the id of student you want to edit " << endl;
	cin >> id;
	while (!cin.good()) {// validation  input should be integer
				//Error messagge
		cout << "Error : Please Enter Integer Number !\n";
		//clear cin
		//then ignore data
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		//then get  input Again
		cout << "enter the id of student you want to edit " << endl;
		cin >> id;
	}
	stud1.set_student_id(id);
	if (Student::check_row_exist(stud1.get_student_id(), stud1.get_student_password())) {
		cout << "if you want to edit finished courses for student press 1 " << endl;
		cout << "if you want to edit in progress  courses for student press 2 " << endl;
		cout << "if you want to exit t press 3 " << endl;

		cin >> p;
		switch (p) {
		case '1':
			cout << "enter the number of  finished courses you want to edit " << endl;
			cin >> num_of_finished_c;
			while (!cin.good()) {// validation  input should be integer
				//Error messagge
				cout << "Error : Please Enter Integer Number !\n";
				//clear cin
				//then ignore data
				cin.clear();
				cin.ignore(INT_MAX, '\n');
				//then get  input Again
				cout << "enter the number of  finished courses you want to edit " << endl;
				cin >> num_of_finished_c;
			}
			if (num_of_finished_c <= DataBase::finished_vector.capacity()) {
				for (int i = 0; i < num_of_finished_c; i++) {
					cout << "enter the name of finished course you want to edit " << endl;
					cin >> f_course_name;
					if (Student::check_row_exist_f(id, f_course_name)) {
						cout << "enter the name of finished course you want  " << endl;
						cin >> new_f_course;
						cout << "if you want to submit click 1 else click any number " << endl;
						cin >> clk;
						while (!cin.good()) {// validation  input should be integer
							//Error messagge
							cout << "Error : Please Enter Integer Number !\n";
							//clear cin
							//then ignore data
							cin.clear();
							cin.ignore(INT_MAX, '\n');
							//then get  input Again
							cout << "if you want to submit click 1 else click any number " << endl;
							cin >> clk;
						}
						if (clk == 1) {
							int index = 0;
							for (auto x : DataBase::finished_vector) {
								if (x.first == id && x.second == f_course_name)
								{
									break;
								}

								index++;
							}
							cout << index;
							DataBase::finished_vector[index].first = id;
							DataBase::finished_vector[index].second = new_f_course;
						}
						else {
							cout << "index does not be  modified " << endl;
						}
					}
					else {
						cout << "course does not  exist " << endl;
					}
				}
			}
			else {
				cout << "index out of range " << endl;
			}
			break;
		case '2':
			cout << "enter the number of  in progress courses you want to edit " << endl;
			cin >> num_of_in_p;
			while (!cin.good()) {// validation  input should be integer
							//Error messagge
				cout << "Error : Please Enter Integer Number !\n";
				//clear cin
				//then ignore data
				cin.clear();
				cin.ignore(INT_MAX, '\n');
				//then get  input Again
				cout << "enter the number of  in progress courses you want to edit " << endl;
				cin >> num_of_in_p;
			}
			if (num_of_in_p <= DataBase::progress_vector.capacity()) {
				for (int i = 0; i < num_of_in_p; i++) {
					cout << "enter the name of  in progress course you want to edit " << endl;
					cin >> in_p_name;
					if (Student::check_row_exist_p(id, in_p_name)) {
						cout << "enter the name of  in progress course you want  " << endl;
						cin >> new_p_course;
						cout << "if you want to submit click 1 else click any number " << endl;
						cin >> clk;
						while (!cin.good()) {// validation  input should be integer
							//Error messagge
							cout << "Error : Please Enter Integer Number !\n";
							//clear cin
							//then ignore data
							cin.clear();
							cin.ignore(INT_MAX, '\n');
							//then get  input Again
							cout << "if you want to submit click 1 else click any number " << endl;
							cin >> clk;
						}
						if (clk == 1) {
							int index = 0;
							for (auto x : DataBase::progress_vector) {
								if (x.first == id && x.second == in_p_name)
								{
									break;
								}

								index++;
							}
							cout << index;
							DataBase::progress_vector[index].first = id;
							DataBase::progress_vector[index].second = new_p_course;
						}
						else {
							cout << "index does not be  modified " << endl;
						}
					}
					else {
						cout << "course does not  exist " << endl;
					}
				}
			}
			else {
				cout << "index out of range " << endl;
			}
			break;
		case '3':
			break;
		default:
			break;
		}
	}
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*THIS FUNCTTION TAKES COURSE NAME FROM USER AND VIEW THE DEATAILS OF THIS COURSE*/
string Student::View_CoursesDetails() {
	cout << "  \n                                        .....Your Course Details..... \n\n";
	string cname;
	cout << "Enter Course name You Want to View....\n";
	cin >> cname;
	transform(cname.begin(), cname.end(), cname.begin(), ::tolower);
	cout << endl;
	if (check_course_name_exist(cname)) {
		for (auto x : DataBase::courses_map) {
			if (cname == x.second.get_Course_name()) {
				cout << "Course Name : " << x.second.get_Course_name() << endl << "Course Code : " << x.first << endl << "Course Hours : " << x.second.get_hours() << endl;
			}
		}
		return cname;
	}
	else {
		cout << "No Such Course: " << cname << " .......!\n\n";
		system("pause 0");
		return "";
	}
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*THERE FUNCTIONS VIEW ALL COURSES OF STUDENT*/
void Student::view_stud_courses(int id_) {
	view_prog_courses(id_);
	view_finished_courses(id_);
}
void Student::view_prog_courses(int iid) {
	vector<string>prog_course;
	for (auto x : DataBase::progress_vector) {
		if (iid == x.first) {
			prog_course.push_back(x.second);
		}
	}
	if (prog_course.size() != 0) {
		cout << "Your Courses in Progress are: \n";
		int count = 1;
		for (auto x : prog_course) {
			cout << count << "- " << x << endl;
			count++;
		}
	}
	else
		cout << " You Have NO Progress Courses\n";
}
void Student::view_finished_courses(int iid) {
	vector<string>finish_course;
	for (auto x : DataBase::finished_vector) {
		if (iid == x.first) {
			finish_course.push_back(x.second);
		}
	}
	if (finish_course.size() != 0) {
		cout << "Your Finished Courses are: \n";
		int count = 1;
		for (auto x : finish_course) {
			cout << count << "- " << x << endl;
			count++;
		}
	}
	else
		cout << " You Have NO Finished Courses\n";
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Student::Request_course(string course_name, int iid) {
	string code;
	bool flag = true;
	if (check_num_courses(iid)) {
		//STUD CAN TAKE 7 COURSES ONLY....AND THIS CHECK NUM OF HIS COURSES
		if (check_course_name_exist(course_name)) {
			for (auto x : DataBase::courses_map) {
				if (course_name == x.second.get_Course_name()) {
					code = x.first;
					break;
				}
			}
		}
		/*FIRST CHECK COURSE ALREADY EXIST....SECOND I TAKE THE CODE OF THIS COURSE TO USE IT AFTER THAT */
		else {
			cout << "Course Name is Incorrect\n";
			system("pause");
			system("cls");
		}
		if (check_max_num_studs(course_name, code)) {
			//CHECK IF THIS COURSE IS FULL OR NOT
			if (check_taken_course_before(iid, course_name)) {
				//CHECK IF THIS STUD TAKE THe COURSE BEFORE
				DataBase::progress_vector.push_back(make_pair(iid, course_name));
				cout << "You Took: " << course_name << " Course Successfully...\n";
				PROG_CHANGED = true;
			}
			else {
				cout << "You Have Already Taken: " << course_name << endl;
			}
		}
		else {
			cout << "\nSorry You Can't take " << course_name << " Course Because It Is FULL...";
		}
	}
	else {
		cout << "Sorry You Can't Take Any Course Because You Have 7 Courses";
	}
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*THERE FUNCTIONS VIEW TO STUD LIST OF COURSES WHICH COULD TAKE*/
void Student::view_available_courses(int id)
{
	vector<string>AvailabeCrs_vec_finnal;
	get_finished_courses(id);
	get_remain_courses();
	fill_pre_list();
	bool flag = true;
	// Printing Avaliable Crs
	for (auto x : AvailabeCrs_vec) {
		flag = true;
		for (auto y : DataBase::progress_vector) {
			if (y.first == id && x == y.second) {
				flag = false;
			}
		}
		if (flag == true) {
			AvailabeCrs_vec_finnal.push_back(x);
		}
	}

	for (size_t i = 0; i < AvailabeCrs_vec_finnal.size(); i++) {
		cout << i + 1 << "- " << AvailabeCrs_vec_finnal[i] << endl;
	}
	AvailabeCrs_vec.clear();
	finishedCourses_forStud_vec.clear();
	preList_forStud_vec.clear();
	remainCrs_vec.clear();
}
void Student::fill_available_crsVector(string remain) {
	int flag2 = -1;
	for (int j = 0; j < preList_forStud_vec.size(); j++) {
		flag2 = 1;
		for (int z = 0; z < finishedCourses_forStud_vec.size(); z++) {
			if (preList_forStud_vec[j] == finishedCourses_forStud_vec[z])
			{
				flag2 = 0;
				break;
			}
		}
	}
	if (flag2 == 0 || preList_forStud_vec.size() == 0)
		AvailabeCrs_vec.push_back(remain);
}
void Student::fill_pre_list()
{
	for (int i = 0; i < remainCrs_vec.size(); i++) {
		string reamain_ok = remainCrs_vec[i];
		for (auto x : DataBase::prerequisite_vector)
		{
			if (remainCrs_vec[i] == x.first) { preList_forStud_vec.push_back(x.second); }
		}
		// fill av_vector
		fill_available_crsVector(reamain_ok);
		// clear pre_vec
		preList_forStud_vec.clear();
	}
}
void Student::get_finished_courses(int iid) {
	for (auto x : DataBase::finished_vector)
	{
		if (iid == x.first) { finishedCourses_forStud_vec.push_back(x.second); }
	}
}
void Student::get_remain_courses() {
	for (auto i : DataBase::courses_map) // all courses
	{
		int flag = 0;
		for (auto j : finishedCourses_forStud_vec) { // finished courses
			if (i.second.get_Course_name() == j)
				flag = 1;
		}
		if (flag == 0)
			remainCrs_vec.push_back(i.second.get_Course_name()); // difference between all & finished
	}
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Student::check_num_courses(int iid) {
	const int max_num_courses = 7;
	int count = 0;
	for (auto x : DataBase::progress_vector) {
		if (iid == x.first) {
			count++;
		}
	}
	if (count < max_num_courses) {
		return true;
	}
	else
		return false;
}
/*****************************************************************************/
bool Student::check_taken_course_before(int iid, string course_name) {
	for (auto x : DataBase::progress_vector) {
		if (iid == x.first && course_name == x.second) {
			return false;
		}
	}
	for (auto x : DataBase::finished_vector) {
		if (iid == x.first && course_name == x.second) {
			return false;
		}
	}
	return true;
}
/*****************************************************************************/
bool Student::check_course_exist(string code) {
	for (auto x : DataBase::courses_map) {
		if (code == x.first)
			return true;
	}
	return false;
}
/*****************************************************************************/
bool Student::check_max_num_studs(string course_name, string code)
{
	int count = 0;
	for (auto x : DataBase::progress_vector) {
		if (x.second == course_name)
			count++;
	}
	if (DataBase::courses_map[code].get_max_numstud() == count) {
		return false;
	}
	return true;
}
/*****************************************************************************/
bool Student::check_course_name_exist(string name) {
	for (auto x : DataBase::courses_map) {
		if (name == x.second.get_Course_name())
			return true;
	}
	return false;
}
/*****************************************************************************/
bool Student::check_row_exist(string id, string password)
{
	bool flag = false;
	for (auto x : DataBase::students_map) {
		if (id == x.first && password == x.second.get_student_password()) {
			flag = true;
		}
	}
	return flag;
}
/*****************************************************************************/
bool Student::check_row_exist_f(int id, string f_course)
{
	bool flag = false;

	for (auto x : DataBase::finished_vector) {
		if (id == x.first && f_course == x.second) {
			flag = true;
		}
	}

	return flag;
}
/*****************************************************************************/
bool Student::check_row_exist_p(int id, string in_p_course)
{
	bool flag = false;

	for (auto x : DataBase::progress_vector) {
		if (id == x.first && in_p_course == x.second) {
			flag = true;
		}
	}

	return flag;
}
/*****************************************************************************/
Student::~Student() {
}