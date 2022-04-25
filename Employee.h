//
// Created by Saleh on 23/04/2022.
//

#ifndef DS_WET1_EMPLOYEE_H
#define DS_WET1_EMPLOYEE_H
#include <iostream>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "library1.h"


namespace MIVNI{

    class Employee
    {
    private:
        int ID;
        int salary;
        int grade;
        int group_id;

    public:
        Employee(int ID = 0 ,int salary = 0,int grade = 0,int group_id = 0):
                ID(ID), salary(salary), grade(grade), group_id(grade){};
        Employee(const Employee& emp) = default;
        Employee& operator=(const Employee& emp) = default;
        ~Employee() = default;
        bool operator<(const Employee& emp) const
        {
            if (grade == emp.grade)
            {
                return ID > emp.ID;
            }
            return grade < emp.grade;
        }
        bool operator==(const Employee& emp) const
        {
            return ( grade == emp.grade && ID == emp.ID);
        }
        bool operator>(const Employee& emp) const
        {
            if (grade == emp.grade)
            {
                return ID < emp.ID;
            }
            return grade > emp.grade;
        }
        int GetCompanyID(){
            return group_id;
        }
        int GetSalary(){
            return salary;
        }
        int GetGrade(){
            return grade;
        }
        void UpdateCompanyID(int new_company_id){
            group_id = new_company_id;
        }
    };
    
    
}

#endif //DS_WET1_EMPLOYEE_H
