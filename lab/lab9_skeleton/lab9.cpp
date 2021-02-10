// COMP2011 Fall 2020
// lab9.cpp -- source file

#include <iostream>
#include <cstring>
#include "lab9.h"
using namespace std;

// This function prints one contact's information.
void print_contact(const Contact *contact)
{
        cout << contact->contact_name << ":" << contact->phone_number << endl;
}

// This function will create (new) a Contact object with the given contact_name & phone_number,
// and return its address (pointer).
Contact *new_contact(const char contact_name[], const char phone_number[])
{
        Contact *c = new Contact;              //create new pointer, c, that points to struct contact
        strcpy(c->contact_name, contact_name); //save content of contact name to the pointer d
        strcpy(c->phone_number, phone_number); //save contect of phone number to pointer 
        return c;
}

// This function will create (new) a Telephone_Directory object,
// initialize num_of_contact to 0, initialize all array elements to nullptr,
// and return the Telephone_Directory pointer (address).
Telephone_Directory *new_telephone_directory()
{
        Telephone_Directory *td = new Telephone_Directory;
        Contact *contacts_by_name = nullptr;         // in sorted order of contact_name
        Contact *contacts_by_phone_number = nullptr; // in sorted order of phone_number
        td->num_of_contacts = 0;
        return td;
}

// This function will print queried contacts' infomation (indices stored in matched_contacts[]) either sorted by their names (when by_name=true) or sorted by their phone numbers (when by_name=false)
void show_contacts(const Telephone_Directory *d, const int matched_contacts[], int matched_contacts_count, bool by_name)
{
        //matched_contacts[] store index for contacts by name in accending order

        //matched_contacts_count is num of correct matches
        if (matched_contacts_count == 0)
        {
                cout << "not found" << endl;
        }

        else if (by_name)
        { //print the names and number from name search
                for (int i = 0; i < matched_contacts_count; i++)
                { // if number of correctly matched count is still not the total number
                        print_contact(d->contacts_by_name[matched_contacts[i]]);
                        //print the contact inside array contacts_by_name with index of the contacts that matched (matched_contacts[i]), in accending order
                }
        }
        else if (!by_name)
        { // print names and number from number search
                for (int i = 0; i < matched_contacts_count; i++)
                {
                        print_contact(d->contacts_by_phone_number[matched_contacts[i]]);
                }
        }
}

// This function will print all contacts' infomation sorted by their names if by_names is true.
// Otherwise print the contacts by their phone numbers
void show_contacts(const Telephone_Directory *d, bool by_names)
{
        if (by_names)
        { //print all contacts sorted by name
                for (int i = 0; i < d->num_of_contacts; i++)
                { // if number of correctly matched count is still not the total number
                        print_contact(d->contacts_by_name[i]);
                        //print the content of the element in array contacts_by_name inside struct d
                }
        }
        else
        { //print all contacts sorted by phone numbers
                for (int i = 0; i < d->num_of_contacts; i++)
                { // if number of correctly matched count is still not the total number
                        print_contact(d->contacts_by_phone_number[i]);
                        // same as *(d.contacts_by_name[i].contact_name), get the char array of name
                }
        }
}

// This function will delete all the Contact objects and the Telephone_Directory object.
void delete_telephone_directory(Telephone_Directory *d)
{
        delete d; //delete memory space of d, making it a dangling pointer
        // d->contacts_by_name=nullptr; //remove value and memory of array contacts_by_name inside struct d
        // d->contacts_by_phone_number=nullptr;
        d = nullptr;
}

// This function will use new_contact() to create object within given contact_name & phone_num,
// and add the pointer (address) to the 2 arrays of pointers in the Telephone_Directory object pointed by d.
// contacts_by_name is to maintain the contacts in sorted order of names,
// contacts_by_phone_number is to maintain the contacts in sorted order of phone numbers.
void add_contact_to_telephone_directory(Telephone_Directory *d, const char contact_name[], const char phone_num[])
{
        Contact *c = new_contact(contact_name, phone_num);
        if (d->num_of_contacts == 0)
        {
                d->contacts_by_name[0] = c; //store both name and phone number iniside the
                d->contacts_by_phone_number[0] = c;
        }
        //sort by name
        for (int i = 0; i < d->num_of_contacts; i++)
        {

                if (strcmp(d->contacts_by_name[i]->contact_name, contact_name) > 0)
                { //if the original name in the telephone address is larger than contact name
                        Contact *temp = d->contacts_by_name[i];
                        d->contacts_by_name[i] = c;

                        for (int j = i + 1; j < d->num_of_contacts + 1; j++)
                        { //shift a position in the array of pointers to put in the pointer to the name that is smaller than some but larger than some
                                Contact *temp2 = d->contacts_by_name[j];
                                d->contacts_by_name[j] = temp;
                                temp = temp2;
                        }
                        break;
                }
                else if (i == d->num_of_contacts - 1)
                { //if the name is larger than all elements in array of names
                        d->contacts_by_name[d->num_of_contacts] = c;
                }
        }
        // sort by number//
        for (int i = 0; i < d->num_of_contacts; i++)
        {

                if (strcmp(d->contacts_by_phone_number[i]->phone_number, phone_num) > 0)
                { //if the original number in the telephone address is larger than contact name
                        Contact *temp = d->contacts_by_phone_number[i];
                        d->contacts_by_phone_number[i] = c;

                        for (int j = i + 1; j < d->num_of_contacts + 1; j++)
                        { // add comment later
                                Contact *temp2 = d->contacts_by_phone_number[j];
                                d->contacts_by_phone_number[j] = temp;
                                temp = temp2;
                        }
                        break;
                }
                else if (i == d->num_of_contacts - 1)
                { //if the phone number is larger than all elements in the arry of phone numbers
                        d->contacts_by_phone_number[d->num_of_contacts] = c;
                }
        }
        d->num_of_contacts += 1;
}

// This function will search for contacts matching with the substring contact_name_partial,
// return num of matched contacts and store the indices of the matched contacts
// in the contacts_by_name array of Telephone_Directory in the array matched_contacts.
int lookup_by_contact_name(const Telephone_Directory *d, const char contact_name_partial[], int matched_contacts[])
{
        int count = 0;
        for (int i = 0; i < d->num_of_contacts; i++)
        {
                if (strstr( d->contacts_by_name[i]->contact_name, contact_name_partial)!=nullptr)
                {
                        matched_contacts[count] = i;
                        count++;
                }
        }
        return count;
}

// This function will search for contacts matching with the substring phone_number_partial,
// return num of matched contacts and store the indicses of the matched contacts
// in the contacts_by_phone_number array of Telephone_Directory in the array matched_contacts.
int lookup_by_phone_number(const Telephone_Directory *d, const char phone_number_partial[], int matched_contacts[])
{
        int count = 0;
        for (int i = 0; i < d->num_of_contacts; i++)
        {
                if (strstr(d->contacts_by_phone_number[i]->phone_number,phone_number_partial)!=nullptr)
                {
                        matched_contacts[count] = i;
                        count++;
                }
        }
        return count;
}

// This function will update a contact's phone number given the contact_name.
// and update the contacts_by_phone_num array in sorted order.
void update_phone_number(Telephone_Directory *d, const char contact_name[], const char phone_number[])
{
        // Contact** a = nullptr;
        // for (int i = 0; i < d->num_of_contacts; i++)
        // {
        //         if (strcmp(contact_name, d->contacts_by_name[i]->contact_name) == 0) // if contact name match with the content of contacts_by_name in d
        //         {
        //                 delete d->contacts_by_name[i];
        //                 d->contacts_by_name[i] = nullptr;
        //                 for (int j = i+1; j< d->num_of_contacts; j++){
        //                         d->contacts_by_name[j-1] = d->contacts_by_name[j];
        //                 }
        //                 // strcpy(d->contacts_by_name[i]->phone_number, phone_number);// STRING COPY phone number and save it to array content of contacts by name
        //         }
        // }
        // get to correct one, delete element form contact by name
        for (int i = 0; i < d->num_of_contacts; i++)
        {
                if (strcmp(contact_name, d->contacts_by_phone_number[i]->contact_name) == 0)
                {
                        delete d->contacts_by_phone_number[i];
                        d->contacts_by_phone_number[i] = nullptr;
                        for (int j = i+1; j< d->num_of_contacts; j++){
                                d->contacts_by_phone_number[j-1] = d->contacts_by_phone_number[j];
                        }
                        // delete d->contacts_by_name[i];//bug when using this together
                        // d->contacts_by_name[i] = nullptr;
                        // for (int j = i+1; j< d->num_of_contacts; j++){
                        //         d->contacts_by_name[j-1] = d->contacts_by_name[j];
                        // }
                }
        }
        --d->num_of_contacts;
        add_contact_to_telephone_directory(d, contact_name, phone_number);
        // delete d->contacts_by_name[d->num_of_contacts];
        // d->contacts_by_name[d->num_of_contacts] =nullptr;
        // delete d->contacts_by_phone_number[d->num_of_contacts];
        // d->contacts_by_phone_number[d->num_of_contacts] = nullptr;
        // --d->num_of_contacts;
        
}
