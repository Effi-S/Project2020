#include "ImgMatchFinderBase.h"

std::vector<std::vector<std::string>> ImgMatchFinderBase::getMatchGroups()
{
	std::lock_guard<std::mutex> lk(m_mutex);
	return std::move(m_stringGroups);
}

//returns the number of images the algorithm has seen already
uint32_t ImgMatchFinderBase::numberOfImagesFound()
{
    std::lock_guard<std::mutex> lk(m_mutex);
    return m_stringGroups.size();
}

void ImgMatchFinderBase::addMatchGroup(std::vector<std::string>& group)
{
	std::lock_guard<std::mutex> lk(m_mutex);
	m_stringGroups.push_back(group);
}