//
// Created by Saleh on 23/04/2022.
//

#include <memory>
#include "Industry.h"

namespace MIVNI{

    void merge_func(Employee arr1[], Employee arr2[] ,int n1, int n2,
                    Employee arr3[]){
        int i = 0, j = 0, k = 0;

        while (i<n1 && j <n2)
        {
            if ((arr1[i]) < (arr2[j]))
                arr3[k++] = arr1[i++];
            else
                arr3[k++] = arr2[j++];
        }

        // Store remaining elements of first array
        while (i < n1)
            arr3[k++] = arr1[i++];

        // Store remaining elements of second array
        while (j < n2)
            arr3[k++] = arr2[j++];
    }


    tree_node<player_level, std::shared_ptr<player_level>>* createFromSortedArrAux(Employee array[], int start,
                                                                                   int end, tree_node<int, Employee>*parent){
        if(start > end)
            return nullptr;
        int mid = (start+end)/2;
        tree_node<int, Employee>* new_node = new tree_node<int, Employee>(*(array[mid])
                ,array[mid],parent, nullptr, nullptr, 0);
        new_node->left_son = createFromSortedArrAux(array, start, mid-1, new_node);
        new_node->right_son = createFromSortedArrAux(array, mid+1, end, new_node);
        new_node->updateHeight();
        return new_node;
    }

    AVL_Tree<player_level, std::shared_ptr<player_level>>* createFromSortedArr(Employee array[], int start, int end){
        AVL_Tree<int, Employee>* new_tree = new AVL_Tree<int, Employee>();
        new_tree->root = createFromSortedArrAux(array, start, end, nullptr);
        new_tree->max = new_tree->root->findMax();
        new_tree->min = new_tree->root->findMin();
        new_tree->size = end+1;
        return new_tree;
    }

    void visitInOrder2(Employee* array, tree_node<int, Employee>* node, int* counter_ptr, int num){
        if (node == nullptr || *counter_ptr == num ) {
            return;
        }
        /* first recur on left child */
        visitInOrder2(array, node->left_son, counter_ptr, num);

        /* add id of the min node to array */
        array[*counter_ptr] = *node->data;
        (*counter_ptr)++;
        if (*counter_ptr == num) {
            return;
        }
        /* now recur on right child */
        visitInOrder2(array, node->right_son, counter_ptr, num);
    }

    StatusType Industry::AddCompany(int CompanyID, int Value){
        if(CompanyID <= 0 || Value <= 0){
            return INVALID_INPUT;
        }
        if(!companies.findNode(CompanyID)){
            return FAILURE;
        }
        Company new_company = Company(CompanyID, Value);
        if (!companies_with_employees.addNode(CompanyID, new_company)){
            return ALLOCATION_ERROR;
        }
        return SUCCESS;
    }

    StatusType Industry::RemoveEmployee(int EmployeeID){
        if(EmployeeID <= 0){
            return INVALID_INPUT;
        }
        if(!workers_by_id.findNode(EmployeeID)){
            return FAILURE;
        }
        Employee* employee_to_remove = workers_by_id.findNode(EmployeeID)->data;
        int company_id = employee_to_remove->GetCompanyID();
        if(companies_with_employees.findNode(company_id)){
            Company* curr_company = companies_with_employees.findNode(company_id)->data;
            if(curr_company->getCompanyNumOfEmployees() == 1){
                companies_with_employees.removeNode(company_id);
            }
            if(curr_company->getHighestEarner() == employee_to_remove){
                curr_company->RemoveEmployee(EmployeeID);
            }
            curr_company->RemoveEmployee(EmployeeID);
        }
        workers_by_id.removeNode(EmployeeID);
        workers_by_grade.removeNode(EmployeeID);
        num_of_workers--;
        return SUCCESS;
    }

    StatusType Industry::GetCompanyInfo(int CompanyID, int *Value, int *NumEmployees){
        if(!Value || !NumEmployees || CompanyID <= 0){
            return ALLOCATION_ERROR;
        }
        if(!companies.findNode(CompanyID)){
            return FAILURE;
        }
        Company* curr_company = companies.findNode(CompanyID)->data;
        *NumEmployees = curr_company->getCompanyNumOfEmployees();
        *Value = curr_company->getCompanyValue();
        return SUCCESS;
    }

    StatusType Industry::GetEmployeeInfo(int EmployeeID, int *EmployerID, int *Salary, int *Grade){
        if(!EmployerID || !Salary || !Grade || EmployeeID <= 0){
            return INVALID_INPUT;
        }
        if(!workers_by_id.findNode(EmployeeID)){
            return FAILURE;
        }
        Employee* curr_employee = workers_by_id.findNode(EmployeeID)->data;
        *EmployerID = curr_employee->GetCompanyID();
        *Salary = curr_employee->GetSalary();
        *Grade = curr_employee->GetGrade();
        return SUCCESS;
    }

    StatusType Industry::HireEmployee(int EmployeeID, int NewCompanyID) {
        if (EmployeeID <= 0 || NewCompanyID <= 0) {
            return INVALID_INPUT;
        }
        if (!workers_by_id.findNode(EmployeeID)) {
            return FAILURE;
        }
        if (!companies.findNode(NewCompanyID)) {
            return FAILURE;
        }
        Employee* curr_employee = workers_by_id.findNode(EmployeeID)->data;
        if(curr_employee->GetCompanyID() == NewCompanyID){
            return FAILURE;
        }
        int salary = curr_employee->GetSalary();
        int grade = curr_employee->GetGrade();
        RemoveEmployee(EmployeeID);
        AddEmployee(EmployeeID, NewCompanyID, salary, grade);
        return SUCCESS;
    }
    StatusType Industry::AcquireCompany(int AcquirerID, int TargetID, double Factor){
        if(AcquirerID <= 0 || TargetID <= 0 || Factor < 1.00 || TargetID == AcquirerID){
            return INVALID_INPUT;
        }
        if(!companies.findNode(AcquirerID) || !companies.findNode(TargetID)){
            return FAILURE;
        }
        Company* acquirer_company = companies.findNode(AcquirerID)->data;
        Company* target_company = companies.findNode(TargetID)->data;
        int acquirer_value = acquirer_company->getCompanyValue();
        int target_value = target_company->getCompanyValue();
        if (acquirer_value < 10*target_value){
            return FAILURE;
        }
        if(!companies_with_employees.findNode(TargetID)){
            RemoveCompany(TargetID);
            acquirer_company->UpdateCompanyValue((acquirer_value+target_value)*Factor);
            return SUCCESS;
        }
        int acquire_num = acquirer_company->getCompanyNumOfEmployees();
        int target_num = target_company->getCompanyNumOfEmployees();

        AVL_Tree<int, Employee>* acquire_employee_tree = companies_with_employees.findNode(AcquirerID)->data->getCompanyEmployeesTreeByID();
        AVL_Tree<int, Employee>* target_employee_tree = companies_with_employees.findNode(TargetID)->data->getCompanyEmployeesTreeByID();

        Employee *acquire_employees_arr = new Employee[acquire_num]();
        Employee *target_employees_arr = new Employee[target_num]();

        int counter = 0;
        visitInOrder2(acquire_employees_arr, acquire_employee_tree->root, &counter, acquire_num);
        int* counter_ptr = &counter;
        *counter_ptr = 0;
        visitInOrder2(target_employees_arr, target_employee_tree->root, &counter, target_num);
        counter_ptr = nullptr;

        Employee *new_arr = new Employee[acquire_num+target_num]();
        merge_func(target_employees_arr, acquire_employees_arr, target_num, acquire_num, new_arr);

        for(int i=0; i<target_num+acquire_num; i++){
            new_arr[i].UpdateCompanyID(AcquirerID);
        }

        AVL_Tree<int, Employee>* new_tree = createFromSortedArr(new_arr, 0, acquire_num+target_num-1);

        RemoveCompany(TargetID);
        RemoveCompany(AcquirerID);

        AVL_Tree<int, Employee> empty_tree =AVL_Tree<int, Employee>();

        all_groups_tree.addNode(ReplacementID,empty_tree);

        all_groups_tree.findNode(ReplacementID)->setData(new_tree);



    }
}






