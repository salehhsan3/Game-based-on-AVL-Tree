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
        Employee(int ID,int salary,int grade,int group_id);
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
    };
    
    
}

#endif //DS_WET1_EMPLOYEE_H
