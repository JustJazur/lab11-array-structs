#ifndef OBSERVATION_H
#define OBSERVATION_H

#include <string> // Provides the string fields used by each observation

struct Observation {
    int id = 0; // Initializes the identifier before data is entered

    std::string state;
    std::string county;

    int democraticVotes = 0;
    int republicanVotes = 0;
    double democraticShare = 0.0;
    double republicanShare = 0.0;

    bool isEmpty = true; // Marks each newly created slot as available
};

#endif