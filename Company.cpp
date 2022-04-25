//
// Created by Saleh on 23/04/2022.
//
#include "Company.h"

namespace MIVNI
{
    StatusType Company::AddEmployee(int EmployeeID, int Grade, Employee& emp)
    {
        this->employees_by_id.addNode(EmployeeID,emp);
        this->employees_by_salary.addNode(Grade,emp);
        this->num_of_employees++;
        UpdateCompanyHighestEarnerAfterAddition(&emp);
        return SUCCESS;   
    }
    void Company::UpdateCompanyHighestEarnerAfterAddition(Employee* emp)
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
    StatusType RemoveEmployee(int EmployeeID);
    StatusType GetCompanyInfo(int CompanyID, int *Value, int *NumEmployees);
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
} // namespace MIVNI

