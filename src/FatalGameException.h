//
// Created by Fiskie on 24/05/15.
//

#pragma once 

#include <exception>
#include <stdio.h>
#include <string.h>

class FatalGameException : public std::exception {
private:
    const char *message;

public:
    FatalGameException(char *message) {
        this->message = message;
    }

    FatalGameException(const char *message) {
        this->message = message;
    }

    virtual const char *what() const throw() {
        char str[] = "Fatal game exception: ";

        return strcat(str, message);
    }
};