#pragma once
#include <unordered_map>
#include <opencv2/opencv.hpp>
#include<opencv2/img_hash/average_hash.hpp>
#include <opencv2/img_hash/phash.hpp>
#include "ImgScanner.h"

class BitExactImgFinder 
{
	const int BITS = 16;
	using HashKey = std::string;
	using ImgInfo = std::pair<cv::Mat, std::string>;
	using MatchMap = std::unordered_map<HashKey, std::vector<ImgInfo>>;

public:
	BitExactImgFinder() { makeSet();} 
	void show();
private:
	
	void makeSet();
	
	MatchMap m_matches;

	cv::Ptr<cv::img_hash::ImgHashBase> m_algo;

};
