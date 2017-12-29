#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/photo.hpp"

#include <iostream>

using namespace cv;
using namespace std;

static void help()
{
    
    cout << "Argument: Filename\n"
        "Wait for the window to show up and then: \n"
        "\tESC - quit the program\n"
        "\ti or SPACE - run inpainting algorithm\n" << endl;
}



void show_img(Mat img)
{
    for(;;) {
        char c = (char)waitKey();

        if( c == 27 )
            break;

        if( c == 'i' || c == ' ' )
            imshow("image", img);
    }
}

Mat auto_inpaint(string fl)
{
    Mat original = imread(fl, -1);
    if(original.empty())
    {
        cout << "Couldn't open the image " << fl << ". Usage: inpaint <image_name>\n" << endl;
        return original;
    }
    Mat src;
    src.create(original.rows, original.cols, CV_8UC1);
    cout << "Created src\n" << endl;
    src = imread(fl, CV_8UC1);
    cout << "read as 8uc1\n" << endl;
    Mat inpainted;
    Mat inpaintMask  = Mat::zeros(src.size(), src.type());
    cout << "Created im\n" << endl;
    adaptiveThreshold(src,inpaintMask,255,ADAPTIVE_THRESH_GAUSSIAN_C,THRESH_BINARY_INV,111,15);
    cout << "adaptiveThreshold\n" << endl;
    show_img(inpaintMask);
    inpaint(original, inpaintMask, inpainted, 3, INPAINT_TELEA);
    cout << "inpainted\n" << endl;
    return inpainted;
}

Mat img, inpaintMask, ip;

int main( int argc, char** argv )
{
    cv::CommandLineParser parser(argc, argv, "{@image|./hair_small.jpg|}");
    help();

    string filename = parser.get<string>("@image");
    
    namedWindow( "image", 1 );

    ip = auto_inpaint(filename);
    cout << "returned\n" << endl;
    show_img(ip);

    return 0;
}

