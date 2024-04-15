#include <iostream>
#include <string>
#include <ctime>
#include <sys/stat.h>

// Class to represent a file
template <typename T>
class File
{
private:
    std::string filename;

public:
    File(const std::string &filename) : filename(filename) {}

    // Get file size in bytes
    T size() const
    {
        struct stat st;
        if (stat(filename.c_str(), &st) != 0)
        {
            return -1; // Error occurred
        }
        return st.st_size;
    }

    // Get file creation time
    T creationTime() const
    {
        struct stat st;
        if (stat(filename.c_str(), &st) != 0)
        {
            return -1; // Error occurred
        }
        return st.st_ctime;
    }

    // Get file last modified time
    T lastModifiedTime() const
    {
        struct stat st;
        if (stat(filename.c_str(), &st) != 0)
        {
            return -1; // Error occurred
        }
        return st.st_mtime;
    }

    // Get file type
    std::string type() const
    {
        // Implement logic to determine file type based on filename or content
        // For simplicity, let's assume all files are text files
        return "Text File";
    }
};

int main()
{
    // Example usage
    File<long> file("file.txt");

    std::cout << "File Size: " << file.size() << " bytes" << std::endl;

    std::time_t creationTime = file.creationTime();
    std::cout << "Creation Time: " << std::ctime(&creationTime);

    std::time_t modifiedTime = file.lastModifiedTime();
    std::cout << "Last Modified Time: " << std::ctime(&modifiedTime);

    std::cout << "File Type: " << file.type() << std::endl;

    return 0;
}
