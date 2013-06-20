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


#include "DefaultSerialPrinter.h"


namespace ofx {
namespace ESCPOS {

//------------------------------------------------------------------------------
DefaultSerialPrinter::DefaultSerialPrinter()
{
}

//------------------------------------------------------------------------------
DefaultSerialPrinter::~DefaultSerialPrinter()
{
}

//------------------------------------------------------------------------------
int DefaultSerialPrinter::write(const BaseHasByteBuffer& command)
{
    return write(command.getBuffer());
}

//------------------------------------------------------------------------------
int DefaultSerialPrinter::write(const ByteBuffer& buffer)
{
    ByteBuffer bb = buffer;
    return writeBytes(bb.getPtr(), bb.size()); // TODO: should ofSerial::writeBytes be const?
}

//------------------------------------------------------------------------------
int DefaultSerialPrinter::read(ByteBuffer& buffer)
{
    size_t numAvailable = available();
    buffer.resize(numAvailable);
    return readBytes(buffer.getPtr(), numAvailable);
}

//------------------------------------------------------------------------------
int DefaultSerialPrinter::write(unsigned char* buffer, size_t length)
{
    return writeBytes(buffer,(int)length);
}

//------------------------------------------------------------------------------
int DefaultSerialPrinter::write(const std::string& msg)
{
    return writeBytes((unsigned char*)msg.c_str(),msg.size());
}

//------------------------------------------------------------------------------
int DefaultSerialPrinter::write(unsigned char d)
{
    return writeByte(d);
}


} } // namespace ofx::ESCPOS
