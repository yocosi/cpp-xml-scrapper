#include <string> // for string
#include <cstring>
#include <iostream>
#include <vector>
#include "envelope.h"
using namespace std; // for string
                     /**
                      * A format.
                      */

envelope_t::envelope_t()
{
    this->height = 0;
    this->width = 0;
}

int envelope_t::get_height() const
{
    return this->height;
}

priority_t envelope_t::get_priority() const
{
    return this->priority;
}

address_t envelope_t::get_recipient() const
{
    return this->recipient;
}

address_t envelope_t::get_sender() const
{
    return this->sender;
}

int envelope_t::get_width() const
{
    return this->width;
}

void envelope_t::handle_e() const
{
    cout << *this;
}

void envelope_t::handle_ec(int postal_code) const
{
    if (this->get_sender().get_postal_code() == postal_code)
    {
        cout << *this;
        cout << endl;
    }
}

void envelope_t::handle_ecge(int postal_code) const
{
    if (this->get_sender().get_postal_code() >= postal_code)
    {
        cout << *this;
        cout << endl;
    }
}

void envelope_t::handle_ecgt(int postal_code) const
{
    if (this->get_sender().get_postal_code() > postal_code)
    {
        cout << *this;
        cout << endl;
    }
}

void envelope_t::handle_ecle(int postal_code) const
{
    if (this->get_sender().get_postal_code() <= postal_code)
    {
        cout << *this;
        cout << endl;
    }
}

void envelope_t::handle_eclt(int postal_code) const
{
    if (this->get_sender().get_postal_code() < postal_code)
    {
        cout << *this;
        cout << endl;
    }
}

void envelope_t::handle_en(string name) const
{
    string sname = this->get_sender().get_name();
    if (sname.find(name) != string::npos)
    {
        cout << *this;
        cout << endl;
    }
}

void envelope_t::set_priority(priority_t priority)
{
    this->priority = priority;
}

void envelope_t::set_recipient(address_t recipient)
{
    this->recipient = recipient;
}

void envelope_t::set_sender(address_t sender)
{
    this->sender = sender;
}

ostream &operator<<(ostream &os, const envelope_t &enveloppe){
    string priority[4] = {"undefined", "high", "low", "medium"};
    os << "((" << enveloppe.get_sender().get_name() << ", " << enveloppe.get_sender().get_street() << ", " << enveloppe.get_sender().get_postal_code() << ", " << enveloppe.get_sender().get_city() << ", " << enveloppe.get_sender().get_country()
         << ") -> ("
         << enveloppe.get_recipient().get_name() << ", " << enveloppe.get_recipient().get_street() << ", " << enveloppe.get_recipient().get_postal_code() << ", " << enveloppe.get_recipient().get_city() << ", " << enveloppe.get_recipient().get_country() << ")"
         << " [" << priority[enveloppe.get_priority()] << "] " << enveloppe.get_width() << "x" << enveloppe.get_height() << " mm)";
    return os;
}


/**
 * string priority[4] = {"undefined", "high", "low", "medium"};
    cout << "((" << this->sender.get_name() << ", " << this->sender.get_street() << ", " << this->sender.get_postal_code() << ", " << this->sender.get_city() << ", " << this->sender.get_country()
         << ") -> ("
         << this->recipient.get_name() << ", " << this->recipient.get_street() << ", " << this->recipient.get_postal_code() << ", " << this->recipient.get_city() << ", " << this->recipient.get_country() << ")"
         << " [" << priority[this->get_priority()] << "] " << this->get_width() << "x" << this->get_height() << " mm)";
 * 
 */
