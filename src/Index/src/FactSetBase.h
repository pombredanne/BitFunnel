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


#pragma once

#include <vector>
#include <string>       // FactInfo embeds std::string.

#include "BitFunnel/Index/IFactSet.h"

namespace BitFunnel
{
    //*************************************************************************
    //
    // FactSetBase provides a base implementation of IFactSet. Consumers can
    // override this class if they want to automatically add facts applicable to
    // their use cases to the set.
    //
    // This class is not thread-safe.
    //
    // DESIGN NOTE: Internally FactHandle is being treated as a Term::Hash.
    // Various classes can detect that certain values of Term::Hash correspond
    // to facts and treat them appropriately, for example TermTable. We are not
    // using Term::Hash instead of FactHandle intentionally because the end
    // users should not know this implementation detail.
    //
    //*************************************************************************
    class FactSetBase : public IFactSet
    {
    public:
        // Creates an empty fact set and automatically adds a fact for a soft
        // deleted document.
        FactSetBase();

        //
        // IFactSet methods.
        //
        virtual FactHandle DefineFact(char const * friendlyName,
                                      bool isMutable) override;
        virtual unsigned GetCount() const override;
        virtual FactHandle operator[](unsigned index) const override;
        virtual bool IsMutable(FactHandle fact) const override;
        virtual char const * GetFriendlyName(FactHandle fact) const override;

    private:
        // Descriptor of a fact. Consumers of the facts use FactHandle in the
        // ingestion API and PlanDescriptor.
        class FactInfo
        {
        public:
            // Constructs a fact with the given friendly name, handle and a
            // mutable flag.
            FactInfo(char const * friendlyName,
                     bool isMutable,
                     FactHandle handle);

            FactInfo(FactInfo const & other);

            // Returns a friendly name associated with the fact.
            char const * GetFriendlyName() const;

            // Returns a handle associated with the fact.
            FactHandle GetHandle() const;

            // Returns whether a fact is mutable or not.
            bool IsMutable() const;

        private:
            // Define but refuse to implement a private assignment operator to
            // force std::vector to use the copy constructor.
            FactInfo const & operator=(FactInfo const &);

            const std::string m_friendlyName;
            const FactHandle m_handle;
            const bool m_isMutable;
            // All facts are now private rank 0 rows. In the future, this class
            // may have other fields such as rank, number of rows, etc.
        };

        // Finds a FactInfo for a given handle. If a fact with this handle is
        // not found, this function throws.
        FactInfo const & GetFactInfoByHandle(FactHandle handle) const;

        std::vector<FactInfo> m_facts;
    };
}
