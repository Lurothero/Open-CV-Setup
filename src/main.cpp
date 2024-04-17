#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <Windows.h>
#include <opencv2/opencv.hpp>
using namespace cv;

// foward declear

int Run();
int playVideo(std::string videoPath);
int useVideoCamera();
int animation();
void testAnimation(std::string video_path);
void ClearConsole();
void createField(Mat &source);
int addMatrix(Mat &sample, int col, int row);
int threshold(int value);


void ClearConsole()
{

    for (int i = 0; i < 32; i++)
    {
        std::cout << " " << std::endl;
    }
}

void createField(Mat &source)
{
    const int column = source.cols; // 120
    const int row = source.rows;    // 30

    // create an array of values just to test
    // std::vector<std::vector<uchar>> scene(column, std::vector<uchar>(row));

    std::vector<std::vector<uchar>> scene(row, std::vector<uchar>(column));

    std::vector<uchar> consoleOutput(column*row);

    for (int r = 0; r < row; r++)
    {
        std::string temp = "";

        for (int c = 0; c < column; c++)
        {

            scene[r][c] = (threshold(static_cast<int>(source.at<uchar>(r, c))));
            //std::cout << scene[r][c];
            temp += scene[r][c];
        }
        std::cout << temp;
    }

    // std::vector<std::vector<char>> scene(120, std::vector<int>(30)); // Char is better
}

int threshold(int value)
{

    // we will be using this pallet
    //--->space ' '.:-=+*#%@

    int threshold = 255 / 10;

    if (value < threshold)
    {
        return 32; // space
    }
    else if (value < 2 * threshold)
    {
        return 46; // period
    }
    else if (value < 3 * threshold)
    {
        return 58; // colon
    }
    else if (value < 4 * threshold)
    {
        return 45; // minus
    }
    else if (value < 5 * threshold)
    {
        return 61; // equal
    }
    else if (value < 6 * threshold)
    {
        return 43; // plus
    }
    else if (value < 7 * threshold)
    {
        return 42; // asterik
    }
    else if (value < 8 * threshold)
    {
        return 35; // pound
    }
    else if (value < 9 * threshold)
    {
        return 37; // percent
    }
    else
    {
        return 64; // at
    }
}

void processImage(cv::Mat &image)
{
    // Get the height and width of the image
    int height = image.rows;
    int width = image.cols;

    // Iterate over every pixel in the image
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            // Access the intensity value of the pixel at coordinates (x, y)
            uchar intensity = image.at<uchar>(y, x);

            // You can perform operations with the pixel intensity here
            // For example, print the intensity value
            std::cout << "Intensity at pixel (" << x << ", " << y << "): " << static_cast<int>(intensity) << std::endl;
        }
    }
}


void consoleAnimation(std::string video_path)
{
    //create a gap
    ClearConsole();

    // Get video
    VideoCapture cap(video_path);
    int framerate = static_cast<int>(cap.get(CAP_PROP_FPS));

    //Video err checking
    if (!cap.isOpened())
    {
        std::cerr << "Error: Could not open video file." << std::endl;
        return;
    }

    while (true)
    {
        // Read a frame from the video
        Mat frame;
        cap >> frame;

        // If no frame is read, break the loop
        if (frame.empty())
            break;

        // Convert the frame to grayscale
        Mat gray_frame;
        cvtColor(frame, gray_frame, COLOR_BGR2GRAY);

        //need to resize frame
        Mat output;
        resize(gray_frame, output, Size(120, 30), 1, 1, INTER_NEAREST); 


        createField(output);
      

        // Check for user input to exit the loop
       // if (waitKey(1000 / framerate) == 'q')
        //    break;
        Sleep(1000/framerate);
    }

    // Release the video capture object and close OpenCV windows
    cap.release();
    destroyAllWindows();
}

int main()
{
    //WINDOWS ONLY
    system("cls");

    consoleAnimation(R"(..\..\res\bad apple.mp4)");
    system("cls");
    std::cout << "End of video, Press Enter...";
    std::cin.get();

    return 0;
}

// CONSOLE SIZE FOR ME IS 120 WIDTH and 30 LINES DOWN