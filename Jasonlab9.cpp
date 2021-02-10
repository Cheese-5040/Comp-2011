// COMP2011 Fall 2020
// lab9.cpp -- source file

#include <iostream>
#include <cstring>
#include "lab9.h"
using namespace std;

// This function prints one contact's information.
void print_contact(Contact *contact)
{
        cout << contact->contact_name << ":" << contact->phone_number << endl;
}

// This function will create (new) a Contact object with the given contact_name & phone_number,
// and return its address (pointer).
Contact *new_contact(const char contact_name[], const char phone_number[])
{
        Contact *temp = new Contact;
        strcpy(temp->contact_name, contact_name);
        strcpy(temp->phone_number, phone_number);
        return temp;
}

// This function will create (new) a Telephone_Directory object,
// initialize num_of_contact to 0, initialize all array elements to nullptr,
// and return the Telephone_Directory pointer (address).
Telephone_Directory *new_telephone_directory()  
{
        Telephone_Directory *New = new Telephone_Directory;
        New->num_of_contacts = 0;
        Contact *contacts_by_name = nullptr;         // in sorted order of contact_name
        Contact *contacts_by_phone_number = nullptr; // in sorted order of phone_number
        return New;
}

// This function will print queried contacts' infomation (indices stored in matched_contacts[]) either sorted by their names (when by_name=true) or sorted by their phone numbers (when by_name=false)
void show_contacts(const Telephone_Directory *d, const int matched_contacts[], int matched_contacts_count, bool by_name)
{
        if (matched_contacts_count == 0)
        {
                cout << "Not Found." << endl;
        }
        if (by_name)
        {
                for (int i = 0; i < matched_contacts_count; i++)
                {
                        cout << d->contacts_by_name[matched_contacts[i]]->contact_name << ":" << d->contacts_by_name[matched_contacts[i]]->phone_number << endl;
                }
        }
        else
        {
                for (int i = 0; i < matched_contacts_count; i++)
                {
                        cout << d->contacts_by_phone_number[matched_contacts[i]]->contact_name << ":" << d->contacts_by_phone_number[matched_contacts[i]]->phone_number << endl;
                }
        }
}

// This function will print all contacts' infomation sorted by their names if by_names is true.
// Otherwise print the contacts by their phone numbers
void show_contacts(const Telephone_Directory *d, bool by_names)
{
        if (by_names)
        {
                for (int i = 0; i < d->num_of_contacts; i++)
                {
                        cout << d->contacts_by_name[i]->contact_name << ":" << d->contacts_by_name[i]->phone_number << endl;
                }
        }
        else
        {
                for (int i = 0; i < d->num_of_contacts; i++)
                {
                        cout << d->contacts_by_phone_number[i]->contact_name << ":" << d->contacts_by_phone_number[i]->phone_number << endl;
                }
        }
}

// This function will delete all the Contact objects and the Telephone_Directory object.
void delete_telephone_directory(Telephone_Directory *d)
{
        delete d;
        d = nullptr;
}

// This function will use new_contact() to create object within given contact_name & phone_num,
// and add the pointer (address) to the 2 arrays of pointers in the Telephone_Directory object pointed by d.
// contacts_by_name is to maintain the contacts in sorted order of names,
// contacts_by_phone_number is to maintain the contacts in sorted order of phone numbers.
void add_contact_to_telephone_directory(Telephone_Directory *d, const char contact_name[], const char phone_num[])
{
        Contact *contact = new_contact(contact_name, phone_num);
        d->num_of_contacts += 1;
        int count = 0;
        Contact *temp[MAX_CONTACT_NUMBER];
        for (int i = 0; i < d->num_of_contacts; i++)
        {
                if (d->num_of_contacts == 0)
                {
                        break;
                }
                if (strcmp(contact_name, d->contacts_by_name[i]->contact_name) < 0)
                {
                        temp[i] = contact;
                        count++;
                }
                if (strcmp(contact_name, d->contacts_by_name[i]->contact_name) > 0)
                {
                        temp[i] = contact;
                }
        }
        for (int i = 0; i < d->num_of_contacts; i++)
        {
                if (i == count)
                {
                        d->contacts_by_name[i] = contact;
                }
                if (i < count)
                {
                        d->contacts_by_name[i] = temp[i];
                }
                if (i > count)
                {
                        d->contacts_by_name[i] = temp[i - 1];
                }
        }
        int count_2 = 0;
        Contact *temp_2[MAX_CONTACT_NUMBER];
        for (int i = 0; i < d->num_of_contacts; i++)
        {
                if (d->num_of_contacts == 0)
                {
                        break;
                }
                if (strcmp(phone_num, d->contacts_by_phone_number[i]->phone_number) < 0)
                {
                        temp_2[i] = contact;
                        count_2++;
                }
                if (strcmp(phone_num, d->contacts_by_phone_number[i]->phone_number) > 0)
                {
                        temp_2[i] = contact;
                }
        }
        for (int i = 0; i < d->num_of_contacts; i++)
        {
                if (i == count_2)
                {
                        d->contacts_by_phone_number[i] = contact;
                }
                if (i < count_2)
                {
                        d->contacts_by_phone_number[i] = temp_2[i];
                }
                if (i > count_2)
                {
                        d->contacts_by_phone_number[i] = temp_2[i - 1];
                }
        }
}

// This function will search for contacts matching with the substring contact_name_partial,
// return num of matched contacts and store the indices of the matched contacts
// in the contacts_by_name array of Telephone_Directory in the array matched_contacts.
int lookup_by_contact_name(const Telephone_Directory *d, const char contact_name_partial[], int matched_contacts[])
{
        int count = 0;
        for (int i = 0; i < d->num_of_contacts; i++)
        {
                if (strcmp(contact_name_partial, d->contacts_by_name[i]->contact_name) >= 0)
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
                if (strcmp(phone_number_partial, d->contacts_by_name[i]->phone_number) >= 0)
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
        for (int i = 0; i < d->num_of_contacts; i++)
        {
                if (strcmp(contact_name, d->contacts_by_name[i]->contact_name) == 0)
                {
                        strcpy(d->contacts_by_name[i]->phone_number, phone_number);
                        //d->contacts_by_name[i]->phone_number = phone_number;
                }
        }
        int count = 0;
        for (int i = 0; i < d->num_of_contacts; i++)
        {
                if (strcmp(contact_name, d->contacts_by_phone_number[i]->contact_name) == 0)
                {
                        strcpy(d->contacts_by_phone_number[i]->phone_number, phone_number);
                }
        }
}