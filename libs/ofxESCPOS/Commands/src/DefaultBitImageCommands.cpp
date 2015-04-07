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
#include "ofAppRunner.h"

namespace ofx {
namespace ESCPOS {
namespace Commands {


DefaultBitImageCommands::DefaultBitImageCommands()
{
}


DefaultBitImageCommands::~DefaultBitImageCommands()
{
}


std::size_t DefaultBitImageCommands::printImage(const ofPixels_<unsigned char>& pixels,
                                                ofAlignHorz alignHorz,
                                                float ditherThreshold,
                                                float ditherQuantWeight,
                                                BaseCodes::PrintResolution printResolution,
                                                int printHeadWidth,
                                                int printHeadHeight)
{

    int numVerticalDots = 0;
    int maxHorizontalDots = 0;
    int verticalScale = 1;

    switch (printResolution)
    {
        case BaseCodes::RESOLUTION_8_DOTS_SINGLE_DENSITY:
            maxHorizontalDots = printHeadWidth / 2;
            numVerticalDots = 8;
            break;
        case BaseCodes::RESOLUTION_8_DOTS_DOUBLE_DENSITY:
            maxHorizontalDots = printHeadWidth;
            numVerticalDots = 8;
            break;
        case BaseCodes::RESOLUTION_24_DOTS_SINGLE_DENSITY:
            maxHorizontalDots = printHeadWidth / 2;
            numVerticalDots = 24;
            break;
        case BaseCodes::RESOLUTION_24_DOTS_DOUBLE_DENSITY:
            maxHorizontalDots = printHeadWidth;
            numVerticalDots = 24;
            break;
    }

    std::size_t totalBytesWritten = 0;

    ofRectangle imageRect(0,0,pixels.getWidth(),pixels.getHeight());
    ofRectangle rectangle(0,0,maxHorizontalDots,pixels.getHeight());

    imageRect.scaleTo(rectangle,
                      OF_ASPECT_RATIO_KEEP,
                      alignHorz,
                      OF_ALIGN_VERT_TOP,
                      alignHorz,
                      OF_ALIGN_VERT_TOP);

    int width = rectangle.getWidth();
    int height = imageRect.getHeight();

    // ensure vertical res
    if (height != numVerticalDots)
    {
        int remainder = height % numVerticalDots;
        if (remainder != 0)
        {
            height = height + numVerticalDots - remainder;
        }
    }

    ofPixels pix = pixels; // get a copy
    ofPixels toPrint;

    toPrint.allocate(width, height, pix.getNumChannels());
    toPrint.setColor(ofColor(255));

    pix.resize(imageRect.getWidth(), imageRect.getHeight());
    pix.pasteInto(toPrint,imageRect.getX(),imageRect.getY());

    toPrint = ImageUtils::dither(toPrint,ditherThreshold,ditherQuantWeight);

    cout << pix.getWidth() << " / " << pix.getHeight() << endl;

    ofPixels bandBuffer;

    bandBuffer.allocate(toPrint.getWidth(), numVerticalDots, toPrint.getNumChannels());

    // go into page mode
    totalBytesWritten += writeByte(BaseCodes::ESC);
    totalBytesWritten += writeByte('L');

    // set the print area / origin
    totalBytesWritten += setPageModePrintArea(0,0,toPrint.getWidth(),toPrint.getHeight() * 2); // TODO 2 * works for double vert density


    for (int y = 0; y < height; y += numVerticalDots)
    {
        // set the vertical displacement
        const uint8_t command[3] = { BaseCodes::ESC, '3', numVerticalDots * 2 }; // TODO 2 * works for double vert density
        totalBytesWritten += writeBytes(command, 3);

        bandBuffer.clear();
        toPrint.cropTo(bandBuffer,0,y,width,numVerticalDots);
        totalBytesWritten += selectBitImageMode(bandBuffer, printResolution);
        totalBytesWritten += writeByte(BaseCodes::LF); // feed a line

        // set vertical displacement back to normal
        const uint8_t command0[2] = { BaseCodes::ESC, '2' };
        totalBytesWritten += writeBytes(command0, 2);
    }


//    totalBytesWritten += writeByte(BaseCodes::LF); // feed a line
    totalBytesWritten += writeByte(BaseCodes::FF);

    return totalBytesWritten;
}


std::size_t DefaultBitImageCommands::setPageModePrintArea(int x,
                                                          int y,
                                                          int width,
                                                          int height)
{
    uint8_t xL = getLowByte(x);
    uint8_t xH = getHighByte(x);

    uint8_t yL = getLowByte(y);
    uint8_t yH = getHighByte(y);

    uint8_t dXL = getLowByte(width);
    uint8_t dXH = getHighByte(width);

    uint8_t dYL = getLowByte(height);
    uint8_t dYH = getHighByte(height);

    const uint8_t command[10] = {BaseCodes::ESC, 'W', xL, xH, yL, yH, dXL, dXH, dYL, dYH };

    return writeBytes(command,10);
}


std::size_t DefaultBitImageCommands::selectBitImageMode(const ofPixels_<unsigned char>& binaryPixels,
                                                        BaseCodes::PrintResolution printResolution)
{
    // width = nL + (nH * 256)
    // nH is the HIGH part of the WIDTH VALUE.
    // nL is the LOW part of the WIDTH VALUE.
    // nH will always be 0 for values less that 256 (1 byte)
    uint8_t nH = getHighByte(binaryPixels.getWidth());
    uint8_t nL = getLowByte(binaryPixels.getWidth());

    std::vector<uint8_t> buffer;

    buffer.push_back(BaseCodes::ESC);
    buffer.push_back('*');
    buffer.push_back(printResolution);
    buffer.push_back(nL);
    buffer.push_back(nH);

    uint8_t currentByte = 0;
    int bitIndex = 0;

    for (int x = 0; x < binaryPixels.getWidth(); ++x)
    {
        currentByte = 0;
        bitIndex = 0;

        for (int y = 0; y < binaryPixels.getHeight(); ++y)
        {
            bool binaryValue = binaryPixels[binaryPixels.getPixelIndex(x,y)] < ofColor_<unsigned char>::limit() / 2;

            currentByte |= binaryValue << (7 - bitIndex);

            bitIndex++;

            if (8 == bitIndex)
            {
                buffer.push_back(currentByte);
                currentByte = 0;
                bitIndex = 0;
            }
        }
    }
    
    return writeBytes(buffer);
}


uint8_t DefaultBitImageCommands::getHighByte(std::size_t d)
{
    return (uint8_t)(d >> 8);
}


uint8_t DefaultBitImageCommands::getLowByte(std::size_t d)
{
    return (uint8_t)(d & 0xFF);
}


} } } // namespace ofx::ESCPOS::Commands
