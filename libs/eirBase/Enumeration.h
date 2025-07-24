#pragma once

class Enumeration
{
public:
    Enumeration();
};

/* g++ -E -dM file.cpp should do the job. -dM, as GNU Preprocessor manual puts it, should generate a list of ‘#define’ directives for all the macros defined during the execution of the preprocessor, including predefined macros. */
