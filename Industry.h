//
// Created by Saleh on 23/04/2022.
//

#ifndef DS_WET1_STOCKEXCHANGE_H
#define DS_WET1_STOCKEXCHANGE_H
#include "Company.h"


namespace MIVNI{

    class Industry
    {
    private:
        int num_of_workers;
        int num_of_companies_with_employees;
        Shared_ptr<Employee> highest_earner;
        AVL_Tree<int,Employee> workers_by_id;
        AVL_Tree<int,Employee> workers_by_grade;
        AVL_Tree<int,Company> companies;
        AVL_Tree<int,Company> companies_with_employees;

    public:
        Industry(
        int num_of_workers,
        int num_of_companies_with_employees,
        Shared_ptr<Employee> highest_earner,
        AVL_Tree<int,Employee> workers_by_id,
        AVL_Tree<int,Employee> workers_by_grade,
        AVL_Tree<int,Company> companies,
        AVL_Tree<int,Company> companies_with_employees
        ){}
        Industry(const Industry& ind) = default;
        Industry& operator=(const Industry& ind) = default;
        ~Industry()= default;
        ~Industry();
    };

}

#endif //DS_WET1_STOCKEXCHANGE_H
