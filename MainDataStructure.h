// this is the main system

#ifndef MAINDATASTRCTURE_H
#define MAINDATASTRCTURE_H
#include "Company.h"
#include "Employee.h"
#include "AVLTree.h"
#include "Exceptions.h"

class MainDataStructure
{
private:
    AVLTree<Company *> companies_tree;
    AVLTree<Employee *> employees_tree;
    AVLTree<Employee *> employees_tree_by_salary;
    Employee *highest_earner;

public:
    MainDataStructure();
    void AddCompany(int companyID, int value);
    void RemoveCompany(int companyID, bool force = false);
    void AddEmployee(int companyID, int employeeID, int salary, int grade);
    void RemoveEmployee(int employeeID);
    bool AcquireCompany(int companyId, int aquiredCompanyId, double factor);

    int GetHighestEarner(int companyId);
    void setHighesEarner(Employee *emp);
    int GetAllEmployeesBySalary(int companyId, int **employees); // returns num of employees
    void GetHighestEarnerInEachCompany(int numOfCompanies, int **highestEarners);
    int GetNumEmployeesMatching(int companyId, int minId, int maxId, int minSalary, int minGrad, int *inRange);

    void GetCompanyInfo(int companyId, int *value, int *numOfEmployees);
    void GetEmployeeInfo(int employeeID, int *employerID, int *salary, int *grade);
    void IncreaseCompanyValue(int companyID, int valueIncrease);
    void PromoteEmployee(int EmployeeID, int salaryIncrease, int bumpGrade);
    void HireEmployee(int EmployeeID, int newCompanyID);

private:
    void checkInRangeRocourisve(Node<Employee *> *current, int minId, int maxId, int minSalary, int minGrade, int *inRange, int *numOfEmployees);
};

#endif