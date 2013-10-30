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


//void DefaultBitImageCommands::print(const ofPixels& pixels,
//                                    const ofRectMode& roi,
//                                    BaseCodes::PrintResolution printResolution,
//                                    float threshold,
//
//
//

void DefaultBitImageCommands::printPixels(const ofPixels_<unsigned char>& _pixels,
                                          float threshold,
                                          BaseCodes::PrintResolution printResolution,
                                          std::size_t maxWidth)
{

    if (OF_IMAGE_GRAYSCALE != _pixels.getImageType())
    {
        ofLogError("DefaultBitImageCommands::printPixels") << "Grayscale images only.";
        return;
    }

    ofPixels_<unsigned char> pixels = _pixels;

    int numVerticalDots;
    int maxHorizontalDots;

    switch(printResolution)
    {
        case BaseCodes::RESOLUTION_8_DOTS_SINGLE_DENSITY:
            maxHorizontalDots = maxWidth / 2;
            numVerticalDots = 8;
            break;
        case BaseCodes::RESOLUTION_8_DOTS_DOUBLE_DENSITY:
            maxHorizontalDots = maxWidth;
            numVerticalDots = 8;
            break;
        case BaseCodes::RESOLUTION_24_DOTS_SINGLE_DENSITY:
            maxHorizontalDots = maxWidth / 2;
            numVerticalDots = 24;
            break;
        case BaseCodes::RESOLUTION_24_DOTS_DOUBLE_DENSITY:
            maxHorizontalDots = maxWidth;
            numVerticalDots = 24;
            break;
    }

    cout << "maxHorizontalDots=" << maxHorizontalDots << endl;
    cout << "numVerticalDots=" << numVerticalDots << endl;

    int width = pixels.getWidth();

    if(width > maxHorizontalDots)
    {
        ofLogWarning("DefaultBitImageCommands::bitmap") << "Pixels width " << pixels.getWidth() << " exceeds print width for setting.";
        width = maxHorizontalDots;
    }

    int height = pixels.getHeight();

    if(height != numVerticalDots)
    {
        ofLogWarning("DefaultBitImageCommands::bitmap") << "Pixels height " << pixels.getHeight() << " exceeds print height for setting.";
        height = numVerticalDots;
    }


    cout << "w=" << width << "h=" << height << endl;

    int numPixels = width * height;

    // width = nL + (nH * 256)
    // nH is the HIGH part of the WIDTH VALUE.
    // nL is the LOW part of the WIDTH VALUE.
    // nH will always be 0 for values less that 256 (1 byte)
    uint8_t nH = (uint8_t)(width >> 8);
    uint8_t nL = (uint8_t)(width & 0xFF);

    cout << "nH=" << (int)nH << endl;
    cout << "nL=" << (int)nL << endl;

    std::vector<uint8_t> buffer;

    buffer.push_back(BaseCodes::ESC);
    buffer.push_back('*');
    buffer.push_back(printResolution);
    buffer.push_back(nL);
    buffer.push_back(nH);

    uint8_t currentByte = 0;
    int bitIndex = 0;

    for(int x = 0; x < width; ++x)
    {
        currentByte = 0;
        bitIndex = 0;

        for(int y = 0; y < height; ++y)
        {
            ofColor_<unsigned char> pixelValue = pixels.getColor(x, y);

            bool thresholdValue = pixelValue.getBrightness() < (threshold * ofColor_<unsigned char>::limit());

            currentByte |= (thresholdValue << (7 - bitIndex));

            bitIndex++;

            if(bitIndex == 8)
            {
                buffer.push_back(currentByte);
                currentByte = 0;
                bitIndex = 0;
            }
        }
    }

    std::size_t bytesWritten = writeBytes(buffer);
}

void DefaultBitImageCommands::printImage(const ofPixels_<unsigned char>& _pixels,
                                        float threshold,
                                        BaseCodes::PrintResolution printResolution,
                                        std::size_t maxWidth)
{
   if (OF_IMAGE_GRAYSCALE != _pixels.getImageType())
   {
       ofLogError("DefaultBitImageCommands::printPixels") << "Grayscale images only.";
       return;
   }

   ofPixels_<unsigned char> pixels = _pixels;

   int numVerticalDots = 0;
   int maxHorizontalDots = 0;

   switch(printResolution)
   {
       case BaseCodes::RESOLUTION_8_DOTS_SINGLE_DENSITY:
           maxHorizontalDots = maxWidth / 2;
           numVerticalDots = 8;
           break;
       case BaseCodes::RESOLUTION_8_DOTS_DOUBLE_DENSITY:
           maxHorizontalDots = maxWidth;
           numVerticalDots = 8;
           break;
       case BaseCodes::RESOLUTION_24_DOTS_SINGLE_DENSITY:
           maxHorizontalDots = maxWidth / 2;
           numVerticalDots = 24;
           break;
       case BaseCodes::RESOLUTION_24_DOTS_DOUBLE_DENSITY:
           maxHorizontalDots = maxWidth;
           numVerticalDots = 24;
           break;
   }

   int width = _pixels.getWidth();

   if(width > maxHorizontalDots)
   {
       ofLogWarning("DefaultBitImageCommands::printImage") << "Pixels width " << _pixels.getWidth() << " exceeds print width for setting.";
       width = maxHorizontalDots;
   }

   int height = _pixels.getHeight();

   if(height != numVerticalDots)
   {
       int remainder = height % numVerticalDots;

       if (remainder != 0)
       {
           height = height + numVerticalDots - remainder;
       }
   }

   ofPixels_<unsigned char> toPrint;

   toPrint.allocate(width, height, 1);

   toPrint = ImageUtils::dither(_pixels);

   ofPixels_<unsigned char> buffer;
   buffer.allocate(width,numVerticalDots,1);

   const uint8_t command[3] = { BaseCodes::ESC, '3', 24 };
   writeBytes(command, 3);

   for(int y = 0; y < height; y += numVerticalDots)
   {
       toPrint.cropTo(buffer, 0, y, width, numVerticalDots);

       printPixels(buffer,
                   threshold,
                   printResolution,
                   maxWidth);

       ofSleepMillis(100);
   }

   const uint8_t command0[2] = { BaseCodes::ESC, '2' };
   writeBytes(command0, 2);


}



} } } // namespace ofx::ESCPOS::Commands
