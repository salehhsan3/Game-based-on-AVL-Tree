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
        workers_by_salary(),
        companies(),
        companies_with_employees()
    {}

    Industry* Init()
    {
        return ( new Industry() );
    }

    void Industry::UpdateIndustryHighestEarnerAfterAddition(Employee* emp)
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

    StatusType Industry::AddEmployee(int EmployeeID, int CompanyID, int Salary, int Grade)
    {
        if (EmployeeID <= 0 || CompanyID <= 0 || Salary <= 0 || Grade < 0)
        {
            return INVALID_INPUT;
        }
        if ( this->workers_by_id.findNode(EmployeeID) != nullptr || this->companies.findNode(CompanyID) == nullptr)
        {
            return FAILURE;
        }
        Employee* emp_to_find = this->workers_by_id.findNode(EmployeeID)->data;
        Company* comp_to_find = this->companies.findNode(CompanyID)->data;
        
       
        Employee emp_to_add = Employee(EmployeeID,Salary,Grade,CompanyID);

        if(comp_to_find->getCompanyNumOfEmployees() == 0)
        {
            this->companies_with_employees.addNode(CompanyID,*comp_to_find);
        }
        comp_to_find->AddEmployee(EmployeeID,Grade,emp_to_add);

        this->workers_by_id.addNode(EmployeeID,emp_to_add);
        this->workers_by_salary.addNode(Grade,emp_to_add);
        this->num_of_workers++;
        this->UpdateIndustryHighestEarnerAfterAddition(&emp_to_add);
    } 
    StatusType Industry::RemoveCompany(int CompanyID)
    {
        if (CompanyID <= 0)
        {
            return INVALID_INPUT;
        }
        if (this->companies.findNode(CompanyID) == nullptr)
        {
            return FAILURE;
        }
        Company* comp = this->companies.findNode(CompanyID)->data;

        int num_of_employees = comp->getCompanyNumOfEmployees();

         if (num_of_employees > 0)
        {
            return FAILURE;
        }
        this->companies.removeNode(CompanyID);
        return SUCCESS;
    }

    StatusType Industry::IncreaseCompanyValue(int CompanyID, int ValueIncrease)
    {
        if (CompanyID <= 0 || ValueIncrease <= 0)
        {
            return INVALID_INPUT;
        }
        if (this->companies.findNode(CompanyID) == nullptr)
        {
            return FAILURE;
        }
        Company* comp = this->companies.findNode(CompanyID)->data;
        comp->increasecompanyvalue(ValueIncrease);
        return SUCCESS;
    }

    StatusType Industry::PromoteEmployee(int EmployeeID, int SalaryIncrease, int BumpGrade)
    {
        if (EmployeeID <= 0 ||SalaryIncrease <= 0)
        {
            return INVALID_INPUT;
        }
        
        if (this->workers_by_id.findNode(EmployeeID) == nullptr)
        {
            return FAILURE;
        }
        Employee* emp = this->workers_by_id.findNode(EmployeeID)->data;
        emp->promote(SalaryIncrease,BumpGrade);
        return SUCCESS;
    }

    StatusType Industry::GetHighestEarner(int CompanyID, int *EmployeeID)
    {
        if (EmployeeID == NULL || CompanyID == 0)
        {
            return INVALID_INPUT;
        }
        if (CompanyID < 0)
        {
            if ( (this->num_of_workers == 0) )
            {
                return FAILURE;
            }
            
            *EmployeeID = (this->highest_earner->getEmployeeID());
            return SUCCESS;
        }
        tree_node<int,Company>* comp_node = this->companies.findNode(CompanyID);
        if (comp_node == nullptr || 
        ( (CompanyID > 0) && (comp_node->data->getCompanyNumOfEmployees() == 0) )  )
        {
            return FAILURE;
        }
        *EmployeeID = ( comp_node->data->getHighestEarner()->getEmployeeID() );
        return SUCCESS;
    }

    void getEmployeesBySalary(tree_node<int,Employee>* node, int *Employees, int *index)
    {
        if(node == nullptr)
        {
            return;
        }
        getEmployeesBySalary(node->left_son,Employees,index);
        Employees[*index] = node->data->getEmployeeID();
        (*index)++;
        getEmployeesBySalary(node->right_son,Employees,index);
    }

    StatusType Industry::GetAllEmployeesBySalary(int CompanyID, int **Employees, int *NumOfEmployees)
    {
        if (Employees == NULL || NumOfEmployees == NULL || CompanyID == 0)
        {
            return INVALID_INPUT;
        }
        if ( (CompanyID < 0) && (this->num_of_workers == 0))
        {
            return FAILURE;
        }
        tree_node<int,Company>* comp_node = this->companies.findNode(CompanyID);
        if (comp_node == nullptr || 
        ( (CompanyID > 0) && (comp_node->data->getCompanyNumOfEmployees() == 0) )  )
        {
            return FAILURE;
        }

        if (CompanyID < 0)
        {
            *Employees = (int*)malloc(this->num_of_workers*sizeof(int));
            if (*Employees == NULL)
            {
                return ALLOCATION_ERROR;
            }
            getEmployeesBySalary(this->workers_by_salary.root,(*Employees),0);
            return SUCCESS;
        }

        if (CompanyID > 0)
        {
            Company* comp = comp_node->data;
            *Employees = (int*)malloc(comp->getCompanyNumOfEmployees()*sizeof(int));
            if (*Employees == NULL)
            {
                return ALLOCATION_ERROR;
            }
            getEmployeesBySalary(comp->getCompanyEmployeesTreeBySalary()->root,(*Employees),0);
            return SUCCESS;
        }
        
    }

        StatusType Industry::GetHighestEarnerInEachCompany(int NumOfCompanies, int **Employees)
        {
            if (Employees == NULL || NumOfCompanies < 1)
            {
                return INVALID_INPUT;
            }
            if (this->companies_with_employees.root == nullptr)
            {
                return FAILURE;
            }
            
            
        }

} // namespace MIVNI

