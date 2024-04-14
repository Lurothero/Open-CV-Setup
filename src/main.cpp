#include <iostream>

#include <opencv2/opencv.hpp>
using namespace cv;

// foward declear
void printImageData(Mat &image);

// Basic image processing
int Run()
{

    std::string img_path = "..\\..\\res\\Muffet_cycle_ServerIco_ clothed.png";
    Mat img = imread(img_path, IMREAD_COLOR);

    // Dont on 2k pict with 12million numbers
    // printImageData(img);

    if (img.empty())
    {
        std::cout << "Failed to read image... " << img_path << std::endl;
        return -1;
    }

    // Create window
    namedWindow("Muffet", WINDOW_NORMAL); // To pass the image to a window it MUST BE THE SAME NAME
    imshow("Muffet", img);

    waitKey(0);
    destroyWindow("Muffet");

    return 1;
}

void printImageData(Mat &image)
{
    std::cout << "Raw Image Data: " << std::endl
              << std::endl;
    std::cout << format(image, Formatter::FMT_PYTHON) << std::endl;
}



//Play a video
int playVideo(std::string videoPath){

 VideoCapture input(videoPath);

    if (input.isOpened() == false)
    {

        std::cout << "Video failed to load..." << videoPath << std::endl;
        return -1;
    }


    //get framerate

    double framerate = input.get(CAP_PROP_FPS);

    std::cout << "Framerate: " << framerate << std::endl;

    std::string videoWindow = "Ball video";
    namedWindow(videoWindow,WINDOW_NORMAL);


    while (true)
    {
        Mat frame;
        bool isSuccess = input.read(frame);

        if (isSuccess == false){
            std::cout << "End of video" <<std::endl;
            break;
        }

        imshow(videoWindow,frame);

        if (waitKey(10)==27){

            std::cout << "Escape key pressed... closing application" << std::endl;
            break;

        }

    }


    return 1;
}

int main()
{
    // Testing if Open CV is installed
    std::cout << CV_VERSION << std::endl;

  
        if (Run() == -1)
        {
            return -1;
        }
    

    std::string path = "..\\..\\res\\0001-0025.mkv";
    playVideo(path);
    


    int n;
    std::cin >> n;
    return 0;
}
