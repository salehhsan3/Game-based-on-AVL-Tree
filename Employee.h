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
#include <memory>


namespace MIVNI{

    class Employee
    {
    private:
        int ID;
        int salary;
        int grade;
        int company_id;

    public:
        Employee(int ID,int salary,int grade,int group_id);
        Employee(const Employee& emp) = default;
        Employee& operator=(const Employee& emp) = default;
        ~Employee() = default;

        StatusType GetEmployeeInfo(int EmployeeID, int *EmployerID, int *Salary, int *Grade);


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
    };
    
    
}

#endif //DS_WET1_EMPLOYEE_H
