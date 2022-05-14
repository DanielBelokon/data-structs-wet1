#include "MainDataStructure.h"

MainDataStructure::MainDataStructure()
{
    companies_tree = AVLTree<Company *>(Company::compareByPointer);
    companies_with_employees_tree = AVLTree<Company *>(Company::compareByPointer);
    employees_tree = AVLTree<Employee *>(Employee::compareByPointer);
    employees_tree_by_salary = AVLTree<Employee *>(Employee::compareBySalary);
    highest_earner = nullptr;
}

void MainDataStructure::AddCompany(int companyID, int value)
{
    if (companyID <= 0 || value <= 0)
    {
        throw InvalidInputException();
    }
    Company *company = new Company(companyID, value);

    if (companies_tree.find(company) != nullptr)
    {
        delete company;
        throw CompanyAlreadyExistsException();
    }
    companies_tree.insert(company);
}

void MainDataStructure::AddEmployee(int employeeID, int companyID, int salary, int grade)
{
    if (companyID <= 0 || employeeID <= 0 || salary <= 0 || grade < 0)
    {
        throw InvalidInputException();
    }

    Company *company = findCompanyById(companyID);
    Employee *employee = new Employee(employeeID, company, salary, grade);
    if (employees_tree.find(employee) != nullptr)
    {
        delete employee;
        throw EmployeeAlreadyExistsException();
    }

    companies_with_employees_tree.insert(company);

    employees_tree.insert(employee);
    company->addEmployee(employee);
    employees_tree_by_salary.insert(employee);
    setHighesEarner(employee);
}

void MainDataStructure::RemoveEmployee(int employeeID)
{
    if (employeeID <= 0)
    {
        throw InvalidInputException();
    }

    Employee *employee = findEmployeeById(employeeID);
    Company *company = employee->getCompany();

    company->removeEmployee(employee);
    employees_tree.remove(employee);
    employees_tree_by_salary.remove(employee);
    if (employee == highest_earner)
    {
        if (employees_tree_by_salary.getSize() > 0)
        {
            highest_earner = employees_tree_by_salary.getHighest();
        }
        else
        {
            highest_earner = nullptr;
        }
    }

    if (company->getNumOfEmployees() == 0)
    {
        companies_with_employees_tree.remove(company);
    }

    delete employee;
}

void MainDataStructure::RemoveCompany(int companyID, bool force)
{
    if (companyID <= 0)
    {
        throw InvalidInputException();
    }

    Company *company = findCompanyById(companyID);

    if (company->getNumOfEmployees() > 0 && !force)
    {
        throw CompanyHasEmployeesException();
    }

    companies_tree.remove(company);
    companies_with_employees_tree.remove(company);
    delete company;
}

void MainDataStructure::GetCompanyInfo(int companyID, int *value, int *numOfEmployees)
{
    if (!value || !numOfEmployees || companyID <= 0)
        throw InvalidInputException();

    Company *company = findCompanyById(companyID);
    *value = company->getValue();
    *numOfEmployees = company->getNumOfEmployees();
}

void MainDataStructure::GetEmployeeInfo(int employeeID, int *employerID, int *salary, int *grade)
{
    if (!employerID || !salary || !grade || employeeID <= 0)
        throw InvalidInputException();

    Employee *Employee = findEmployeeById(employeeID);
    *salary = Employee->getSalary();
    *grade = Employee->getGrade();
    *employerID = Employee->getCompany()->getCompanyID();
}

void MainDataStructure::IncreaseCompanyValue(int companyID, int valueIncrease)
{
    if (companyID <= 0 || valueIncrease <= 0)
        throw InvalidInputException();

    Company *company = findCompanyById(companyID);
    company->setValue(company->getValue() + valueIncrease);
}

void MainDataStructure::PromoteEmployee(int employeeID, int salaryIncrease, int bumpGrade)
{
    if (employeeID <= 0 || salaryIncrease <= 0)
        throw InvalidInputException();

    Employee *employee = findEmployeeById(employeeID);

    Company *company = employee->getCompany();
    company->getEmployeesTreeBySalary()->remove(employee);
    employees_tree_by_salary.remove(employee);
    employee->increaseSalary(salaryIncrease);
    company->getEmployeesTreeBySalary()->insert(employee);
    employees_tree_by_salary.insert(employee);

    company->setHighesEarner(employee);
    setHighesEarner(employee);

    if (bumpGrade > 0)
        employee->increaseGrade();
}

void MainDataStructure::HireEmployee(int employeeID, int newCompanyID)
{
    if (employeeID <= 0 || newCompanyID <= 0)
        throw InvalidInputException();

    Employee *employee = findEmployeeById(employeeID);
    Company *new_company = findCompanyById(newCompanyID);

    if (employee->getCompany() == new_company)
        throw EmployeeAlreadyExistsException();

    Company *old_company = employee->getCompany();
    old_company->removeEmployee(employee);
    if (old_company->getNumOfEmployees() == 0)
    {
        companies_with_employees_tree.remove(old_company);
    }
    new_company->addEmployee(employee);
    companies_with_employees_tree.insert(new_company);

    employee->setCompany(new_company);
}

bool MainDataStructure::AcquireCompany(int companyID, int aquiredCompanyID, double factor)
{
    if (companyID <= 0 || aquiredCompanyID <= 0 || factor < 1 || companyID == aquiredCompanyID)
    {
        throw InvalidInputException();
    }

    Company *company = findCompanyById(companyID);
    Company *aqcuiredCompany = findCompanyById(aquiredCompanyID);

    if (company->getValue() < 10 * aqcuiredCompany->getValue())
    {
        return false;
    }

    company->merge(aqcuiredCompany, factor);
    if (company->getNumOfEmployees() > 0)
    {
        companies_with_employees_tree.insert(company);
    }

    RemoveCompany(aquiredCompanyID, true);
    return true;
}

int MainDataStructure::GetHighestEarner(int companyID)
{
    Employee *employee = nullptr;
    if (companyID == 0)
    {
        throw InvalidInputException();
    }

    if (companyID < 0)
    {
        employee = highest_earner;
    }
    else
    {
        Company *company = findCompanyById(companyID);
        employee = company->getHighestEarner();
    }

    if (employee == nullptr)
        throw EmployeeNotFoundException();
    else
        return employee->getEmployeeID();
}

int MainDataStructure::GetAllEmployeesBySalary(int companyID, int **employeeIDs)
{
    if (companyID == 0)
    {
        throw InvalidInputException();
    }

    AVLTree<Employee *> *cur_employees_tree_by_salary = &(this->employees_tree_by_salary);
    if (companyID > 0)
    {
        Company *company = findCompanyById(companyID);
        cur_employees_tree_by_salary = company->getEmployeesTreeBySalary();
    }

    int numOfEmployees = cur_employees_tree_by_salary->getSize();
    if (numOfEmployees == 0)
    {
        *employeeIDs = nullptr;
        throw EmployeeNotFoundException();
    }
    auto employees = cur_employees_tree_by_salary->getInOrderArray();
    *employeeIDs = (int *)(malloc(sizeof(int) * numOfEmployees));
    if (employeeIDs == NULL)
    {
        throw std::bad_alloc();
    }

    for (int i = 0; i < numOfEmployees; i++)
    {
        (*employeeIDs)[i] = employees[numOfEmployees - 1 - i]->getEmployeeID();
    }

    delete[] employees;

    return numOfEmployees;
}

void MainDataStructure::GetHighestEarnerInEachCompany(int numOfCompanies, int **highestEarners)
{
    if (numOfCompanies <= 0)
    {
        throw InvalidInputException();
    }

    if (numOfCompanies > companies_with_employees_tree.getSize())
        throw CompanyNotFoundException();
    *highestEarners = (int *)(malloc(sizeof(int) * numOfCompanies));
    if (highestEarners == NULL)
    {
        throw std::bad_alloc();
    }

    Company **companies_with_employees = companies_with_employees_tree.getInOrderArray(numOfCompanies);
    for (int i = 0; i < numOfCompanies; i++)
    {
        (*highestEarners)[i] = companies_with_employees[i]->getHighestEarner()->getEmployeeID();
    }
    delete[] companies_with_employees;
}

void MainDataStructure::setHighesEarner(Employee *emp)
{
    if (emp == nullptr)
        return;

    if (highest_earner == nullptr || Employee::compareBySalary(highest_earner, emp))
    {
        highest_earner = emp;
    }
}

int MainDataStructure::GetNumEmployeesMatching(int companyID, int minId, int maxId, int minSalary, int minGrade, int *inRange)
{
    if (companyID == 0 || minId < 0 || maxId < 0 || minSalary < 0 || minGrade < 0 || maxId < minId)
    {
        throw InvalidInputException();
    }
    AVLTree<Employee *> *employeesTree = &this->employees_tree;
    if (companyID > 0)
    {
        Company *company = findCompanyById(companyID);
        employeesTree = company->getEmployeesTree();
    }

    if (employeesTree->getSize() == 0)
    {
        throw EmployeeNotFoundException();
    }

    int numOfEmployees = 0;
    *inRange = 0;

    Node<Employee *> *current = employeesTree->getRoot();

    checkInRangeRocourisve(current, minId, maxId, minSalary, minGrade, inRange, &numOfEmployees);

    return numOfEmployees;
}

void MainDataStructure::checkInRangeRocourisve(Node<Employee *> *current, int minId, int maxId, int minSalary, int minGrade, int *inRange, int *numOfEmployees)
{
    if (current == nullptr)
        return;

    if (current->getData()->getEmployeeID() >= minId && current->getData()->getEmployeeID() <= maxId)
    {
        (*inRange)++;
        if (current->getData()->getSalary() >= minSalary && current->getData()->getGrade() >= minGrade)
        {
            (*numOfEmployees)++;
        }
    }

    if (current->getData()->getEmployeeID() >= minId)
        checkInRangeRocourisve(current->getLeft(), minId, maxId, minSalary, minGrade, inRange, numOfEmployees);
    if (current->getData()->getEmployeeID() <= maxId)
        checkInRangeRocourisve(current->getRight(), minId, maxId, minSalary, minGrade, inRange, numOfEmployees);
}

Company *MainDataStructure::findCompanyById(int id)
{
    Company tmp = Company(id, 0);
    Company *result = this->companies_tree.find(&tmp);
    if (result == nullptr)
        throw CompanyNotFoundException();
    return result;
}

Employee *MainDataStructure::findEmployeeById(int id)
{
    Employee tmp = Employee(id, 0, 0, 0);
    Employee *result = this->employees_tree.find(&tmp);
    if (result == nullptr)
        throw EmployeeNotFoundException();
    return result;
}

MainDataStructure::~MainDataStructure()
{
    Employee **employees = employees_tree.getInOrderArray();
    for (int i = 0; i < employees_tree.getSize(); i++)
    {
        delete employees[i];
    }
    delete[] employees;

    Company **companies = companies_tree.getInOrderArray();
    for (int i = 0; i < companies_tree.getSize(); i++)
    {
        delete companies[i];
    }
    delete[] companies;
}
