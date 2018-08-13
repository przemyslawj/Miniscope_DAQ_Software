#ifndef __FRAME_ANALYSIS__
#define __FRAME_ANALYSIS__

#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"

#include <list>


class BlurredFrameBuffer
{
private:
	int mFramesAdded = 0;
	int mBufferSize;
	int mBaselineFramesSize;
	std::list<cv::Mat> mBaselineBuffer;
	std::list<cv::Mat> mTailBuffer;
	cv::Mat baselineFrame;
	cv::Size mGaussianKernelSize = cv::Size2i(5, 5);

public:
	BlurredFrameBuffer(int mBaselineFramesSize, int mBufferSize);
	
	void addFrame(cv::Mat* frame);
	cv::Mat getBaseline();
};

cv::Mat dFOverF(cv::Mat* baseline, cv::Mat* currentFrame);

#endif
