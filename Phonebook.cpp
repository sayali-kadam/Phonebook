#include<iostream>
#include<string>

using namespace std;

class node{
    int number[10];
    string gmail;
    string name;
    node *prev, *next;

    public:
    //Constructor
    node(int num[], string g, string n){
        name = n;
        gmail = g;
        for(int i=0; i<10; i++){
            number[i] = num[i];
        }
        next = NULL;
        prev = NULL;
    }
    //Operations on the phonebook
    friend class phonebook;
};

class phonebook{
    node *head, *temp, *ptr, *ptr1, *ptr2, *dup;

    public:
    //Constructor
    phonebook(){
        head = NULL;
        temp = NULL;
        ptr = NULL;
        ptr1 = NULL;
        ptr2 = NULL;
        dup = NULL;
    }

    //Functions for operations on the phone book
    void accept();
    void display();
    void update(string na);
    void searchByName(string na);
    void searchByNum(int num[]);
    void searchByGmail(string gm);
    void deleteContact(string delna);
    void deleteSameName();
    void deleteSameNum();
    void deleteSameGmail();

    //Comparing number array
    bool arrcmp(int a[], int b[]){
        for(int i=0; i<10; i++){
            if(a[i] != b[i])
                return false;
        }
        return true;
    }
};

void phonebook::accept(){
    int number[10];
    string gmail;
    string name;
    string num;
    char ans;

    do{
        cout<<"Enter Name: ";
        cin>>name;
        cout<<"Enter Number: ";
        cin>>num;
        for(int i=0; i<num.size() && i<10; i++){
            number[i] = (int)num[i] - 48; 
        }
        cout<<"Enter Gmail: ";
        cin>>gmail;

        temp = new node(number, gmail, name);
        if(head == NULL)
            head = temp;
        else{
            ptr = head;
            while(ptr->next != NULL){
                ptr = ptr->next;
            }
            ptr->next = temp;
            temp->prev = ptr;
        }
        cout<<endl;
        cout<<"Do you want to add more contacts??: ";
        cin>>ans;
    }while(ans=='Y');
}

void phonebook::display(){
    ptr = head;
    while(ptr){
        cout<<"\t\tName: "<<ptr->name<<endl;
        cout<<"\t\tNumber: ";
        for(int i=0; i<10; i++){
            cout<<ptr->number[i];
        }
        cout<<endl;
        cout<<"\t\tGmail: "<<ptr->gmail<<endl;
        cout<<endl;
        ptr = ptr->next;
    }
}

void phonebook::update(string name){
    char ans;
    string num;
    int opt;
    ptr = head;
    while(ptr){
        if(name==ptr->name){
            do{
                cout<<"What do you want update: \n1.  Name\n2.  Phone number\n3.  Gmail"<<endl;
                cout<<"Enter your option: ";
                cin>>opt;
                switch(opt){
                    case 1:
                        cout<<"Enter new name: ";
                        cin>>ptr->name;
                        cout<<"Contact updated successfully"<<endl;
                        break;

                    case 2:
                        cout<<"Enter new phone number: ";
                        cin>>num;
                        for(int i=0; i<num.size() && i<10; i++){
                            ptr->number[i] = (int)num[i] - 48;
                        }
                        cout<<"Contact updated successfully"<<endl;
                        break;

                    case 3:
                        cout<<"Enter new Gmail: ";
                        cin>>ptr->gmail;
                        cout<<"Contact updated successfully"<<endl;
                        break;

                    default:
                        cout<<"Please, choose correct option..........."<<endl;
                        break;
                }
                cout<<endl;
                cout<<"Do you want to updating more??: ";
                cin>>ans;
            }while(ans=='Y');
        }
        ptr = ptr->next;
    }
}

void phonebook::searchByName(string name){
    ptr = head;
    while(ptr){
        if(name==ptr->name){
            cout<<"Name is found"<<endl;
            cout<<"Contact details are: "<<endl;
            cout<<"\t\t Name: "<<ptr->name<<endl;
            cout<<"\t\t Phone Number: ";
            for(int i=0; i<10; i++){
                cout<<ptr->number[i];
            }
            cout<<endl;
            cout<<"\t\t Gmail: "<<ptr->gmail<<endl;
            return;
        }
        ptr = ptr->next;
    }
    cout<<"The contact is not available"<<endl;
}

void phonebook::searchByNum(int num[]){
    ptr = head;
    while(ptr){
        if(arrcmp(num, ptr->number)){
            cout<<"Number is found"<<endl;
            cout<<"Contact details are: "<<endl;
            cout<<"\t\t Name: "<<ptr->name<<endl;
            cout<<"\t\t Phone Number: ";
            for(int i=0; i<10; i++){
                cout<<ptr->number[i];
            }
            cout<<endl;
            cout<<"\t\t Gmail: "<<ptr->gmail<<endl;
            return;
        }
        ptr = ptr->next;
    }
    cout<<"The contact is not available"<<endl;
}

void phonebook::searchByGmail(string gmail){
    ptr = head;
    while(ptr){
        if(gmail==ptr->gmail){
            cout<<"Gmail is found"<<endl;
            cout<<"Contact details are: "<<endl;
            cout<<"\t\t Name: "<<ptr->name<<endl;
            cout<<"\t\t Phone Number: ";
            for(int i=0; i<10; i++){
                cout<<ptr->number[i];
            }
            cout<<endl;
            cout<<"\t\t Gmail: "<<ptr->gmail<<endl;
            return;
        }
        ptr = ptr->next;
    }
    cout<<"The contact is not available"<<endl;
}

void phonebook::deleteContact(string delName){
    int c = 0;
    ptr = head;
    while(ptr){
        if(delName==ptr->name){
            c = 1;
            break;
        }else{
            c = 2;
        }
        ptr = ptr->next;
    }
    //If contact is available in between the list
    if(c==1 && (ptr!=head && ptr->next)){
        ptr->prev->next = ptr->next;
        ptr->next->prev = ptr->prev;
        delete(ptr);
        cout<<"Contact deleted successfully"<<endl;
    }
    //If contact is at head node
    if(ptr == head){
        head = head->next;
        head->prev = NULL;
        delete(ptr);
        cout<<"Contact deleted successfully"<<endl;
    }
    //If contact is at tail
    if(ptr->next == NULL){
        ptr->prev->next = NULL;
        ptr->prev = NULL;
        delete(ptr);
        cout<<"Contact deleted successfully"<<endl;
    }
    //If contact is not availble in list
    if(c==2){
        cout<<"Contact is not available in the phone book"<<endl;
    }
}

void phonebook::deleteSameName(){
    ptr1 = head;
    while(ptr1 && ptr1->next){
        ptr2 = ptr1;
        while(ptr2->next){
            if(ptr1->name == ptr2->name){
                dup = ptr2->next;
                ptr2->next = ptr2->next->next;
                delete(dup);
                cout<<"Contact deleted successfully"<<endl;
                return;
            }else{
                ptr2 = ptr2->next;
            }
        }
        ptr1 = ptr1->next;
    }
    cout<<"The contact is not available"<<endl;
}

void phonebook::deleteSameNum(){
    ptr1 = head;
    while(ptr1 && ptr1->next){
        ptr2 = ptr1;
        while(ptr2->next){
            if(arrcmp(ptr1->number, ptr2->number)){
                dup = ptr2->next;
                ptr2->next = ptr2->next->next;
                delete(dup); 
                cout<<"Contact deleted successfully"<<endl;
                return;
            }else{
                ptr2 = ptr2->next;
            }
        }
        ptr1 = ptr1->next;
    }
    cout<<"The contact is not available"<<endl;
}

void phonebook::deleteSameGmail(){
    ptr1 = head;
    while(ptr1 && ptr1->next){
        ptr2 = ptr1;
        while(ptr2->next){
            if(ptr1->gmail == ptr2->gmail){
                dup = ptr2->next;
                ptr2->next = ptr2->next->next;
                delete(dup);
                cout<<"Contact deleted successfully"<<endl;
                return;
            }else{
                ptr2 = ptr2->next;
            }
        }
        ptr1 = ptr1->next;
    }
    cout<<"The contact is not available"<<endl;
}

int main(){
    string name;
    int number[10];
    string gmail;
    cout<<"-----------------------------------------------------------    Phone-Book  -----------------------------------------------------------"<<endl;
    cout<<"Please enter your name: ";
    cin>>name;
    cout<<"********************************************************    Welcome "<<name<<"   ********************************************************"<<endl;
    int ch, sea, del;
    char ans;
    string update_Name, search_name, search_gmail, delete_name;
    int search_num[10];
    phonebook p;
    do{
        cout<<"Options:\n1.  Create a Phonebook\n2.  Display the Phonebook\n3.  Insert new contact\n4.  Update the details of existing contacts\n5.  Search\n6.  Delete"<<endl;
        cout<<"Enter your option: ";
        cin>>ch;
        switch (ch)
        {
        case 1:
            p.accept();
            break;

        case 2:
            cout<<"Your contacts are: "<<endl;
            p.display();
            break;

        case 3:
            cout<<"Please enter the new contacts: "<<endl;
            p.accept();
            break;

        case 4:
            cout<<"Enter the name of person whose details want to update: ";
            cin>>update_Name;
            p.update(update_Name);
            break;

        case 5:
            do{
                cout<<"What do you want to search: \n1.  Name\n2.  Phone number\n3.  Gmail"<<endl;
                cout<<"Enter your option: ";
                cin>>sea;
                switch(sea){
                    case 1:
                        cout<<"Enter the name to search: ";
                        cin>>search_name;
                        p.searchByName(search_name);
                        break;

                    case 2:
                        cout<<"Enter the phone number to search: ";
                        for(int i=0; i<10; i++){
                            cin>>search_num[i];
                        }
                        p.searchByNum(search_num);
                        break;

                    case 3:
                        cout<<"Enter the gmail to search: ";
                        cin>>search_gmail;
                        p.searchByGmail(search_gmail);
                        break;

                    default:
                        cout<<"Please, choose correct option..........."<<endl;
                        break;    
                }
                cout<<endl;
                cout<<"Do you want to searching more??: ";
                cin>>ans;
            }while(ans=='Y');
            break;
        
        case 6:
            do{
                cout<<"What do you want to delete: \n1.  Contact\n2.  Same Name\n3.  Same Phone number \n4.  Same Gmail"<<endl;
                cout<<"Enter your option: ";
                cin>>del;
                switch(del){
                    case 1:
                        cout<<"Enter the name of contact you want to delete: ";
                        cin>>delete_name;
                        p.deleteContact(delete_name);
                        break;

                    case 2:
                        p.deleteSameName();
                        break;

                    case 3:
                        p.deleteSameNum();
                        break;

                    case 4:
                        p.deleteSameGmail();
                        break;

                    default:
                        cout<<"Please, choose correct option..........."<<endl;
                        break;    
                }
                cout<<endl;
                cout<<"Do you want to deleting more??: ";
                cin>>ans;
            }while(ans=='Y');
            break;
        
        default:
            cout<<"Please, choose correct option..........."<<endl;
            break;
        }
        cout<<endl;
        cout<<"Do you want to continue??:  ";
        cin>>ans;
    }while(ans=='Y');
    cout<<"********************************************************    Thank You "<<name<<" !!   ********************************************************"<<endl;
    return 0;
}