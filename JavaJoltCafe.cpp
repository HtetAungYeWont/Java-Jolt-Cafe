#include <iostream>
#include <iomanip>
#include <algorithm>
#include <limits>
#include <vector>
using namespace std;

// Global variable
int security_tax = 10;

class Employee
{
    private:
    int employee_ID;
    string employee_name,employee_type,employee_position,start_date;
    double basic_salary;

    public:
    virtual~Employee() {}
    int empID() { return employee_ID; }
    string empName() { return employee_name; }
    string empPosition() { return employee_position; }
    string empType() { return employee_type; }
    string startDate() { return start_date; }
    double basicSalary() { return basic_salary; }

    // Default constructor
    Employee() : employee_ID(0), employee_name(""), employee_position(""), employee_type(""), start_date(""), basic_salary(0) {}

    // Set employee data
    void inputEmp()
    {
        cout << "Enter Employee ID: ";
        cin >> employee_ID;
        cin.ignore(); // Clear input buffer
        cout << "Enter Employee Name: ";
        getline(cin, employee_name);

        // Loop until a valid employee position is entered
        while (true)
        {
            cout << "Enter Employee Position (Fulltime: Barista, Cashier, Supervisor / Parttime: Cleaner, Kitchen Staff, Waiter, Waitress): ";
            getline(cin, employee_position);

            if (employee_position == "Barista" || employee_position == "barista")
            {
                basic_salary = 1920;
                employee_type = "fulltime";
                break;
            }
            else if (employee_position == "Cashier" || employee_position == "cashier")
            {
                basic_salary = 1790;
                employee_type = "fulltime";
                break;
            }
            else if (employee_position == "Cleaner" || employee_position == "cleaner")
            {
                basic_salary = 1400;
                employee_type = "parttime";
                break;
            }
            else if (employee_position == "Kitchen Staff" || employee_position == "kitchen staff")
            {
                basic_salary = 1850;
                employee_type = "parttime";
                break;
            }
            else if (employee_position == "Waiter" || employee_position == "waiter" || employee_position == "Waitress" || employee_position == "waitress")
            {
                basic_salary = 1700;
                employee_type = "parttime";
                break;
            }
            else if (employee_position == "Supervisor" || employee_position == "supervisor")
            {
                basic_salary = 2400;
                employee_type = "fulltime";
                break;
            }
            else
            {
                cout << "Invalid Employee Position. Please try again." << endl;
            }
        }

        cout << "Enter Employee Start Date (dd/mm/yy): ";
        cin >> start_date;
    }
};

class FullTime : public Employee
{
private:
    int leave_days;
    double overtime_hours = 0;
    double bonus = 0;
    double overtime_fees = 0;
    double total_amount = 0;
    double tax_salary = 0;
    double net_salary = 0;

public:
    FullTime() : leave_days(0), overtime_hours(0.0) {}

    void inputFulltimeData()
    {
        inputEmp(); // Set common data from Employee
        cout << "Enter number of leave days: ";
        cin >> leave_days;
        cout << "Enter overtime hours: ";
        cin >> overtime_hours;

        // Calculate bonus based on leave days
        if (leave_days == 0)
        {
            bonus = 300;
        }
        else if (leave_days == 1)
        {
            bonus = 200;
        }
        else if (leave_days == 2)
        {
            bonus = 100;
        }
        else
        {
            bonus = 0;
        }
        fulltimeTotalSalary();
    }

    double fulltimeTotalSalary()
    {
        double salary = basicSalary();

        // Calculate overtime fees
        overtime_fees = (((salary / 30) / 8) * overtime_hours) * 2;

        // Calculate total amount considering leave days and overtime
        if (leave_days < 4 && overtime_hours >= 0)
        {
            total_amount = salary + bonus + overtime_fees;
            tax_salary = (total_amount / 100) * 2;
        }
        else if (leave_days > 4 && overtime_hours > 0)
        {
            total_amount = salary - ((salary / 100) * 1) + overtime_fees - bonus;
            tax_salary = (total_amount / 100) * 2;
        }
        else
        {
            total_amount = salary - bonus + overtime_fees;
            tax_salary = (total_amount / 100) * 2;
        }

        return total_amount;
    }

    double fulltimeTotalNetSalary()
    {
        if (total_amount == 0) // Ensure total_amount is calculated
            fulltimeTotalSalary();

        net_salary = total_amount - tax_salary - security_tax;
        return net_salary;
    }

    int LeaveDay() { return leave_days; }
    double OvertimeHr() { return overtime_hours; }
    double OvertimeFees() { return overtime_fees; }
    double Bonus() { return bonus; }
    double getNetSalary() { return net_salary; }
};

class PartTime : public Employee
{
private:
    double hourly_wage = 0;
    double working_hours = 0;
    double total_amount = 0;
    double tax_deduction = 0;
    double net_salary = 0;

public:
    PartTime() : working_hours(0) {}

    void inputParttimeData()
    {
        inputEmp();
        cout << "Enter working hours (Monthly): ";
        cin >> working_hours;
        parttimeTotalNetSalary();
    }

    double parttimeTotalNetSalary()
    {
        double salary = basicSalary();
        hourly_wage = (salary / 30) / 8;
        total_amount = hourly_wage * working_hours;
        tax_deduction = (total_amount / 100) * 2;
        net_salary = total_amount - tax_deduction - security_tax;
        return net_salary;
    }
    double getWorkingHours() { return working_hours; }
    double getHourlyWage() { return hourly_wage; }
    double getNetSalary() { return net_salary; }
};

vector<FullTime> Fulltime_Employees;
vector<PartTime> PartTime_Employees;

// Quick Sort Helper Functions
int partition(vector<Employee *> &employees, int low, int high)
{
    double pivot = employees[high]->basicSalary();
    int i = low - 1;

    for (int j = low; j < high; j++)
    {
        if (employees[j]->basicSalary() < pivot)
        {
            i++;
            swap(employees[i], employees[j]);
        }
    }
    swap(employees[i + 1], employees[high]);
    return i + 1;
}

void quickSort(vector<Employee *> &employees, int low, int high)
{
    if (low < high)
    {
        int pi = partition(employees, low, high);
        quickSort(employees, low, pi - 1);
        quickSort(employees, pi + 1, high);
    }
}

int main()
{
    int opt = 0;
    cout << "****************************************" << endl;
    cout << "             Java Jolt Cafe             " << endl;
    cout << "****************************************" << endl;
    int fulltime_employee = 0, parttime_employee = 0;
    double fulltime_employee_salary = 0, parttime_employee_salary = 0, monthly_total = 0;
    while (opt != 6)
    {
        cout << "1. Insert Employee Data \n"
             << "2. Update Employee Data \n"
             << "3. View Fulltime Employees Salary \n"
             << "4. View Parttime Employees Salary \n"
             << "5. View All Employees Salary \n"
             << "6. Exit" << endl<<endl;
        cout << "Choose an option: ";
        cin >> opt;

        // Clear invalid input
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Please enter a number between 1 and 6." << endl;
            continue;
        }

        cin.ignore(); // Clear input buffer

        switch (opt)
        {
        case 1:
        {
            int n;
            cout << "Enter the number of employees you want to insert: ";
            cin >> n;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            for (int i = 0; i < n; i++)
            {
                cout << "Enter details for Employee " << i + 1 << ":" << endl;
                string employee_type;
                cout << "Which Type Of Employee Data You Want To Insert (fulltime/parttime): ";
                cin >> employee_type;
                cin.ignore(); // Clear buffer after reading employee_type

                if (employee_type == "fulltime")
                {
                    FullTime New_Employee;
                    New_Employee.inputFulltimeData();
                    cout << endl;
                    Fulltime_Employees.push_back(New_Employee);
                    fulltime_employee++;
                    fulltime_employee_salary += New_Employee.fulltimeTotalNetSalary();
                }
                else if (employee_type == "parttime")
                {
                    PartTime New_Employee;
                    New_Employee.inputParttimeData();
                    cout << endl;
                    PartTime_Employees.push_back(New_Employee);
                    parttime_employee++;
                    parttime_employee_salary += New_Employee.parttimeTotalNetSalary();
                }
                else
                {
                    cout << "Invalid Employee Type...." << endl;
                }
            }

            monthly_total = fulltime_employee_salary + parttime_employee_salary;
            cout << "Employee Data Added..." << endl;
            break;
        }

        case 2:
        {
            int num;
            string type;
            bool found = false;

            cout << "Enter The Employee Type to Update Data (fulltime/parttime): ";
            cin >> type;

            if (type == "fulltime")
            {
                cout << "Enter Employee ID You Want To Update: ";
                cin >> num;
                for (int i = 0; i < Fulltime_Employees.size(); i++)
                {
                    if (num == Fulltime_Employees[i].empID())
                    {
                        cout << "Updating data for Full-Time Employee ID: " << num << endl;
                        Fulltime_Employees[i].inputFulltimeData();
                        Fulltime_Employees[i].fulltimeTotalSalary();
                        Fulltime_Employees[i].fulltimeTotalNetSalary();
                        found = true;
                        break;
                    }
                }
                if (!found)
                {
                    cout << "No Full-Time Employee found with ID: " << num << endl;
                }
            }
            else if (type == "parttime")
            {
                cout << "Enter Employee ID You Want To Update: ";
                cin >> num;
                for (int i = 0; i < PartTime_Employees.size(); i++)
                {
                    if (num == PartTime_Employees[i].empID())
                    {
                        cout << "Updating data for Part-Time Employee ID: " << num << endl;
                        PartTime_Employees[i].inputParttimeData();
                        PartTime_Employees[i].parttimeTotalNetSalary();
                        found = true;
                        break;
                    }
                }
                if (!found)
                {
                    cout << "No Parttime Employee found with ID: " << num << endl;
                }
            }
            else
            {
                cout << "Invalid Employee Type..." << endl;
            }
            break;
        }
        case 3:
        {
            if (Fulltime_Employees.empty())
            {
                cout << "No Fulltime Employees Found..." << endl;
            }
            else
            {
                cout << "********** Fulltime Employees **********" << endl;

                // Table Headers
                cout << left << setw(5) << "ID"
                     << setw(7) << "Name"
                     << setw(15) << "Position"
                     << setw(12) << "Start Date"
                     << setw(15) << "Basic Salary"
                     << setw(12) << "Leave Days"
                     << setw(14) << "Overtimehrs"
                     << setw(15) << "OvertimeFees"
                     << setw(10) << "Bonus"
                     << setw(12) << "Tax Fees"
                     << setw(12) << "Sec Fees"
                     << setw(15) << "Total Amount"
                     << setw(12) << "Net Salary" << endl;

                // Table Rows
                for (int i = 0; i < Fulltime_Employees.size(); i++)
                {
                    Fulltime_Employees[i].fulltimeTotalSalary();
                    double total_salary = Fulltime_Employees[i].fulltimeTotalSalary();
                    double net_salary = Fulltime_Employees[i].fulltimeTotalNetSalary();
                    double tax_deduction = (total_salary / 100) * 2;

                    cout << left << setw(5) << Fulltime_Employees[i].empID()
                         << setw(7) << Fulltime_Employees[i].empName()
                         << setw(15) << Fulltime_Employees[i].empPosition()
                         << setw(12) << Fulltime_Employees[i].startDate()
                         << setw(15) << fixed << setprecision(2) << Fulltime_Employees[i].basicSalary()
                         << setw(12) << Fulltime_Employees[i].LeaveDay()
                         << setw(14) << fixed << setprecision(2) << Fulltime_Employees[i].OvertimeHr()
                         << setw(15) << fixed << setprecision(2) << Fulltime_Employees[i].OvertimeFees()
                         << setw(10) << fixed << setprecision(2) << Fulltime_Employees[i].Bonus()
                         << setw(12) << fixed << setprecision(2) << tax_deduction
                         << setw(12) << fixed << setprecision(2) << security_tax
                         << setw(15) << fixed << setprecision(2) << total_salary
                         << setw(12) << fixed << setprecision(2) << net_salary << endl;
                }

                cout << "******************************************" << endl;
            }
            break;
        }
        case 4:
        {
            if (PartTime_Employees.empty())
            {
                cout << "No Parttime Employees Found!" << endl;
            }
            else
            {
                cout << "********** Parttime Employees **********" << endl;
                // Table Header
                cout << left << setw(5) << "ID"
                     << setw(10) << "Name"
                     << setw(15) << "Position"
                     << setw(12) << "Start Date"
                     << setw(15) << "Basic Salary"
                     << setw(12) << "Hours"
                     << setw(15) << "Hourly Wage"
                     << setw(15) << "Total Amount"
                     << setw(12) << "Tax Fees"
                     << setw(17) << "Security Fees"
                     << setw(12) << "Net Amount" << endl;

                // Table Rows
                for (int i = 0; i < PartTime_Employees.size(); i++)
                {
                    double basic_salary = PartTime_Employees[i].basicSalary();
                    double working_hours = PartTime_Employees[i].getWorkingHours();
                    double hourly_wage = (basic_salary / 30) / 8;
                    double total_amount = hourly_wage * working_hours;
                    double tax_deduction = (total_amount / 100) * 2;
                    double net_amount = total_amount - tax_deduction - security_tax;

                    cout << left << setw(5) << PartTime_Employees[i].empID()
                         << setw(10) << PartTime_Employees[i].empName()
                         << setw(15) << PartTime_Employees[i].empPosition()
                         << setw(12) << PartTime_Employees[i].startDate()
                         << setw(15) << fixed << setprecision(2) << basic_salary
                         << setw(12) << fixed << setprecision(2) << working_hours
                         << setw(15) << fixed << setprecision(2) << hourly_wage
                         << setw(15) << fixed << setprecision(2) << total_amount
                         << setw(12) << fixed << setprecision(2) << tax_deduction
                         << setw(17) << fixed << setprecision(2) << security_tax
                         << setw(12) << fixed << setprecision(2) << net_amount << endl;
                }

                cout << "******************************************" << endl;
            }
            break;
        }
        case 5:
        {
            vector<Employee *> all_employees;
            for (auto &ft : Fulltime_Employees)
                all_employees.push_back(&ft);
            for (auto &pt : PartTime_Employees)
                all_employees.push_back(&pt);

            quickSort(all_employees, 0, all_employees.size() - 1);

            // Display sorted employees
            if (all_employees.empty())
            {
                cout << "No employees found to display!" << endl;
                break;
            }

            double total_fulltime_net_salary = 0.0;
            double total_parttime_net_salary = 0.0;

            cout << "\n***** Employees Sorted by Net Salary (Low to High) *****\n";
            cout << left << setw(10) << "ID"
                 << setw(20) << "Name"
                 << setw(15) << "Position"
                 << setw(15) << "Type"
                 << setw(15) << "Net Salary" << endl;

            for (int i = 0; i < all_employees.size(); i++)
            {
                double net_salary = 0.0;
                if (all_employees[i]->empType() == "fulltime")
                {
                    FullTime *ft = dynamic_cast<FullTime *>(all_employees[i]);
                    net_salary = ft->fulltimeTotalNetSalary();
                    total_fulltime_net_salary += net_salary;
                }
                else if (all_employees[i]->empType() == "parttime")
                {
                    PartTime *pt = dynamic_cast<PartTime *>(all_employees[i]);
                    net_salary = pt->parttimeTotalNetSalary();
                    total_parttime_net_salary += net_salary;
                }

                cout << left << setw(10) << all_employees[i]->empID()
                     << setw(20) << all_employees[i]->empName()
                     << setw(15) << all_employees[i]->empPosition()
                     << setw(15) << all_employees[i]->empType()
                     << setw(15) << fixed << setprecision(2) << net_salary << endl;
            }

            double total_monthly_salary = total_fulltime_net_salary + total_parttime_net_salary;

            // Monthly report
            cout<<endl;
            cout << "************************* Monthly Report *************************" << endl;
            cout << "--- Total Monthly Fulltime Salary Fees ---" << endl;
            cout << "------------------------------------------" << endl;
            cout << " Total Fulltime Employee : " << Fulltime_Employees.size() << endl;
            cout << " Total Fulltime Monthly Salary Cost : " << fixed << setprecision(2) << total_fulltime_net_salary << endl;

            cout << "--- Total Monthly Parttime Salary Fees ---" << endl;
            cout << "------------------------------------------" << endl;
            cout << " Total Parttime Employee : " << PartTime_Employees.size() << endl;
            cout << " Total Parttime Monthly Salary Cost : " << fixed << setprecision(2) << total_parttime_net_salary << endl;
            cout << "******************************************************************" << endl;
            cout << "Total Monthly Salary for all Employees : " << fixed << setprecision(2) << total_monthly_salary << endl;
            cout << "******************************************************************" << endl;
            break;
        }
        case 6:
            cout << "Thank You for using this program..." << endl;
            return 0;
        default:
            cout << "Invalid option, please try again..." << endl;
            break;
        }
    }
    return 0;
}


