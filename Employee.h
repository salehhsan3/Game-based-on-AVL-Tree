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
            if (salary == emp.salary)
            {
                return ID > emp.ID;
            }
            return grade < emp.grade;
        }
        bool operator==(const Employee& emp) const
        {
            return ( salary == emp.salary && ID == emp.ID);
        }
        bool operator>(const Employee& emp) const
        {
            if (salary == emp.salary)
            {
                return ID < emp.ID;
            }
            return salary > emp.salary;
        }
        int getEmployeeID();
        int getEmployeeGrade();
        int getEmployeeSalary();
        int getEmployeersid();
        void increaseSalary(int increase);
        void bumpGrade(int bump);
        void promote(int increase,int bump);
    };
    
    
}

#endif //DS_WET1_EMPLOYEE_H
