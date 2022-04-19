#include "Company.h"

Company::Company(int companyID, int value) : companyID(companyID), value(value)
{
    num_of_employees = 0;
    highest_earner = nullptr;
    employees_tree = AVLTree<Employee *>(Employee::compareByPointer);
    employees_tree_by_salary = AVLTree<Employee *>(Employee::compareBySalary);
};

int Company::getCompanyID() const
{
    return companyID;
}

int Company::getValue() const
{
    return value;
}

int Company::getNumOfEmployees() const
{
    return num_of_employees;
}

Employee* Company::getHighestEarner(){
    return highest_earner;
}

void Company::setCompanyID(int newID){
    companyID=newID;
}

void Company::setValue(int value){
    this->value = value;
}

void Company::setHighesEarner(Employee* emp){
    if (highest_earner == nullptr || Employee::compareBySalary(highest_earner, emp))
    {
        highest_earner = emp;
    }
}

AVLTree<Employee *> *Company::getEmployeesTree()
{
    return &employees_tree;
}

void Company::addEmployee(Employee* employee){
    setHighesEarner(employee);
    num_of_employees++;
    employees_tree.add(employee);
    employees_tree_by_salary.add(employee);
}

void Company::removeEmployee(Employee* employee){
    employees_tree.remove(employee);
    if (employee == highest_earner)
        highest_earner = employees_tree_by_salary.getHighest();
    num_of_employees--;
}

void Company::merge(Company *company, int factor)
{
    if (company == nullptr)
        return;

    num_of_employees += company->getNumOfEmployees();
    this->setValue(factor * (company->getValue() + this->getValue()));

    employees_tree.merge(company->getEmployeesTree());
    employees_tree_by_salary.merge(company->getEmployeesTreeBySalary());
    setHighesEarner(company->getHighestEarner());
}

AVLTree<Employee *> *Company::getEmployeesTreeBySalary()
{
    return &employees_tree_by_salary;
}

bool Company::compareByPointer(Company *const &a, Company *const &b)
{
    return a->getCompanyID() < b->getCompanyID();
}