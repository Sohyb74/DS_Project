#include "DataBase.h"
#include"sqlite/sqlite3.h"
#include <string>
#include<iostream>
#include"vector"
using namespace std;
static sqlite3* DB{};
/////////////////////////////////////////////////////////////////////////////////////////
map<string,Student>DataBase::students_map;
map<string,Course>DataBase::courses_map;
map<string,Admin>DataBase::admins_map;
vector<pair<int,string>>DataBase::finished_vector;
vector<pair<int,string>>DataBase::progress_vector;
vector<pair<string,string>>DataBase::prerequisite_vector;
/////////////////////////////////////////////////////////////////////////////////////////
void DataBase::load_DB() {
	sqlite3_open("myDb.db", &DB);
	load_students_in_memory(students_map);
	load_courses_in_memory(courses_map);
	load_Admins_in_memory(admins_map);
	load_FinishedCourse_in_memory(finished_vector);
	load_ProgressedCourse_in_memory(progress_vector);
	load_CoursesPREREQUISITE_in_memory(prerequisite_vector);
	sqlite3_close(DB);
}
/////////////////////////////////////////////////////////////////////////////////////////
bool DataBase::load_students_in_memory(std::map<std::string, Student>& students) // load student Data
{
	sqlite3_stmt* result;
	// construct query
	string sql("SELECT * FROM STUDENT;");
	// execute prepared query
	int exec = sqlite3_prepare_v2(DB, sql.c_str(), -1, &result, NULL);
	// check query status
	if (exec != SQLITE_OK) {
		std::cerr << "Error:  " << sqlite3_errmsg(DB) << std::endl;
		return false;
	}
	while ((exec = sqlite3_step(result)) == SQLITE_ROW) {
		std::string id = std::string(reinterpret_cast<const char*>(sqlite3_column_text(result, 0)));
		// create student object
		Student student;
		student.set_student_id(stoi(id)); // set id
		student.set_f_name(std::string(reinterpret_cast<const char*>(sqlite3_column_text(result, 1))));//set id
		student.set_s_name(std::string(reinterpret_cast<const char*>(sqlite3_column_text(result, 2))));
		student.set_th_name(std::string(reinterpret_cast<const char*>(sqlite3_column_text(result, 3))));//set student name
		student.set_student_password(string(reinterpret_cast<const char*>(sqlite3_column_text(result, 4)))); //set student password
		student.set_acadamic_year(std::string(reinterpret_cast<const char*>(sqlite3_column_text(result, 5)))); //set student academic_year
		// load student to students hash tables
		students[id] = student;
	}
	return true;
}
/////////////////////////////////////////////////////////////////////////////////////////
bool DataBase::load_courses_in_memory(std::map<std::string, Course>& courses) // load course data
{
	sqlite3_stmt* result;
	// construct query
	string sql("SELECT * FROM COURSE;");
	// execute prepared query
	int exec = sqlite3_prepare_v2(DB, sql.c_str(), -1, &result, NULL);
	// check query status
	if (exec != SQLITE_OK) {
		std::cerr << "Error:  " << sqlite3_errmsg(DB) << std::endl;
		return false;
	}

	while ((exec = sqlite3_step(result)) == SQLITE_ROW) {
		std::string code = std::string(reinterpret_cast<const char*>(sqlite3_column_text(result, 0)));

		// create course object
		Course course;

		course.set_code(code); // set code
		course.set_Course_Name(std::string(reinterpret_cast<const char*>(sqlite3_column_text(result, 1))));// set course name
		course.set_hours(stoi(reinterpret_cast<const char*>(sqlite3_column_text(result, 2))));// set course hours
		course.set_max_numstud(stoi(reinterpret_cast<const char*>(sqlite3_column_text(result, 3))));// set course max num of student

		// load student to students hash tables
		courses[code] = course;
	}
	return true;
}
/////////////////////////////////////////////////////////////////////////////////////////
bool DataBase::load_Admins_in_memory(std::map<std::string, Admin>& admins) // load Admin Data
{
	sqlite3_stmt* result;
	// construct query
	string sql("SELECT * FROM Admin;");
	// execute prepared query
	int exec = sqlite3_prepare_v2(DB, sql.c_str(), -1, &result, NULL);
	// check query status
	if (exec != SQLITE_OK) {
		std::cerr << "Error:  " << sqlite3_errmsg(DB) << std::endl;
		return false;
	}

	while ((exec = sqlite3_step(result)) == SQLITE_ROW) {
		std::string id = std::string(reinterpret_cast<const char*>(sqlite3_column_text(result, 0)));

		// create student object
		Admin admin;

		admin.set_admin_id(stoi(id)); // set  admin id
		admin.set_fname(std::string(reinterpret_cast<const char*>(sqlite3_column_text(result, 1))));//set admin first name
		admin.set_lname(std::string(reinterpret_cast<const char*>(sqlite3_column_text(result, 2))));//set admin last name
		admin.set_admin_pass(std::string(reinterpret_cast<const char*>(sqlite3_column_text(result, 3))));// set admin  password

		 // load student to students hash tables
		admins[id] = admin;

		//printf("Admin: %s loaded successfully.\n", sqlite3_column_text(result, 1));
	}

	return true;
}
/////////////////////////////////////////////////////////////////////////////////////////
bool DataBase::load_FinishedCourse_in_memory(vector<pair<int, string>>& finished_vec) // load course data
{
	sqlite3_stmt* result;
	// construct query
	string sql("SELECT * FROM COURSE_FINSHED ;");
	// execute prepared query
	int exec = sqlite3_prepare_v2(DB, sql.c_str(), -1, &result, NULL);
	// check query status
	if (exec != SQLITE_OK) {
		std::cerr << "Error:  " << sqlite3_errmsg(DB) << std::endl;
		return false;
	}

	while ((exec = sqlite3_step(result)) == SQLITE_ROW) {
		int id_stud = stoi(reinterpret_cast<const char*>(sqlite3_column_text(result, 0)));
		string Fcourse_name = (std::string(reinterpret_cast<const char*>(sqlite3_column_text(result, 1))));
		finished_vec.push_back(make_pair(id_stud, Fcourse_name));

		//printf("Finished Courses: %s loaded successfully.\n", sqlite3_column_text(result, 1));
	}

	return true;
}
/////////////////////////////////////////////////////////////////////////////////////////
bool DataBase::load_ProgressedCourse_in_memory(vector<pair<int, string>>& prog_vector) {
	int exit = 0;
	sqlite3* DB{};
	exit = sqlite3_open("myDb.db", &DB);
	sqlite3_stmt* result;
	// construct query
	string sql("SELECT * FROM COURSE_PROG ;");
	// execute prepared query
	int exec = sqlite3_prepare_v2(DB, sql.c_str(), -1, &result, NULL);
	// check query status
	if (exec != SQLITE_OK) {
		std::cerr << "Error:  " << sqlite3_errmsg(DB) << std::endl;
		return false;
	}

	while ((exec = sqlite3_step(result)) == SQLITE_ROW) {
		int id_stud = stoi(reinterpret_cast<const char*>(sqlite3_column_text(result, 0)));
		string Pcourse_name = (std::string(reinterpret_cast<const char*>(sqlite3_column_text(result, 1))));
		prog_vector.push_back(make_pair(id_stud, Pcourse_name));

		//printf("Progressed Courses: %s loaded successfully.\n", sqlite3_column_text(result, 1));
	}
	sqlite3_close(DB);
	return true;
}
/////////////////////////////////////////////////////////////////////////////////////////
bool DataBase::load_CoursesPREREQUISITE_in_memory(vector<pair<string, string>>& prerequisite_vector)
{
	int exit = 0;
	sqlite3* DB{};
	exit = sqlite3_open("myDb.db", &DB);
	sqlite3_stmt* result;
	// construct query
	string sql("SELECT * FROM COURSE_PREREQUISITE ;");
	// execute prepared query
	int exec = sqlite3_prepare_v2(DB, sql.c_str(), -1, &result, NULL);
	// check query status
	if (exec != SQLITE_OK) {
		std::cerr << "Error:  " << sqlite3_errmsg(DB) << std::endl;
		return false;
	}

	while ((exec = sqlite3_step(result)) == SQLITE_ROW) {
		string course_name = (std::string(reinterpret_cast<const char*>(sqlite3_column_text(result, 0))));
		string preq_list_name = (std::string(reinterpret_cast<const char*>(sqlite3_column_text(result, 1))));
		prerequisite_vector.push_back(make_pair(course_name, preq_list_name));

		//printf("PreqList Courses: %s loaded successfully.\n", sqlite3_column_text(result, 1));
	}
	sqlite3_close(DB);
	return true;
}
/////////////////////////////////////////////////////////////////////////////////////////
/***************************************************************************************/
/////////////////////////////////////////////////////////////////////////////////////////
/***************************************************************************************/
void DataBase::update_DB() {
	sqlite3_open("myDb.db", &DB);
	Student s;
	if (s.STUDENT_CHANGED == true) { update_Student(); }
	Admin a;
	if (a.ADMIN_CHANGED == true) { update_Admin(); }
	Course c;
	if (c.COURSE_CHANGED == true) { update_Course(); }
	if (a.PRE_LIST_CHANGED == true) { update_preList_course(); }
	update_prog_course();
	update_finished_course();
	sqlite3_close(DB);
}
/////////////////////////////////////////////////////////////////////////////////////////
void DataBase::update_Student() {
	sqlite3_stmt* result;
	// construct query
	string sql("DELETE FROM STUDENT;");
	// execute prepared query
	int rc = sqlite3_exec(DB, sql.c_str(), NULL, NULL, 0);
	// check query status
	if (rc != SQLITE_OK) {
		std::cerr << "Error:  " << sqlite3_errmsg(DB) << std::endl;
	}

	string query;
	for (auto x : students_map) {
		query = "insert into STUDENT VALUES('" + x.first + "', '" + x.second.get_f_name() + "','" + x.second.get_s_name() + "','" + x.second.get_th_name() + "','" + x.second.get_student_password() + "','" + x.second.get_acadamic_year() + "'); ";
		rc = sqlite3_exec(DB, query.c_str(), NULL, NULL, 0);
	}

	if (rc != SQLITE_OK) {
		std::cerr << "Error:  " << sqlite3_errmsg(DB) << std::endl;
	}
}
/////////////////////////////////////////////////////////////////////////////////////////
void DataBase::update_Course() {
	sqlite3_stmt* result;
	// construct query
	string sql("DELETE FROM COURSE;");
	// execute prepared query
	int rc = sqlite3_exec(DB, sql.c_str(), NULL, NULL, 0);
	// check query status
	if (rc != SQLITE_OK) {
		std::cerr << "Error:  " << sqlite3_errmsg(DB) << std::endl;
	}
	string query;
	for (auto x : courses_map) {
		query = "insert into COURSE VALUES('" + x.first + "','" + x.second.get_Course_name() + "','" + to_string(x.second.get_hours()) + "','" + to_string(x.second.get_max_numstud()) + "');";
		rc = sqlite3_exec(DB, query.c_str(), NULL, NULL, 0);
	}

	if (rc != SQLITE_OK) {
		std::cerr << "Error:  " << sqlite3_errmsg(DB) << std::endl;
	}
}
/////////////////////////////////////////////////////////////////////////////////////////
void DataBase::update_Admin() {
	sqlite3_stmt* result;
	// construct query
	string sql("DELETE FROM ADMIN;");
	// execute prepared query
	int rc = sqlite3_exec(DB, sql.c_str(), NULL, NULL, 0);
	// check query status
	if (rc != SQLITE_OK) {
		std::cerr << "Error:  " << sqlite3_errmsg(DB) << std::endl;
	}
	string query;
	for (auto x : admins_map) {
		query = "insert into ADMIN VALUES('" + x.first + "','" + x.second.get_fname() + "','" + x.second.get_lname() + "','" + "1879" + "');";
		rc = sqlite3_exec(DB, query.c_str(), NULL, NULL, 0);
	}

	if (rc != SQLITE_OK) {
		std::cerr << "Error:  " << sqlite3_errmsg(DB) << std::endl;
	}
}
/////////////////////////////////////////////////////////////////////////////////////////
void DataBase::update_prog_course() {
	sqlite3_stmt* result;
	// construct query
	string sql("DELETE FROM COURSE_PROG;");
	// execute prepared query
	int rc = sqlite3_exec(DB, sql.c_str(), NULL, NULL, 0);
	// check query status
	if (rc != SQLITE_OK) {
		std::cerr << "Error:  " << sqlite3_errmsg(DB) << std::endl;
	}
	string query;
	for (auto x : progress_vector) {
		query = "insert into COURSE_PROG VALUES('" + to_string(x.first) + "','" + x.second + "'); ";
		rc = sqlite3_exec(DB, query.c_str(), NULL, NULL, 0);
	}

	if (rc != SQLITE_OK) {
		std::cerr << "Error:  " << sqlite3_errmsg(DB) << std::endl;
	}
}
/////////////////////////////////////////////////////////////////////////////////////////
void DataBase::update_finished_course() {
	sqlite3_stmt* result;
	// construct query
	string sql("DELETE FROM COURSE_FINSHED;");
	// execute prepared query
	int rc = sqlite3_exec(DB, sql.c_str(), NULL, NULL, 0);
	// check query status
	if (rc != SQLITE_OK) {
		std::cerr << "Error:  " << sqlite3_errmsg(DB) << std::endl;
	}
	string query;
	for (auto x : finished_vector) {
		query = "insert into COURSE_FINSHED VALUES('" + to_string(x.first) + "','" + x.second + "'); ";
		rc = sqlite3_exec(DB, query.c_str(), NULL, NULL, 0);
	}

	if (rc != SQLITE_OK) {
		std::cerr << "Error:  " << sqlite3_errmsg(DB) << std::endl;
	}
}
/////////////////////////////////////////////////////////////////////////////////////////
void DataBase::update_preList_course() {
	sqlite3_stmt* result;
	// construct query
	string sql("DELETE FROM COURSE_PREREQUISITE;");
	// execute prepared query
	int rc = sqlite3_exec(DB, sql.c_str(), NULL, NULL, 0);
	// check query status
	if (rc != SQLITE_OK) {
		std::cerr << "Error:  " << sqlite3_errmsg(DB) << std::endl;
	}
	string query;
	for (auto x : prerequisite_vector) {
		query = "insert into COURSE_PREREQUISITE VALUES('" + x.first + "','" + x.second + "'); ";
		rc = sqlite3_exec(DB, query.c_str(), NULL, NULL, 0);
	}

	if (rc != SQLITE_OK) {
		std::cerr << "Error:  " << sqlite3_errmsg(DB) << std::endl;
	}
}
/////////////////////////////////////////////////////////////////////////////////////////