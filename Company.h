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
        shared_ptr<Employee> highest_earner;
        AVL_Tree<SalaryID,shared_ptr<Employee>> employees_by_salary;
        AVL_Tree<int,shared_ptr<Employee>> employees_by_id;

    public:
        // Company(int id, int val, int num_of_emp, shared_ptr<Employee> &highest_earner,
        //         AVL_Tree<int,shared_ptr<Employee>> *emp_by_salary, AVL_Tree<int,shared_ptr<Employee>> *emp_by_id):
        //     ID(id),
        //     value(val),
        //     num_of_employees(num_of_emp),
        //     highest_earner(highest_earner),
        //     employees_by_salary(emp_by_salary),
        //     employees_by_id(emp_by_id)
        // {}
        explicit Company(int id, int val,int num_of_employes = 0):
            ID(id),
            value(val),
            num_of_employees(num_of_employes),
            highest_earner(),
            employees_by_salary(),
            employees_by_id()
        {}
        ~Company() = default;

        void AddEmployee(int EmployeeID, int Salary, shared_ptr<Employee> emp, SalaryID salary_id);
        void RemoveEmployee(int EmployeeID, int Salary);
        void GetCompanyInfo(int CompanyID, int *Value, int *NumEmployees);
        void UpdateCompanyHighestEarnerAfterAddition(shared_ptr<Employee> emp);
        void UpdateCompanyHighestEarnerAfterRemove();
        void UpdateCompanyValue(int new_value);
        void updateHighestEarner();
        void updateNumOfEmployees(int new_num);
        int getCompanyID();
        int getCompanyValue();
        int getCompanyNumOfEmployees();
        void increasecompanyvalue(int increase);
        int getHighestEarnerID();
        shared_ptr<Employee> getHighestEarner();
        AVL_Tree<int,shared_ptr<Employee>>* getCompanyEmployeesTreeByID();
        void changeCompanyEmployeesTreeByID(AVL_Tree<int,shared_ptr<Employee>>& tree);
        AVL_Tree<SalaryID,shared_ptr<Employee>>* getCompanyEmployeesTreeBySalary();
        void changeCompanyEmployeesTreeBySalary(AVL_Tree<SalaryID,shared_ptr<Employee>>& tree);


    };


}

#endif //DS_WET1_COMPANY_H