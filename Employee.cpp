#include "Employee.h"
#include<iostream>

Employee:: Employee(int employee_id, int company_id, int salary , int grade):employee_id(employee_id),company_id(company_id),salary(salary),grade(grade){}

int Employee::getGrade() {
     return grade;
};

int Employee::getSalary(){
    return salary;
}
int Employee::getEmployeeID(){
    return employee_id;
}
int Employee::getCompanyID(){
    return company_id;
}

void Employee::setGrade(int grade){
    this->grade = grade;
}
void Employee::setSalary(int salary){
    this->salary = salary;
}
void Employee::setCompanyID(int company_id){
    this->company_id = company_id;
}

bool Employee::compareBySalary(Employee *temp)
{
    if (this->salary < temp->getSalary())
        return true;
    if (this->salary == temp->getSalary())
        return this->employee_id > temp->getEmployeeID();
    return false;
}

bool Employee::operator<(const Employee &other) const
{
    return this->employee_id < other.employee_id;
}

bool Employee::operator==(const Employee &other) const
{
    return this->employee_id == other.employee_id;
}

bool Employee::operator>(const Employee &other) const
{
    return this->employee_id > other.employee_id;
}

bool Employee::operator!=(const Employee &other) const
{
    return this->employee_id != other.employee_id;
}
//