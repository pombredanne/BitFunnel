// The MIT License (MIT)

// Copyright (c) 2016, Microsoft

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#include <iostream>

#include "FailOnExceptionCommand.h"
#include "Environment.h"


namespace BitFunnel
{
    //*************************************************************************
    //
    // FailOnException
    //
    //*************************************************************************
    FailOnException::FailOnException(Environment & environment,
                                     Id id,
                                     char const * /*parameters*/)
        : TaskBase(environment, id, Type::Synchronous)
    {
    }


    void FailOnException::Execute()
    {
        GetEnvironment().SetFailOnException(true);
        std::cout
            << "REPL will now throw an exception if an error is detected." << std::endl
            << "Restart REPL to reenable catching of exceptions." << std::endl
            << std::endl;
    }


    ICommand::Documentation FailOnException::GetDocumentation()
    {
        return Documentation(
            "failOnException",
            "Forces application failure when exceptions are thrown.",
            "failOnException\n"
            "  Forces application failure when exceptions are thrown."
        );
    }
}
