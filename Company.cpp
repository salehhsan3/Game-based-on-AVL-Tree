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
    StatusType Company::RemoveEmployee(int EmployeeID, int Salary){
        employees_by_id.removeNode(EmployeeID);
        employees_by_salary.removeNode(Salary);
        num_of_employees--;
        // this->highest_earner = *(employees_by_salary.max->data); // updateHighestEarnerafterRemove
        this->updateHighestEarner();
        return SUCCESS;

    }
    void Company::UpdateCompanyHighestEarnerAfterAddition(shared_ptr<Employee> emp)
    {
        if (this->highest_earner == nullptr)
        {
            this->highest_earner = emp;
            return;
        }
        if ( emp->getEmployeeSalary() > this->highest_earner->getEmployeeSalary() )
        {
            this->highest_earner = emp;
            return;
        }

        if ( (emp->getEmployeeSalary() == this->highest_earner->getEmployeeSalary()) 
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

    void Company::increasecompanyvalue(int increase)
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

    void Company::updateHighestEarner()
    {
        this->highest_earner = *(this->employees_by_salary.max->data);
        return;
    }

} // namespace MIVNI
