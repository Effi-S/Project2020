#pragma once
#include <vector>
#include <string>
#include <mutex>

/******************************
 * Base class for all image finding classes
 *
 * This is a abstract base class
 *
 * for algorithms that run on images
 *
 * found by Img File Scanner and look for matches
 *
 * makeMatchGroups is the abstract method that must
 *
 * be redefined - each algorithm must have
 *
 * it's own match making sceme.
 *
 * The destructor should be overriden as well
 ****************************** */

class ImgMatchFinderBase
{
public:
    virtual void makeMatchGroups() = 0; ///< MUST be overriden
    std::vector<std::vector<std::string>> getMatchGroups();
    uint32_t numberOfImagesFound ();

    virtual ~ImgMatchFinderBase()  = default; ///< Should  be overriden as well
protected:

    void addMatchGroup(std::vector<std::string>& group);

private:

    std::mutex m_mutex;	///< mutex for safe use of match database
    std::vector<std::vector<std::string>> m_stringGroups; ///< holds the match groups
};
