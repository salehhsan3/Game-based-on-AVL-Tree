//
// Created by Saleh on 23/04/2022.
//
#include "Company.h"

namespace MIVNI
{
    StatusType Company::AddEmployee(int EmployeeID, int Grade, Employee& emp)
    {
        this->employees_by_id.addNode(EmployeeID,emp);
        this->employees_by_grade.addNode(Grade,emp);
        this->num_of_employees++;
        return SUCCESS;   
    }
    void Company::UpdateCompanyHighestEarnerAfterAddition(Employee& emp)
    {
        if (this->highest_earner == nullptr)
        {
            this->highestearner = emp;
            return;
        }
        if ( (player->playerlevel) > (this->champion->data->playerlevel))
        {
            this->champion->data = player;
            this->champion->key = IDRank(player->playerlevel,player->playerid);
            return;
        }

        if ( ( (player->playerlevel) == (this->champion->data->playerlevel) )
                 && ( (player->playerid) < (this->champion->data->playerid) ) )
        {
            this->champion->data = player;
            this->champion->key = IDRank(player->playerlevel,player->playerid);
            return;
        }
        return;
    }
    StatusType RemoveEmployee(int EmployeeID);
    StatusType GetCompanyInfo(int CompanyID, int *Value, int *NumEmployees);
    int Company::getCompanyID()
    {
        return ID;
    }
    int Company::getCompanyValue()
    {
        return value;
    }
    int Company::getCompanyNumOfEmployees()
    {
        return num_of_employees;
    }
} // namespace MIVNI

