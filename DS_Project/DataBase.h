#pragma once
#include<iostream>
#include <unordered_map>
#include <string>
#include "Student.h"
#include "Course.h"
#include "Admin.h"
#include <map>
#include <vector>

using namespace std;

class DataBase
{
private:
	bool load_students_in_memory(std::map<std::string, Student>& students);
	bool load_courses_in_memory(std::map<std::string, Course>& courses);
	bool load_Admins_in_memory(std::map<std::string, Admin>& admins);
	bool load_FinishedCourse_in_memory(vector<pair<int, string>>& finished_vec);
	bool load_ProgressedCourse_in_memory(vector<pair<int, string>>& prog_vector);
	bool load_CoursesPREREQUISITE_in_memory(vector<pair<string, string>>& prerequisite_vector);
	void update_Student();
	void update_Course();
	void update_Admin();
	void update_prog_course();
	void update_preList_course();
	void update_finished_course();
public:
	static map<string, Student> students_map;
	static map<string, Course> courses_map;
	static map<string, Admin> admins_map;
	static vector<pair<int, string>> finished_vector;
	static vector<pair<int, string>> progress_vector;
	static vector<pair<string, string>> prerequisite_vector;
	///////////////////////////////////////////////////////////////////////
	void load_DB();
	void update_DB();
};
