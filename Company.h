//
// Created by Saleh on 23/04/2022.
//

#ifndef DS_WET1_COMPANY_H
#define DS_WET1_COMPANY_H

#include "Employee.h"
#include <memory>
#include "AO_AVL_Tree.h"
using namespace std;

namespace MIVNI{


    class Company
    {
    private:
        int ID;
        int value;
        int num_of_employees;
        Employee* highest_earner;
        AVL_Tree<int,Employee> employees_by_salary;
        AVL_Tree<int,Employee> employees_by_id;

    public:
        Company(int id, int val, int num_of_emp, std::shared_ptr<Employee> highest_earner,
                AVL_Tree<int,Employee> emp_by_salary, AVL_Tree<int,Employee> emp_by_id):
            ID(id),
            value(val),
            num_of_employees(num_of_emp),
            highest_earner(),
            employees_by_salary(),
            employees_by_id()
        {}
        explicit Company(int id, int val):
            ID(id),
            value(val),
            num_of_employees(),
            highest_earner(),
            employees_by_salary(),
            employees_by_id()
        {}
        ~Company();

        StatusType AddEmployee(int EmployeeID, int Salary, Employee& emp);
        StatusType RemoveEmployee(int EmployeeID);
        StatusType GetCompanyInfo(int CompanyID, int *Value, int *NumEmployees);
        void UpdateCompanyHighestEarnerAfterAddition(Employee* emp);
        void UpdateCompanyHighestEarnerAfterRemove();
        Employee* getHighestEarner();
        int getCompanyID();
        int getCompanyValue();
        int getCompanyNumOfEmployees();
        int increasecompanyvalue(int increase);
        void UpdateCompanyValue(int new_value);
        AVL_Tree<int,Employee>* getCompanyEmployeesTreeByID();
        AVL_Tree<int,Employee>* getCompanyEmployeesTreeBySalary();


    };


}

#endif //DS_WET1_COMPANY_H