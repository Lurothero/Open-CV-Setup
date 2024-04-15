#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <Windows.h>

#include <opencv2/opencv.hpp>
using namespace cv;

// foward declear
void printImageData(Mat &image);
int Run();
int playVideo(std::string videoPath);
int useVideoCamera();
int animation();
void testAnimation(std::string video_path);
void ClearConsole();
void createField(Mat &source);
int addMatrix(Mat &sample, int col, int row);
int threshold(int value);

// Basic image processing
int Run()
{

    std::string img_path = "..\\..\\res\\Muffet_cycle_ServerIco_ clothed.png";
    Mat img = imread(img_path, IMREAD_COLOR);

    // Dont on 2k pict with 12million values
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
    std::cout << image << std::endl;
}

// Play a video
int playVideo(std::string videoPath)
{

    VideoCapture input(videoPath);

    if (input.isOpened() == false)
    {

        std::cout << "Video failed to load..." << videoPath << std::endl;
        return -1;
    }

    // get framerate

    double framerate = input.get(CAP_PROP_FPS);

    std::cout << "Framerate: " << framerate << std::endl;

    std::string videoWindow = "Ball video";
    namedWindow(videoWindow, WINDOW_NORMAL);

    while (true)
    {
        Mat frame, grey;

        cvtColor(frame, grey, COLOR_RGB2GRAY);

        bool isSuccess = input.read(frame);

        if (isSuccess == false)
        {
            std::cout << "End of video" << std::endl;
            break;
        }

        imshow(videoWindow, grey);

        if (waitKey(10) == 27)
        {

            std::cout << "Escape key pressed... closing application" << std::endl;
            break;
        }
    }

    return 1;
}

int useVideoCamera()
{

    VideoCapture cap(0);

    if (cap.isOpened() == false)
    {

        std::cout << "Failed to open camera..." << std::endl;
        std::cin.get();
        return -1;
    }

    double height = cap.get(CAP_PROP_FRAME_HEIGHT);
    double width = cap.get(CAP_PROP_FRAME_WIDTH);

    std::cout << "Resolution is : " << height << " x " << width << std::endl;

    std::string windowName = "Live Camera";

    namedWindow(windowName, WINDOW_FULLSCREEN);

    while (true)
    {
        Mat frame;
        bool isSuccess = cap.read(frame);

        if (isSuccess == false)
        {

            std::cout << "Error with camera..." << std::endl;
            break;
        }

        imshow(windowName, frame);
        if (waitKey(10) == 27)
        {
            std::cout << "Esc key is pressed..." << std::endl;
            break;
        }
    }

    return 1;
}

int animation()
{
    const int numFrames = 4;                      // value of frames for the spinning animation
    const char spinner[] = {'|', '/', '-', '\\'}; // Characters for the spinner animation
    std::cout << std::endl;
    for (int i = 0; i < 30; ++i)
    {                                                                  // Loop 20 times (adjust this value as needed)
        std::cout << "\r" << spinner[i % numFrames] << " Spinning..."; // Print the spinner character
        std::cout.flush();                                             // Flush the output buffer
        Sleep(1000);                                                   // Sleep for 100 milliseconds (adjust this value as needed)
    }

    std::cout << std::endl; // Print a newline at the end
    return 0;
}

// Lazy rn Chat GPT
void testAnimation(std::string video_path)
{
    // Open the video file
    VideoCapture cap(video_path);

    // Check if the video file is opened successfully
    if (!cap.isOpened())
    {
        std::cerr << "Error: Could not open video file." << std::endl;
        return;
    }

    // Create a window to display the grayscale video
    namedWindow("Grayscale Video", WINDOW_NORMAL);

    // Read and display each frame until the end of the video
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

        // Display the grayscale frame
        imshow("Grayscale Video", gray_frame);

        // Check for user input to exit the loop
        if (waitKey(2000 / 24) == 'q')
            break;
    }

    // Release the video capture object and close OpenCV windows
    cap.release();
    destroyAllWindows();
}

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
    // Testing if Open CV is installed
    // std::cout << CV_VERSION << std::endl;


   // playSound(R"(..\..\res\Magic Pen 1.wav)",10000);
    std::string imgpath = "..\\..\\res\\ref.png";

    Mat img = imread(imgpath, IMREAD_COLOR);

    Mat toGrey;
    cvtColor(img, toGrey, COLOR_RGB2GRAY);

    Mat outputMat;
    resize(toGrey, outputMat, Size(120, 30), 1, 1, INTER_NEAREST); // 120 30
    // std::cout << "Type: " << Shrink.type() << std::endl;
    // std::cout << "Image dimension is " << Shrink.cols << " x " << Shrink.rows << std::endl;

    // std::cout << Shrink.at<Vec3b>(0, 0) << std::endl;

    //  Vec3b new_color(0, 0, 255); // BGR
    //  Shrink.at<Vec3b>(4, 4) = new_color;

    // printImageData(toGrey);

    //  uchar color = toGrey.at<uchar>(0, 0);
    //  std::cout << color << std::endl;
    // std::cout << "toGray has " << toGrey.channels() << " channels " << "and is " << toGrey.cols << " " << toGrey.rows << std::endl;
    // processImage(toGrey);
    //  int counter = 0;

    /**
        for (int row = 0; row < toGrey.rows; row++)
        {

            for (int col = 0; col < toGrey.cols; col++)
            {
                int sum = 0;
            }
        }

        for (int i = 0; i < toGrey.cols; i++)
        {

            for (int j = 0; j < toGrey.rows; j++)
            {

                // std::cout << counter++ <<std::endl;
                // std::cout << toGrey.at<uchar>(j,i) << "at col: "<< i << " and row: " <<j<<std::endl;
                // std::cout << toGrey.at<uchar>(29,119) <<std::endl;//Its always row then colum
            }
        }

        //  std::cout << "The Video is " << toGrey.rows << " and " << toGrey.cols << " long." << std::endl;

        // printImageData(toGrey);
    */

    namedWindow("Grid", WINDOW_NORMAL);
    imshow("Grid", outputMat);

    waitKey(0);
    destroyAllWindows();

    // Start the console animation

    ClearConsole();
    createField(outputMat);
    ClearConsole();


    std::vector<uchar> array(120*30);

    for (int i=0;i <array.size() ;i++){

        array[i] = 79;//O
    }





    for(int i =0; i <50; i++){

        std::string temp  = "";
        for(auto i : array){
            temp += i;

        }

        //std::cout << temp;
    }


   // consoleAnimation("..\\..\\res\\0001-0025.mkv");

   std::string vid = "";

    consoleAnimation(R"(C:\Users\renea\Downloads\bad apple.mp4)");

    std::cout << "End of video";
    std::cin.get();
    // animation();
    return 0;
}

// CONSOLE SIZE FOR ME IS 120 WIDTH and 30 LINES DOWN