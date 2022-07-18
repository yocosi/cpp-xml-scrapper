#include <string> // for string
#include <vector> // for vector
#include <iostream>
#include "company.h"
using namespace std; // for string
                     /**
                      * A company.
                      */

company_t::company_t()
{
    this->name = "undefined";
    this->web = "undefined";
}

string company_t::get_name() const
{
    return this->name;
}

string company_t::get_web() const
{
    return this->web;
}

void company_t::handle_e() const
{
    for (int i = 0; i < this->envelopes_size(); i++)
    {
        this->envelopes_at(i).handle_e();
        cout << endl;
    }
}

void company_t::handle_i() const
{
    cout << *this;
}

void company_t::handle_n() const
{
    cout << this->get_name() << endl;
}

void company_t::handle_ec(int postal_code) const
{
    for (int i = 0; i < this->envelopes_size(); i++)
    {
        this->envelopes_at(i).handle_ec(postal_code);
    }
}

void company_t::handle_ecge(int postal_code) const
{
    for (int i = 0; i < this->envelopes_size(); i++)
    {
        this->envelopes_at(i).handle_ecge(postal_code);
    }
}

void company_t::handle_ecgt(int postal_code) const
{
    for (int i = 0; i < this->envelopes_size(); i++)
    {
        this->envelopes_at(i).handle_ecgt(postal_code);
    }
}

void company_t::handle_ecle(int postal_code) const
{
    for (int i = 0; i < this->envelopes_size(); i++)
    {
        this->envelopes_at(i).handle_ecle(postal_code);
    }
}

void company_t::handle_eclt(int postal_code) const
{
    for (int i = 0; i < this->envelopes_size(); i++)
    {
        this->envelopes_at(i).handle_eclt(postal_code);
    }
}

void company_t::handle_en(string name) const
{
    for (int i = 0; i < this->envelopes_size(); i++)
    {
        this->envelopes_at(i).handle_en(name);
    }
}

void company_t::handle_w() const
{
}

envelope_t company_t::envelopes_at(int index) const
{
    return this->envelopes.at(index);
}

void company_t::envelopes_push_back(envelope_t envelope)
{
    this->envelopes.push_back(envelope);
}

int company_t::envelopes_size() const
{
    return this->envelopes.size();
}

void company_t::set_name(string name)
{
    this->name = name;
}

void company_t::set_web(string web)
{
    this->web = web;
}

ostream &operator<<(ostream &os, const company_t &company)
{
    cout << "(" << company.get_name() << ", " << company.get_web() << ", (";
    for (int i = 0; i < company.envelopes_size() - 1; i++)
    {
        company.envelopes_at(i).handle_e();
        cout << ", ";
    }
    company.envelopes_at(company.envelopes_size() - 1).handle_e();
    cout << "))" << endl;
    return os;
}