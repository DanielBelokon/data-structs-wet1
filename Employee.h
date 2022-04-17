
#ifndef EMPLOYEE_H
#define EMPLOYEE_H


class Employee
{  
    int employee_id;
    int company_id;
    int salary;
    int grade; // the rank of the employee
    
  
    

public:

    Employee() = default;
    Employee(int employee_id, int company_id, int salary , int grade);
    ~Employee()=default;


    int getGrade();
    int getSalary();
    int getEmployeeID();
    int getCompanyID();
    void setGrade(int grade);
    void setSalary(int salary);
    void setCompanyID(int company_id);

    /*compare function by salary
    if salary < temp.salary return -1;
    if eqaul - return 0;
    else return 1;
    */
    bool compareBySalary(Employee *temp);

    bool operator<(const Employee &other) const;
    bool operator>(const Employee &other) const;
    bool operator==(const Employee &other) const;
    bool operator!=(const Employee &other) const;
};
#endif