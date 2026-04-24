#include <string>

class fileSystem
{
public:
    static std::string getPath(const std::string& relativePath) {
        // Implement logic to get the absolute path based on the relative path
        // This is a placeholder implementation and may need adjustments based on your project structure
        
      
        //std::cout << basePath() + "/" + relativePath << std::endl;
        //std::cout << relativePath << std::endl;
        return relativePath;
    }
private:
    static std::string basePath() {
        // Implement logic to determine the base path of your project
        // This could be the directory where the executable is located or a specific resource directory
        return "."; // Replace with actual logic to determine base path
    }
};