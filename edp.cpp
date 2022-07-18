#include <iostream>
#include <string>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include "pugixml.hpp"
#include "company.h"
#include "envelope.h"
#include "address.h"
#include "envelope-c4.h"
#include "envelope-dl.h"
#include "str2i-error.h"
#include "str2l-error.h"
#include <climits>
#include <cfloat>

using namespace std;
using namespace pugi;

// Create envelopes based on the envelope's format
void create_envelope(xml_node root, vector<envelope_t> &envelopes)
{
  string str = "envelope";
  string format1 = "c4";
  string format2 = "dl";
  xml_node envelopes_node = root.first_child();
  xml_node envelope = envelopes_node.first_child();
  while (envelope.name() == str)
  {
    xml_attribute format = envelope.first_attribute();
    if (format.value() == format1)
    {
      envelope_c4_t envelope;
      envelopes.push_back(envelope);
    }
    if (format.value() == format2)
    {
      envelope_dl_t envelope;
      envelopes.push_back(envelope);
    }
    envelope = envelope.next_sibling();
  }
}

// Function to fill the address of an envelope
int fill_address(const xml_node &envelope_node, address_t &recipient, address_t &sender, int postal_code, char *endPtr, char *file_name)
{
  xml_node recipient_node = envelope_node.first_child().next_sibling();
  xml_node recipient_attr = recipient_node.first_child();
  xml_node sender_node = envelope_node.first_child().next_sibling().next_sibling();
  xml_node sender_attr = sender_node.first_child();
  while (recipient_attr && sender_attr)
  {
    if (recipient_attr.name() == (string) "city" && sender_attr.name() == (string) "city")
    {
      recipient.set_city(recipient_attr.first_child().value());
      sender.set_city(sender_attr.first_child().value());
    }
    if (recipient_attr.name() == (string) "country" && sender_attr.name() == (string) "country")
    {
      recipient.set_country(recipient_attr.first_child().value());
      sender.set_country(sender_attr.first_child().value());
    }
    if (recipient_attr.name() == (string) "name" && sender_attr.name() == (string) "name")
    {
      recipient.set_name(recipient_attr.first_child().value());
      sender.set_name(sender_attr.first_child().value());
    }
    if (recipient_attr.name() == (string) "postal-code" && sender_attr.name() == (string) "postal-code")
    {
      // Exception handling to convert a string to a long
      try
      {
        if (strtol(recipient_attr.first_child().value(), &endPtr, 10) <= 0 || strtol(recipient_attr.first_child().value(), &endPtr, 10) >= LONG_MAX)
        {
          throw str2l_error(recipient_attr.first_child().value());
        }
      }
      catch (str2l_error &e)
      {
        cerr << file_name << ": an exception occured " << e.what() << endl;
        return 1;
      }

      // Exception handling to convert a string to an int
      try
      {
        if ((int)strtol(recipient_attr.first_child().value(), &endPtr, 10) <= 0 || (int)strtol(recipient_attr.first_child().value(), &endPtr, 10) >= INT_MAX)
        {
          throw str2i_error(recipient_attr.first_child().value());
        }
      }
      catch (str2i_error &e)
      {
        cerr << file_name << ": an exception occured " << e.what() << endl;
        return 1;
      }
      postal_code = strtol(recipient_attr.first_child().value(), &endPtr, 10);
      recipient.set_postal_code(postal_code);
      postal_code = strtol(sender_attr.first_child().value(), &endPtr, 10);
      sender.set_postal_code(postal_code);
    }
    if (recipient_attr.name() == (string) "street" && sender_attr.name() == (string) "street")
    {
      recipient.set_street(recipient_attr.first_child().value());
      sender.set_street(sender_attr.first_child().value());
    }
    recipient_attr = recipient_attr.next_sibling();
    sender_attr = sender_attr.next_sibling();
  }
  return 0;
}

// Fetch the envelope's address data from the xml file
int envelope_address(xml_node root, envelope_t &envelope, int postal_code, char *endPtr, char *file_name)
{
  address_t recipient;
  address_t sender;
  string str = "envelope";
  string format1 = "c4";
  string format2 = "dl";
  xml_node envelopes_node = root.first_child();
  xml_node envelope_node = envelopes_node.first_child();
  while (envelope_node.name() == str)
  {
    xml_attribute format = envelope_node.first_attribute();
    if (envelope.get_width() == 229)
    {
      if (format.value() == format1)
      {
        if (fill_address(envelope_node, recipient, sender, postal_code, endPtr, file_name) == 1)
        {
          return 1;
        }
      }
    }
    if (envelope.get_width() == 110)
    {
      if (format.value() == format2)
      {
        if (fill_address(envelope_node, recipient, sender, postal_code, endPtr, file_name) == 1)
        {
          return 1;
        }
      }
    }
    envelope_node = envelope_node.next_sibling();
  }
  envelope.set_recipient(recipient);
  envelope.set_sender(sender);
  return 0;
}

// Fetch the envelope's priority data from the xml file
void envelope_priority(xml_node root, envelope_t &envelope)
{
  priority_t priority;
  string str = "envelope";
  string format1 = "c4";
  string format2 = "dl";
  xml_node envelopes_node = root.first_child();
  xml_node envelope_node = envelopes_node.first_child();
  while (envelope_node.name() == str)
  {
    xml_attribute format = envelope_node.first_attribute();
    if (envelope.get_width() == 229)
    {
      if (format.value() == format1)
      {
        xml_node priority_node = envelope_node.first_child().first_child();
        if (priority_node.value() == (string) "low")
          priority = low;
        if (priority_node.value() == (string) "high")
          priority = high;
        if (priority_node.value() == (string) "medium")
          priority = medium;
        envelope.set_priority(priority);
      }
    }
    if (envelope.get_width() == 110)
    {
      if (format.value() == format2)
      {
        xml_node priority_node = envelope_node.first_child().first_child();
        if (priority_node.value() == (string) "low")
          priority = low;
        if (priority_node.value() == (string) "high")
          priority = high;
        if (priority_node.value() == (string) "medium")
          priority = medium;
        envelope.set_priority(priority);
      }
    }
    envelope_node = envelope_node.next_sibling();
  }
}

// Fetch company's name data from the xml file
void company_name(xml_node root, company_t &company)
{
  xml_attribute name = root.first_attribute();
  company.set_name(name.value());
}

// Fetch company's web address data from the xml file
void company_web(xml_node root, company_t &company)
{
  string stop_node_at = "web";
  xml_node web = root.first_child();
  while (web.name() != stop_node_at)
  {
    web = web.next_sibling();
  }
  company.set_web(web.first_child().value());
}

// Reusable function to check if a string contain a number
bool isNumber(string str)
{
  return str.find_first_not_of("0123456789") == string::npos;
}

// Reusable function to check if the ec commands are correct
int ec_command_verif(string param, string command, char *file_name)
{
  if (param.size() == 0)
  {
    cerr << file_name << ": missing parameter for the " << command << " command" << endl;
    return 1;
  }
  else if (param.size() > 5 || param.size() < 5 || !isNumber(param))
  {
    cerr << file_name << ": invalid parameter for the " << command << " command" << endl;
    return 1;
  }
  else
  {
    return 0;
  }
}

// Main function
int main(int argc, char *argv[])
{
  char *str_char = new char[sizeof(char)];
  char *param_char = new char[sizeof(char)];
  char *endPtr;
  int postal_code = 0;
  company_t company;
  vector<envelope_t> envelopes;

  xml_document doc;
  xml_parse_result result = doc.load_file(argv[1]);
  xml_node root = doc.child("company");

  if (argc != 2)
  {
    cerr << argv[0] << ": invalid number of arguments" << endl;
    return 1;
  }

  if (!result)
  {
    cerr << argv[0] << ": unable to parse the document" << endl;
    return 1;
  }

  create_envelope(root, envelopes);
  for (unsigned i = 0; i < envelopes.size(); i++)
  {
    if (envelope_address(root, envelopes.at(i), postal_code, endPtr, argv[0]) == 1)
    {
      return 1;
    }
    envelope_priority(root, envelopes.at(i));
    company.envelopes_push_back(envelopes.at(i));
  }
  company_name(root, company);
  company_web(root, company);

  do
  {
    cout << "EDP> ";
    fgets(str_char, 25, stdin); // To be able to let the space caracter to be detected
    string str = str_char;
    str.at(str.size() - 1) = '\0';

    string param = "";
    string command = "";
    // Handle the param / command separation and stock both of the objects in the corresponding variable
    if (str.find_first_of(' ') >= 2 && str.find_first_of(' ') < str.size())
    {
      if (str.find_first_of(' ') == 2)
      {
        command.append(str.begin(), str.begin() + 2);
        param.append(str.begin() + 3, str.end() - 1);
      }
      else
      {
        command.append(str.begin(), str.begin() + 4);
        param.append(str.begin() + 5, str.end() - 1);
      }
    }
    else
    {
      command.append(str.begin(), str.end() - 1);
    }

    if (str.size() <= 18)
    {
      if (command == "h")
      {
        cout << "e: prints the envelopes\n"
             << "ec CODE: prints the envelopes with the sender postal code equal to CODE\n"
             << "ecge CODE: prints the envelopes with the sender postal code greater than or equal to CODE\n"
             << "ecgt CODE: prints the envelopes with the sender postal code greater than CODE\n"
             << "ecle CODE: prints the envelopes with the sender postal code less than or equal to CODE\n"
             << "eclt CODE: prints the envelopes with the sender postal code less than CODE\n"
             << "en NAME: prints the envelopes with the sender name containing NAME\n"
             << "h: prints this help\n"
             << "i: prints information about the company\n"
             << "n: prints the company name\n"
             << "q: quits EDP\n"
             << "v: prints the EDP version\n"
             << "w: prints the company web address"
             << endl;
      }
      else if (command == "e")
      {
        company.handle_e();
      }
      else if (command == "ec")
      {
        if (ec_command_verif(param, command, argv[0]) == 0)
        {
          param_char = new char[param.size() + 1];
          memcpy(param_char, param.c_str(), param.size() + 1);
          postal_code = strtol(param_char, &endPtr, 10);
          company.handle_ec(postal_code);
        }
      }
      else if (command == "ecge")
      {
        if (ec_command_verif(param, command, argv[0]) == 0)
        {
          param_char = new char[param.size() + 1];
          memcpy(param_char, param.c_str(), param.size() + 1);
          postal_code = strtol(param_char, &endPtr, 10);
          company.handle_ecge(postal_code);
        }
      }
      else if (command == "ecgt")
      {
        if (ec_command_verif(param, command, argv[0]) == 0)
        {
          param_char = new char[param.size() + 1];
          memcpy(param_char, param.c_str(), param.size() + 1);
          postal_code = strtol(param_char, &endPtr, 10);
          company.handle_ecgt(postal_code);
        }
      }
      else if (command == "ecle")
      {
        if (ec_command_verif(param, command, argv[0]) == 0)
        {
          param_char = new char[param.size() + 1];
          memcpy(param_char, param.c_str(), param.size() + 1);
          postal_code = strtol(param_char, &endPtr, 10);
          company.handle_ecle(postal_code);
        }
      }
      else if (command == "eclt")
      {
        if (ec_command_verif(param, command, argv[0]) == 0)
        {
          param_char = new char[param.size() + 1];
          memcpy(param_char, param.c_str(), param.size() + 1);
          postal_code = strtol(param_char, &endPtr, 10);
          company.handle_eclt(postal_code);
        }
      }
      else if (command == "en")
      {
        company.handle_en(param);
      }
      else if (command == "i")
      {
        company.handle_i();
      }
      else if (command == "n")
      {
        cout << company.get_name() << endl;
      }
      else if (command == "v")
      {
        cout << "EDP (Envelope Delivery Program) 20220306\n\nCopyright (C) 2022 Alicia Nunes and Pierre Amari.\n\nWritten by Alicia Nunes <alicia.nunes@etud.univ-pau.fr> and Pierre Amari <pierre.amari@etud.univ-pau.fr>." << endl;
      }
      else if (command == "w")
      {
        cout << company.get_web() << endl;
      }
      else if (command == "q")
      {
        break;
      }
      else
      {
        cerr << argv[0] << ": invalid command" << endl;
      }
    }
    else
    {
      cerr << argv[0] << ": too many characters for the command" << endl;
    }

  } while (true);

  free(str_char);
  free(param_char);
}