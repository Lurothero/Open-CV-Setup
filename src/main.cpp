#include <iostream>

#include <opencv2/opencv.hpp>
using namespace cv;

// Forward declearation



// Basic image processing
int Run(){


    std::string img_path = "..\\..\\res\\girl.jpg";
    Mat img = imread(img_path,IMREAD_COLOR);

    if(img.empty()){
        std::cout << "Failed to read image... " <<img_path <<std::endl;
        return 1;
    }


    //Create window
    namedWindow("Girl",WINDOW_AUTOSIZE);//To pass the image to a window it MUST BE THE SAME NAME
    imshow("Girl",img);
    waitKey(0);
    destroyWindow("Girl");
  
    return 0;
}


int main()
{
    // Testing if Open CV is installed
    std::cout << CV_VERSION << std::endl;

    if(Run() == 1){
        return 1;

    }
    return 0;
}

