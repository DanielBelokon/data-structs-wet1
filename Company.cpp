#include "Company.h"

Company::Company(int companyID,int value):companyID(companyID),value(value){};

int Company::getCompanyID(){
    return companyID;
}

int Company::getValue(){
    return value;
}

int Company::getNumOfEmployees(){
    return num_of_employees;
}

Employee* Company::getHighestEarner(){
    return highest_earner;
}

void Company::setCompanyID(int newID){
    companyID=newID;
}

void Company::setValue(int value){
    this->value=value;
}

void Company::setHighesEarner(Employee* emp){
    highest_earner=emp;
}
AVLTree<Employee>* Company::getEmployeesTree(){
    return employees_tree;
}

void Company::addEmployee(Employee* employee){
    employees_tree->add(*employee);
}

void Company::removeEmployee(Employee* employee){
    employees_tree->remove(*employee);
}