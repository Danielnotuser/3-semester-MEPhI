#include "../lib/stud.h"
#include "../lib/group.h"

namespace University
{
    std::string Group::key(std::shared_ptr<Student> &st)
    {
        return st->get_surname();
    }

    Group::Group(std::string index, int sem) : index(index), grades_num(0), sem(sem) 
    {
    	studs = Table<std::shared_ptr<Student>, std::string>(key);
    }
    
    Group::Group(std::string index, std::vector<std::shared_ptr<Student>> vect, int sem) :
        index(index), sem(sem)
    {
        int max = grades_num;
        for (int i = 0; i < vect.size(); i++)
            if (vect[i]->get_grades_num() > max) max = vect[i]->get_grades_num();
        studs = Table<std::shared_ptr<Student>, std::string>(vect, key);
    }

    Group::Group(std::string index, Table <std::shared_ptr<Student>, std::string> studs, int sem) :
        index(index), studs(std::move(studs)), sem(sem)
    {
        int max = grades_num;
        for (auto it = studs.begin(); it != studs.end(); it++)
            if ((*it)->get_grades_num() > max) max = (*it)->get_grades_num();
    }

    Group &Group::operator=(Group&& gr) noexcept
    {
        index = std::move(gr.index);
        grades_num = gr.grades_num;
        sem = gr.sem;
        studs = std::move(gr.studs);
        gr.studs = Table<std::shared_ptr<Student>, std::string>(University::Group::key);
        return *this;
    }

    Group::operator bool() {
        return !(studs.is_empty());
    }

}
