//
// Created by Saleh on 23/04/2022.
//

#ifndef DS_WET1_COMPANY_H
#define DS_WET1_COMPANY_H

#include "Employee.h"
#include "AO_AVL_Tree.h"
using namespace std;

namespace MIVNI{


    class Company
    {
    private:
        int ID;
        int value;
        int num_of_employees;
        Shared_ptr<Employee> highest_earner;
        AVL_Tree<int,Employee> employees_by_grade;
        AVL_Tree<int,Employee> employees_by_id;

    public:
        Company(int id, int val, int num_of_emp, std::shared_ptr<Employee> highest_earner,
                    AVL_Tree<int,Employee> emp_by_grade, AVL_Tree<int,Employee> emp_by_id){}
        ~Company();
    };
    
    
}

#endif //DS_WET1_COMPANY_H
