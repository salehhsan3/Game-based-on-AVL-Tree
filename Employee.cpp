//
// Created by Saleh on 23/04/2022.
//
#include "Employee.h"

namespace MIVNI
{
    int Employee::getEmployeeID()
    {
        return ID;
    }
    int Employee::getEmployeeGrade()
    {
        return grade;
    }
    int Employee::getEmployeeSalary()
    {
        return salary;
    }
    int Employee::getEmployersid()
    {
        return company_id;
    }
    void Employee::increaseSalary(int increase)
    {
        this->salary += increase;
        return;
    }
    void Employee::bumpGrade(int bump)
    {
        if (bump > 0)
        {
            this->grade++;
        }
        return;
    }
    void Employee::promote(int increase, int bump)
    {
        this->increaseSalary(increase);
        this->bumpGrade(bump);
        return;
    }
    void Employee::UpdateCompanyID(int NewID)
    {
        this->company_id = NewID;
    }

} // namespace MIVNI
