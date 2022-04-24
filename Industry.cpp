//
// Created by Saleh on 23/04/2022.
//
#include "Industry.h"

namespace MIVNI
{

    Industry::Industry():
        num_of_workers(),
        num_of_companies_with_employees(),
        highest_earner(),
        workers_by_id(),
        workers_by_grade(),
        companies(),
        companies_with_employees()
    {}

    Industry* Init()
    {
        return ( new Industry() );
    }



    StatusType Industry::AddEmployee(int EmployeeID, int CompanyID, int Salary, int Grade)
    {
        if (EmployeeID <= 0 || CompanyID <= 0 || Salary <= 0 || Grade < 0)
        {
            return INVALID_INPUT;
        }

        Employee* emp_to_find = this->workers_by_id.findNode(EmployeeID)->data;
        Company* comp_to_find = this->companies.findNode(CompanyID)->data;
        if (emp_to_find != nullptr || comp_to_find == nullptr)
        {
            return FAILURE;
        }
        
       
        Employee emp_to_add = Employee(EmployeeID,Salary,Grade,CompanyID);

        this->workers_by_id.addNode(EmployeeID,emp_to_add);
        this->workers_by_grade.addNode(Grade,emp_to_add);
        if(comp_to_find->getCompanyNumOfEmployees() == 0)
        {
            this->companies_with_employees.addNode(CompanyID,*comp_to_find);
        }
        comp_to_find->AddEmployee(EmployeeID,Grade,emp_to_add);
        this->num_of_workers++;
        comp_to_find->UpdateCompanyHighestEarnerAfterAddition();
      
        
    } 
} // namespace MIVNI

