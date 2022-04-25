// #include "library1.h"
#include "Industry.h"

namespace MIVNI
{
    void *Init()
    {
        return static_cast<void*>(new Industry());
    }

    StatusType AddCompany(void *DS, int CompanyID, int Value)
    {
        if (DS == NULL)
        {
            return INVALID_INPUT;
        }
        return static_cast<Industry*>(DS)->AddCompany(CompanyID,Value);
    }

    StatusType AddEmployee(void *DS, int EmployeeID, int CompanyID, int Salary, int Grade)
    {
        if (DS == NULL)
        {
            return INVALID_INPUT;
        }
        return static_cast<Industry*>(DS)->AddEmployee(EmployeeID,CompanyID,Salary,Grade);
    }

    StatusType RemoveCompany(void *DS, int CompanyID)
    {
        if (DS == NULL)
        {
            return INVALID_INPUT;
        }
        return static_cast<Industry*>(DS)->RemoveCompany(CompanyID);
    }

    StatusType RemoveEmployee(void *DS, int EmployeeID)
    {
        if (DS == NULL)
        {
            return INVALID_INPUT;
        }
        return static_cast<Industry*>(DS)->RemoveEmployee(EmployeeID);
    }

    StatusType GetCompanyInfo(void *DS, int CompanyID, int *Value, int *NumEmployees)
    {
        if (DS == NULL)
        {
            return INVALID_INPUT;
        }
        return static_cast<Industry*>(DS)->GetCompanyInfo(CompanyID,Value,NumEmployees);
    }

    StatusType GetEmployeeInfo(void *DS, int EmployeeID, int *EmployerID, int *Salary, int *Grade)
    {
        if (DS == NULL)
        {
            return INVALID_INPUT;
        }
        return static_cast<Industry*>(DS)->GetEmployeeInfo(EmployeeID,EmployerID,Salary,Grade);
    }

    StatusType IncreaseCompanyValue(void *DS, int CompanyID, int ValueIncrease)
    {
        if (DS == NULL)
        {
            return INVALID_INPUT;
        }
        return static_cast<Industry*>(DS)->IncreaseCompanyValue(CompanyID,ValueIncrease);
    }

    StatusType PromoteEmployee(void *DS, int EmployeeID, int SalaryIncrease, int BumpGrade)
    {
        if (DS == NULL)
        {
            return INVALID_INPUT;
        }
        return static_cast<Industry*>(DS)->PromoteEmployee(EmployeeID,SalaryIncrease,BumpGrade);
    }

    StatusType HireEmployee(void *DS, int EmployeeID, int NewCompanyID)
    {
        if (DS == NULL)
        {
            return INVALID_INPUT;
        }
        return static_cast<Industry*>(DS)->HireEmployee(EmployeeID,NewCompanyID);
    }

    StatusType AcquireCompany(void *DS, int AcquirerID, int TargetID, double Factor)
    {
        if (DS == NULL)
        {
            return INVALID_INPUT;
        }
        return static_cast<Industry*>(DS)->AcquireCompany(AcquirerID,TargetID,Factor);
    }

    StatusType GetHighestEarner(void *DS, int CompanyID, int *EmployeeID)
    {
        if (DS == NULL)
        {
            return INVALID_INPUT;
        }
        return static_cast<Industry*>(DS)->GetHighestEarner(CompanyID,EmployeeID);
    }

    StatusType GetAllEmployeesBySalary(void *DS, int CompanyID, int **Employees, int *NumOfEmployees)
    {
        if (DS == NULL)
        {
            return INVALID_INPUT;
        }
        return static_cast<Industry*>(DS)->GetAllEmployeesBySalary(CompanyID,Employees,NumOfEmployees);
    }

    StatusType GetHighestEarnerInEachCompany(void *DS, int NumOfCompanies, int **Employees)
    {
        if (DS == NULL)
        {
            return INVALID_INPUT;
        }
        return static_cast<Industry*>(DS)->GetHighestEarnerInEachCompany(NumOfCompanies,Employees);
    }

    StatusType GetNumEmployeesMatching(void *DS, int CompanyID, int MinEmployeeID, int MaxEmployeeId,
            int MinSalary, int MinGrade, int *TotalNumOfEmployees, int *NumOfEmployees)
            {
                if (DS == NULL)
        {
            return INVALID_INPUT;
        }
        return static_cast<Industry*>(DS)->GetNumEmployeesMatching(CompanyID,MinEmployeeID,MaxEmployeeId,
                                                                   MinSalary,MinGrade,TotalNumOfEmployees,NumOfEmployees);
            }

    void Quit(void** DS)
    {
        if (DS == NULL || (*DS) == NULL)
        {
            return;
        }
        delete static_cast<Industry*>(*DS);
        *DS =nullptr;
    }
} // namespace MIVNI
