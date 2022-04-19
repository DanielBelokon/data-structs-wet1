/****************************************************************************/
/*                                                                          */
/* This file contains the interface functions                               */
/* you should use for the wet ex 1                                          */
/*                                                                          */
/****************************************************************************/

/****************************************************************************/
/*                                                                          */
/* File Name : library1.h                                                   */
/* Holds declarations of functions you should implement                     */
/* Your code should compile using: "g++ -std=c++11 -DNDEBUG -Wall *.cpp"    */
/* Tests are run with: "./a.out < test.in > test.out"                       */
/*                                                                          */
/****************************************************************************/

#ifndef _234218_WET1
#define _234218_WET1

#ifdef __cplusplus
extern "C" {
#endif

    /* Return Values
     * ----------------------------------- */
    typedef enum {
        SUCCESS = 0,
        FAILURE = -1,
        ALLOCATION_ERROR = -2,
        INVALID_INPUT = -3
    } StatusType;


    void *Init();

    StatusType AddCompany(void *DS, int CompanyID, int Value);

    StatusType AddEmployee(void *DS, int EmployeeID, int CompanyID, int Salary, int Grade);

    StatusType RemoveCompany(void *DS, int CompanyID);

    StatusType RemoveEmployee(void *DS, int EmployeeID);

    StatusType GetCompanyInfo(void *DS, int CompanyID, int *Value, int *NumEmployees);

    StatusType GetEmployeeInfo(void *DS, int EmployeeID, int *EmployerID, int *Salary, int *Grade);

    StatusType IncreaseCompanyValue(void *DS, int CompanyID, int ValueIncrease);

    StatusType PromoteEmployee(void *DS, int EmployeeID, int SalaryIncrease, int BumpGrade);

    StatusType HireEmployee(void *DS, int EmployeeID, int NewCompanyID);

    StatusType AcquireCompany(void *DS, int AcquirerID, int TargetID, double Factor);

    StatusType GetHighestEarner(void *DS, int CompanyID, int *EmployeeID);

    StatusType GetAllEmployeesBySalary(void *DS, int CompanyID, int **Employees, int *NumOfEmployees);

    StatusType GetHighestEarnerInEachCompany(void *DS, int NumOfCompanies, int **Employees);

    StatusType GetNumEmployeesMatching(void *DS, int CompanyID, int MinEmployeeID, int MaxEmployeeId,
            int MinSalary, int MinGrade, int *TotalNumOfEmployees, int *NumOfEmployees);

    void Quit(void** DS);

#ifdef __cplusplus
}
#endif

#endif    /*_234218_WET1 */
