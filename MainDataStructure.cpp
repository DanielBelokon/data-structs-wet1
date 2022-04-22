#include "MainDataStructure.h"

MainDataStructure::MainDataStructure()
{
    companies_tree = AVLTree<Company *>(Company::compareByPointer);
    employees_tree = AVLTree<Employee *>(Employee::compareByPointer);
    employees_tree_by_salary = AVLTree<Employee *>(Employee::compareBySalary);
    highest_earner = nullptr;
}

void MainDataStructure::AddCompany(int companyID, int value)
{
    if (companyID <= 0)
    {
        throw InvalidInputException();
    }
    Company *company = new Company(companyID, value);

    if (companies_tree.search(company) != nullptr)
    {
        delete company;
        throw CompanyAlreadyExistsException();
    }
    companies_tree.add(company);
}

void MainDataStructure::RemoveCompany(int companyID, bool force)
{
    if (companyID == 0)
    {
        throw InvalidInputException();
    }

    Company tmp = Company(companyID, 0);
    Company *company = companies_tree.search(&tmp);
    if (company == nullptr)
    {
        throw CompanyNotFoundException();
    }

    if (company->getNumOfEmployees() > 0 && !force)
    {
        throw CompanyHasEmployeesException();
    }

    companies_tree.remove(company);
    delete company;
}

void MainDataStructure::AddEmployee(int employeeID, int companyID, int salary, int grade)
{
    if (companyID <= 0 || employeeID <= 0 || salary <= 0)
    {
        throw InvalidInputException();
    }

    Company tmp = Company(companyID, 0);
    Company *company = companies_tree.search(&tmp);
    if (company == nullptr)
    {
        throw CompanyNotFoundException();
    }

    Employee *employee = new Employee(employeeID, companyID, salary, grade);
    if (employees_tree.search(employee) != nullptr)
    {
        delete employee;
        throw EmployeeAlreadyExistsException();
    }

    employees_tree.add(employee);
    company->addEmployee(employee);
    employees_tree_by_salary.add(employee);
    setHighesEarner(employee);
}

void MainDataStructure::RemoveEmployee(int employeeID)
{
    if (employeeID <= 0)
    {
        throw InvalidInputException();
    }

    int company_id, salary, grade;
    GetEmployeeInfo(employeeID, &company_id, &salary, &grade);

    Company tmp = Company(company_id, 0);
    Company *company = companies_tree.search(&tmp);
    if (company == nullptr)
    {
        throw CompanyNotFoundException();
    }

    Employee tmp2 = Employee(employeeID, company_id, 0, 0);
    Employee *employee = company->getEmployeesTree()->search(&tmp2);
    if (employee == nullptr)
    {
        throw EmployeeNotFoundException();
    }

    company->removeEmployee(employee);
    employees_tree.remove(employee);
    employees_tree_by_salary.remove(employee);
    if (employee == highest_earner)
        if (employees_tree_by_salary.getSize() > 0)
        {
            highest_earner = employees_tree_by_salary.getHighest();
        }
        else
        {
            highest_earner = nullptr;
        }
    delete employee;
}

bool MainDataStructure::AcquireCompany(int companyID, int aquiredCompanyID, double factor)
{
    if (companyID <= 0 || aquiredCompanyID <= 0 || factor < 1)
    {
        throw InvalidInputException();
    }

    Company tmp = Company(companyID, 0);
    Company *company = companies_tree.search(&tmp);
    if (company == nullptr)
    {
        throw CompanyNotFoundException();
    }

    Company tmp2 = Company(aquiredCompanyID, 0);

    Company *aqcuiredCompany = companies_tree.search(&tmp2);
    if (aqcuiredCompany == nullptr)
    {
        throw CompanyNotFoundException();
    }

    if (company->getValue() < 10 * aqcuiredCompany->getValue())
    {
        return false;
    }

    company->merge(aqcuiredCompany, factor);
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
        Company tmp = Company(companyID, 0);

        Company *company = companies_tree.search(&tmp);
        if (company == nullptr)
        {
            throw CompanyNotFoundException();
        }

        employee = company->getHighestEarner();
    }

    if (employee == nullptr)
        throw EmployeeNotFoundException();
    else
        return employee->getEmployeeID();
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

int MainDataStructure::GetAllEmployeesBySalary(int companyID, int **employeeIDs)
{
    if (companyID <= 0)
    {
        throw InvalidInputException();
    }

    Company tmp = Company(companyID, 0);
    Company *company = companies_tree.search(&tmp);
    if (company == nullptr)
    {
        throw CompanyNotFoundException();
    }
    int numOfEmployees = company->getNumOfEmployees();

    Employee **employees = company->getEmployeesTreeBySalary()->getInOrderArray();
    *employeeIDs = new int[numOfEmployees];
    for (int i = 0, j = numOfEmployees - 1; i < company->getNumOfEmployees(); i++, j--)
    {
        (*employeeIDs)[i] = employees[j]->getEmployeeID();
    }

    delete[] employees;

    return numOfEmployees;
}

void MainDataStructure::GetHighestEarnerInEachCompany(int numOfCompanies, int **highestEarners)
{
    if (numOfCompanies <= 0 || numOfCompanies > companies_tree.getSize())
    {
        throw InvalidInputException();
    }

    *highestEarners = new int[numOfCompanies];

    Company **companies = companies_tree.getInOrderArray();
    for (int i = 0; i < numOfCompanies; i++)
    {
        Employee *employee = companies[i]->getHighestEarner();
        if (employee == nullptr)
            throw NotEnoughCompaniesException();

        (*highestEarners)[i] = employee->getEmployeeID();
    }
    delete[] companies;
}

int MainDataStructure::GetNumEmployeesMatching(int companyID, int minId, int maxId, int minSalary, int minGrade, int *inRange)
{
    if (companyID == 0 || minId < 0 || maxId <= 0 || minSalary <= 0 || minGrade <= 0)
    {
        throw InvalidInputException();
    }
    AVLTree<Employee *> *employeesTree = &this->employees_tree;
    if (companyID > 0)
    {
        Company tmp = Company(companyID, 0);

        Company *company = companies_tree.search(&tmp);
        if (company == nullptr)
        {
            throw CompanyNotFoundException();
        }
        employeesTree = company->getEmployeesTree();
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

void MainDataStructure::GetCompanyInfo(int companyID, int *value, int *numOfEmployees)
{
    if (!value || !numOfEmployees || companyID <= 0)
        throw InvalidInputException();

    Company tmp = Company(companyID, 0);
    Company *temp = companies_tree.search(&tmp);
    if (temp == nullptr)
        throw CompanyNotFoundException();
    *value = temp->getValue();
    *numOfEmployees = temp->getNumOfEmployees();
}

void MainDataStructure::GetEmployeeInfo(int employeeID, int *employerID, int *salary, int *grade)
{
    if (!employerID || !salary || !grade || employeeID <= 0)
        throw InvalidInputException();

    Employee tmp = Employee(employeeID, 0, 0, 0);
    Employee *temp = employees_tree.search(&tmp);
    if (temp == nullptr)
        throw EmployeeNotFoundException();
    *salary = temp->getSalary();
    *grade = temp->getGrade();
    *employerID = temp->getCompanyID();
}

void MainDataStructure::IncreaseCompanyValue(int companyID, int valueIncrease)
{
    if (companyID <= 0 || valueIncrease <= 0)
        throw InvalidInputException();

    Company tmp = Company(companyID, 0);
    Company *company = companies_tree.search(&tmp);
    if (company == nullptr)
        throw CompanyNotFoundException();
    company->setValue(company->getValue() + valueIncrease);
}

void MainDataStructure::PromoteEmployee(int employeeID, int salaryIncrease, int bumpGrade)
{
    if (employeeID <= 0 || salaryIncrease <= 0)
        throw InvalidInputException();

    Employee tmp = Employee(employeeID, 0, 0, 0);
    Employee *employee = employees_tree.search(&tmp);

    if (employee == nullptr)
        throw EmployeeNotFoundException();
    Company tmp2 = Company(employee->getCompanyID(), 0);
    Company *company = companies_tree.search(&tmp2);
    if (company == nullptr)
        throw CompanyNotFoundException();
    company->getEmployeesTreeBySalary()->remove(employee);
    employees_tree_by_salary.remove(employee);
    employee->increaseSalary(salaryIncrease);
    company->getEmployeesTreeBySalary()->add(employee);
    employees_tree_by_salary.add(employee);

    setHighesEarner(employee);

    if (bumpGrade > 0)
        employee->increaseGrade();
}

void MainDataStructure::HireEmployee(int employeeID, int newCompanyID)
{
    if (employeeID <= 0 || newCompanyID <= 0)
        throw InvalidInputException();

    Employee tmp = Employee(employeeID, 0, 0, 0);
    Employee *employee = employees_tree.search(&tmp);
    if (!employee)
        throw EmployeeNotFoundException();

    Company tmp2 = Company(newCompanyID, 0);
    Company *new_company = companies_tree.search(&tmp2);
    if (!new_company)
        throw CompanyNotFoundException();
    if (employee->getCompanyID() == newCompanyID)
        throw EmployeeAlreadyExistsException();

    Company tmp3 = Company(employee->getCompanyID(), 0);
    Company *old_company = companies_tree.search(&tmp3);
    employee->setCompanyID(newCompanyID);
    old_company->removeEmployee(employee);
    new_company->addEmployee(employee);
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
