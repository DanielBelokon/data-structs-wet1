#ifndef COMPANY_H
#define COMPANY_H

#include "Employee.h"
#include "AVLTree.h"

class Company 
{
    int companyID;
    int value;
    int num_of_employees;
    Employee* highest_earner;
    AVLTree<Employee *> employees_tree;
    AVLTree<Employee *> employees_tree_by_salary;

public:
    Company() = default;
    Company(int companyID, int value);
    int getCompanyID() const;
    int getValue() const;
    int getNumOfEmployees() const;
    AVLTree<Employee *> *getEmployeesTree();
    AVLTree<Employee *> *getEmployeesTreeBySalary();
    Employee* getHighestEarner();
    void setCompanyID(int newID);
    void setValue(int value);
    void setHighesEarner(Employee* emp);

    void addEmployee(Employee* employee);
    void removeEmployee(Employee* employee);
    void merge(Company *company, int factor);

    bool operator<(const Company &other) const;
    bool operator>(const Company &other) const;
    bool operator==(const Company &other) const;
    bool operator!=(const Company &other) const;

    static bool compareByPointer(Company *const &a, Company *const &b);
};

#endif