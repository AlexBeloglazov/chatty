/*
 * helpers.cpp : File contains helper methods needed for both Server and Client modes
 * Created for CSE 589 Fall 2017 Programming Assignment 1
 * @author Alexander Beloglazov
 */

#include "../include/helpers.h"

/* 
 * Method is used for comparing port numbers of two Machine instances.
 * Used in vector of Machine sorting
 * @input l pointer to left Machine in vector
 * @input r pointer to right machine in vector
 * @return bool True if port number of first Machine > port number of left Machine
 */
bool cmp_ports(Machine *l, Machine *r) {
    return (l->port < r->port);
}

/* 
 * Method sorts vector of Machine
 * @input mlist vector of Machine pointers
 */
void ml_sort_by_port(std::vector<Machine*> *mlist) {
    std::sort(mlist->begin(), mlist->end(), cmp_ports);
}

/* 
 * Method removes Machine with certain IP from Machine vector
 * @input mlist pointer to vector of Machine pointers
 * @input ip IP address of a machine to delete
 */
void ml_remove_by_ip(std::vector<Machine*> *mlist, const std::string &ip) {
    std::vector<Machine*>::iterator it;
    for(it = mlist->begin(); it != mlist->end(); ++it) {
        if ((*it)->ip == ip) {
            delete *it;
            mlist->erase(it);
            break;
        }
    }
}

/* 
 * Method returns pointer to Machine which has certain IP address
 * Uses global IP->Machine map as a container to search in
 * @input ip IP address to search
 * @return pointer to Machine in the map ip2machine
 */
Machine *get_machine(const std::string &ip)
{
    std::map<std::string, Machine *>::iterator it;
    it = ip2machine->find(ip);
    return (it == ip2machine->end()) ? NULL : it->second;
}

/* 
 * Method returns pointer to Machine which has certain IP address
 * @input ip IP address to search
 * @input vector of Machine pointers
 * @return pointer to Machine in the map ip2machine
 */
Machine *get_machine(const std::string &ip, std::vector<Machine*> &ml)
{
    std::vector<Machine *>::iterator it;
    for (it = ml.begin(); it != ml.end(); ++it) {
        if (ip == (*it)->ip) return *it;
    }
    
    return NULL;
}

/* 
 * Method extracts ip addres from sockaddr_in structure
 * @input sa sockaddr_in structure
 * @return IP address as C++ string
 */
std::string extract_ip(struct sockaddr_in &sa)
{
    char str_ip[INET_ADDRSTRLEN];
    inet_ntop(sa.sin_family, &(sa.sin_addr), str_ip, sizeof(str_ip));
    return std::string(str_ip);
}

/* 
 * Method checks whether a given IP address is valid
 * @input ip C++ string contains IP address to check
 * @return bool whether IP address is valid
 */
bool is_valid_ip(const std::string &ip)
{
    struct sockaddr_in sa;
    return inet_pton(AF_INET, &ip[0], &(sa.sin_addr)) == 1;
}

/* 
 * Method checks whether a given C++ string is a valid number
 * @input number C++ string
 * @return bool whether the given string is a valid number
 */
bool is_number(const std::string &number) {
    std::string::const_iterator it = number.begin();
    while(it != number.end() && isdigit(*it)) ++it;
    return !number.empty() && it == number.end();
}

/* 
 * Method reads STDIN and saves input in a stringstream object
 * @input inp stringstream object to save user's input in
 */
void read_stdin(std::stringstream &inp)
{
    std::string line;
    std::getline(std::cin, line);
    inp.str(line);
}

/* 
 * Method reads specified number of characters from a given istringstream
 * @input ss istringstream to read characters from
 * @input l number of characters to read
 * @input bus C++ string object where the read characters will be saved
 */
void read_from_stream(std::istringstream &ss, int l, std::string &buf) {
    buf.resize(l);
    ss >> std::ws;
    ss.read(&buf[0], l);
}
