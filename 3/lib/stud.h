#ifndef STUD_H
#define STUD_H

#include <iostream>
#include <string>
#include <vector>
#include "table.h"

namespace University 
{
	/*
	* @class Class for student with name and grades
	*/
    class Student {
        private:
            std::string surname, inits;
            std::vector <int> grades;
            int grades_num;
            void check_name();
        public:
            // constructors
            Student() = default;
            /*
            * @brief Constructor with name and number of grades fields
            * @param surname Surname of student
            * @param initials Initials
            * @param grades_num Number of grades
            */
            Student(std::string surname, std::string initials, int grades_num) : surname(surname), inits(initials), grades_num(grades_num) {check_name();};
            /*
            * @brief Constructor with name and grades fields
            * @param surname Surname of student
            * @param initials Initials
            * @param grades Vector of int - grades
            * @param num Number of the grades
            */		
            Student(std::string surname, std::string initials, std::vector <int> grades, int num) : 
                    surname(surname), inits(initials), grades_num(num), grades(grades) {check_name();};
            /*
            * @brief Moving constructor
            */
            Student(Student&& st) : surname(st.get_surname()), inits(st.get_initials()), 
                                    grades_num(st.get_grades_num()), grades(st.get_grades()) {};
            // setters & getters
            std::string get_surname() const {return surname;};
            std::string get_initials() const {return inits;};
            int get_grades_num() const {return grades_num;};
            std::vector <int> get_grades() const {return grades;};
            Student &set_surname(std::string sur);
            Student &set_initials(std::string ins);
            Student &set_grades(std::vector <int> &&grades_vect);
            // other
            /*
            * @brief Average grade of all grades
            * @return double Average number
            */
            double get_avr();
            /*
            * @brief Method for clearing grades vector and updating number of grades
            * @param num New number of grades
            */
            void refresh_grades(int num) {grades.clear(); grades_num = num;};
            explicit operator bool() {return !surname.empty();};
            // destructor
            virtual ~Student() = default;
    };

    /*
    * @struct Structure for Academic and Reserching Work
    */
    typedef struct AcademicWork {
        std::string topic, place;
        int grade;
        AcademicWork() {};
        AcademicWork(std::string t, std::string p, int g) : topic(t), place(p), grade(g) {};
    } AcademicWork;

    class Senior : public Student {
        private:
            AcademicWork arw;
        public:
            // constructors
            Senior(std::string surname, std::string ins, int grades_num) : Student(surname, ins, grades_num) {};
            Senior(std::string surname, std::string ins, int grades_num, std::string topic) : Student(surname, ins, grades_num) {arw.topic = topic;};
            Senior(std::string surname, std::string ins, int grades_num, std::string topic, std::string place, int grade) :
                    Student(surname, ins, grades_num), arw(topic, place, grade) {};
            Senior(Student &stud) : Student(std::move(stud)) {};
            Senior(Student &stud, std::string topic) : Student(std::move(stud)) {arw.topic = topic;};
            Senior(Senior &&s) noexcept;
            // setters & getters
            AcademicWork get_arw() const {return arw;};
            std::string get_topic() const {return arw.topic;};
            std::string get_place() const {return arw.place;};
            int get_arw_grade() const {return arw.grade;};
            Senior &set_arw(std::string topic, std::string place, int grade);
            Senior &set_topic(std::string topic);
            Senior &set_place(std::string place);
            Senior &set_arw_grade(int grade);
            // destructor
            ~Senior() override = default;
    };
}

#endif
