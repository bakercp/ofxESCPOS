// =============================================================================
//
// Copyright (c) 2013 Christopher Baker <http://christopherbaker.net>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
// =============================================================================


#pragma once


#include <vector>
#include "ofUtils.h"
#include "BaseTypes.h"

namespace ofx {
namespace ESCPOS {


class ByteBuffer : public BaseWriteBytes {
public:
    typedef std::vector<unsigned char> Data;
    typedef std::vector<unsigned char>::iterator Iter;
    typedef std::vector<unsigned char>::const_iterator ConstIter;

    ByteBuffer();
    explicit ByteBuffer(const Data& data);
    explicit ByteBuffer(const std::string& data);
    explicit ByteBuffer(unsigned char* buffer, size_t length);
    explicit ByteBuffer(unsigned char d0);
    explicit ByteBuffer(unsigned char d0, unsigned char d1);
    explicit ByteBuffer(unsigned char d0, unsigned char d1, unsigned char d2);
    explicit ByteBuffer(unsigned char d0, unsigned char d1, unsigned char d2, unsigned char d3);
    explicit ByteBuffer(unsigned char d0, unsigned char d1, unsigned char d2, unsigned char d3, unsigned char d4);

    ~ByteBuffer();

    int write(const Data& data);
    int write(const BaseHasByteBuffer& data);
    int write(const ByteBuffer& data);
    int write(const std::string& data);
    int write(unsigned char* buffer, size_t length);
    int write(unsigned char d);

    size_t size() const;

    bool empty() const;

    size_t resize(size_t newSize);

    void clear();

    const Data& getDataRef() const;

    bool endsWith(unsigned char c) const;
    bool beginsWith(unsigned char c) const;
    bool isAscending() const;

	unsigned char& operator[](size_t n)
    {
		return _data[n];
	}

	unsigned char operator[](size_t n) const
    {
		return _data[n];
	}

    unsigned char* getPtr() {
        if(_data.empty()){
            return NULL;
        }
        return &_data[0];
    }

    friend ostream& operator<<(ostream& os, const ByteBuffer& vec);

private:
    Data _data;

};


inline ostream& operator<<(ostream& os, const ByteBuffer& buffer) {
    ByteBuffer::ConstIter iter = buffer._data.begin();
    while(iter != buffer._data.end()) {
        os << (int)*iter;
        ++iter;
        if(iter != buffer._data.end()) {
            os << " ";
        }
    }

    return os;
}

} }  // namespace ofx::ESCPOS
