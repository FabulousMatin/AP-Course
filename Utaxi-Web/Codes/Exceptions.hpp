#ifndef Exceptions_H
#define Exceptions_H

#include <iostream>
#include <sstream>

class Exceptions
{
public:
    Exceptions(int err);
    virtual std::string handle_error(int& code) = 0;
    std::string create_html();
    std::string create_style();
protected:
    std::string prev_page_url;
    std::string err_text;
    std::string err_header;
    int error_type;
};

class Empty : public Exceptions
{
public:
    Empty(int err);
    std::string handle_error(int& code);

    enum types
    {
        NO_TRIP,
        VARIABLE_EMPTY
    };
};

class Not_found : public Exceptions
{
public:
    std::string handle_error(int& code);
    Not_found(int err);

    enum types
    {
        PASS_NF_ADD_TRIP,
        DRI_NF_GET_TRIP,
        TRIP_NF,
        PASS_NF_GET_COST,
        PASS_NF_CANCEL,
        TRIP_NF_CANCEL,
        DRI_NF_ACC,
        TRIP_NF_ACC,
        DRI_NF_FIN,
        TRIP_NF_FIN

    };
};

class Bad_request : public Exceptions
{
public:

    Bad_request(int err);
    std::string handle_error(int& code);

    enum types
    {
        USER_EXIST,
        ALREADY_IN_TRIP,
        DEFAULT,
        TRIP_NOT_CANCELABLE,
        TRIP_NOT_ACCEPTABLE,
        DRIVER_NOT_IN_TRIP
    };

};

class Permission_denied : public Exceptions
{
public:
    Permission_denied(int err);
    std::string handle_error(int& code);

    enum types
    {
        AFTER_ADD_TRIP,
        AFTER_GET_TRIP,
        AFTER_GET_COST,
        AFTER_CANCEL,
        CANCEL_AMOTHER_TRIP,
        AFTER_ACCEPT,
        AFTER_FINISH,
        FINISH_ANOTHER_TRIP
    };
};
#endif