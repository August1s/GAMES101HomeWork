#include <chrono>
#include <iostream>
#include <opencv2/opencv.hpp>

std::vector<cv::Point2f> control_points;

void mouse_handler(int event, int x, int y, int flags, void *userdata) 
{
    if (event == cv::EVENT_LBUTTONDOWN && control_points.size() < 6) 
    {
        std::cout << "Left button of the mouse is clicked - position (" << x << ", "
        << y << ")" << '\n';
        control_points.emplace_back(x, y);
    }     
}

void naive_bezier(const std::vector<cv::Point2f> &points, cv::Mat &window) 
{
    auto &p_0 = points[0];
    auto &p_1 = points[1];
    auto &p_2 = points[2];
    auto &p_3 = points[3];

    for (double t = 0.0; t <= 1.0; t += 0.001) 
    {
        auto point = std::pow(1 - t, 3) * p_0 + 3 * t * std::pow(1 - t, 2) * p_1 +
                 3 * std::pow(t, 2) * (1 - t) * p_2 + std::pow(t, 3) * p_3;

        window.at<cv::Vec3b>(point.y, point.x)[2] = 255;
    }
}

cv::Point2f recursive_bezier(const std::vector<cv::Point2f> &control_points, float t) 
{
    // TODO: Implement de Casteljau's algorithm
    std::vector<cv::Point2f> oldPoints(control_points), newPoints;
    while (oldPoints.size() != 1)
    {
        for (int i = 0; i < oldPoints.size() - 1; i++)
        {
            newPoints.push_back(oldPoints[i] * (1 - t) + oldPoints[i + 1] * t);
        }
        oldPoints.clear();
        oldPoints = newPoints;
        newPoints.clear();
    }

    return oldPoints[0];

}

void bezier(const std::vector<cv::Point2f> &control_points, cv::Mat &window) 
{
    // TODO: Iterate through all t = 0 to t = 1 with small steps, and call de Casteljau's 
    // recursive Bezier algorithm.
    std::vector<cv::Point2f> points;

    for (double t = 0.0; t <= 1.0; t += 0.001)
    {
        auto point = recursive_bezier(control_points, t);
        //window.at<cv::Vec3b>(point.y, point.x)[2] = 255; // R
        window.at<cv::Vec3b>(point.y, point.x)[1] = 255; // G
        points.push_back(point);
    }

    
    //使用一个3*3卷积核来对边缘像素进行均值模糊
    // 0.05 0.2 0.05
    // 0.2  0   0.2
    // 0.05 0.2 0.05
    for (auto& point : points)
    {
        int x = point.x, y = point.y;
        int left = x - 1, right = x + 1;
        int top = y - 1, bottom = y + 1;
        for (int i = left; i <= right; i++) 
        {
            for (int j = top; j <= bottom; j++) 
            {
                // 不影响原本的像素和已经着色的像素
                if ((int)window.at<cv::Vec3b>(j, i)[1] == 0) 
                {
                    float color = window.at<cv::Vec3b>(j - 1, i - 1)[1] * 0.05f + window.at<cv::Vec3b>(j, i - 1)[1] * 0.2f + window.at<cv::Vec3b>(j + 1, i - 1)[1] * 0.05f +
                                window.at<cv::Vec3b>(j - 1, i)[1] * 0.2f + window.at<cv::Vec3b>(j + 1, i)[1] * 0.2f +
                                window.at<cv::Vec3b>(j - 1, i + 1)[1] * 0.05f + window.at<cv::Vec3b>(j, i + 1)[1] * 0.2f + window.at<cv::Vec3b>(j + 1, i + 1)[1] * 0.05f;
                    window.at<cv::Vec3b>(j, i)[1] = int(color);
                }
            }
        }
    }



}

int main() 
{
    cv::Mat window = cv::Mat(700, 700, CV_8UC3, cv::Scalar(0));
    cv::cvtColor(window, window, cv::COLOR_BGR2RGB);
    cv::namedWindow("Bezier Curve", cv::WINDOW_AUTOSIZE);

    cv::setMouseCallback("Bezier Curve", mouse_handler, nullptr);

    int key = -1;
    while (key != 27) 
    {
        for (auto &point : control_points) 
        {
            cv::circle(window, point, 3, {255, 255, 255}, 3);
        }

        if (control_points.size() == 6) 
        {
            //naive_bezier(control_points, window);
            bezier(control_points, window);

            cv::imshow("Bezier Curve", window);
            cv::imwrite("my_bezier_curve_with_AA.png", window);
            key = cv::waitKey(0);

            return 0;
        }

        cv::imshow("Bezier Curve", window);
        key = cv::waitKey(20);
    }

return 0;
}
