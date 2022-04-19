#include <iostream>
#include "MainDataStructure.h"

// test MainDataStructure class
int main()
{
    MainDataStructure mainDataStructure;
    mainDataStructure.AddCompany(1, 100);
    mainDataStructure.AddCompany(2, 200);
    mainDataStructure.AddCompany(3, 300);
    mainDataStructure.AddCompany(4, 50000);

    mainDataStructure.AddEmployee(1, 1, 100, 1);
    mainDataStructure.AddEmployee(1, 2, 200, 2);
    mainDataStructure.AddEmployee(1, 3, 30000, 3);

    mainDataStructure.AddEmployee(2, 4, 400, 4);
    mainDataStructure.AddEmployee(2, 5, 500, 5);
    mainDataStructure.AddEmployee(2, 6, 600, 6);

    mainDataStructure.AddEmployee(3, 7, 700, 7);
    mainDataStructure.AddEmployee(3, 8, 800, 8);
    mainDataStructure.AddEmployee(3, 9, 900, 9);

    mainDataStructure.AddEmployee(4, 10, 1000, 10);
    mainDataStructure.AddEmployee(4, 11, 1100, 11);
    mainDataStructure.AddEmployee(4, 12, 100, 12);

    // hire employee
    mainDataStructure.HireEmployee(12, 1);

    // promote employee
    mainDataStructure.PromoteEmployee(12, 100, 2);

    // increase company value
    mainDataStructure.IncreaseCompanyValue(1, 100);

    // get highest earner
    int highestEarner = mainDataStructure.GetHighestEarner(1);

    // get all employees by salary
    int *employees = nullptr;
    int numOfEmployees = mainDataStructure.GetAllEmployeesBySalary(1, &employees);

    // get highest earner in each company
    int *highestEarners = nullptr;
    mainDataStructure.GetHighestEarnerInEachCompany(3, &highestEarners);

    mainDataStructure.AcquireCompany(4, 1, 2);

    mainDataStructure.RemoveCompany(1);
    mainDataStructure.RemoveCompany(2);
    mainDataStructure.RemoveCompany(3);
    mainDataStructure.RemoveCompany(4);
    return 0;
}