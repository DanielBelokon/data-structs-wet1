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
    AVLTree<Employee>* employees_tree;

    public:

    Company()=default;
    Company(int companyID,int value);
    int getCompanyID();
    int getValue();
    int getNumOfEmployees();
    AVLTree<Employee>* getEmployeesTree();
    Employee* getMostEarner();
    void setCompanyID(int newID);
    void setValue(int value);
    void setMostEarner(Employee* emp);
    void addEmployee(Employee* employee);
    
}

















#endif