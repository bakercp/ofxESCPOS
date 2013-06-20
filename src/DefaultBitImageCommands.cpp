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


#include "DefaultBitImageCommands.h"


namespace ofx {
namespace ESCPOS {
namespace Commands {


DefaultBitImageCommands::DefaultBitImageCommands()
{
}

DefaultBitImageCommands::~DefaultBitImageCommands()
{
}

//void DefaultBitImageCommands::print(const BitImage& image)
void DefaultBitImageCommands::print(const ofPixels& pixels,
                       BaseCodes::PrintResolution printResolution,
                       float threshold)
{

    if(pixels.getImageType() != OF_IMAGE_GRAYSCALE) {
        ofLogError("DefaultBitImageCommands::print") << "Only OF_IMAGE_GRAYSCALE.";
        return;
    }

    const int width     = pixels.getWidth();
    const int height    = pixels.getHeight();
    const int numPixels = width * height;

    // width = nL + (nH * 256)
    unsigned char nH = (unsigned char)(width >> 8);
    unsigned char nL = (unsigned char)(width & 0xFF);

    int numVerticalDots;

    switch(printResolution) {
        case BaseCodes::RESOLUTION_8_DOTS_SINGLE_DENSITY:
        case BaseCodes::RESOLUTION_8_DOTS_DOUBLE_DENSITY:
            numVerticalDots = 8;
            break;
        case BaseCodes::RESOLUTION_24_DOTS_SINGLE_DENSITY:
        case BaseCodes::RESOLUTION_24_DOTS_DOUBLE_DENSITY:
            numVerticalDots = 24;
            break;
        default:
            numVerticalDots = 0;
    }

    int numVerticalBytes = numVerticalDots / 8;

    int yOffset = 0;

    const unsigned char* pPixels = pixels.getPixels();

    while(yOffset < height) {

        ByteBuffer buffer;

        buffer.write(BaseCodes::ESC);
        buffer.write('*'); // specify bit image mode
        buffer.write((unsigned char)printResolution); // resolution
        buffer.write(nL); // low byte
        buffer.write(nH); // high byte

        for(int x = 0; x < width; x++) {
            
            for(int byteIndex = 0; byteIndex < numVerticalBytes; byteIndex++) {

                unsigned char currentByte = 0;

                for(int bitIndex = 0; bitIndex < 8; bitIndex++) {

                    int y = (((yOffset / 8) + byteIndex) * 8) + bitIndex;

                    int index = pixels.getPixelIndex(x,y);

                    if(index < numPixels) {
                        currentByte |= (pPixels[index] < threshold * 255 ? 1 : 0) << (7 - bitIndex);
                    }
                }

                buffer.write(currentByte);
            }
        }

        buffer.write(BaseCodes::LF);

        write(buffer);

        yOffset += numVerticalDots;
    }
}


} } } // namespace ofx::ESCPOS::Commands
