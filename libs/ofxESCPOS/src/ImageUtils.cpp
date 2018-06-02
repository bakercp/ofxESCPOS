//
// Copyright (c) 2013 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:    MIT
//


#include "ImageUtils.h"
#include "ofGraphicsConstants.h"


namespace ofx {
namespace ESCPOS {


ofPixels_<unsigned char> ImageUtils::scaleAndCropTo(const ofPixels_<unsigned char>& pixels,
                                                    std::size_t width,
                                                    std::size_t height,
                                                    ofScaleMode scaleMode)
{
    ofRectangle inRect(0, 0, pixels.getWidth(), pixels.getHeight());

    ofRectangle outRect(0, 0, width, height);

    inRect.scaleTo(outRect, scaleMode);

    auto inPixels = pixels;

    inPixels.resize(inRect.getWidth(), inRect.getHeight());

    ofPixels_<unsigned char> outPixels;

    inPixels.cropTo(outPixels,
                    outRect.x - inRect.x,
                    0,
                    outRect.width,
                    outRect.height);

    return outPixels;
}


ofPixels_<unsigned char> ImageUtils::dither(const ofPixels_<unsigned char>& pixels,
                                            float threshold,
                                            float quantWeight)
{
    // Special thanks to @julapy / ofxDither
    auto pixelsIn = pixels;

    // Ensure the image is grayscale
    if (OF_IMAGE_GRAYSCALE != pixelsIn.getImageType())
    {
        pixelsIn = toGrayscale(pixels);
    }

    // make a copy
    auto pixelsOut = pixelsIn;

    // set up the quantization error
    std::size_t width  = pixelsOut.getWidth();
    std::size_t height = pixelsOut.getHeight();

    std::size_t numPixels = width * height; // 1 byte / pixel

    float qErrors[numPixels];

    std::fill(qErrors, qErrors + numPixels, 0.0);

    //unsigned char* inPix  = pixelsIn.getPixels();
    unsigned char* outPix = pixelsOut.getData();

    float limit = ofColor_<unsigned char>::limit();

    for (std::size_t y = 0; y < height; y++)
    {
        for (std::size_t x = 0; x < width; x++)
        {
            std::size_t p = pixelsIn.getPixelIndex(x, y);

            std::size_t oldPx = outPix[p] + qErrors[p]; // add error
            std::size_t newPx = (oldPx < (threshold * limit)) ? 0 : limit;  // threshold

            outPix[p] = newPx;

            std::size_t qError = oldPx - newPx;

            accumulateDitherError(x+1,y  ,pixelsOut,qError,qErrors,quantWeight); // check east
            accumulateDitherError(x+2,y  ,pixelsOut,qError,qErrors,quantWeight); // check east east
            accumulateDitherError(x-1,y+1,pixelsOut,qError,qErrors,quantWeight); // check southwest
            accumulateDitherError(x  ,y+1,pixelsOut,qError,qErrors,quantWeight); // check south
            accumulateDitherError(x+1,y+1,pixelsOut,qError,qErrors,quantWeight); // check southeast
            accumulateDitherError(x  ,y+2,pixelsOut,qError,qErrors,quantWeight); // check south south
        }
    }

    return pixelsOut;
}

////------------------------------------------------------------------------------
//BitImage ImageUtils::makeBitImage(const ofPixels& pixelsIn,
//                                  BitImage::ByteFormat format,
//                                  float threshold)
//{
//    if(pixelsIn.getImageType() != OF_IMAGE_GRAYSCALE) {
//        // warning ... must be grayscale
//    }
//
//    ByteBuffer buffer;
//
//    int width  = pixelsIn.getWidth();
//    int height = pixelsIn.getHeight();
//
//    const unsigned char* pixels = pixelsIn.getPixels();
//
//    unsigned char currentByte = 0;
//    unsigned char bitIndex = 0;
//
//    cout << "w/h=" << width << " / " << height << endl;
//
//    if(format == BitImage::BYTE_FORMAT_COLUMN) {
//        for(int x = 0; x < width; x++) {
//            for(int y = 0; y < height; y++) {
//
//                int p = pixelsIn.getPixelIndex(x,y);
//
//                buffer.write(pixels[p] < threshold * 255 ? 0 : 1);
//
////                currentByte |= (pixels[p] < threshold * 255 ? 0 : 1) << bitIndex;
////                bitIndex++;
////
////                if(y + 1 < height && bitIndex >= 8) {
////                    buffer.write(currentByte);
////                    currentByte = 0;
////                    bitIndex = 0;
////                }
//            }
//
////            buffer.write(currentByte);
////            currentByte = 0;
////            bitIndex    = 0;
//        }
//    }
//
////    unsigned char numBytesHorizontal = width / 8;
////    unsigned char numBytesVertical   = height;
//
//
//    cout << pixelsIn.getWidth() << "/" << pixelsIn.getHeight() << " : " << (int)(width - 7)/8 << "/" << (int)height << " currentBytes=" << (int)buffer.size() << endl;
//
//    return BitImage(buffer,format,(width - 7)/8,height);
//
//}


ofPixels_<unsigned char> ImageUtils::toGrayscale(const ofPixels_<unsigned char>& pixels)
{
    if (OF_IMAGE_GRAYSCALE == pixels.getImageType())
    {
        return pixels;
    }

    ofPixels pix;

    pix.allocate(pixels.getWidth(), pixels.getHeight(), OF_IMAGE_GRAYSCALE);

    for (std::size_t x = 0; x < pixels.getWidth(); ++x)
    {
        for (std::size_t y = 0; y < pixels.getHeight(); ++y)
        {
            auto c = pixels.getColor(x, y);
            pix.setColor(x, y, 0.21 * c.r + 0.71 * c.g + 0.07 * c.b);
        }
    }

    return pix;
}


} } // namespace ofx::ESCPOS
