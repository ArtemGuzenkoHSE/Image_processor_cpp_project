#include "Filters.h"
#include "FabricBMP.h"
#include <iostream>
#include <vector>
#include <string>

class Controller {
public:
    int ProcessCommandLine(int argc, char *argv[]) {
        try {
            if (argc <= 2) {
                PrintUsage(argv[0]);
                return 1;
            }

            std::string input_path = argv[1];
            std::string output_path = argv[2];

            Image image = FabricBMP::LoadImage(input_path);
            std::cout << "Loaded image: " << image.GetWidth() << "x" << image.GetHeight() << "\n";

            image = ApplyFilters(image, argc, argv);

            FabricBMP::SaveImage(image, output_path);

            std::cout << "Successfully saved to: " << output_path << "\n";

            return 0;
        } catch (const std::exception &e) {
            std::cerr << "Error: " << e.what() << "\n";
            return 1;
        }
    }

private:
    Image ApplyFilters(Image image, int argc, char *argv[]) {
    for (int i = 3; i < static_cast<int>(argc);) {
        std::string filter_name = argv[i];
        std::vector<std::string> params = ExtractFilterParameters(argc, argv, i);

        auto filter = FilterFactory::Create(filter_name, params);

        std::cout << "Applying filter: " << filter->GetName() << "\n";
        image = filter->Apply(image);

        i += 1 + static_cast<int>(params.size());
    }
    return image;
}

    std::vector<std::string> ExtractFilterParameters(int argc, char *argv[], int index) {
        std::vector<std::string> params;
        for (int j = index + 1; j < static_cast<int>(argc) && argv[j][0] != '-'; ++j) {
            params.push_back(argv[j]);
        }
        return params;
    }

    void PrintUsage(const char *program_name) const {
        std::cout << "Usage: " << program_name
                  << " {input file path} {output file path} "
                     "[-{filter name 1} [filter parameter 1] [filter parameter 2] ...] "
                     "[-{filter name 2} [filter parameter 1] [filter parameter 2] ...] ...\n";
        std::cout << "Apply filters to BMP images (24-bit format only)\n\n";

        std::cout << "Available filters:\n";
        std::cout << "  -gs - grayscale\n";
        std::cout << "  -neg - negative\n";
        std::cout << "  -sharp - sharpening\n";
        std::cout << "  -crop - crop (requires width and height)\n";
        std::cout << "  -edge - edge detection (requires threshold)\n";
        std::cout << "  -blur - blur (requires sigma)\n";
        std::cout << "  -comic - comic (r_levels g_levels b_levels contrast saturation edge_threshold "
                     "r_outline_color g_outline_color b_outline_color)\n\n";

        std::cout << "Examples:\n";
        std::cout << "  " << program_name << " input.bmp /tmp/output.bmp -crop 800 600 -gs -blur 0.5\n\n";

        std::cout << "Notes:\n";
        std::cout << "  - Filters are applied in the order they are specified\n";
        std::cout << "  - Only 24-bit BMP files are supported\n";
    }
};

int main(int argc, char *argv[]) {
    Controller controller;
    return controller.ProcessCommandLine(argc, argv);
}