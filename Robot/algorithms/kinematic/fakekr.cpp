#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <cmath>

class fakeKR {
public:
    ~fakeKR() {}

    void init_fakeKR(const std::string& filename, std::vector<int> jointData[7]) {
        std::ifstream inputFile(filename);
        if (!inputFile.is_open()) {
            std::cerr << "open failed" << std::endl;
            return;
        }

        std::string line;
        while (std::getline(inputFile, line)) {
         
            if (line.find("data:") != std::string::npos) {
            
                line = line.substr(line.find('[') + 1); 
                std::istringstream iss(line);
                double value;
                int jointIndex = 0;

                while (iss >> value && jointIndex < 7) {
                    double degreeValue = value * (180.0 / M_PI);  
                    jointData[jointIndex].push_back(static_cast<int>(std::round(degreeValue)));
                    jointIndex++;

                
                    if (iss.peek() == ',') iss.ignore();
                }
            }
        }
        inputFile.close();
    }
};
