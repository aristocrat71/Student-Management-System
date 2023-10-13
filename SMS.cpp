#include<iostream>
#include<stdio.h>
#include<cstring>
#include<fstream>
#include<sstream>
#include<unistd.h>

using namespace std;

void pageclear()
{
    #if defined(_WIN32)
        // Windows-specific code
        system("cls");
    #elif defined(__linux__)
        // Linux-specific code
        system("clear");
    #else
        // General code or warning
        printf("Running on an unsupported OS.\n");
    #endif
}

class Student
{
    string name;
    int roll_number;
    string email_id;
    string gender;
    string address;
    string phone_no;

    friend class SIMS;

    public:

        Student(string _name, int _roll, string _gender, string _address, string _phone_no)
        {
            name = _name;
            roll_number = _roll;
            gender = _gender;
            address = _address;
            phone_no = _phone_no;
        }

        friend void operator<< (ostream &print, const Student& obj)
        {
            print<<"\tName: "<<obj.name<<endl;
            print<<"\tRoll no: "<<obj.roll_number<<endl;
            print<<"\tEmail id: "<<obj.email_id<<endl;
            print<<"\tPhone number: "<<obj.phone_no<<endl;
            print<<"\tGender: "<<obj.gender<<endl;
            print<<"\tAddress: "<<obj.address<<endl;
        }
};
    
class Admissions 
{
    string admission_status,email_id;
    bool reporting;
    public:
    Admissions(string _email_id, string _admission)
    {
        admission_status = _admission;
        email_id = _email_id;
    }

    friend void operator<< (ostream &print, const Admissions& obj)
    {
        print<<"\tAdmission Status: "<<obj.admission_status<<endl;
        print<<"\tEmail id provided: "<<obj.email_id<<endl;
    }

};

class Mess_Tracking 
{
    string dish_type;
    public:
    Mess_Tracking()
    {}

    Mess_Tracking(string _dish)
    {dish_type = _dish;}

    void setDish(string _dish)
    {
        dish_type = _dish;
    }

    int dishCost()
    {
        if(dish_type =="Veg")
            return 50000;
        return 52000;
    }
};

class Fees : public Mess_Tracking
{
    int paid_fee;
    int messhostel_fee;
    int tuition_fee;
    int pending_fee;

    public:
    Fees(int _paid, int _tuition, string _dish)
    {
        paid_fee = _paid;
        setDish(_dish);
        messhostel_fee = dishCost();
        tuition_fee = _tuition;
        pending_fee = calcPending();
    }

    int calcPending()
    {
        pending_fee = messhostel_fee + tuition_fee - paid_fee;
        return pending_fee;
    }

    friend void operator<< (ostream &print, const Fees& obj)
    {
        print<<"\tPaid fee: "<<obj.paid_fee<<endl;
        print<<"\tMess hostel fee: "<<obj.messhostel_fee<<endl;
        print<<"\tTuition fee: "<<obj.tuition_fee<<endl;
        print<<"\tPending fee: "<<obj.pending_fee<<endl;
    }

};

class CourseRegistration
{
    string course;
    string branch;
    int jee_rank;

    public:
    CourseRegistration()
    {}
    CourseRegistration(string _course, string _branch, int _jee)
    {
        course = _course;
        branch = _branch;
        jee_rank = _jee;
    }
    friend void operator<< (ostream &print, const CourseRegistration& obj)
    {
        print<<"\tJee Rank: "<<obj.jee_rank<<endl;
        print<<"\tCourse: "<<obj.course<<endl;
        print<<"\tBranch: "<<obj.branch<<endl;
    }
};

class HostelAdmission 
{
    int room_no;
    string roommate;
    
    public:
    HostelAdmission(int _room, string _mate)
    {
        room_no = _room;
        roommate = _mate;
    }
    int getRoom()
        {return room_no;}
    
    string getRoommate()
        {return roommate;}

    friend void operator<< (ostream &print, const HostelAdmission& obj)
    {
        print<<"\tHostel Room: "<<obj.room_no<<endl;
        print<<"\tAlloted Roommate: "<<obj.roommate<<endl;
    }
};

class ResultGeneration
{
    int marks;
    string letter_grade;
    string pass_status;
    string remarks;

    public:

    ResultGeneration(int _marks)
    {
        marks = _marks;
        calcResult();
    }

    void calcResult()
    {
        if(marks > 95)
        {
            letter_grade = 'S';
            pass_status = "Pass";
        }
        else if(marks > 85)
        {
            letter_grade = 'A';
            pass_status = "Pass";
        }
        else if(marks > 75)
        {
            letter_grade = 'B';
            pass_status = "Pass";
        }
        else if(marks > 68)
        {
            letter_grade = 'C';
            pass_status = "Pass";
        }
        else if(marks > 60)
        {
            letter_grade = 'E';
            pass_status = "Pass";
        }
        else
        {
            letter_grade = 'F';
            pass_status = "Fail";
        }
    }

    string getPass()
        {return pass_status;}
    
    string getLetter()
        {return letter_grade;}

    void setRemarks(string _remarks)
        {remarks = _remarks;}

    friend void operator<< (ostream &print, const ResultGeneration& obj)
    {
        print<<"\tMarks: "<<obj.marks<<endl;
        print<<"\tGrade: "<<obj.letter_grade<<endl;
        print<<"\tPass Status: "<<obj.pass_status<<endl;
        print<<"\tRemarks: "<<obj.remarks<<endl;
    }
};

class SMS
{
    public:
        void cmdInput();
        void update(int current, string* edit);
        void deleteStudent(int current);
        friend void operator<<(ostream &print, SMS &obj)
        {
            obj.cmdInput();
        }
};

void SMS :: deleteStudent(int current)
{
    fstream file;
    fstream tempfile;
    string line;

    tempfile.open("newtemp.csv",ios::app);
    tempfile.clear();
    file.open("database.csv", ios::in | ios::app);
    int track=-1;
    while (getline(file, line))
    {
        track++;
        if(track==current)
            continue;
        else
            tempfile<<line<<"\n";
    }
    tempfile<<"\b";
    tempfile.close();
    file.close();
    remove("database.csv");
    sleep(1);
    rename("newtemp.csv","database.csv");
}

void SMS::update(int current, string* edit)
{
    fstream file;
    fstream tempfile;
    string line;

    tempfile.open("newtemp.csv",ios::app);
    tempfile.clear();
    file.open("database.csv", ios::in | ios::app);
    int i=0, track=-1;
    while (getline(file, line))
    {
        i=0;
        track++;
        if(track==current)
        {
            while(i<21)
                tempfile<<edit[i++]<<",";
            tempfile<<"\n";
        }
        else
            tempfile<<line<<"\n";
    }
    tempfile<<"\b";
    tempfile.close();
    file.close();
    remove("database.csv");
    sleep(1);
    rename("newtemp.csv","database.csv");
}

void SMS::cmdInput()
{
    int query, flag= false,delstudent= false;
    bool goquery = false;
    string cmd;
    string inp;
    int current;
    pageclear();
    cout<<"\t<< Welcome to the Student Management System (SMS) >>\n"<<endl;
    while(1)
    {
        cout<<">Enter query: \n1.Add new Student\n2.Search prexisting student\n3.Exit\n\nChoice: ";
        cin>>query;
        if(query == 1)
        {
            ofstream writer;
            writer.open("database.csv", ios::app);
            pageclear();
            //[0.NAME, 1.ROLL, 2.GENDER, 3.PHONE, 4.ADDRESS, 5.EMAIL ID, 6.ADMISSION STATUS, 7.MESS_DISH_TYPE, 8.PAID FEE, 9.MESS + HOSTEL FEE, 10.TUITION FEE, 11.PENDING FEE, 12.COURSE, 13.BRANCH, 14.JEE_RANK, 15.MARKS, 16.LETTER_GRADE, 17.PASS/GRADUATION, 18.REMARKS, 19.ROOM NO., 20.ROOMMATE]
            string details[21];
            cout<<"-----Add Student-----"<<endl;
            cout<<"Name: ";
            cin>>details[0];
            cout<<"Roll no: ";
            cin>>details[1];
            cout<<"Gender: ";
            cin>>details[2];
            cout<<"Phone no: ";
            cin>>details[3];
            cout<<"Address: ";
            getline(cin,details[4]);
            getline(cin,details[4]);
            Student stud(details[0], stoi(details[1]), details[2], details[4], details[3]);
            cout<<"Email: ";
            cin>>details[5];
            cout<<"Admission status: ";
            cin>>details[6];
            Admissions admission(details[5], details[6]);
            cout<<"Veg/Non-Veg Preference: ";
            cin>>details[7];
            Mess_Tracking mess(details[7]);
            cout<<"Paid fee: ";
            cin>>details[8];
            cout<<"Mess+Hostel Fee: "<<mess.dishCost()<<endl;
            details[9] = to_string(mess.dishCost());
            cout<<"Tuition Fee: ";
            cin>>details[10];
            Fees fee(stoi(details[8]),stoi(details[10]), details[7]);
            cout<<"Pending fee: "<<fee.calcPending();
            details[11] = to_string(fee.calcPending());
            cout<<"\nCourse: ";
            cin>>details[12];
            cout<<"Branch: ";
            cin>>details[13];
            cout<<"JEE Rank: ";
            cin>>details[14];
            CourseRegistration coursereg(details[12],details[13],stoi(details[14]));
            cout<<"Marks: ";
            cin>>details[15];
            ResultGeneration results(stoi(details[15]));
            cout<<"Grade: "<<results.getLetter()<<endl;
            details[16] = results.getLetter();
            cout<<"Status: "<<results.getPass()<<endl;
            details[17] = results.getPass();
            cout<<"Remarks: ";
            getline(cin,details[18]);
            getline(cin, details[18]);
            results.setRemarks(details[18]);
            cout<<"Hostel Room No.: ";
            cin>>details[19];
            cout<<"Roommate: ";
            cin>>details[20];
            HostelAdmission hostel(stoi(details[19]), details[20]);

            int i=0;
            writer<<"\n";
            while(i<21)
                writer<<details[i++]<<",";
            
            cout<<"\t\tStudent added successfully ! "<<endl;
            sleep(2);
            pageclear();
        }
        else if(query == 3)
        {
            cout<<"\n\t\t<< Thank you for using the SMS >>"<<endl;
            sleep(2);
            pageclear();
            exit(1);
        }
        else
        {
            pageclear();
            while(1)
            {
                current = -1;
                flag = false;
                cout<<">Following are the commands: "<<endl;
                cout<<"-fulldetails (Read full details of student)"<<endl;
                cout<<"-<rd/up> personal (read/update Student details)"<<endl;
                cout<<"-<rd/up> admission (read/update Admission related query)"<<endl;
                cout<<"-<rd/up> mess (read/update Mess related query)"<<endl;
                cout<<"-<rd/up> fee (read/update Fee related query)"<<endl;
                cout<<"-<rd/up> course (read/update Course related query)"<<endl;
                cout<<"-<rd/up> result (read/update Fee related query)"<<endl;
                cout<<"-<rd/up> hostel (read/update Hostel related query)"<<endl;
                cout<<"-del student (Delete student)"<<endl;
                cout<<"-gosearch (Go to search)"<<endl;
                cout<<"-goquery (Go to select query)\n"<<endl;
                cout<<">Roll no / Name: ";
                cin>>inp;
                if(inp == "goquery")
                    {pageclear();break;}

                ifstream reader;
                reader.open("database.csv");
                string line;
                //[0.NAME, 1.ROLL, 2.GENDER, 3.PHONE, 4.ADDRESS, 5.EMAIL ID, 6.ADMISSION STATUS, 7.MESS_DISH_TYPE, 8.PAID FEE, 9.MESS + HOSTEL FEE, 10.TUITION FEE, 11.PENDING FEE, 12.COURSE, 13.BRANCH, 14.JEE_RANK, 15.MARKS, 16.LETTER_GRADE, 17.PASS/GRADUATION, 18.REMARKS, 19.ROOM NO., 20.ROOMMATE]
                string details[21];
                while (getline(reader, line))
                {
                    int i=0;
                    current++;
                    stringstream comd(line);
                    while(!comd.eof())
                        {getline(comd, details[i++], ',');if(i==21)break;}
                    if(details[0] == inp || details[1] == inp)
                        {flag = true;break;}
                }
                reader.close();
                if(!flag)
                    {cout<<">Student not found\n"<<endl;sleep(1);pageclear();}
                else
                {
                    Student stud(details[0], stoi(details[1]), details[2], details[4], details[3]);
                    Admissions admission(details[5], details[6]);
                    Mess_Tracking mess(details[7]);
                    Fees fee(stoi(details[8]),stoi(details[10]),details[7]);
                    CourseRegistration coursereg(details[12],details[13],stoi(details[14]));
                    ResultGeneration results(stoi(details[15]));
                    results.setRemarks(details[18]);
                    HostelAdmission hostel(stoi(details[19]), details[20]);
                    cout<<"Student found : \n"<<details[0]<<"\n"<<details[1]<<"\n"<<endl;
                    while(1)
                    {
                        goquery = false;
                        cout<<">";
                        getline(cin, inp);
                        cout<<"\b";
                        if(inp.substr(0,2) == "rd")
                        {
                            cmd = inp.substr(3);
                            if(cmd == "personal")
                                cout<<stud;
                            if(cmd == "admission")
                                cout<<admission;
                            else if(cmd == "fee")
                                cout<<fee;
                            else if(cmd == "hostel")
                                cout<<hostel;
                            else if(cmd == "result")
                                cout<<results;
                        }

                        else if(inp.substr(0,2) == "up")
                        {
                            cmd = inp.substr(3);
                            if(cmd == "personal")
                            {
                                cout<<"\tName: ";
                                cin>>details[0];
                                cout<<"\tRoll no: ";
                                cin>>details[1];
                                cout<<"\tGender: ";
                                cin>>details[2];
                                cout<<"\tPhone no: ";
                                cin>>details[3];
                                cout<<"\tAddress: ";
                                getline(cin,details[4]);
                                getline(cin,details[4]);
                                Student stud(details[0], stoi(details[1]), details[2], details[4], details[3]);
                                update(current, details);
                            }
                            else if(cmd == "admission")
                            {
                                cout<<"\tEmail: ";
                                cin>>details[5];
                                cout<<"\tAdmission status: ";
                                cin>>details[6];
                                Admissions admission(details[5], details[6]);
                                update(current, details);
                            }
                            else if(cmd == "mess")
                            {
                                cout<<"\tVeg/Non-Veg Preference: ";
                                cin>>details[7];
                                Mess_Tracking mess(details[7]);
                                update(current, details);
                            }
                            else if(cmd == "fee")
                            {
                                cout<<"\tPaid fee: ";
                                cin>>details[8];
                                cout<<"\tMess+Hostel Fee: "<<mess.dishCost()<<endl;
                                details[9] = to_string(mess.dishCost());
                                cout<<"\tTuition Fee: ";
                                cin>>details[10];
                                Fees fee(stoi(details[8]),stoi(details[10]), details[7]);
                                update(current, details);
                            }
                            else if(cmd == "course")
                            {
                                cout<<"\n\tCourse: ";
                                cin>>details[12];
                                cout<<"\tBranch: ";
                                cin>>details[13];
                                cout<<"\tJEE Rank: ";
                                cin>>details[14];
                                CourseRegistration coursereg(details[12],details[13],stoi(details[14]));
                                update(current, details);
                            }
                            else if(cmd == "result")
                            {
                                cout<<"\tMarks: ";
                                cin>>details[15];
                                ResultGeneration results(stoi(details[15]));
                                cout<<"\tGrade: "<<results.getLetter()<<endl;
                                details[16] = results.getLetter();
                                cout<<"\tStatus: "<<results.getPass()<<endl;
                                details[17] = results.getPass();
                                cout<<"\tRemarks: ";
                                getline(cin,details[18]);
                                getline(cin, details[18]);
                                results.setRemarks(details[18]);
                                update(current, details);
                            }
                            else if(cmd == "hostel")
                            {
                                cout<<"\tHostel Room No.: ";
                                cin>>details[19];
                                cout<<"\tRoommate: ";
                                cin>>details[20];
                                HostelAdmission hostel(stoi(details[19]), details[20]);
                                update(current, details);   
                            }
                        } 

                        else if(inp == "del student")
                        {
                            sleep(1);
                            deleteStudent(current);
                            pageclear();
                            break;
                        }
                        else if(inp == "fulldetails")
                        {
                            cout<<"\tName: "<<details[0]<<endl;
                            cout<<"\tRoll No: "<<details[1]<<endl;
                            cout<<"\tGender: "<<details[2]<<endl;
                            cout<<"\tPhone Number: "<<details[3]<<endl;
                            cout<<"\tAddress: "<<details[4]<<endl;
                            cout<<"\tEmail Id: "<<details[5]<<endl;
                            cout<<"\tAdmission Status: "<<details[6]<<endl;
                            cout<<"\tMess dish type: "<<details[7]<<endl;
                            cout<<"\tPaid fees: "<<details[8]<<endl;
                            cout<<"\tMess+Hostel fees: "<<details[9]<<endl;
                            cout<<"\tTuition fees: "<<details[10]<<endl;
                            cout<<"\tPending fees: "<<details[11]<<endl;
                            cout<<"\tCourse: "<<details[12]<<endl;
                            cout<<"\tBranch: "<<details[13]<<endl;
                            cout<<"\tJee rank: "<<details[14]<<endl;
                            cout<<"\tMarks: "<<details[15]<<endl;
                            cout<<"\tGrade: "<<details[16]<<endl;
                            cout<<"\tAcademic status: "<<details[17]<<endl;
                            cout<<"\tRemarks: "<<details[18]<<endl;
                            cout<<"\tHostel Room: "<<details[19]<<endl;
                            cout<<"\tRoom-mate: "<<details[20]<<endl;
                        }

                        else if(inp == "gosearch")
                            {pageclear();break;}
                        else if(inp == "goquery")
                            {goquery = true;break;}
                    }
                    if(goquery)
                        {pageclear();break;}
                }
            }
        }
    }
}

int main()
{
    SMS system1;
    cout<<system1;
    return 0;
}