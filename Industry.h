//
// Created by Saleh on 23/04/2022.
//

#ifndef DS_WET1_STOCKEXCHANGE_H
#define DS_WET1_STOCKEXCHANGE_H
#include "Company.h"
#include <memory>

using namespace std;
namespace MIVNI{

    class Industry
    {
    private:
        int num_of_workers;
        int num_of_companies_with_employees;
        std::Shared_ptr<Employee> highest_earner;
        AVL_Tree<int,Employee> workers_by_id;
        AVL_Tree<int,Employee> workers_by_grade;
        AVL_Tree<int,Company> companies;
        AVL_Tree<int,Company> companies_with_employees;

    public:
        Industry(
        // int num_of_workers,
        // int num_of_companies_with_employees,
        // Shared_ptr<Employee> highest_earner,
        // AVL_Tree<int,Employee> workers_by_id,
        // AVL_Tree<int,Employee> workers_by_grade,
        // AVL_Tree<int,Company> companies,
        // AVL_Tree<int,Company> companies_with_employees
        );
        Industry(const Industry& ind) = default;
        Industry& operator=(const Industry& ind) = default;
        ~Industry()= default;
        ~Industry();


        Industry *Init();

        StatusType AddCompany(int CompanyID, int Value);

        StatusType AddEmployee(int EmployeeID, int CompanyID, int Salary, int Grade);

        StatusType RemoveCompany(int CompanyID);

        StatusType RemoveEmployee(int EmployeeID);

        StatusType GetCompanyInfo(int CompanyID, int *Value, int *NumEmployees);

        StatusType GetEmployeeInfo(int EmployeeID, int *EmployerID, int *Salary, int *Grade);

        StatusType IncreaseCompanyValue(int CompanyID, int ValueIncrease);

        StatusType PromoteEmployee(int EmployeeID, int SalaryIncrease, int BumpGrade);

        StatusType HireEmployee(int EmployeeID, int NewCompanyID);

        StatusType AcquireCompany(int AcquirerID, int TargetID, double Factor);

        StatusType GetHighestEarner(int CompanyID, int *EmployeeID);

        StatusType GetAllEmployeesBySalary(int CompanyID, int **Employees, int *NumOfEmployees);

        StatusType GetHighestEarnerInEachCompany(int NumOfCompanies, int **Employees);

        StatusType GetNumEmployeesMatching(int CompanyID, int MinEmployeeID, int MaxEmployeeId,
                int MinSalary, int MinGrade, int *TotalNumOfEmployees, int *NumOfEmployees);


    };

}

#endif //DS_WET1_STOCKEXCHANGE_H