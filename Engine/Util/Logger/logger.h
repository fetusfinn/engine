/*
 *  logger.h
 */
#pragma once

#include "console.h"

#define debug(msg)   log(msg, LOG_DEFAULT, "debug", fg::yellow)
#define message(msg) log(msg, LOG_DEFAULT, "engine", fg::cyan)
#define error(msg)   log(msg, LOG_ERROR)
#define error_line(msg) print_error_line(msg, __FILE__, __LINE__)

#define log_msg
#define log_err
#define log_warn
#define log_dev

enum LOG_LEVEL
{
    LOG_DEFAULT = 1,
    LOG_WARN    = 2,
    LOG_ERROR   = 3,
};

template <class t>
void log(t message, int level = LOG_DEFAULT, std::string prefix = "log", fg color = fg::reset)
{
    switch (level)
    {
        case LOG_WARN:
            std::cout << fg::yellow << "[WARNING] " << style::reset << message << std::endl;
            break;
        case LOG_ERROR:
            std::cout << fg::red << "[ERROR] " << style::reset << message << std::endl;
            break;
        case LOG_DEFAULT:
        default:
            std::cout << color << "[" << prefix << "] " << style::reset << message << std::endl;
            break;
    }
}

 template<class t>
 inline void print_error_line(t message, std::string file, int line)
 {
     file = std::string(find_if(file.rbegin(), file.rend(), [=](char ch) { return ch == '/'; }).base(), file.end());
     log(std::string(message + "|" + file + ":" + std::to_string(line)), LOG_ERROR);
 }
