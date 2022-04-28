//
// Created by Saleh on 23/04/2022.
//

#ifndef DS_WET1_STOCKEXCHANGE_H
#define DS_WET1_STOCKEXCHANGE_H
#include "Company.h"
#include "library1.h"

using namespace std;
namespace MIVNI{

    class Industry
    {
    private:
        int num_of_workers;
        int num_of_companies_with_employees;
        shared_ptr<Employee> highest_earner;
        AVL_Tree<int,shared_ptr<Employee>> workers_by_id;
        AVL_Tree<SalaryID,shared_ptr<Employee>> workers_by_salary;
        AVL_Tree<int,shared_ptr<Company>> companies;
        AVL_Tree<int,shared_ptr<Company>> companies_with_employees;

    public:
        Industry();
        Industry(const Industry& ind) = default;
        Industry& operator=(const Industry& ind) = default;
        ~Industry()= default;


        static void getEmployeesBySalary(tree_node<SalaryID,shared_ptr<Employee>>* node, int *Employees, int *index);

        static int countEmployeesByID(tree_node<int,shared_ptr<Employee>>* node, int MinEmployeeID, int MaxEmployeeId);

        static void getEmployeesByIDInArray(tree_node<int,shared_ptr<Employee>>* node, shared_ptr<Employee> *Employees, int *index, int MinEmployeeID, int MaxEmployeeId);

        static int getEmployeesWithMinSalaryAndGrade(shared_ptr<Employee> *Employees, int size, int MinSalary, int MinGrade);

        void UpdateIndustryHighestEarnerAfterRemove(Employee& emp);

        void getHighestEarnerInEachCompanyIntoArray(int *index, int max_index,tree_node<int,shared_ptr<Company>>* node, int *Employees);

        void updateHighestEarner();

        static int countNodes(tree_node<int,shared_ptr<Company>> *node);

        void visitInOrder3(shared_ptr<Employee> * array, tree_node<SalaryID, shared_ptr<Employee> >* node, int* counter_ptr, int num);

        void merge_func(shared_ptr<Employee> arr1[], shared_ptr<Employee> arr2[] ,int n1, int n2,
                        shared_ptr<Employee>  arr3[]);

        void merge_func_by_id(shared_ptr<Employee> arr1[], shared_ptr<Employee> arr2[] ,int n1, int n2,
                                shared_ptr<Employee>  arr3[]);

        void visitInOrder2(shared_ptr<Employee> * array, tree_node<int, shared_ptr<Employee> >* node, int* counter_ptr, int num);

        void addEmployeeToIndustry(int EmployeeID, shared_ptr<Employee> emp, SalaryID salaryId);

        void removeEmployeeFromIndustry(int EmployeeID, SalaryID salaryId);
        
        tree_node<int, shared_ptr<Employee>>* createFromSortedArrAuxForID(shared_ptr<Employee> array[], int start,
                                                              int end, tree_node<int, shared_ptr<Employee>> *parent);

        AVL_Tree<int, shared_ptr<Employee>>* createFromSortedArrForID(shared_ptr<Employee> array[], int start, int end);

        tree_node<SalaryID, shared_ptr<Employee>>* createFromSortedArrAuxForSalary(shared_ptr<Employee> array[], int start,
                                                              int end, tree_node<SalaryID, shared_ptr<Employee>> *parent);

        AVL_Tree<SalaryID, shared_ptr<Employee>>* createFromSortedArrForSalary(shared_ptr<Employee> array[], int start, int end);

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
        tree_node<int,shared_ptr<Employee>>* findLCA(tree_node<int,shared_ptr<Employee>> *root, int MinID, int MaxID);

    };

}

#endif //DS_WET1_STOCKEXCHANGE_H