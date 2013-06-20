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


#include <string>
#include "BaseCodes.h"


namespace ofx {
namespace ESCPOS {

    
class ByteBuffer;
class BaseHasByteBuffer;


class BaseWriteBytes {
public:
    BaseWriteBytes()
    {
    }

    virtual ~BaseWriteBytes()
    {
    }

    virtual int write(const BaseHasByteBuffer& data) = 0;
    virtual int write(const ByteBuffer& data) = 0;
    virtual int write(const std::string& data) = 0;
    virtual int write(unsigned char* buffer, size_t length) = 0;
    virtual int write(unsigned char d) = 0;
};

class BaseHasByteBuffer {
public:
    BaseHasByteBuffer()
    {
    }

    virtual ~BaseHasByteBuffer()
    {
    }
    
    virtual ByteBuffer getBuffer() const = 0;

};

class BaseUserDefinedCharacter : public BaseHasByteBuffer {
public:
    BaseUserDefinedCharacter()
    {
    }

    virtual ~BaseUserDefinedCharacter()
    {
    }

    virtual unsigned char getCharacter() = 0;
};

class BaseUserDefinedCharacterSet : public BaseHasByteBuffer{
public:
    BaseUserDefinedCharacterSet()
    {
    }

    virtual ~BaseUserDefinedCharacterSet()
    {
    }

    virtual void set(const BaseUserDefinedCharacter& userDefinedCharacter) = 0;
    virtual void clear() = 0;
};


//class BaseCharacterCommands {
//public:
//    BaseCharacterCommands()
//    {
//    }
//
//    virtual ~BaseCharacterCommands()
//    {
//    }
//}
//



class BasePrinter : public BaseWriteBytes {
public:
    BasePrinter()
    {
    }

    virtual ~BasePrinter()
    {
    }

    virtual int read(ByteBuffer& buffer) = 0;

};


} }  // namespace ofx::ESCPOS
