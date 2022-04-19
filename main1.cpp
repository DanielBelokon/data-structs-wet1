/***************************************************************************/
/*                                                                         */
/* 234218 Data Structures 1, Spring-2022                                   */
/* Homework : Wet 1                                                        */
/*                                                                         */
/***************************************************************************/

/***************************************************************************/
/*                                                                         */
/* File Name : main1.cpp                                                   */
/*                                                                         */
/* Holds the "int main()" function and the parser of the shell's           */
/* command line.                                                           */
/***************************************************************************/

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "library1.h"
#include <iostream>
using namespace std;

#ifdef __cplusplus
extern "C" {
#endif

/***************************************************************************/
/* helpers                                                                 */
/***************************************************************************/
/* we assume maximum string size is not longer than 256  */
#define MAX_STRING_INPUT_SIZE (255)
#define MAX_BUFFER_SIZE       (255)

#define StrCmp(Src1,Src2) ( strncmp((Src1),(Src2),strlen(Src1)) == 0 )

typedef enum {
    error_free, error
} errorType;
static errorType parser(const char* const command);

#define ValidateRead(read_parameters,required_parameters,ErrorString) \
if ( (read_parameters)!=(required_parameters) ) { printf(ErrorString); return error; }

/* enum to string for return value */
static const char* ReturnValToStr(int val) {
    switch (val) {
        case SUCCESS:
            return "SUCCESS";
        case ALLOCATION_ERROR:
            return "ALLOCATION_ERROR";
        case FAILURE:
            return "FAILURE";
        case INVALID_INPUT:
            return "INVALID_INPUT";
        default:
            return "";
    }
}

/* Global isInit for running data structure */
static bool isInit = false;


/***************************************************************************/
/* Exercise Commands                                                       */
/***************************************************************************/

/* Number of exercise commands */
static const int numActions = 16;

/* The commands' types */
typedef enum {
    NONE_CMD                                = -2,
    COMMENT_CMD                             = -1,
    INIT_CMD                                = 0,
    ADD_COMPANY_CMD                         = 1,
    ADD_EMPLOYEE_CMD                        = 2,
    REMOVE_COMPANY_CMD                      = 3,
    REMOVE_EMPLOYEE_CMD                     = 4,
    GET_COMPANY_INFO_CMD                    = 5,
    GET_EMPLOYEE_INFO_CMD                   = 6,
    INCREASE_COMPANY_VALUE_CMD              = 7,
    PROMOTE_EMPLOYEE_CMD                    = 8,
    MOVE_COMPANY_CMD                        = 9,
    ACQUIRE_COMPANY_CMD                     = 10,
    GET_HIGHEST_EARNER_CMD                  = 11,
    GET_ALL_EMPLOYEES_BY_SALARY_CMD         = 12,
    GET_HIGHEST_EARNER_IN_EACH_COMPANY_CMD  = 13,
    GET_NUM_EMPLOYEES_MATCHING_CMD          = 14,
    QUIT_CMD                                = 15
} commandType;

/* The commands' strings */
static const char *commandStr[] = {
    "Init",
    "AddCompany",
    "AddEmployee",
    "RemoveCompany",
    "RemoveEmployee",
    "GetCompanyInfo",
    "GetEmployeeInfo",
    "IncreaseCompanyValue",
    "PromoteEmployee",
    "HireEmployee",
    "AcquireCompany",
    "GetHighestEarner",
    "GetAllEmployeesBySalary",
    "GetHighestEarnerInEachCompany",
    "GetNumEmployeesMatching",
    "Quit" 
};

/* On-Command Functions */
static errorType OnInit(void** DS, const char* const command);
static errorType OnAddCompany(void **DS, const char* const command);
static errorType OnAddEmployee(void **DS, const char* const command);
static errorType OnRemoveCompany(void **DS, const char* const command);
static errorType OnRemoveEmployee(void **DS, const char* const command);
static errorType OnGetCompanyInfo(void **DS, const char* const command);
static errorType OnGetEmployeeInfo(void **DS, const char* const command);
static errorType OnIncreaseCompanyValue(void **DS, const char* const command);
static errorType OnPromoteEmployee(void **DS, const char* const command);
static errorType OnHireEmployee(void **DS, const char* const command);
static errorType OnAcquireCompany(void **DS, const char* const command);
static errorType OnGetHighestEarner(void **DS, const char* const command);
static errorType OnGetAllEmployeesBySalary(void **DS, const char* const command);
static errorType OnGetHighestEarnerInEachCompany(void **DS, const char* const command);
static errorType OnGetNumEmployeesMatching(void **DS, const char* const command);
static errorType OnQuit(void** DS, const char* const command);

/* On-Command Function Pointers */
typedef errorType(*OnFuncPtr)(void**, const char* const);
static OnFuncPtr OnCmdPtrs[] = {
    OnInit,
    OnAddCompany,
    OnAddEmployee,
    OnRemoveCompany,
    OnRemoveEmployee,
    OnGetCompanyInfo,
    OnGetEmployeeInfo,
    OnIncreaseCompanyValue,
    OnPromoteEmployee,
    OnHireEmployee,
    OnAcquireCompany,
    OnGetHighestEarner,
    OnGetAllEmployeesBySalary,
    OnGetHighestEarnerInEachCompany,
    OnGetNumEmployeesMatching,
    OnQuit
};

/***************************************************************************/
/* main                                                                    */
/***************************************************************************/

int main(int argc, const char**argv) {
    char buffer[MAX_STRING_INPUT_SIZE];

    // Reading commands
    while (fgets(buffer, MAX_STRING_INPUT_SIZE, stdin) != NULL) {
        fflush(stdout);
        if (parser(buffer) == error)
            break;
    };
    return 0;
}

/***************************************************************************/
/* Command Checker                                                         */
/***************************************************************************/

static commandType CheckCommand(const char* const command,
        const char** const command_arg) {
    if (command == NULL || strlen(command) == 0 || StrCmp("\n", command))
        return (NONE_CMD);
    if (StrCmp("#", command)) {
        if (strlen(command) > 1)
            printf("%s", command);
        return (COMMENT_CMD);
    };
    for (int index = numActions-1; index>=0; index--) {
        if (StrCmp(commandStr[index], command)) {
            *command_arg = command + strlen(commandStr[index]) + 1;
            return ((commandType) index);
        };
    };
    return (NONE_CMD);
}


/***************************************************************************/
/* Parser                                                                  */
/***************************************************************************/
static errorType parser(const char* const command) {
    static void *DS = NULL; /* The general data structure */
    const char* command_args = NULL;
    errorType rtn_val = error;
    commandType command_val = CheckCommand(command, &command_args);
    if ((command_val >= INIT_CMD) && (command_val <= QUIT_CMD)) {
        rtn_val = OnCmdPtrs[command_val](&DS, command_args);
    } else if (command_val == COMMENT_CMD) {
        rtn_val = error_free;
    } else if (command_val == NONE_CMD) {
        rtn_val = error;
    } else {
        assert(false);
    }
    return (rtn_val);
}

/************************************************************************/
/* OnInit                                                               */
/************************************************************************/
static errorType OnInit(void** DS, const char* const command) {
    if (isInit) {
        printf("Init was already called\n");
        return (error_free);
    } else {
        *DS = Init();
        if (*DS == NULL) {
            printf("Init failed\n");
            return error;
        } else {
            isInit = true;
            printf("Init done\n");
            return error_free;
        }
    }
}

/************************************************************************/
/* OnQuit                                                               */
/************************************************************************/
static errorType OnQuit(void** DS, const char* const command) {
    if (!isInit) {
        printf("Quit not needed\n");
        return (error_free);
    } else {
        Quit(DS);
        if (*DS != NULL) {
            printf("Quit failed\n");
            return error;
        } else {
            isInit = false;
            printf("Quit done\n");
            return error_free;
        }
    }
}

/************************************************************************/
/* OnAddCompany                                                         */
/************************************************************************/
static errorType OnAddCompany(void **DS, const char* const command) {
    int CompanyID, Value;
    ValidateRead(sscanf(command, "%d %d", &CompanyID, &Value), 2, "AddCompany failed.\n");
    StatusType res = AddCompany(*DS, CompanyID, Value);
    printf("AddCompany: %s\n", ReturnValToStr(res));
    return error_free;
}

/************************************************************************/
/* OnAddEmployee                                                        */
/************************************************************************/
static errorType OnAddEmployee(void **DS, const char* const command) {
    int EmployeeID, CompanyID, Salary, Grade;
    ValidateRead(sscanf(command, "%d %d %d %d", &EmployeeID, &CompanyID, &Salary, &Grade), 4, "AddEmployee failed.\n");
    StatusType res = AddEmployee(*DS, EmployeeID, CompanyID, Salary, Grade);
    printf("AddEmployee: %s\n", ReturnValToStr(res));
    return error_free;
}

/************************************************************************/
/* OnRemoveCompany                                                      */
/************************************************************************/
static errorType OnRemoveCompany(void **DS, const char* const command) {
    int CompanyID;
    ValidateRead(sscanf(command, "%d", &CompanyID), 1, "RemoveCompany failed.\n");
    StatusType res = RemoveCompany(*DS, CompanyID);
    printf("RemoveCompany: %s\n", ReturnValToStr(res));
    return error_free;
}

/************************************************************************/
/* OnRemoveEmployee                                                     */
/************************************************************************/
static errorType OnRemoveEmployee(void **DS, const char* const command) {
    int EmployeeID;
    ValidateRead(sscanf(command, "%d", &EmployeeID), 1, "RemoveEmployee failed.\n");
    StatusType res = RemoveEmployee(*DS, EmployeeID);
    printf("RemoveEmployee: %s\n", ReturnValToStr(res));
    return error_free;
}

/************************************************************************/
/* OnGetCompanyInfo                                                     */
/************************************************************************/
static errorType OnGetCompanyInfo(void **DS, const char* const command) {
    int CompanyID, Value, NumEmployees;
    ValidateRead(sscanf(command, "%d", &CompanyID), 1, "GetCompanyInfo failed.\n");
    StatusType res = GetCompanyInfo(*DS, CompanyID, &Value, &NumEmployees);
    if (res == SUCCESS) {
        printf("GetCompanyInfo: SUCCESS. Company %d has %d employees and value %d\n", CompanyID, NumEmployees, Value);
    } else {
        printf("GetCompanyInfo: %s\n", ReturnValToStr(res));
    }
    return error_free;
}

/************************************************************************/
/* OnGetEmployeeInfo                                                    */
/************************************************************************/
static errorType OnGetEmployeeInfo(void **DS, const char* const command) {
    int EmployeeID, EmployerID, Salary, Grade;
    ValidateRead(sscanf(command, "%d", &EmployeeID), 1, "GetEmployeeInfo failed.\n");
    StatusType res = GetEmployeeInfo(*DS, EmployeeID, &EmployerID, &Salary, &Grade);
    if (res == SUCCESS) {
        printf("GetEmployeeInfo: SUCCESS. Employee %d works at %d and earns %d at grade %d\n", EmployeeID, EmployerID, Salary, Grade);
    } else {
        printf("GetEmployeeInfo: %s\n", ReturnValToStr(res));
    }
    return error_free;
}

/************************************************************************/
/* OnIncreaseCompanyValue                                               */
/************************************************************************/
static errorType OnIncreaseCompanyValue(void **DS, const char* const command) {
    int CompanyID, ValueIncrease;
    ValidateRead(sscanf(command, "%d %d", &CompanyID, &ValueIncrease), 2, "IncreaseCompanyValue failed.\n");
    StatusType res = IncreaseCompanyValue(*DS, CompanyID, ValueIncrease);
    printf("IncreaseCompanyValue: %s\n", ReturnValToStr(res));
    return error_free;
}

/************************************************************************/
/* OnPromoteEmployee                                                    */
/************************************************************************/
static errorType OnPromoteEmployee(void **DS, const char* const command) {
    int EmployeeID, SalaryIncrease, BumpGrade;
    ValidateRead(sscanf(command, "%d %d %d", &EmployeeID, &SalaryIncrease, &BumpGrade), 3, "PromoteEmployee failed.\n");
    StatusType res = PromoteEmployee(*DS, EmployeeID, SalaryIncrease, BumpGrade);
    printf("PromoteEmployee: %s\n", ReturnValToStr(res));
    return error_free;
}

/************************************************************************/
/* OnHireEmployee                                                       */
/************************************************************************/
static errorType OnHireEmployee(void **DS, const char* const command) {
    int EmployeeID, NewCompanyID;
    ValidateRead(sscanf(command, "%d %d", &EmployeeID, &NewCompanyID), 2, "HireEmployee failed.\n");
    StatusType res = HireEmployee(*DS, EmployeeID, NewCompanyID);
    printf("HireEmployee: %s\n", ReturnValToStr(res));
    return error_free;
}

/************************************************************************/
/* OnAcquireCompany                                                     */
/************************************************************************/
static errorType OnAcquireCompany(void **DS, const char* const command) {
    int AcquirerID, TargetID;
    double Factor;
    ValidateRead(sscanf(command, "%d %d %lf", &AcquirerID, &TargetID, &Factor), 3, "AcquireCompany failed.\n");
    StatusType res = AcquireCompany(*DS, AcquirerID, TargetID, Factor);
    printf("AcquireCompany: %s\n", ReturnValToStr(res));
    return error_free;
}

/************************************************************************/
/* OnGetHighestEarner                                                   */
/************************************************************************/
static errorType OnGetHighestEarner(void **DS, const char* const command) {
    int CompanyID, EmployeeID;
    ValidateRead(sscanf(command, "%d", &CompanyID), 1, "GetHighestEarner failed.\n");
    StatusType res = GetHighestEarner(*DS, CompanyID, &EmployeeID);
    if (res == SUCCESS) {
        printf("GetHighestEarner: SUCCESS. Highest earner is %d\n", EmployeeID);
    } else {
        printf("GetHighestEarner: %s\n", ReturnValToStr(res));
    }
    return error_free;
}

/************************************************************************/
/* OnGetAllEmployeesBySalary                                            */
/************************************************************************/
static errorType OnGetAllEmployeesBySalary(void **DS, const char* const command) {
    int CompanyID, *Employees, NumOfEmployees;
    ValidateRead(sscanf(command, "%d", &CompanyID), 1, "GetAllEmployeesBySalary failed.\n");
    StatusType res = GetAllEmployeesBySalary(*DS, CompanyID, &Employees, &NumOfEmployees);
    if (res == SUCCESS) {
        printf("GetAllEmployeesBySalary: SUCCESS. Highest earners:\n");
        printf("Employee Rank || Employee ID\n");
        for (int i=0; i<NumOfEmployees; i++) {
            printf("%d - %d\n", i, Employees[i]);
        }
        free(Employees);
    } else {
        printf("GetAllEmployeesBySalary: %s\n", ReturnValToStr(res));
    }
    return error_free;
}

/************************************************************************/
/* OnGetHighestEarnerInEachCompany                                      */
/************************************************************************/
static errorType OnGetHighestEarnerInEachCompany(void **DS, const char* const command) {
    int NumOfCompanies, *Employees;
    ValidateRead(sscanf(command, "%d", &NumOfCompanies), 1, "GetHighestEarnerInEachCompany failed.\n");
    StatusType res = GetHighestEarnerInEachCompany(*DS, NumOfCompanies, &Employees);
    if (res == SUCCESS) {
        printf("GetHighestEarnerInEachCompany: SUCCESS. Highest earners:\n");
        printf("Company Index || Employee ID\n");
        for (int i=0; i<NumOfCompanies; i++) {
            printf("%d - %d\n", i, Employees[i]);
        }
        free(Employees);
    } else {
        printf("GetHighestEarnerInEachCompany: %s\n", ReturnValToStr(res));
    }
    return error_free;
}

/************************************************************************/
/* OnGetNumEmployeesMatching                                            */
/************************************************************************/
static errorType OnGetNumEmployeesMatching(void **DS, const char* const command) {
    int CompanyID, MinEmployeeID, MaxEmployeeId, MinSalary, MinGrade, TotalNumOfEmployees, NumOfEmployees;
    ValidateRead(sscanf(command, "%d %d %d %d %d", &CompanyID, &MinEmployeeID, &MaxEmployeeId, &MinSalary, &MinGrade), 5, "GetNumEmployeesMatching failed.\n");
    StatusType res = GetNumEmployeesMatching(*DS, CompanyID, MinEmployeeID, MaxEmployeeId, MinSalary, MinGrade, &TotalNumOfEmployees, &NumOfEmployees);
    if (res == SUCCESS) {
        printf("GetNumEmployeesMatching: SUCCESS. Out of %d, %d match\n", TotalNumOfEmployees, NumOfEmployees);
    } else {
        printf("GetNumEmployeesMatching: %s\n", ReturnValToStr(res));
    }
    return error_free;
}

#ifdef __cplusplus
}
#endif
