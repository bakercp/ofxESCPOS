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


#include "ByteBuffer.h"


namespace ofx {
namespace ESCPOS {

    
//------------------------------------------------------------------------------
ByteBuffer::ByteBuffer()
{
}

////------------------------------------------------------------------------------
//ByteBuffer::ByteBuffer(const ByteBuffer& data)
//{
//    write(data);
//}

//------------------------------------------------------------------------------
ByteBuffer::ByteBuffer(const Data& data)
{
    write(data);
}

//------------------------------------------------------------------------------
ByteBuffer::ByteBuffer(const std::string& data)
{
    write(data);
}

//------------------------------------------------------------------------------
ByteBuffer::ByteBuffer(unsigned char* buffer, size_t length)
{
    write(buffer,length);
}

//------------------------------------------------------------------------------
ByteBuffer::ByteBuffer(unsigned char d0)
{
    write(d0);
}

//------------------------------------------------------------------------------
ByteBuffer::ByteBuffer(unsigned char d0,
                       unsigned char d1)
{
    write(d0);
    write(d1);
}

//------------------------------------------------------------------------------
ByteBuffer::ByteBuffer(unsigned char d0,
                       unsigned char d1,
                       unsigned char d2)
{
    write(d0);
    write(d1);
    write(d2);
}

//------------------------------------------------------------------------------
ByteBuffer::ByteBuffer(unsigned char d0,
                       unsigned char d1,
                       unsigned char d2,
                       unsigned char d3)
{
    write(d0);
    write(d1);
    write(d2);
    write(d3);
}

//------------------------------------------------------------------------------
ByteBuffer::ByteBuffer(unsigned char d0,
                       unsigned char d1,
                       unsigned char d2,
                       unsigned char d3,
                       unsigned char d4)
{
    write(d0);
    write(d1);
    write(d2);
    write(d3);
    write(d4);
}

//------------------------------------------------------------------------------
ByteBuffer::~ByteBuffer()
{
}

//------------------------------------------------------------------------------
int ByteBuffer::write(const BaseHasByteBuffer& data)
{
    ByteBuffer buffer = data.getBuffer();
    _data.insert(_data.end(), buffer.getDataRef().begin(), buffer.getDataRef().end());
    return buffer.size();
}

//------------------------------------------------------------------------------
int ByteBuffer::write(const Data& data)
{
    _data.insert(_data.end(), data.begin(), data.end());
    return data.size();
}

//------------------------------------------------------------------------------
int ByteBuffer::write(const ByteBuffer& data)
{

    _data.insert(_data.end(), data._data.begin(), data._data.end());

//    Data d = data.getDataRef();
//
//    for(int i = 0; i < d.size(); i++) {
//        _data.push_back(d[i]);
//    }


    return data.size();
}

//------------------------------------------------------------------------------
int ByteBuffer::write(const std::string& data)
{
    _data.insert(_data.end(), data.begin(), data.end());
    return data.size();
}

//------------------------------------------------------------------------------
int ByteBuffer::write(unsigned char* buffer, size_t length)
{
    _data.insert(_data.end(), buffer, buffer+length);
    return length;
}

//------------------------------------------------------------------------------
int ByteBuffer::write(unsigned char d)
{
    _data.push_back(d);
    return 1;
}

//------------------------------------------------------------------------------
size_t ByteBuffer::size() const
{
    return _data.size();
}

//------------------------------------------------------------------------------
bool ByteBuffer::empty() const
{
    return _data.empty();
}

//------------------------------------------------------------------------------
size_t ByteBuffer::resize(size_t newSize)
{
    _data.resize(newSize);
}

//------------------------------------------------------------------------------
void ByteBuffer::clear()
{
    _data.clear();
}

//------------------------------------------------------------------------------
const ByteBuffer::Data& ByteBuffer::getDataRef() const {
    return _data;
}

//------------------------------------------------------------------------------
bool ByteBuffer::endsWith(unsigned char c) const
{
    if(!_data.empty()) {
        return _data.back() == c;
    } else {
        return false;
    }
}

//------------------------------------------------------------------------------
bool ByteBuffer::beginsWith(unsigned char c) const
{
    if(!_data.empty()) {
        return _data.front() == c;
    } else {
        return false;
    }
}

//------------------------------------------------------------------------------
bool ByteBuffer::isAscending() const
{
    unsigned char lastChar = 0;
    ConstIter iter = _data.begin();
    while(iter != _data.end()) {
        if(iter != _data.begin() && *iter < lastChar) return false;
        lastChar = *iter;
        ++iter;
    }

    return true;

}


} }  // namespace ofx::ESCPOS
