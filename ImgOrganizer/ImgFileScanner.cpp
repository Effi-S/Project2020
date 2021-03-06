﻿#include "ImgFileScanner.h"

void addImgToDB( const std::filesystem::directory_entry& entry)
{	 

    cv::Mat img = MyUtils::unicodeImgRead(entry.path().wstring(), cv::ImreadModes::IMREAD_GRAYSCALE);

    std::wstring path = entry.path().wstring();
    std::replace(path.begin() , path.end(), '\\', '/');  // necessary for windows paths to work properly

    if(!img.empty())
        ImgFileScanner::IMG_DB().push_back(std::make_pair(*new cv::Ptr<cv::Mat>(
    std::make_shared<cv::Mat>(img)),
    std::make_unique<std::wstring>(path)));
}

void ImgFileScanner::scan(std::wstring path, std::atomic_bool & stop_flg  )
{
    int tmp = _scan(path, stop_flg);
}

int ImgFileScanner::getNumberOfImages(std::wstring path, std::atomic_bool & stop_flg)
{
    return _scan(path, stop_flg, true);
}

// The main scanning algorithm
// Recursively iterates over the path given into path
//
int ImgFileScanner::_scan(std::wstring path, std::atomic_bool & stop_flg, bool dry)
{
    static std::mutex mu;
    mu.lock();

	std::clock_t start(std::clock());

	uint img_count = 0;

	uint failed_count = 0;

    IMG_DB().clear();

    std::unordered_set<std::wstring> extension_set({ L".png", L".jpg", L".jpeg", L".bmp" });

    std::future<void> future;

    mu.unlock();


	for (const auto& entry : fs::recursive_directory_iterator(path, fs::directory_options::skip_permission_denied))
    {
    try {
        std::wstring extension = entry.path().extension().wstring();

		if (extension_set.find(extension) != extension_set.end())
		{
            //TODO remove try catch block.
			try
			{
				if(!dry)
                    future = std::future(std::async(&addImgToDB, entry));

                img_count++;
                if(stop_flg)
                {
                    future.get();
                    IMG_DB().clear();
                    return 0;
                }

			}
			catch (cv::Exception & e)
			{
				std::cout << RED << "cv error:" << e.what() << RESET << std::endl;
				failed_count++;
				break;
			}
			catch (std::exception& e) {
				// mostly unicode errors 
				std::cout << RED << "imread error for file " << entry.path().c_str() << "\n " << RESET << std::endl;
				std::cout << ORANGE << "imread error:" << e.what() << " " << RESET << std::endl;
				failed_count++;
			}
			catch (...)
			{
				//just in case libpng/cv send strange errors
				std::cout << RED << "unknown error" << RESET << std::endl;
				failed_count++;
			}

		}

      } catch (std::exception & e) {
        std::cout <<RED "\n >>>>>>> ERROR <<<<<<\n " << e.what()
        << "\n >>>>>>>>>><<<<<<<<<<<" << RESET << std::endl;
        }
	}
    std::lock_guard<std::mutex> lk(mu);
    if(future.valid())
            future.get();

    //std::cout << GREEN << "\nNumber Of images Found: " << BLUE << img_count << std::endl
    //         << GREEN <<"Time it took: " << RESET << double(std::clock()) - start << GREEN
    //         <<" Number of fails:" << RED << failed_count<< std::endl <<RESET <<std::endl;

	return img_count ;
}

IMG_DataBase& ImgFileScanner::IMG_DB()
{
    static std::mutex imgMutex;
    std::lock_guard<std::mutex> lk(imgMutex);

	static IMG_DataBase _DB;
    return _DB;
}





