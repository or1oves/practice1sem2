#include "iostream"
#include <string>
#include <fstream>

using namespace std;

int task;
const int COUNT = 30;

struct Student{
    string fullName;
    char sex;
    int id;
    int group;
    int grades[8];
    float GPA; // средний балл
};

Student database[COUNT];

void clearStream() {
    cin.clear();
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void perenosik(){
    cout << '\n';
}

int inputInt(){
    int number;
    while(!(cin >> number)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "wrong input! \n";
    }
    return number;
}

void menu(){
    cout << "0) exit"; perenosik();
    cout << "1) add de student"; perenosik();
    cout << "2) edit de information of student"; perenosik();
    cout << "3) show de all students"; perenosik();
    cout << "4) show de all students in group"; perenosik();
    cout << "5) show de top 3 of students"; perenosik();
    cout << "6) show de students by his gender"; perenosik();
    cout << "7) show de students grade information"; perenosik();
    cout << "8) show ~K student"; perenosik();
}

// void addStudent(Student student, Student *students);
// int countOfStudents(Student *students);

float countGPA(int grades[8]){
    float GPAScore = 0;
    for(int i = 0; i < 8; i++){
        GPAScore += grades[i];
    }
    GPAScore /= 8;
    return GPAScore;
}

Student createStudent(){
    cout << "enter name: ";
    clearStream();
    Student student;
    getline(cin, student.fullName);
    cout << "enter sex: ";
    cin >> student.sex;
    cout << "enter group: ";
    student.group = inputInt();
    cout << "enter id: ";
    student.id = inputInt();
    cout << "enter grades (by spaces): ";
    for(int i = 0; i < 8; i++){
        student.grades[i] = inputInt();
    }
    countGPA(student.grades);
    return student;
}

void displayStudent(int a, Student database[COUNT]){
    cout << "name: " << database[a].fullName;
    perenosik();
    cout << "sex: " << database[a].sex;
    perenosik();
    cout << "group: " << database[a].group;
    perenosik();
    cout << "id: " << database[a].id;
    perenosik();
    cout << "grades: ";
    for(int i = 0; i < 8; i++){
        cout << database[a].grades[i] << " ";
    }
    perenosik();
    cout << "GPA: " << database[a].GPA;
    perenosik();
    perenosik();
}

void displayAllStudent(int &listStudent, Student database[]){
    for(int a = 0; a < listStudent; a++){
        cout << "name: " << database[a].fullName;
        perenosik();
        cout << "sex: " << database[a].sex;
        perenosik();
        cout << "group: " << database[a].group;
        perenosik();
        cout << "id: " << database[a].id;
        perenosik();
        cout << "grades: ";
        for(int i = 0; i < 8; i++){
            cout << database[a].grades[i] << " ";
        }
        perenosik();
        cout << "GPA: " << database[a].GPA;
        perenosik();
        perenosik();
    }
}

Student changeId(Student student, int studentGroup, int &studentId, int &listStudent){
    if(studentId == 1){
        for(int i = 0; i < listStudent; i++){
            if(database[i].id >= studentId && database[i].group == studentGroup){
                ++database[i].id;
            }
        }
        student.id = studentId;
    }
    else{
        for(int i = 0; i < listStudent; i++){
            if(database[i].id >= studentId && database[i].id < student.id && database[i].group == studentGroup){
                ++database[i].id;
            }
        }
        student.id = studentId;
    }
    return student;
}

void changeStudents(int &studentGroup, int &studentId, int &listStudent){
    Student student;
    int exist = -1;
    for(int i = 0; i < listStudent; i++) {
        if (database[i].group == studentGroup && database[i].id == studentId) {
            student = database[i];
            exist = i;
            break;
        }
    }
    if(exist == -1){
        perenosik();
        cout << "wrong student";
        perenosik();
        perenosik();
    }
    else{
        perenosik();
        cout << "choose what to change:\n" <<
             "1) name\n" <<
             "2) sex\n" <<
             "3) group\n" <<
             "4) id\n" <<
             "5) grades\n";
        task = inputInt();
        switch (task){

            case 1:
                perenosik();
                cout << "change name: ";
                student.fullName = "";
                clearStream();
                getline(cin, student.fullName);
                break;

            case 2:
                perenosik();
                cout << "change sex: ";
                cin >> student.sex;
                break;

            case 3:
                perenosik();
                cout << "change group: ";
                student.group = studentGroup;
                student.group = inputInt();
                for(int i = 0; i << listStudent; i++){ // если студента убрали из группы
                    if(database[i].group == studentGroup && database[i].id > studentId){
                        --database[i].id;
                    }
                }
                student = changeId(student, student.group, studentId, listStudent);
                break;

            case 4:
                perenosik();
                cout << "change id: ";
                student.id = inputInt();
                student = changeId(student, studentGroup, studentId, listStudent);
                break;

            case 5:
                perenosik();
                cout << "change grades: ";
                for(int i = 0; i < 8; i++){
                    student.grades[i] = inputInt();
                }
                break;
        }
        database[exist] = student;
    }
}

void studentGrades(int &listStudent){
    int listGrades = 0;
    cout << "3 students: ";
    perenosik();
    for(int i = 0; i < listStudent; i++){
        for(int j = 0; j < 8; j++){
            if(database[i].grades[j] == 3){
                displayStudent(i, database);
                break;
            }
        }
    }
    perenosik();
    cout << "4-5 students: ";
    perenosik();
    for(int i = 0; i < listStudent; i++){
        for(int j = 0; j < 8; j++){
            if(database[i].grades[j] == 3){
                listGrades = -1;
                break;
            }
            else if(database[i].grades[j] == 5){
                ++listGrades;
            }
        }
        if(listGrades != -1 && listGrades != 8){
            displayStudent(i, database);
        }
    }
    perenosik();
    cout << "5 students: ";
    perenosik();
    for(int i = 0; i < listStudent; i++){
        if(database[i].GPA == 5){
            displayStudent(i, database);
        }
    }
}

void topStudents(Student top[COUNT], int &listStudent){
    int a;
    Student top2;
    for(int i = 1; i < listStudent; i++){
        top2 = top[i];
        a = i - 1;
        while(a >= 0 && (top[a].GPA > top2.GPA)){
            top[a + 1] = top[a];
            a = a - 1;
        }
        top[a + 1] = top2;
    }
    for(int a = listStudent - 1; a >= listStudent - 4; a--){
        displayStudent(a, top);
    }
}

int main(){
    int listStudent = 0, studentGroup, studentId, femaleStudent = 0, maleStudent = 0, existGroup = 0;
    ofstream outFile;
    ifstream inFile;
    fstream fs;
    inFile.open("/Users/or1oves/CLionProjects/untitled1/studentsLETI.txt");
    if(!inFile.is_open()){
        cout << "open error ***404***";
        exit(0);
    }
    else{
        while(!inFile.eof()){ // проверка на пустой файл
            getline(inFile, database[listStudent].fullName);
            inFile >> database[listStudent].sex;
            inFile >> database[listStudent].group;
            inFile >> database[listStudent].id;
            for(int i = 0; i < 8; i++){
                inFile >> database[listStudent].grades[i];
            }
            listStudent++;
            inFile.get();
        }
        for(int i = 0; i < listStudent; i++){
            database[i].GPA = countGPA(database[i].grades);
        }
        cout << "Done!";
        perenosik();
        perenosik();
    }
    inFile.close();
    while (true){
        menu();
        cout << "enter task: ";
        task = inputInt();
        switch(task){

            case 0:
                exit(0);

            case 1:
                outFile.open("/Users/or1oves/CLionProjects/untitled1/studentsLETI.txt", ofstream::app);
                if(!outFile.is_open()){
                    cout << "open error ***404***";
                    exit(404);
                }
                else if(listStudent + 1 > COUNT){
                    cout << "error : max size";
                    perenosik();
                }
                else{
                    database[listStudent] = createStudent();
                    outFile << '\n' << database[listStudent].fullName << '\n';
                    outFile << database[listStudent].sex << '\n';
                    outFile << database[listStudent].group << '\n';
                    outFile << database[listStudent].id << '\n';
                    for(int i = 0; i < 7; i++){
                        outFile << database[listStudent].grades[i] << " ";
                    }
                    outFile << database[listStudent].grades[7];
                    listStudent++;
                }
                outFile.close();
                perenosik();
                cout << "recording success";
                perenosik();
                break;

            case 2:
                perenosik();
                cout << "enter number of group: ";
                studentGroup = inputInt();
                cout << "enter number of id: ";
                studentId = inputInt();
                changeStudents(studentGroup,studentId,listStudent);
                outFile.open("/Users/or1oves/CLionProjects/untitled1/studentsLETI.txt");
                if(!outFile.is_open()){
                    cout << "open error ***404***";
                    exit(404);
                }
                else{
                    for(int i = 0; i < listStudent; i++){
                        outFile << database[i].fullName << '\n';
                        outFile << database[i].sex << '\n';
                        outFile << database[i].group << '\n';
                        outFile << database[i].id << '\n';
                        for(int j = 0; j < 7; j++){
                            outFile << database[i].grades[j] << " ";
                        }
                        outFile << database[i].grades[7];
                        if(i != listStudent - 1) outFile << '\n';
                    }
                }
                outFile.close();
                break;

            case 3:
                system("clear");
                displayAllStudent(listStudent, database);
                break;

            case 4:
                cout << "enter de group: ";
                studentGroup = inputInt();
                for(int i = 0; i < listStudent; i++){
                    if(database[i].group == studentGroup){
                        cout << database[i].fullName << "\t";
                        cout << database[i].sex << "\t";
                        cout << database[i].group << "\t";
                        cout << database[i].id << "\t";
                        for(int j = 0; j < 8; j++){
                            cout << database[i].grades[j] << " ";
                        }
                        cout << "\n\n";
                        ++existGroup;
                    }
                }
                if(existGroup == 0){
                    cout << "no students found :(";
                }
                break;

            case 5:
                topStudents(database, listStudent);
                break;

            case 6:
                for(int i = 0; i < listStudent; i++){
                    if(database[i].sex == 'M'){
                        maleStudent += 1; //maleStudent++
                    }
                    else{
                        femaleStudent += 1; //femaleStudent++
                    }
                }
                perenosik();
                cout << "female students: " << femaleStudent;
                perenosik();
                cout << "male students: " << maleStudent;
                perenosik();
                perenosik();
                break;

            case 7:
                system("clear");
                studentGrades(listStudent);
                break;

            case 8:
                clearStream();
                cout << "enter id: ";
                studentId = inputInt();
                for(int i = 0; i < listStudent; i++){
                    if(database[i].id == studentId){
                        displayStudent(i, database);
                    }
                }
                break;

            default:
                cout << "wrong task";
                perenosik();
                break;
        }
    }
    return 0;
}