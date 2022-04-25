//
// Created by Saleh on 23/04/2022.
//
#include "Company.h"

namespace MIVNI
{
    StatusType Company::AddEmployee(int EmployeeID, int Salary, shared_ptr<Employee> emp)
    {
        this->employees_by_id.addNode(EmployeeID,emp);
        this->employees_by_salary.addNode(Salary,emp);
        this->num_of_employees++;
        UpdateCompanyHighestEarnerAfterAddition(emp);
        return SUCCESS;   


    }
    StatusType Company::RemoveEmployee(int EmployeeID){
        employees_by_id.removeNode(EmployeeID);
        employees_by_salary.removeNode(EmployeeID);
        num_of_employees--;
        return SUCCESS;

    }
    void Company::UpdateCompanyHighestEarnerAfterAddition(shared_ptr<Employee> emp)
    {
        if (this->highest_earner == nullptr)
        {
            this->highest_earner = emp;
            return;
        }
        if ( emp->getEmployeeGrade() > this->highest_earner->getEmployeeGrade() )
        {
            this->highest_earner = emp;
            return;
        }

        if ( (emp->getEmployeeGrade() == this->highest_earner->getEmployeeGrade()) 
                 && ( emp->getEmployeeID() < this->highest_earner->getEmployeeID() ) )

        {
            this->highest_earner = emp;
            return;
        }
        return;
    }
    int Company::getCompanyID()
    {
        return ID;
    }
    int Company::getCompanyValue()
    {
        return value;
    }
    int Company::getCompanyNumOfEmployees()
    {
        return num_of_employees;
    }

    int Company::increasecompanyvalue(int increase)
    {
        this->value += increase;
    }

    void Company::UpdateCompanyValue(int new_value){
        value = new_value;
    }

    int Company::getHighestEarnerID()
    {
        return (highest_earner->getEmployeeID());
    }

    AVL_Tree<int,shared_ptr<Employee>>* Company::getCompanyEmployeesTreeByID(){
        return &employees_by_id;
    }

} // namespace MIVNI
