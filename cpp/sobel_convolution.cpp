/*
 * 编程作业：模板运算（卷积）
 * 语言：C++
 * 依赖库：OpenCV
 */

#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp> // 包含图像处理功能
#include <opencv2/imgcodecs.hpp> // 包含图像读写功能

int main() {
    // 1. 任取一幅灰度图像
    // 请将 "your_image.png" 替换为你的灰度图像文件的实际路径
    // cv::IMREAD_GRAYSCALE 确保图像以灰度模式加载
    std::string image_path = "test_clean.png"; // 或者你的绝对路径
    cv::Mat srcImage = cv::imread(image_path, cv::IMREAD_GRAYSCALE); // <-- 改成 GRAYSCALE

    if (srcImage.empty()) {
        std::cerr << "错误: 无法加载图像。" << std::endl;
        std::cerr << "请确保文件路径 '" << image_path << "' 正确。" << std::endl; // <-- 打印变量
        return -1;
    }

    // 2. 定义作业中给出的模板（卷积核）
    // 我们使用 float 类型来定义，这在OpenCV中是标准做法
    cv::Mat kernel = (cv::Mat_<float>(3, 3) <<
        -1, 0, 1,
        -2, 0, 2,
        -1, 0, 1);

    // 3. 用如下模板做模板运算
    cv::Mat dstImage;

    // 使用 cv::filter2D 函数执行 2D 卷积
    // 第一个参数: srcImage (输入图像)
    // 第二个参数: dstImage (输出图像)
    // 第三个参数: -1 (表示输出图像的深度与输入图像相同，但我们稍后会更改)
    //
    // 重要提示：
    // Sobel 算子会产生负值（例如，从亮到暗的边缘）。
    // 原始图像是 8 位无符号的 (CV_8U, 0-255)。
    // 如果我们输出到 CV_8U，所有负值都会被截断为 0，导致信息丢失。
    //
    // 最佳实践是先将结果计算到 16 位有符号整数 (CV_16S) 中。
    cv::Mat grad_x;
    cv::filter2D(srcImage, grad_x, CV_16S, kernel, cv::Point(-1, -1), 0, cv::BORDER_DEFAULT);
    // 4. 输出结果图像
    // 为了能够正确显示（或保存）包含负值的梯度图像，
    // 我们需要将其转换回 8 位无符号类型 (CV_8U)。
    // cv::convertScaleAbs() 会计算结果的绝对值，并将其缩放到 0-255 范围。
    // 这对于可视化边缘检测结果非常理想。
    cv::Mat abs_grad_x;
    cv::convertScaleAbs(grad_x, abs_grad_x);

    // 保存结果图像到文件
    cv::imwrite("result_image.png", abs_grad_x);

    // 在窗口中显示原始图像和结果图像
    cv::imshow("Original Grayscale Image", srcImage);
    cv::imshow("Convolution Result (Sobel X)", abs_grad_x);

    std::cout << "卷积完成！结果已保存为 'result_image.png'" << std::endl;
    std::cout << "按任意键退出..." << std::endl;

    // 等待用户按键
    cv::waitKey(0);

    return 0;
}