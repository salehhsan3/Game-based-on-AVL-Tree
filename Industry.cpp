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

    void Industry::merge_func(shared_ptr<Employee> arr1[], shared_ptr<Employee> arr2[] ,int n1, int n2,
                    shared_ptr<Employee>  arr3[]){
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

    void Industry::merge_func_by_id(shared_ptr<Employee> arr1[], shared_ptr<Employee> arr2[] ,int n1, int n2,
                    shared_ptr<Employee>  arr3[]){
        int i = 0, j = 0, k = 0;

        while (i<n1 && j <n2)
        {
            if ((arr1[i]->getEmployeeID()) < (arr2[j]->getEmployeeID()))
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

    tree_node<int, shared_ptr<Employee>> *Industry::createFromSortedArrAuxForID(shared_ptr<Employee> array[], int start,
                                                        int end, tree_node<int, shared_ptr<Employee>> *parent){
        if(start > end)
            return nullptr;
        int mid = (start+end)/2;
        tree_node<int, shared_ptr<Employee>> *new_node = new tree_node<int, shared_ptr<Employee>>(array[mid]->getEmployeeID(),array[mid],parent, nullptr, nullptr, 0);
        new_node->left_son = createFromSortedArrAuxForID(array, start, mid-1, new_node);
        new_node->right_son = createFromSortedArrAuxForID(array, mid+1, end, new_node);
        new_node->updateHeight();
        return new_node;
    }

    AVL_Tree<int, shared_ptr<Employee>>* Industry::createFromSortedArrForID(shared_ptr<Employee> array[], int start, int end){
        AVL_Tree<int, shared_ptr<Employee>> *new_tree = new AVL_Tree<int, shared_ptr<Employee>>();
        new_tree->root = createFromSortedArrAuxForID(array, start, end, nullptr);
        new_tree->max = new_tree->root->findMax();
        new_tree->min = new_tree->root->findMin();
        new_tree->size = end+1;
        return new_tree;
    }

    tree_node<SalaryID, shared_ptr<Employee>> *Industry::createFromSortedArrAuxForSalary(shared_ptr<Employee> array[], int start,
                                                        int end, tree_node<SalaryID, shared_ptr<Employee>> *parent){
        if(start > end)
            return nullptr;
        int mid = (start+end)/2;
        tree_node<SalaryID, shared_ptr<Employee>> *new_node = new tree_node<SalaryID, shared_ptr<Employee>>(array[mid]->getEmployeeSalaryID(),array[mid],parent, nullptr, nullptr, 0);
        new_node->left_son = createFromSortedArrAuxForSalary(array, start, mid-1, new_node);
        new_node->right_son = createFromSortedArrAuxForSalary(array, mid+1, end, new_node);
        new_node->updateHeight();
        return new_node;
    }

    AVL_Tree<SalaryID, shared_ptr<Employee>>* Industry::createFromSortedArrForSalary(shared_ptr<Employee> array[], int start, int end){
        AVL_Tree<SalaryID, shared_ptr<Employee>> *new_tree = new AVL_Tree<SalaryID, shared_ptr<Employee>>();
        new_tree->root = createFromSortedArrAuxForSalary(array, start, end, nullptr);
        new_tree->max = new_tree->root->findMax();
        new_tree->min = new_tree->root->findMin();
        new_tree->size = end+1;
        return new_tree;
    }

    void Industry::visitInOrder2(shared_ptr<Employee> * array, tree_node<int, shared_ptr<Employee> >* node, int* counter_ptr, int num){
        if (node == nullptr || *counter_ptr == num ) {
            return;
        }
        /* first recur on left child */
        visitInOrder2(array, node->left_son, counter_ptr, num);
       // added by - saleh
       if (*counter_ptr == num ) { 
            return;
        }
        // added by - saleh

        /* add id of the min node to array */
//        array[*counter_ptr] = *(node->data);
        // added by - saleh
        if (node->data)
        {
            array[*counter_ptr] = *(node->data);
            (*counter_ptr)++;
        }
        else
        {
            return;
        }
        // added by saleh
        if (*counter_ptr == num) {
            return;
        }
        /* now recur on right child */
        visitInOrder2(array, node->right_son, counter_ptr, num);
    }

    void Industry::visitInOrder3(shared_ptr<Employee> * array, tree_node<SalaryID, shared_ptr<Employee> >* node, int* counter_ptr, int num){
        if (node == nullptr || *counter_ptr == num ) {
            return;
        }
        /* first recur on left child */
        visitInOrder3(array, node->left_son, counter_ptr, num);
        // added by - saleh
        if (*counter_ptr == num ) {
            return;
        }
        // added by - saleh

        /* add id of the min node to array */
        //        array[*counter_ptr] = *(node->data);
        // added by - saleh
        if (node->data)
        {
            array[*counter_ptr] = *(node->data);
            (*counter_ptr)++;
        }
        else
        {
            return;
        }
        // added by saleh
        if (*counter_ptr == num) {
            return;
        }
        /* now recur on right child */
        visitInOrder3(array, node->right_son, counter_ptr, num);
    }

    Industry *Industry::Init()
    {
        return(new Industry());
    }

    StatusType Industry::AddCompany(int CompanyID, int Value){
        if(CompanyID <= 0 || Value <= 0){
            return INVALID_INPUT;
        }
        if( companies.findNode(CompanyID) != nullptr){
            return FAILURE;
        }
        shared_ptr<Company> new_company = make_shared<Company>(CompanyID, Value);
        if (!companies.addNode(CompanyID, new_company)){
            return ALLOCATION_ERROR;
        }
        return SUCCESS;
    }

    void Industry::addEmployeeToIndustry(int EmployeeID, shared_ptr<Employee> emp, SalaryID salaryId)
    {
        this->workers_by_id.addNode(EmployeeID,emp);
        this->workers_by_salary.addNode(salaryId,emp);
        this->num_of_workers++;
        this->updateHighestEarner();
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
        shared_ptr<Company> comp_to_find = *(this->companies.findNode(CompanyID)->data);
        shared_ptr<Employee> emp_to_add = make_shared<Employee>(EmployeeID,Salary,Grade,CompanyID);

        if(comp_to_find->getCompanyNumOfEmployees() == 0)
        {
            this->companies_with_employees.addNode(CompanyID,comp_to_find);
        }
        SalaryID sal_id = SalaryID(Salary, EmployeeID);
        comp_to_find->AddEmployee(EmployeeID,emp_to_add, sal_id);
        this->addEmployeeToIndustry(EmployeeID,emp_to_add,sal_id);
        return SUCCESS;
    } 

    void Industry::removeEmployeeFromIndustry(int EmployeeID, SalaryID salaryId)
    {
        this->workers_by_salary.removeNode(salaryId);
        this->workers_by_id.removeNode(EmployeeID);
        this->num_of_workers--;
        this->updateHighestEarner();
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
        int emp_salary = employee_to_remove->getEmployeeSalary();
        if(companies_with_employees.findNode(company_id)){
            shared_ptr<Company> curr_company = *(companies_with_employees.findNode(company_id)->data);
            if(curr_company->getCompanyNumOfEmployees() == 1){
                companies_with_employees.removeNode(company_id);
            }
            curr_company->RemoveEmployee(EmployeeID,emp_salary);
        }
        SalaryID sal_id = SalaryID(emp_salary, EmployeeID);
        this->removeEmployeeFromIndustry(EmployeeID,sal_id);
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
            return INVALID_INPUT;
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

    void Industry::updateHighestEarner()
    {
        // this->highest_earner = *(this->workers_by_salary.max->data);
        // return;
        if (this->workers_by_salary.max != nullptr){
            this->highest_earner = *(this->workers_by_salary.max->data);
        }
        else
        {
            this->highest_earner = nullptr;
        }
        return;
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
        SalaryID sal_id = SalaryID(emp->getEmployeeSalary(),EmployeeID);
        shared_ptr<Company> comp = *(this->companies.findNode(emp->getEmployersid())->data);

        comp->RemoveEmployeeFromSalaryTree(sal_id);
        this->workers_by_salary.removeNode(sal_id);

        emp->promote(SalaryIncrease,BumpGrade);
        sal_id = SalaryID(emp->getEmployeeSalary(),EmployeeID);

        comp->AddEmployeeToSalaryTree(sal_id,emp);
        this->workers_by_salary.addNode(sal_id,emp);
        this->updateHighestEarner();
        comp->updateHighestEarner();
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
        int after_value = ((acquirer_value + target_value)*Factor);

        if (acquirer_value < (10*target_value) ){
            return FAILURE;
        }

        if(companies_with_employees.findNode(TargetID) == nullptr){ // TargetCompany has no employess case
            RemoveCompany(TargetID);
            acquirer_company->UpdateCompanyValue(after_value);
            return SUCCESS;
        }

        int acquire_num = acquirer_company->getCompanyNumOfEmployees();
        int target_num = target_company->getCompanyNumOfEmployees();
        int after_num = acquire_num + target_num;

        AVL_Tree<int, shared_ptr<Employee>>* acquire_employee_tree = companies.findNode(AcquirerID)->data->get()->getCompanyEmployeesTreeByID();
        AVL_Tree<int, shared_ptr<Employee>>* target_employee_tree = companies.findNode(TargetID)->data->get()->getCompanyEmployeesTreeByID();
        AVL_Tree<SalaryID, shared_ptr<Employee>>* acquire_employee_tree_salary = companies.findNode(AcquirerID)->data->get()->getCompanyEmployeesTreeBySalary();
        AVL_Tree<SalaryID, shared_ptr<Employee>>* target_employee_tree_salary = companies.findNode(TargetID)->data->get()->getCompanyEmployeesTreeBySalary();

        shared_ptr<Employee> *acquire_employees_arr = new shared_ptr<Employee>[acquire_num]();
        shared_ptr<Employee> *target_employees_arr = new shared_ptr<Employee>[target_num]();
        shared_ptr<Employee> *acquire_employees_arr_salary = new shared_ptr<Employee>[acquire_num]();
        shared_ptr<Employee> *target_employees_arr_salary = new shared_ptr<Employee>[target_num]();
        int x=0;
        if ( AcquirerID==28 && TargetID==179 && Factor>2.35 && acquirer_value==136 && target_value==4 && acquire_num==15 && target_num==1 ){
            x++;
        }
        int counter = 0;
        int *counter_ptr = &counter;
        visitInOrder2(acquire_employees_arr, acquire_employee_tree->root, &counter, acquire_num);
        *counter_ptr = 0;
        visitInOrder3(acquire_employees_arr_salary, acquire_employee_tree_salary->root, &counter, acquire_num);
        *counter_ptr = 0;
        visitInOrder2(target_employees_arr, target_employee_tree->root, &counter, target_num);
        *counter_ptr = 0;
        visitInOrder3(target_employees_arr_salary, target_employee_tree_salary->root, &counter, target_num);
        counter_ptr = nullptr;

        shared_ptr<Employee> *new_arr = new shared_ptr<Employee>[after_num](); //potential memory leaks?
        merge_func_by_id(target_employees_arr, acquire_employees_arr, target_num, acquire_num, new_arr);
        shared_ptr<Employee> *new_arr_salary = new shared_ptr<Employee>[after_num](); //potential memory leaks?
        merge_func(target_employees_arr_salary, acquire_employees_arr_salary, target_num, acquire_num, new_arr_salary);
        if (x==1)
        {
            x++;
        }
        for(int i=0; i<after_num; i++){
//            if (new_arr[i])//needed?
                new_arr[i]->UpdateCompanyID(AcquirerID);
//            if (new_arr_salary[i])//needed?
                new_arr_salary[i]->UpdateCompanyID(AcquirerID);
        }
        // AVL_Tree<int, shared_ptr<Employee>> new_tree_by_id;
        // AVL_Tree<SalaryID, shared_ptr<Employee>> new_tree_by_salary;
        // createFromSortedArrForID(new_tree_by_id,new_arr, 0, acquire_num+target_num-1);
        // createFromSortedArrForSalary(new_tree_by_salary,new_arr_salary, 0, acquire_num+target_num-1);

        AVL_Tree<int, shared_ptr<Employee>>* new_tree_by_id = createFromSortedArrForID(new_arr, 0, acquire_num+target_num-1);
        AVL_Tree<SalaryID, shared_ptr<Employee>>* new_tree_by_salary = createFromSortedArrForSalary(new_arr_salary, 0, acquire_num+target_num-1);

        this->companies.removeNode(TargetID);
        if (target_num > 0)
        {
            this->companies_with_employees.removeNode(TargetID);
        }

        acquirer_company->UpdateCompanyValue(after_value);
        acquirer_company->updateNumOfEmployees(after_num);
//        acquirer_company->getCompanyEmployeesTreeByID()->treeClear();
        acquirer_company->changeCompanyEmployeesTreeByID(new_tree_by_id);
//        acquirer_company->getCompanyEmployeesTreeBySalary()->treeClear();
        acquirer_company->changeCompanyEmployeesTreeBySalary(new_tree_by_salary);
        acquirer_company->updateHighestEarner();

        delete[] acquire_employees_arr;
        delete[] acquire_employees_arr_salary;
        delete[] target_employees_arr;
        delete[] target_employees_arr_salary;
        delete[] new_arr;
        delete[] new_arr_salary;

        this->updateHighestEarner();
        if (after_num > 0)
        {
            this->companies_with_employees.addNode(AcquirerID,acquirer_company);//maybe check if company already exists in tree?
            //potential problem, I believe that if the node already exists there then the algorithm terminates!
        }
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
        tree_node<int,shared_ptr<Company>>* comp_node = this->companies.findNode(CompanyID);
        if ( ((CompanyID > 0) && (comp_node == nullptr)) ||
        ( (CompanyID > 0) && (comp_node->data->get()->getCompanyNumOfEmployees() == 0) )  )
        {
            return FAILURE;
        }
        *EmployeeID = ( comp_node->data->get()->getHighestEarnerID() );
        return SUCCESS;
    }



    void Industry::getEmployeesBySalary(tree_node<SalaryID,shared_ptr<Employee>>* node, int *Employees, int *index)
    {
        if(node == nullptr || node->data == nullptr)
        {
            // added by - saleh
            // node->data == nullptr
            // added by - saleh
            return;
        }
        getEmployeesBySalary(node->right_son,Employees,index);
        Employees[*index] = node->data->get()->getEmployeeID();
        (*index)++;
        getEmployeesBySalary(node->left_son,Employees,index);
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
        if ( ( (CompanyID > 0) && (comp_node == nullptr) ) ||
                        ( (CompanyID > 0) && (comp_node->data->get()->getCompanyNumOfEmployees() == 0) )  )
        {
            return FAILURE;
        }
        int index = 0;
        int *index_ptr = &index;

        if (CompanyID < 0)
        {
            *Employees = (int*)malloc(this->num_of_workers*sizeof(int));
            if (*Employees == NULL)
            {
                return ALLOCATION_ERROR;
            }
            getEmployeesBySalary(this->workers_by_salary.root,(*Employees),index_ptr);
            (*NumOfEmployees) = *index_ptr;//correct implementation?
            return SUCCESS;
        }

        if (CompanyID > 0)
        {
            shared_ptr<Company> comp = *(comp_node->data);
            *Employees = (int*)malloc(comp->getCompanyNumOfEmployees()*sizeof(int));
            if (*Employees == nullptr)
            {
                return ALLOCATION_ERROR;
            }
            getEmployeesBySalary(comp->getCompanyEmployeesTreeBySalary()->root,(*Employees),index_ptr);
            *NumOfEmployees = *index_ptr;//correct implementation?
            return SUCCESS;
        }
        return SUCCESS;
    }

    void Industry::getHighestEarnerInEachCompanyIntoArray(int *index, int max_index,tree_node<int,shared_ptr<Company>>* node, int *Employees)
    {
        if(node == nullptr || ( (*index) >= max_index ))
        {
            return;
        }
        getHighestEarnerInEachCompanyIntoArray(index,max_index,node->left_son,Employees);
        if ( (*index) == max_index)
        {
            return;
        }
        SalaryID sal_id = SalaryID(116,1598);
        Employees[*index] = node->data->get()->getHighestEarnerID();
//        Employees[*index] = node->data->get()->getCompanyEmployeesTreeBySalary()->max->data->get()->getEmployeeID();
        (*index)++; // pointer or regular int?
        getHighestEarnerInEachCompanyIntoArray(index,max_index,node->right_son,Employees);
    }

    int Industry::countNodes(tree_node<int,shared_ptr<Company>> *node)
    {
        if (node == nullptr)
        {
            return 0;
        }
        return(countNodes(node->left_son)+countNodes(node->right_son)+1);
    }

    StatusType Industry::GetHighestEarnerInEachCompany(int NumOfCompanies, int **Employees)
    {
        if (Employees == NULL || NumOfCompanies < 1)
        {
            return INVALID_INPUT;
        }
        if ( (this->companies_with_employees.root == nullptr) ||
             (countNodes(this->companies_with_employees.root) < NumOfCompanies) )
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
            if (NumOfCompanies == 3)
            {
                int y =0;
                y++;
            }
            int x = 0;
            getHighestEarnerInEachCompanyIntoArray(index,NumOfCompanies,this->companies_with_employees.root,*Employees);
//            if (NumOfCompanies == 3)
//            {
//                x++;
//               if ( ((*Employees)[0] == 3812) && ((*Employees)[1] == 2733) && ((*Employees)[2] == 5632))
//               {
//                   x++;
//               }
//            }
            
            delete index;
        }
        catch(const std::bad_alloc& e)
        {
            return ALLOCATION_ERROR;
        }
        
        return SUCCESS;
    }

    int Industry::countEmployeesByID(tree_node<int,shared_ptr<Employee>>* node, int MinEmployeeID, int MaxEmployeeId)
    {
        if (node == nullptr || (node->data == nullptr))
        {
            return 0;
        }

        if ( (node->data->get()->getEmployeeID() <= MaxEmployeeId) && ((node->data->get()->getEmployeeID() >= MinEmployeeID)) )
        {
            return 1 + countEmployeesByID(node->left_son, MinEmployeeID, MaxEmployeeId) + countEmployeesByID(node->right_son, MinEmployeeID, MaxEmployeeId);
        }
        else if ( (node->data->get()->getEmployeeID() < MinEmployeeID) )
        {
            return countEmployeesByID(node->right_son, MinEmployeeID, MaxEmployeeId);
        }
        else{
            return countEmployeesByID(node->left_son, MinEmployeeID, MaxEmployeeId);
        }        
    }

    void Industry::getEmployeesByIDInArray(tree_node<int,shared_ptr<Employee>>* node, shared_ptr<Employee> *Employees, int *index, int MinEmployeeID, int MaxEmployeeId)
    {
        // if (node == nullptr || (node->data == nullptr))
        // {
        //     return;
        // }
        // // added by - saleh
        //     // (node->data == nullptr)
        // // added by - saleh
        // if (node->data->get()->getEmployeeID() < MinEmployeeID )
        // {
        //     return;
        // }
        // if (node->data->get()->getEmployeeID() > MaxEmployeeId )
        // {
        //     return;
        // }
        // getEmployeesByIDInArray(node->left_son,Employees,index,MinEmployeeID,MaxEmployeeId);
        // getEmployeesByIDInArray(node->right_son,Employees,index,MinEmployeeID,MaxEmployeeId);
        // Employees[*index] = *(node->data);
        // (*index)++;

        if (node == nullptr || (node->data == nullptr))
        {
            return;
        }

        if ( (node->data->get()->getEmployeeID() <= MaxEmployeeId) && ((node->data->get()->getEmployeeID() >= MinEmployeeID)) )
        {
            Employees[*index] = *(node->data);
            (*index)++;
            getEmployeesByIDInArray(node->left_son,Employees,index, MinEmployeeID, MaxEmployeeId);
            getEmployeesByIDInArray(node->right_son,Employees,index, MinEmployeeID, MaxEmployeeId);
        }
        else if ( (node->data->get()->getEmployeeID() < MinEmployeeID) )
        {
            getEmployeesByIDInArray(node->right_son,Employees,index, MinEmployeeID, MaxEmployeeId);
        }
        else{
            getEmployeesByIDInArray(node->left_son,Employees,index, MinEmployeeID, MaxEmployeeId);
        }        
    }

    int Industry::getEmployeesWithMinSalaryAndGrade(shared_ptr<Employee> *Employees,int size, int MinSalary, int MinGrade)
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

    tree_node<int,shared_ptr<Employee>> *Industry::findLCA(tree_node<int,shared_ptr<Employee>> *root, int MinID, int MaxID)
    {
        // Base case
        if (root == nullptr)
        {
            return nullptr;
        }

        // If either n1 or n2 matches with root's key, report
        // the presence by returning root (Note that if a key is
        // ancestor of other, then the ancestor key becomes LCA
        if (*(root->key) == MinID || *(root->key) == MaxID)
            return root;

        // Look for keys in left and right subtrees
        tree_node<int,shared_ptr<Employee>> *left_lca  = findLCA(root->left_son, MinID, MaxID);
        tree_node<int,shared_ptr<Employee>> *right_lca  = findLCA(root->right_son, MinID, MaxID);

        // If both of the above calls return Non-NULL, then one key
        // is present in once subtree and other is present in other,
        // So this node is the LCA
        if (left_lca && right_lca)
        {
            return root;
        }
        // Otherwise check if left subtree or right subtree is LCA
        return (left_lca != nullptr)? left_lca: right_lca;

        // if (root == nullptr)
        // {
        //     return nullptr;
        // }
        
        // if ( (*(root->key) >= MinID) && (*(root->key) <= MaxID) )
        // {
        //     return root;
        // }
        
        // else if ( *(root->key) > MaxID )
        // {
        //     findLCA(root->left_son,MinID,MaxID);
        // }
        // findLCA(root->right_son,MinID,MaxID);
        
    }

    StatusType Industry::GetNumEmployeesMatching(int CompanyID, int MinEmployeeID, int MaxEmployeeId,
                                                 int MinSalary, int MinGrade, int *TotalNumOfEmployees, int *NumOfEmployees)
    {
        if ( (CompanyID == 0) || (MinEmployeeID < 0) || (MaxEmployeeId < 0) || (MinSalary < 0) ||
             (MinGrade < 0) || (MinEmployeeID > MaxEmployeeId) || (TotalNumOfEmployees == nullptr) || (NumOfEmployees == nullptr))
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


            shared_ptr<Employee> min_emp = make_shared<Employee>(MinEmployeeID);
            shared_ptr<Employee> max_emp = make_shared<Employee>(MaxEmployeeId);
            tree_node<int,shared_ptr<Employee>> *min_res = nullptr;
            tree_node<int,shared_ptr<Employee>> *max_res = nullptr;
            shared_ptr<Employee> *Employees = nullptr;
            if (CompanyID < 0)
            {
                min_res = this->workers_by_id.addNode(MinEmployeeID,min_emp);
                max_res = this->workers_by_id.addNode(MaxEmployeeId,max_emp);
                *num = countEmployeesByID(findLCA(this->workers_by_id.root,MinEmployeeID,MaxEmployeeId),MinEmployeeID,MaxEmployeeId);
                Employees = new shared_ptr<Employee>[*num]();
                getEmployeesByIDInArray(findLCA(this->workers_by_id.root,MinEmployeeID,MaxEmployeeId),Employees,index,MinEmployeeID,MaxEmployeeId);
                *NumOfEmployees =  getEmployeesWithMinSalaryAndGrade(Employees,*num,MinSalary,MinGrade);
                *TotalNumOfEmployees = *num;

                *TotalNumOfEmployees = (*num);
                if (min_res)
                {
                    (*TotalNumOfEmployees)--;
                    if (MinGrade == 0 && MinSalary == 0)
                    {
                        (*NumOfEmployees)--;
                    }

                    this->workers_by_id.removeNode(MinEmployeeID);
                }
                if (max_res)
                {
                    (*TotalNumOfEmployees)--;
                    if (MinGrade == 0 && MinSalary == 0)
                    {
                        (*NumOfEmployees)--;
                    }
                    this->workers_by_id.removeNode(MaxEmployeeId);
                }

            }
            if (CompanyID > 0)
            {
                int y =0;
                if ( CompanyID == 50 && MinEmployeeID ==824 && MaxEmployeeId==4591 && MinSalary==17 &&MinGrade==5 )
                {
                    y+= (*NumOfEmployees);//first potential problem!
                }
                shared_ptr<Company> comp = *(this->companies.findNode(CompanyID)->data);
                min_res = comp->AddEmployeeToIDTree(MinEmployeeID,min_emp);
                max_res = comp->AddEmployeeToIDTree(MaxEmployeeId,max_emp);
                tree_node<int,shared_ptr<Employee>> *LCA_node = findLCA(comp->getEmployeeTreeByIDRoot(),MinEmployeeID,MaxEmployeeId);
                *num = countEmployeesByID( LCA_node,MinEmployeeID,MaxEmployeeId);
                Employees = new shared_ptr<Employee>[*num]();
                getEmployeesByIDInArray( LCA_node,Employees,index,MinEmployeeID,MaxEmployeeId);
                *TotalNumOfEmployees = *num;
                *NumOfEmployees =  getEmployeesWithMinSalaryAndGrade(Employees,*num,MinSalary,MinGrade);


                if (min_res)
                {
                    (*TotalNumOfEmployees)--;
                    if (MinGrade == 0 && MinSalary == 0)
                    {
                        (*NumOfEmployees)--;
                    }

                    comp->getCompanyEmployeesTreeByID()->removeNode(MinEmployeeID);
                }
                if (max_res)
                {
                    (*TotalNumOfEmployees)--;
                    if (MinGrade == 0 && MinSalary == 0)
                    {
                        (*NumOfEmployees)--;
                    }
                    comp->getCompanyEmployeesTreeByID()->removeNode(MaxEmployeeId);
                }

            }

            delete index;
            delete num;
            delete[] Employees;
        }
        catch(const std::bad_alloc& e)
        {
            return ALLOCATION_ERROR;
        }
        return SUCCESS;
    }
} // namespace MIVNI