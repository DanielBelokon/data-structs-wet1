
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


    int getGrade() const;
    int getSalary() const;
    int getEmployeeID() const;
    int getCompanyID() const;
    void setGrade(int grade);
    void increaseGrade();
    void setSalary(int salary);
    void increaseSalary(int salary);
    void setCompanyID(int company_id);

    bool operator<(const Employee &other) const;
    bool operator>(const Employee &other) const;
    bool operator==(const Employee &other) const;
    bool operator!=(const Employee &other) const;
    static bool compareBySalary(Employee *const &temp1, Employee *const &temp2);
    static bool compareByPointer(Employee *const &temp1, Employee *const &temp2);
};

#endif