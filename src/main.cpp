#include <iostream>

#include <opencv2/opencv.hpp>
using namespace cv;


//foward declear
void printImageData(Mat &image);


// Basic image processing
int Run()
{

    std::string img_path = "..\\..\\res\\Muffet_cycle_ServerIco_ clothed.png";
    Mat img = imread(img_path, IMREAD_COLOR);

    //Dont on 2k pict with 12million numbers
    //printImageData(img);

    if (img.empty())
    {
        std::cout << "Failed to read image... " << img_path << std::endl;
        return 1;
    }

    // Create window
    namedWindow("Muffet",WINDOW_KEEPRATIO); // To pass the image to a window it MUST BE THE SAME NAME
    imshow("Muffet", img);

    waitKey(0);
    destroyWindow("Muffet");

    return 0;
}

void printImageData(Mat &image)
{
    std::cout << "Raw Image Data: " << std::endl << std::endl;
    std::cout << format(image,Formatter::FMT_PYTHON) << std::endl;
}

int main()
{
    // Testing if Open CV is installed
    std::cout << CV_VERSION << std::endl;

    if (Run() == 1)
    {
        return 1;
    }
    return 0;
}
