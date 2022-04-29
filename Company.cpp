//
// Created by Saleh on 23/04/2022.
//
#include "Company.h"

namespace MIVNI
{
    void Company::AddEmployee(int EmployeeID,  shared_ptr<Employee> emp, SalaryID salaryId)
    {
        this->employees_by_id.addNode(EmployeeID,emp);
        this->employees_by_salary.addNode(salaryId,emp);
        this->num_of_employees++;
        this->updateHighestEarner();
        return;   
    }

    void Company::AddEmployeeToSalaryTree(SalaryID sal_id, shared_ptr<Employee> emp)
    {
        this->employees_by_salary.addNode(sal_id,emp);
        // this->employees_by_id.addNode(sal_id.getID(),emp);
        this->updateHighestEarner();
        return;
    }
    
    tree_node<int,shared_ptr<Employee>> *Company::AddEmployeeToIDTree(int id, shared_ptr<Employee> emp)
    {
        return(this->employees_by_id.addNode(id,emp));
    }

    tree_node<int,shared_ptr<Employee>> *Company::getEmployeeTreeByIDRoot()
    {
        return(this->employees_by_id.root);
    }

    void Company::RemoveEmployeeFromSalaryTree(SalaryID sal_id)
    {
        this->employees_by_salary.removeNode(sal_id);
        this->updateHighestEarner();
        return;


    }
    void Company::RemoveEmployee(int EmployeeID, int Salary){
        SalaryID sal_id = SalaryID(Salary, EmployeeID);
        employees_by_id.removeNode(EmployeeID);
        employees_by_salary.removeNode(sal_id);
        num_of_employees--;
        this->updateHighestEarner();
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
        return this->num_of_employees;
    }

    void Company::increasecompanyvalue(int increase)
    {
        this->value+=increase;
    }

    void Company::UpdateCompanyValue(int new_value){
        this->value=new_value;
    }

    int Company::getHighestEarnerID()
    {
        return (highest_earner->getEmployeeID());
    }

    void Company::updateNumOfEmployees(int new_num)
    {
        this->num_of_employees = new_num;
        return;
    }

    AVL_Tree<int,shared_ptr<Employee>>* Company::getCompanyEmployeesTreeByID(){
        return &(this->employees_by_id);
    }

    AVL_Tree<SalaryID,shared_ptr<Employee>>* Company::getCompanyEmployeesTreeBySalary(){
        return &(this->employees_by_salary);
    }

    void Company::updateHighestEarner()
    {
        if (this->employees_by_salary.max != nullptr){
            this->highest_earner = *(this->employees_by_salary.max->data);
        }
        else
        {
            this->highest_earner = nullptr;
        }
        return;
    }
    void Company::changeCompanyEmployeesTreeByID(AVL_Tree<int,shared_ptr<Employee>>* tree)
    {
        // review later!
        this->employees_by_id.treeClear();
        this->employees_by_id = *tree;
        return;
    }
    void Company::changeCompanyEmployeesTreeBySalary(AVL_Tree<SalaryID,shared_ptr<Employee>>* tree)
    {
        this->employees_by_salary.treeClear();
        this->employees_by_salary = *tree;
        return;
    }


} // namespace MIVNI
