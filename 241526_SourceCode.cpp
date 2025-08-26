#include<iostream>
#include<windows.h>
#include <filesystem>
#include<chrono>
#include<ctime>
#include<fstream>

using namespace std;

void write_metadata(string,string);
void read_metadata(string,string);
string encryption(string);
string decryption(string);

//Save Alternate Stream file with original file as an metadata
void write_metadata(string file,string message)
{
    string Path = file + ":metadata";
    ofstream File(Path, ios::out);
    string ls=encryption(message);
    File << ls;
    File.close();
    cout << "Alternate data stream written successfully." << endl;
    cout<<"\n";
}

//Substitution Cipher
string encryption(string str)
{
    string passphrase;
    cout<<"Enter Pass Pharse : ";
    getline(cin,passphrase);
    
    int key=0;
    for(int i=0;i<passphrase.size();i++)
    {
       key+=int(passphrase[i]);
    }
    key = key % 26;
    for(int i=0;i<str.size();i++)
    {
        if(isupper(str[i]))
        str[i]=(((str[i]-65+key)%26)+65);
        else if(islower(str[i]))
        str[i]=(((str[i]-97+key)%26)+97);
        else if(isdigit(str[i]))
        str[i]=(((str[i]-48+key)%10)+48);
    }
    return str;
}

//Deciphering the message
string decryption(string msg)
{
    string passphrase;
    cout<<"Enter Pass Pharse : ";
    getline(cin,passphrase);
    
    int key=0;
    for(int i=0;i<passphrase.size();i++)
    {
       key+=int(passphrase[i]);
    }
    key = key % 26;
    for(int i=0;i<msg.size();i++)
    {
        if(isupper(msg[i]))
        msg[i]=(((msg[i]-65-key+26)%26)+65);
        else if(islower(msg[i]))
        msg[i]=(((msg[i]-97-key+26)%26)+97);
        else if(isdigit(msg[i]))
        msg[i]=(((msg[i]-48-key+10)%10)+48);
    }
    return msg;
}

//Read Alternate Data Stream
void read_metadata(string file)
{
    string Path=file+":metadata";
    ifstream File(Path, ios::in);
    string content;
    string ls;
    getline(File,content);
    File.close();
    ls=decryption(content);
    cout<<"Message : "<<ls<<endl;
    cout<<"\n";
}   


int main()
{
    int choice;
    while(true)
    {
    cout<<"1. Add Metadata\n";
    cout<<"2. Read Metadata\n";
    cout<<"3. Exit\n";
    cout<<"Choice : ";
    cin>>choice;
    cin.ignore();
    if(choice==1)
    { 
      string file,msg;
      cout<<"Enter File : ";
      getline(cin,file);
      cout<<"Enter Message : ";
      getline(cin,msg);
      write_metadata(file,msg);
    }
    else if(choice==2)
    {
      string file;
      cout<<"Enter File : ";
      getline(cin,file);
      read_metadata(file);
    }
    else if(choice==3)
    {
        exit(0);
    }
    else
    {
        cout<<"You Entered Wrong Choice\n";
    } 
    }
}