#include <complex>
#include <print>
#include <vector>

namespace mandelbrot {
std::vector<double> idToCoordinate(int pixel_id, double real_coord_left_top, double imag_coord_left_top, double w_coord_gap, double h_coord_gap) {
    std::vector<double> coordinates(2);
    int height_steps = (pixel_id + 1) / 200;
    int width_steps = (pixel_id + 1) % 200;

    coordinates[0] = real_coord_left_top + width_steps * w_coord_gap;
    coordinates[1] = imag_coord_left_top - height_steps * h_coord_gap;

    return coordinates;
}

int checkDivergence(double x, double y) {
    std::complex<double> c(x, y);

    std::complex<double> last_result = c;
    for (int i = 0; i < 200; i++) {
        last_result = std::pow(last_result, 2) + c;
        if (std::abs(last_result) > 2)
            return 1;
    }

    return 0;
}

void printMandelbrot(std::vector<char>& area, int w_pixels, int h_pixels) {
    for (int pixel_id = 0; pixel_id < w_pixels * h_pixels; pixel_id++) {
        std::print("{}", area[pixel_id]);
        if ((pixel_id + 1) % w_pixels == 0)
            std::print("\n");
    }
}

void mandelbrot(double realCenter, double imagCenter, double width, double height) {
    double aspect_ratio = width / height;

    const int w_pixels = 200;
    const int h_pixels = static_cast<int>((w_pixels / aspect_ratio) * 0.4);

    const double real_coord_left_top = realCenter - width / 2;
    const double imag_coord_left_top = imagCenter + height / 2;
    const double w_coord_gap = width / w_pixels;
    const double h_coord_gap = height / h_pixels;

    std::vector<char> area;
    area.push_back(' ');

    for (int pixel_id = 0; pixel_id < w_pixels * h_pixels; pixel_id++) {
        std::vector<double> coordinates = idToCoordinate(pixel_id, real_coord_left_top, imag_coord_left_top, w_coord_gap, h_coord_gap);
        double x = coordinates[0];
        double y = coordinates[1];

        if (checkDivergence(x, y)) {
            area.push_back(' ');
        } else {
            area.push_back('*');
        }
    }

    printMandelbrot(area, w_pixels, h_pixels);
}
} // namespace mandelbrot