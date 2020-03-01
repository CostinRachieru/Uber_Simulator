// Copyright 2019 Rachieru Costin Tudor <<costinrch46@gmail.com>>

#ifndef HASHFUNCTIONS_H_
#define HASHFUNCTIONS_H_

#include <string>

int hash(std::string str) {
	return (str.length() << 10 / 8497);
}

#endif  // HASHFUNCTIONS_H_
