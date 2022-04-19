#include "library1.h"
#include "MainDataStructure.h"

void *Init()
{
    MainDataStructure *ds = new MainDataStructure();
    return ds;
}

StatusType AddCompany(void *DS, int CompanyID, int Value)
{
    try
    {
        MainDataStructure *ds = (MainDataStructure *)DS;
        ds->AddCompany(CompanyID, Value);
        return SUCCESS;
    }
    catch (const std::exception &e)
    {
        return ExceptionToEnum(e);
    }
}

StatusType AddEmployee(void *DS, int EmployeeID, int CompanyID, int Salary, int Grade)
{
    try
    {
        MainDataStructure *ds = (MainDataStructure *)DS;
        ds->AddEmployee(EmployeeID, CompanyID, Salary, Grade);
        return SUCCESS;
    }
    catch (const std::exception &e)
    {
        return ExceptionToEnum(e);
    }
}

StatusType RemoveCompany(void *DS, int CompanyID)
{
    try
    {
        MainDataStructure *ds = (MainDataStructure *)DS;
        ds->RemoveCompany(CompanyID);
        return SUCCESS;
    }
    catch (const std::exception &e)
    {
        return ExceptionToEnum(e);
    }
}

StatusType RemoveEmployee(void *DS, int EmployeeID)
{
    try
    {
        MainDataStructure *ds = (MainDataStructure *)DS;
        ds->RemoveEmployee(EmployeeID);
        return SUCCESS;
    }
    catch (const std::exception &e)
    {
        return ExceptionToEnum(e);
    }
}

StatusType GetCompanyInfo(void *DS, int CompanyID, int *Value, int *NumEmployees)
{
    try
    {
        MainDataStructure *ds = (MainDataStructure *)DS;
        ds->GetCompanyInfo(CompanyID, Value, NumEmployees);
        return SUCCESS;
    }
    catch (const std::exception &e)
    {
        return ExceptionToEnum(e);
    }
}

StatusType GetEmployeeInfo(void *DS, int EmployeeID, int *EmployerID, int *Salary, int *Grade)
{
    try
    {
        MainDataStructure *ds = (MainDataStructure *)DS;
        ds->GetEmployeeInfo(EmployeeID, EmployerID, Salary, Grade);
        return SUCCESS;
    }
    catch (const std::exception &e)
    {
        return ExceptionToEnum(e);
    }
}

StatusType IncreaseCompanyValue(void *DS, int CompanyID, int ValueIncrease)
{
    try
    {
        MainDataStructure *ds = (MainDataStructure *)DS;
        ds->IncreaseCompanyValue(CompanyID, ValueIncrease);
        return SUCCESS;
    }
    catch (const std::exception &e)
    {
        return ExceptionToEnum(e);
    }
}

StatusType PromoteEmployee(void *DS, int EmployeeID, int SalaryIncrease, int BumpGrade)
{
    try
    {
        MainDataStructure *ds = (MainDataStructure *)DS;
        ds->PromoteEmployee(EmployeeID, SalaryIncrease, BumpGrade);
        return SUCCESS;
    }
    catch (const std::exception &e)
    {
        return ExceptionToEnum(e);
    }
}

StatusType HireEmployee(void *DS, int EmployeeID, int NewCompanyID)
{
    try
    {
        MainDataStructure *ds = (MainDataStructure *)DS;
        ds->HireEmployee(EmployeeID, NewCompanyID);
        return SUCCESS;
    }
    catch (const std::exception &e)
    {
        return ExceptionToEnum(e);
    }
}

StatusType AcquireCompany(void *DS, int AcquirerID, int TargetID, double Factor)
{
    try
    {
        MainDataStructure *ds = (MainDataStructure *)DS;
        ds->AcquireCompany(AcquirerID, TargetID, Factor);
        return SUCCESS;
    }
    catch (const std::exception &e)
    {
        return ExceptionToEnum(e);
    }
}

StatusType GetHighestEarner(void *DS, int CompanyID, int *EmployeeID)
{
    try
    {
        MainDataStructure *ds = (MainDataStructure *)DS;
        *EmployeeID = ds->GetHighestEarner(CompanyID);
        return SUCCESS;
    }
    catch (const std::exception &e)
    {
        return ExceptionToEnum(e);
    }
}

StatusType GetAllEmployeesBySalary(void *DS, int CompanyID, int **Employees, int *NumOfEmployees)
{
    try
    {
        MainDataStructure *ds = (MainDataStructure *)DS;
        *NumOfEmployees = ds->GetAllEmployeesBySalary(CompanyID, Employees);
        return SUCCESS;
    }
    catch (const std::exception &e)
    {
        return ExceptionToEnum(e);
    }
}

StatusType GetHighestEarnerInEachCompany(void *DS, int NumOfCompanies, int **Employees)
{
    try
    {
        MainDataStructure *ds = (MainDataStructure *)DS;
        ds->GetHighestEarnerInEachCompany(NumOfCompanies, Employees);
        return SUCCESS;
    }
    catch (const std::exception &e)
    {
        return ExceptionToEnum(e);
    }
}

StatusType GetNumEmployeesMatching(void *DS, int CompanyID, int MinEmployeeID, int MaxEmployeeId,
                                   int MinSalary, int MinGrade, int *TotalNumOfEmployees, int *NumOfEmployees)
{
    try
    {
        MainDataStructure *ds = (MainDataStructure *)DS;
        *NumOfEmployees = ds->GetNumEmployeesMatching(CompanyID, MinEmployeeID, MaxEmployeeId, MinSalary, MinGrade, TotalNumOfEmployees);
        return SUCCESS;
    }
    catch (const std::exception &e)
    {
        return ExceptionToEnum(e);
    }
}

void Quit(void **DS)
{
    MainDataStructure *ds = (MainDataStructure *)*DS;
    delete ds;
    *DS = nullptr;
}

StatusType ExceptionToEnum(std::exception ex)
{
    if (dynamic_cast<InvalidInputException *>(&ex))
    {
        return INVALID_INPUT;
    }
    else if (dynamic_cast<CompanyAlreadyExistsException *>(&ex))
    {
        return FAILURE;
    }
    else if (dynamic_cast<CompanyNotFoundException *>(&ex))
    {
        return FAILURE;
    }
    else if (dynamic_cast<CompanyHasEmployeesException *>(&ex))
    {
        return FAILURE;
    }
    else if (dynamic_cast<EmployeeAlreadyExistsException *>(&ex))
    {
        return FAILURE;
    }
    else if (dynamic_cast<EmployeeNotFoundException *>(&ex))
    {
        return FAILURE;
    }
    else if (dynamic_cast<std::bad_alloc *>(&ex))
    {
        return ALLOCATION_ERROR;
    }
    else
    {
        return FAILURE;
    }
}