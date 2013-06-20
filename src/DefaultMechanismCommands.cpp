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


#include "DefaultMechanismCommands.h"


namespace ofx {
namespace ESCPOS {
namespace Commands {

    //------------------------------------------------------------------------------
DefaultMechanismCommands::DefaultMechanismCommands()
{
}

//------------------------------------------------------------------------------
DefaultMechanismCommands::~DefaultMechanismCommands()
{
}

//------------------------------------------------------------------------------
void DefaultMechanismCommands::cut(BaseCodes::PaperCut type, unsigned char numDotsToFeed)
{
    if(numDotsToFeed > 0) {
        write(ByteBuffer(BaseCodes::GS,'V',type));
    } else {
        write(ByteBuffer(BaseCodes::GS,'V',type + 65, numDotsToFeed)); // shift -> A/B
    }
}


} } } // namespace ofx::ESCPOS::Commands
