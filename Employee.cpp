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

int Employee::compareBySalary(Employee* temp)
{
    if(this->salary < temp->getSalary())
        return -1;
    if(this->salary == temp->getSalary())
        return 0;
    return 1;

}
int main(){
    Employee a;
    a.setSalary(1000);
    Employee* b = new Employee(2,4,700,34);
    int result = a.compareBySalary(b);
    std::cout<<result;
}
//