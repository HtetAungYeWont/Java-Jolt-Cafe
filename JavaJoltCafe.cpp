#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int security_tax = 10;

class Employee
{
private:
    int employee_ID;
    string employee_name;
    string employee_position;
    string employee_type;
    string start_date;
    float basic_salary;

public:
    int EmployeeID() { return employee_ID; }
    string EmployeeName() { return employee_name; }
    string EmployeePosition() { return employee_position; }
    string EmployeeType() { return employee_type; }
    string StartDate() { return start_date; }
    double BasicSalary() { return basic_salary; }
    // Default Constructor
    Employee() : employee_ID(0), employee_name(""), employee_position(""), employee_type(""), start_date(""), basic_salary(0) {}

    void inputEmployee()
    {
        cout << "Enter Employee ID: ";
        cin >> employee_ID;
        cin.ignore();
        cout << "Enter Employee Name: ";
        getline(cin, employee_name);

        while (true)
        {
            cout << "Enter Employee Position (Full time: Supervisor, Barista, Cashier / Part time: Waiter, Waitress, Cleaner, Kitchen Staff): ";
            getline(cin, employee_position);

            if (employee_position == "Supervisor" || employee_position == "supervisor")
            {
                employee_type = "Full time";
                basic_salary = 2400;
                break;
            }
            else if (employee_position == "Barista" || employee_position == "barista")
            {
                employee_type = "Full time";
                basic_salary = 1920;
                break;
            }
            else if (employee_position == "Cashier" || employee_position == "cashier")
            {
                employee_type = "Full time";
                basic_salary = 1790;
                break;
            }
            else if (employee_position == "Waiter" || employee_position == "waiter")
            {
                employee_type = "Part time";
                basic_salary = 1700;
                break;
            }
            else if (employee_position == "Waitress" || employee_position == "waitress")
            {
                employee_type = "Part time";
                basic_salary = 1700;
                break;
            }
            else if (employee_position == "Cleaner" || employee_position == "cleaner")
            {
                employee_type = "Part time";
                basic_salary = 1400;
                break;
            }
            else if (employee_position == "KitchenStaff" || employee_position == "kitchenstaff")
            {
                employee_type = "Part time";
                basic_salary = 1850;
                break;
            }
            else
            {
                cout << "Invalid Employee Position, try again..." << endl;
            }
        }
        cout << "Enter Employee's Start Date (dd/mm/yy): ";
        cin >> start_date;
    }

    void displayEmployee()
    {
        cout << left << setw(15) << "Employee ID: " << setw(15) << employee_ID << endl;
        cout << left << setw(15) << "Employee Name: " << setw(15) << employee_name << endl;
        cout << left << setw(15) << "Employee Position: " << setw(15) << employee_position << endl;
        cout << left << setw(15) << "Employee Type: " << setw(15) << employee_type << endl;
        cout << left << setw(15) << "Start Date: " << setw(15) << start_date << endl;
        cout << left << setw(15) << "Basic Salary: $" << setw(15) << basic_salary << endl;
    }
};

class Fulltime : public Employee
{
private:
    int leave_day;
    int overtime_hr, overtime_sal, bonus, total_amount, tax_sal, net_sal = 0;

public:
    Fulltime() : leave_day(0), overtime_hr(0) {}

    void fulltimeData()
    {
        inputEmployee();
        cout << "Enter Leave Days: ";
        cin >> leave_day;
        cout << "Enter Overtime Hours: ";
        cin >> overtime_hr;

        if (leave_day == 0)
        {
            bonus = 300;
        }
        else if (leave_day == 1)
        {
            bonus = 200;
        }
        else if (leave_day == 2)
        {
            bonus = 100;
        }
        else
        {
            bonus = 0;
        }
    }

    int fulltimeTotalSalary()
    {
        double salary = BasicSalary();

        overtime_sal = (((salary / 30) / 8) * overtime_hr) * 2;

        if (leave_day < 4 && overtime_hr >= 0)
        {
            total_amount = salary + overtime_sal + bonus;
            tax_sal = (total_amount / 100) * 2;
        }
        else if (leave_day > 4 && overtime_hr > 0)
        {
            total_amount = salary - ((salary / 100) * 1) + overtime_sal - bonus;
            tax_sal = (total_amount / 100) * 2;
        }
        else
        {
            total_amount = salary - bonus + overtime_sal;
            tax_sal = (total_amount / 100) * 2;
        }
        return total_amount;
    }

    int fulltimeTotalNetSalary()
    {
        if (total_amount == 0)
            fulltimeTotalSalary();

        net_sal = total_amount - ((total_amount / 100) * 2) - security_tax;
        return net_sal;
    }

    void displayFulltimeData()
    {
        fulltimeTotalSalary();
        fulltimeTotalNetSalary();

        displayEmployee();
        cout << left << setw(22) << "Leave Days: " << setw(22) << leave_day << endl;
        cout << left << setw(22) << "Over Time Hours: " << setw(22) << overtime_hr << endl;
        cout << left << setw(22) << "Over Time Salary: $" << setw(22) << overtime_sal << endl;
        cout << left << setw(22) << "Bonus: $" << setw(22) << overtime_hr << endl;
        cout << left << setw(22) << "Tax Fees: $" << setw(22) << tax_sal << endl;
        cout << left << setw(22) << "Security Fees: $" << setw(22) << security_tax << endl;
        cout << left << setw(22) << "Total Amount: $" << setw(22) << total_amount << endl;
        cout << left << setw(22) << "Total Net Amount: $" << setw(22) << net_sal << endl;
        cout<<endl;
    }
};

class Parttime : public Employee
{
private:
    int hourly_wage, working_hours, total_amount, tax_fees, net_sal = 0;

public:
    Parttime() : working_hours(0) {}

    void inputParttimeData()
    {
        inputEmployee();
        cout << "Enter working hours: ";
        cin >> working_hours;
        parttimeTotalNetSalary();
    }

    int parttimeTotalNetSalary()
    {
        int salary = BasicSalary();
        hourly_wage = (salary / 30) / 8;

        total_amount = hourly_wage * working_hours;
        tax_fees = (total_amount / 100) * 2;
        net_sal = total_amount - tax_fees - security_tax;
        return net_sal;
    }

    void displayParttimeData()
    {
        parttimeTotalNetSalary();

        displayEmployee();
        cout << left << setw(22) << "Working Hours: $" << setw(22) << working_hours << endl;
        cout << left << setw(22) << "Hourly Wage: $" << setw(22) << hourly_wage << endl;
        cout << left << setw(22) << "Total Amount: $" << setw(22) << total_amount << endl;
        cout << left << setw(22) << "Tax Fees: $" << setw(22) << tax_fees << endl;
        cout << left << setw(22) << "Security Fees: $" << setw(22) << security_tax << endl;
        cout << left << setw(22) << "Total Net Amount: $" << setw(22) << net_sal << endl;
        cout << endl;
    }
};

vector<Fulltime> Fulltime_Employees;
vector<Parttime> PartTime_Employees;

int main()
{
    int opt_no;
    cout << "******************************" << endl;
    cout << "        Java Jolt Cafe        " << endl;
    cout << "******************************" << endl;

    while (opt_no != 6)
    {
        cout << "1. View All Employees Salary" << endl;
        cout << "2. View Full Time Employees Salary" << endl;
        cout << "3. View Part Time Employees Salary" << endl;
        cout << "4. Insert Employee Data" << endl;
        cout << "5. Update Employee Data" << endl;
        cout << "6. Exit" << endl;

        cout << "Enter Option Number: ";
        cin >> opt_no;
        cin.ignore();

        switch (opt_no)
        {
        case 1:
        {
            cout << "***** Full Time Employess Data *****" << endl;
            for (int i = 0; i < Fulltime_Employees.size(); i++)
            {
                Fulltime_Employees[i].displayFulltimeData();
            }

            cout << "***** Part Time Employess Data *****" << endl;
            for (int i = 0; i < PartTime_Employees.size(); i++)
            {
                PartTime_Employees[i].displayParttimeData();
            }
            break;
        }

        case 2:
        {
            if (Fulltime_Employees.empty())
            {
                cout << "Empty Data....." << endl;
            }
            else
            {
                for (int i = 0; i < Fulltime_Employees.size(); i++)
                {
                    cout << "***** Full Time Employees Data *****" << endl;
                    Fulltime_Employees[i].displayFulltimeData();
                }
            }
            break;
        }

        case 3:
        {
            if (PartTime_Employees.empty())
            {
                cout << "Empty Data....." << endl;
            }
            else
            {
                for (int i = 0; i < PartTime_Employees.size(); i++)
                {
                    cout << "***** Part Time Employees Data *****" << endl;
                    PartTime_Employees[i].displayParttimeData();
                }
            }
            break;
        }

        case 4:
        {
            int e_num=0;
            string e_type;
            cout<<"Enter Number of Employees to Insert: ";
            cin>>e_num;

            for(int i=0;i<e_num;i++)
            {
                cout<<"***** For Employee No. "<<i+1<<" *****"<<endl;
                cout<<"Enter Type of Employee to Insert (FullTime/PartTime): ";
                cin>>e_type;

                if(e_type=="FullTime" || e_type=="fulltime")
                {
                    Fulltime new_employee;
                    new_employee.fulltimeData();
                    cout<<endl;
                    Fulltime_Employees.push_back(new_employee);
                }
                else if(e_type=="PartTime" || e_type=="parttime")
                {
                    Parttime new_employee;
                    new_employee.inputParttimeData();
                    cout<<endl;
                    PartTime_Employees.push_back(new_employee);
                }
            }
            break;
        }

        case 5:
        {
            int e_id;
            string e_type;
            bool cond=false;

            cout<<"Enter Employee Type to Update (Full Time/Part Time): ";
            cin>>e_type;
            cin.ignore();

            if(e_type=="FullTime" || e_type=="fulltime")
            {
                cout<<"Enter Employee ID to Update: ";
                cin>>e_id;

                for(int i=0;i<Fulltime_Employees.size();i++)
                {
                    if(e_id==Fulltime_Employees[i].EmployeeID())
                    {
                        cout<<"Update Data for Full Time Employee ID "<<e_id<<endl;
                        Fulltime_Employees[i].fulltimeData();
                        Fulltime_Employees[i].fulltimeTotalSalary();
                        Fulltime_Employees[i].fulltimeTotalNetSalary();
                        cond=true;
                        break;
                    }
                }
                if(cond==false)
                {
                    cout<<"Invalid Full Time Employee..."<<endl;
                }
            }
            else if(e_type=="PartTime" || e_type=="parttime")
            {
                cout<<"Enter Employee ID to Update: ";
                cin>>e_id;

                for(int i=0;i<PartTime_Employees.size();i++)
                {
                    if(e_id==PartTime_Employees[i].EmployeeID())
                    {
                        cout<<"Update Data for Part Time Employee ID "<<e_id<<endl;
                        PartTime_Employees[i].inputParttimeData();
                        PartTime_Employees[i].parttimeTotalNetSalary();
                        cond=true;
                        break;
                    }
                }
                if(cond==false)
                {
                    cout<<"Invalid Part Time Employee..."<<endl;
                }
            }
            else
            {
                cout<<"Invalid Employee Type....."<<endl;
            }
            break;
        }

        case 6:
        {
            return 0;
        }
        default:
            cout << "Invalid Option, please try again....." << endl;
            break;
        }
    }
}