
//***** STUDENT REPORT MANAGEMENT SYSTEM *****

#include<iostream>
#include<conio.h>
#include<string.h>
#include <fstream>
#include <sstream>              ////sstream is basically convert numercial to string or viceversa.

using namespace std;

int totalstudents=0;                          // globally define variable     // Number of Students

struct Student                   // Here Structure is used to store the Student details
{ 
  int id;
  float marks,per;
  string name,grade;
};

Student s[100];          // can handle 100 students only, change this to haandle more
            
 // function to load number of total records from file           
void updateTotalStudents(){
	ifstream inFile("totalstudents.txt");
	if (inFile.is_open()) {
        inFile >> totalstudents;  // only int totalstudents is stored in this file, loading totalstudents from file
        inFile.close();
    }
}   
  
// Function to Enter the student record         
void enter()
{   
	system("cls");
	Student newstudent;
	cout<<"\n\n\t\t\t *** ENTER THE STUDENT RECORD DETAILS ***";
	cout<<"\n\n Enter student Id:";
	cin>>newstudent.id;
	cout<<"\n\n Enter Student Name without space:";
	cin>>newstudent.name;
	cout<<"\n\n Enter Student Marks:";
	cin>>newstudent.marks;
	newstudent.per = newstudent.marks/500.0*100;
	if(newstudent.per >=85)
	newstudent.grade = "A+";
	else if(newstudent.per >=75)
	newstudent.grade = "A";
	else if(newstudent.per >=65)
	newstudent.grade = "B+";
	else if(newstudent.per >=55)
	newstudent.grade = "B";
	else if(newstudent.per >=50)
	newstudent.grade = "C";
	else if(newstudent.per >=45)
    newstudent.grade = "D";
	else if(newstudent.per >=33)
	newstudent.grade = "E";
	else
	newstudent.grade = "F";
	
	updateTotalStudents();
	
	ofstream outFile("records.txt", std::ios::app); // opens the file in append mode
    outFile << newstudent.id << "," << newstudent.name << "," << newstudent.marks << ","  << newstudent.per << ","  << newstudent.grade  << endl; // writes the record to the file
    outFile.close(); // closes the file
    
    
    ofstream outFile2("totalstudents.txt", ios::out | ios::trunc); // opens the file in rewrite mode
    outFile2 << ++totalstudents <<endl; // increment the totalstudents and save to the file 
    outFile2.close(); // closes the file
	cout<<"\n\n ***  RECORD ENTERED SUCCESSFULLY ***";                     
}

void writestudents(){
	ofstream outFile("records.txt", ios::out | ios::trunc); // opens the file in rewrite mode (write and truncate already written text mode)
	
	for(int a=0;a<totalstudents;a++){
		outFile << s[a].id << "," << s[a].name << "," << s[a].marks << ","  << s[a].per << ","  << s[a].grade  << endl; // writes the record to the file
	} 
	outFile.close(); // closes the file
}

void loadstudents(){
	ifstream inFile("records.txt"); //open file as input stream
	int index=0;
	string line;
	string  tid, tname, tmarks, tper, tgrade; //strings to temporary store the infromation from file
	
	while (getline(inFile, line)) {  //get a line from file in a while loop and store the info in struct
	    stringstream ss(line);
	    
	    getline(ss, tid, ',');  // break the line by comma and put the string in tid  1,kinza,500,100%,A+
	    getline(ss, tname, ',');
	    getline(ss, tmarks, ',');
	    getline(ss, tper, ',');
	    getline(ss, tgrade);
	  //sstream is basically convert numercial to string or viceversa.
		s[index].id = stoi(tid);  // convert tid to int
		s[index].name=tname;
		s[index].marks = stof(tmarks); // convert tmarks to float
		s[index].per = stof(tper); // convert tid to float
		s[index].grade=tgrade;	    
	    
	    index++;
	}
	
}

                   // Function to Search the record
void search()
{
	system("cls");
	cout<<"\n\n\t\t\t ***SEARCH RECORD ***";
	updateTotalStudents();
	if(totalstudents==0)
		cout<<"\n\n There are no records ";
	else{ 
		int id,found=0;
		cout<<"\n\n Enter Student Id:";
		cin>>id;
		loadstudents(); //load students from file to struct array
		for(int a=0;a<totalstudents;a++)
		{
			if(id == s[a].id)
			{
				cout<<"\n\n Name:"<<s[a].name;
				cout<<"\n\n Marks:"<<s[a].marks;
				cout<<"\n\n Percentage:"<<s[a].per<<"%";
				cout<<"\n\n Grade:"<<s[a].grade;
				found++;
			}
		}
		if(found==0)
			cout<<"\n\n *** Student Id Not Found ***";
	}
}

              // Fuction to Update the record
 void update()
{
	system("cls");
	cout<<"\n\n\t\t\t ***UPDATE RECORD ***";
	updateTotalStudents(); //update number of total students from file
	loadstudents();  //load students from file to struct array
	if(totalstudents==0)
		cout<<"\n\n No Record Found ";
	else{
		int id,found=0;
		cout<<"\n\n Enter Student Id:";
		cin>>id;
		for(int a=0;a<totalstudents;a++)
		{
			if(id == s[a].id)
			{
			    cout<<"\n\n Enter Student Name:";
				cin>>s[a].name;
				cout<<"\n\n Enter Student Marks:";
				cin>>s[a].marks;
				s[a].per = s[a].marks/500*100;
				if(s[a].per >=85)
				s[a].grade = "A+";
				else if(s[a].per >=75)
			    s[a].grade = "A";
				else if(s[a].per >=65)
				s[a].grade = "B+";
				else if(s[a].per >=55)
				s[a].grade = "B";
				else if(s[a].per >=50)
				s[a].grade = "C";
				else if(s[a].per >=45)
				s[a].grade = "D";
				else if(s[a].per >=33)
				s[a].grade = "E";
				else
				s[a].grade = "F";
				
				
				
				cout<<"\n\n *** UPDATE RECORD SUCCESSFULLY";
				found++;
				writestudents(); //update the struct array and write to the file
				break;
			}
		}
		if(found==0)
			cout<<"\n\n *** Student Id Not Found ***";
		}
		
		
	
	
}

         // Function to Delete the record
void del()
{
	system("cls");
	cout<<"\n\n\t\t\t ***DELETE RECORD ***";
	updateTotalStudents();
	loadstudents();
	
	if(totalstudents==0)
		cout<<"\n\n No Record Found ";
	else
	{	
		int id,found=0;
		cout<<"\n\n Enter Student Id:";
		cin>>id;
		for(int a=0;a<totalstudents;a++)
		{
			if(id == s[a].id){ // if record is found
				ofstream outFile("records.txt", ios::out | ios::trunc); // opens the file in rewrite mode
	
				for(int b=0;b<totalstudents;b++){
					if(b==a){
						found++;
						continue; // skip writing the struct to be deleted to file
					}
					else  // write other structs to the file
						outFile << s[b].id << "," << s[b].name << "," << s[b].marks << ","  << s[b].per << ","  << s[b].grade  << endl; // writes the record to the file
				} 
				outFile.close(); // closes the file	
				loadstudents();
				ofstream outFile2("totalstudents.txt", ios::out | ios::trunc); // opens the file in rewrite mode
			    outFile2 << --totalstudents <<endl;
			    outFile2.close(); // closes the file
				cout<<"\n\n ***  RECORD deleted SUCCESSFULLY ***"; 
				break;
			}
		}
		if(found==0)
			cout<<"\n\n *** Student Id Not Found ***";
	}
	
	
	
}

          // Function to Show the record
void show()
{
	system("cls");
	cout<<"\n\n\t\t\t ***SHOW ALL RECORD ***";
	updateTotalStudents();  //update total student from file
	loadstudents();  // load the students from file to struct
	
	if(totalstudents==0)
		cout<<"\n\n No Record Found ";
	else
	{
	    for(int a=0;a<totalstudents;a++)
		{
			cout<<"\n\n Student Id:"<<s[a].id;
			cout<<"\n\n Name:"<<s[a].name;
			cout<<"\n\n Marks:"<<s[a].marks;
			cout<<"\n\n Percentage:"<<s[a].per<<"%";
		    cout<<"\n\n Grade:"<<s[a].grade;
			cout<<"\n\n  ******************************";
			         	 	
		}
	}
}


void menu(){
	
	
	
	cout<<"\n\n\t\t ############################ STUDENT MANAGEMENT SYSTEM ############################# ";
	cout<<"\n\n 1.Enter Record";
	cout<<"\n\n 2.Search Record";
	cout<<"\n\n 3.Update Record";
	cout<<"\n\n 4.Delete Record";
	cout<<"\n\n 5.Show Record";
	cout<<"\n\n 6. Exit";
	cout<<"\n\n Enter your choice: ";
	
}
          // From here Main Function Starts
int main()
{
	system("cls");
	ifstream inFile("totalstudents.txt");
	if (inFile.is_open()) {
	        inFile >> totalstudents;
	        inFile.close();
	} 
	else {
        ofstream outFile("totalstudents.txt", std::ios::out ); // opens the file in write mode
	    outFile << totalstudents <<endl;
	    outFile.close(); // closes the file
	}


	
	int choice;
	cout<<" %%      %%                                                        "<<endl;
	cout<<" %%      %% %%%%%%%% %%       %%%%%%   %%%%%% %%%%% %%%%% %%%%%%%  "<<endl;
	cout<<" %%      %% %%       %%       %%       %%  %% %%  %%%  %% %%       "<<endl;
	cout<<" %%  %%  %% %%%%%%   %%       %%       %%  %% %%  %%%  %% %%%%%    "<<endl;
	cout<<" %%  %%  %% %%       %%       %%       %%  %% %%       %% %%       "<<endl;
	cout<<" %%%%%%%%%% %%%%%%%% %%%%%%%% %%%%%%%% %%%%%% %%       %% %%%%%%%  "<<endl;
	cout<<"                                                                   "<<endl;
	cout<<"                              $$$$$$$$  $$$$$                         "<<endl;
	cout<<"                                 $$     $   $                         "<<endl;
	cout<<"                                 $$     %%$$$                         "<<endl;
	
	do{
		
		menu();
		cin>>choice;
		switch(choice)
		{
			case 1:
			       enter();
				    break;
			case 2:
				   search();
				    break;
		    case 3:
		    	   update();
				    break;
			case 4:
				   del();
				    break;
			case 5:
				   show();
				    break;
			case 6:
				   cout<<"EXIT(0)";
				    break;
		    default:
		    	  cout<<"\n\n ***INVALID CHOICE ***";
		}
	
		
	}while(choice!=6);
	
	
	return 0;

}
