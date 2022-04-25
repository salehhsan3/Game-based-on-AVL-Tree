//
// Created by Saleh on 23/04/2022.
//

#include "Industry.h"

namespace MIVNI{

    Industry::Industry():
        num_of_workers(),
        num_of_companies_with_employees(),
        highest_earner(),
        workers_by_id(),
        workers_by_salary(),
        companies(),
        companies_with_employees()
    {}

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

    void Industry::UpdateIndustryHighestEarnerAfterAddition(shared_ptr<Employee> emp)
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
    tree_node<player_level, std::shared_ptr<player_level>>* createFromSortedArrAux(Employee array[], int start,
                                                                                   int end, tree_node<int, shared_ptr<Employee>>*parent){
        if(start > end)
            return nullptr;
        int mid = (start+end)/2;
        tree_node<int, shared_ptr<Employee>>* new_node = new tree_node<int, shared_ptr<Employee>>(*(array[mid])
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
        shared_ptr<Company> new_company = make_shared<Company>(CompanyID, Value);
        if (!companies_with_employees.addNode(CompanyID, new_company)){
            return ALLOCATION_ERROR;
        }
        return SUCCESS;
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
        shared_ptr<Employee> emp_to_find = *(this->workers_by_id.findNode(EmployeeID)->data);
        shared_ptr<Company> comp_to_find = *(this->companies.findNode(CompanyID)->data);
        
       
        shared_ptr<Employee> emp_to_add = make_shared<Employee>(EmployeeID,Salary,Grade,CompanyID);

        if(comp_to_find->getCompanyNumOfEmployees() == 0)
        {
            this->companies_with_employees.addNode(CompanyID,comp_to_find);
        }
        comp_to_find->AddEmployee(EmployeeID,Salary,emp_to_add);

        this->workers_by_id.addNode(EmployeeID,emp_to_add);
        this->workers_by_salary.addNode(Salary,emp_to_add);
        this->num_of_workers++;
        this->UpdateIndustryHighestEarnerAfterAddition(emp_to_add);
    } 

    StatusType Industry::RemoveEmployee(int EmployeeID){
        if(EmployeeID <= 0){
            return INVALID_INPUT;
        }
        if(!workers_by_id.findNode(EmployeeID)){
            return FAILURE;
        }
        shared_ptr<Employee> employee_to_remove = *(workers_by_id.findNode(EmployeeID)->data);
        int company_id = employee_to_remove->getEmployersid();
        if(companies_with_employees.findNode(company_id)){
            shared_ptr<Company> curr_company = *(companies_with_employees.findNode(company_id)->data);
            if(curr_company->getCompanyNumOfEmployees() == 1){
                companies_with_employees.removeNode(company_id);
            }
            if(curr_company->getHighestEarner() == employee_to_remove){
                curr_company->RemoveEmployee(EmployeeID);
            }
            curr_company->RemoveEmployee(EmployeeID);
        }
        workers_by_id.removeNode(EmployeeID);
        workers_by_salary.removeNode(EmployeeID);
        num_of_workers--;
        return SUCCESS;
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
        shared_ptr<Company> comp = *(this->companies.findNode(CompanyID)->data);

        int num_of_employees = comp->getCompanyNumOfEmployees();

         if (num_of_employees > 0)
        {
            return FAILURE;
        }
        this->companies.removeNode(CompanyID);
        return SUCCESS;
    }

    StatusType Industry::GetCompanyInfo(int CompanyID, int *Value, int *NumEmployees){
        if(!Value || !NumEmployees || CompanyID <= 0){
            return ALLOCATION_ERROR;
        }
        if(!companies.findNode(CompanyID)){
            return FAILURE;
        }
        shared_ptr<Company> curr_company = *(companies.findNode(CompanyID)->data);
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
        shared_ptr<Employee> curr_employee = *(workers_by_id.findNode(EmployeeID)->data);
        *EmployerID = curr_employee->getEmployersid();
        *Salary = curr_employee->getEmployeeSalary();
        *Grade = curr_employee->getEmployeeGrade();
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
        shared_ptr<Company> comp = *(this->companies.findNode(CompanyID)->data);
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
        shared_ptr<Employee> emp = *(this->workers_by_id.findNode(EmployeeID)->data);
        emp->promote(SalaryIncrease,BumpGrade);
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
        shared_ptr<Employee> curr_employee = *(workers_by_id.findNode(EmployeeID)->data);
        if(curr_employee->getEmployersid() == NewCompanyID){
            return FAILURE;
        }
        int salary = curr_employee->getEmployeeSalary();
        int grade = curr_employee->getEmployeeGrade();
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
        shared_ptr<Company> acquirer_company = *(companies.findNode(AcquirerID)->data);
        shared_ptr<Company> target_company = *(companies.findNode(TargetID)->data);
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

        AVL_Tree<int, shared_ptr<Employee>>* acquire_employee_tree = companies_with_employees.findNode(AcquirerID)->data->getCompanyEmployeesTreeByID();
        AVL_Tree<int, shared_ptr<Employee>>* target_employee_tree = companies_with_employees.findNode(TargetID)->data->getCompanyEmployeesTreeByID();

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

        AVL_Tree<int, shared_ptr<Employee>>* new_tree = createFromSortedArr(new_arr, 0, acquire_num+target_num-1);

        RemoveCompany(TargetID);
        RemoveCompany(AcquirerID);

        AVL_Tree<int, shared_ptr<Employee>> empty_tree =AVL_Tree<int, shared_ptr<Employee>>();

        all_groups_tree.addNode(ReplacementID,empty_tree);

        all_groups_tree.findNode(ReplacementID)->setData(new_tree);



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
        tree_node<int,shared_ptr<Company>>* comp_node = this->companies.findNode(CompanyID);
        if (comp_node == nullptr || 
        ( (CompanyID > 0) && (comp_node->data->get()->getCompanyNumOfEmployees() == 0) )  )
        {
            return FAILURE;
        }
        *EmployeeID = ( comp_node->data->get()->getHighestEarner()->getEmployeeID() );
        return SUCCESS;
    }



    void getEmployeesBySalary(tree_node<int,shared_ptr<Employee>>* node, int *Employees, int *index)
    {
        if(node == nullptr)
        {
            return;
        }
        getEmployeesBySalary(node->left_son,Employees,index);
        Employees[*index] = node->data->get()->getEmployeeID();
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
        tree_node<int,shared_ptr<Company>>* comp_node = this->companies.findNode(CompanyID);
        if (comp_node == nullptr || 
        ( (CompanyID > 0) && (comp_node->data->get()->getCompanyNumOfEmployees() == 0) )  )
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
            shared_ptr<Company> comp = *(comp_node->data);
            *Employees = (int*)malloc(comp->getCompanyNumOfEmployees()*sizeof(int));
            if (*Employees == NULL)
            {
                return ALLOCATION_ERROR;
            }
            getEmployeesBySalary(comp->getCompanyEmployeesTreeBySalary()->root,(*Employees),0);
            return SUCCESS;
        }
        
    }

    void getHighestEarnerInEachCompanyIntoArray(int *index, int max_index,tree_node<int,shared_ptr<Company>>* node, int *Employees)
    {
        if(node == nullptr || ( (*index) >= max_index ))
        {
            return;
        }
        getHighestEarnerInEachCompanyIntoArray(index,max_index,node->left_son,Employees);
        Employees[*index] = node->data->get()->getHighestEarnerID();
        (*index)++; // pointer or regular int?
        getHighestEarnerInEachCompanyIntoArray(index,max_index,node->right_son,Employees);
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
        
        *Employees = (int*)malloc(NumOfCompanies*sizeof(int));
        if (*Employees == NULL)
        {
            return ALLOCATION_ERROR;
        }
        try
        {
            int *index = new int();
            getHighestEarnerInEachCompanyIntoArray(index,NumOfCompanies,this->companies_with_employees.root,*Employees);
            delete index;
        }
        catch(const std::bad_alloc& e)
        {
            return ALLOCATION_ERROR;
        }
        
        return SUCCESS;
    }

    static void countEmployeesByID(tree_node<int,shared_ptr<Employee>>* node, int MinEmployeeID, int MaxEmployeeId,int *counter)
    {
        if (node == nullptr)
        {
            return;
        }
        if (node->data->get()->getEmployeeID() < MinEmployeeID )
        {
            return;
        }
        if (node->data->get()->getEmployeeID() > MaxEmployeeId )
        {
            return;
        }
        countEmployeesByID(node->left_son,MinEmployeeID,MaxEmployeeId,counter);
        countEmployeesByID(node->right_son,MinEmployeeID,MaxEmployeeId,counter);
        (*counter)++;   
    }

    static void getEmployeesByIDInArray(tree_node<int,shared_ptr<Employee>>* node, shared_ptr<Employee> *Employees, int *index, int MinEmployeeID, int MaxEmployeeId)
    {
        if (node == nullptr)
        {
            return;
        }
        if (node->data->get()->getEmployeeID() < MinEmployeeID )
        {
            return;
        }
        if (node->data->get()->getEmployeeID() > MaxEmployeeId )
        {
            return;
        }
        getEmployeesByIDInArray(node->left_son,Employees,index,MinEmployeeID,MaxEmployeeId);
        getEmployeesByIDInArray(node->right_son,Employees,index,MinEmployeeID,MaxEmployeeId);
        Employees[*index] = *(node->data);
        (*index)++;
    }

    static int getEmployeesWithMinSalaryAndGrade(shared_ptr<Employee> *Employees,int size, int MinSalary, int MinGrade)
    {
        int counter = 0;
        for (int i = 0; i < size; i++)
        {
            if ( (Employees[i]->getEmployeeGrade() >= MinGrade) && (Employees[i]->getEmployeeSalary() >= MinSalary) )
            {
                counter++;
            }
        }
        return counter;
    }

    StatusType Industry::GetNumEmployeesMatching(int CompanyID, int MinEmployeeID, int MaxEmployeeId,
                                        int MinSalary, int MinGrade, int *TotalNumOfEmployees, int *NumOfEmployees)
    {
        if ( (CompanyID == 0) || (MinEmployeeID < 0) || (MaxEmployeeId < 0) || (MinSalary < 0) ||
            (MinGrade < 0) || (MinEmployeeID > MaxEmployeeId) || (TotalNumOfEmployees == NULL) || (NumOfEmployees == NULL))
        {
            return INVALID_INPUT;
        }
        if ( ( (CompanyID > 0) && (this->companies.findNode(CompanyID)->data) == nullptr ) ||
             ( (CompanyID > 0) && (this->companies.findNode(CompanyID)->data)->get()->getCompanyNumOfEmployees() == 0 ) ||
             ( (CompanyID < 0) && (this->num_of_workers == 0 ) ) )
        {
            return FAILURE;
        }
        //allocate an array the size of workers
        try
        {
            int *num = new int();
            int *index = new int();
            if (CompanyID < 0)
            {
                countEmployeesByID(this->workers_by_id.root,MinEmployeeID,MaxEmployeeId,num);
                shared_ptr<Employee> *Employees = new shared_ptr<Employee>[*num]();
                getEmployeesByIDInArray(this->workers_by_id.root,Employees,index,MinEmployeeID,MaxEmployeeId);
                *NumOfEmployees =  getEmployeesWithMinSalaryAndGrade(Employees,*num,MinSalary,MinGrade);
                *TotalNumOfEmployees = *num;

            }
            if (CompanyID > 0)
            {
                shared_ptr<Company> comp = *(this->companies.findNode(CompanyID)->data);
                countEmployeesByID(comp->getCompanyEmployeesTreeByID()->root,MinEmployeeID,MaxEmployeeId,num);
                shared_ptr<Employee> *Employees = new shared_ptr<Employee>[*num]();
                getEmployeesByIDInArray(comp->getCompanyEmployeesTreeByID()->root,Employees,index,MinEmployeeID,MaxEmployeeId);
                *NumOfEmployees =  getEmployeesWithMinSalaryAndGrade(Employees,*num,MinSalary,MinGrade);
                *TotalNumOfEmployees = *num;
            }
            delete index;
            delete num;
        }
        catch(const std::bad_alloc& e)
        {
            return ALLOCATION_ERROR;
        }
        return SUCCESS;

    }

} // namespace MIVNI
