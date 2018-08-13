#include "stdafx.h"
#include "FrameAnalysis.h"

BlurredFrameBuffer::BlurredFrameBuffer(int baselineFramesSize, int bufferSize)
{
	assert(baselineFramesSize < bufferSize);
	this->mBaselineFramesSize = baselineFramesSize;
	this->mBufferSize = bufferSize;
	this->baselineFrame;
}

void BlurredFrameBuffer::addFrame(cv::Mat* frame)
{
	if (baselineFrame.size.dims() == 0)
	{
		baselineFrame = cv::Mat(frame->rows, frame->cols, CV_8UC1);
	}
	cv::Mat blur;
	cv::GaussianBlur(*frame, blur, mGaussianKernelSize, 1, 0);
	if (mFramesAdded < mBaselineFramesSize)
	{
		mBaselineBuffer.push_back(blur);
		baselineFrame += blur;
	}
	else 
	{ 
		mTailBuffer.push_back(blur);
		if (mFramesAdded > mBufferSize)
		{
			cv::Mat newBufferMat = mTailBuffer.front();
			mTailBuffer.pop_front();

			cv::Mat prevBufferMat = mBaselineBuffer.front();
			mBaselineBuffer.pop_front();
			mBaselineBuffer.push_back(newBufferMat);
			baselineFrame += newBufferMat - prevBufferMat;
		}
	}

	
	++mFramesAdded;
}

cv::Mat BlurredFrameBuffer::getBaseline()
{
	return baselineFrame / mBaselineFramesSize;
}

cv::Mat dFOverF(cv::Mat* baseline, cv::Mat* currentFrame)
{
	cv::Mat res = (*currentFrame - *baseline) / *baseline;
	cv::Mat norm(res);
	cv::normalize(res, norm, 0, 255, CV_MINMAX);
	return norm;
}
