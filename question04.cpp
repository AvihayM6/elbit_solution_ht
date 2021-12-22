//Question 4 - Filesystem & args  

// Task: Implement the code as described in the main body, make sure to handle cases when the requested
// file is not found or the "files" directory doesn't exists and you have to create it
// Prefer modern solutions over classic C style solutions and keep in mind that this code
// should be able to run in other windows, linux and other platforms (hint: '/' and '\' in file paths)


#include <iostream>
#include <cstring>
#include <sys/stat.h> // stat
#include <cerrno>    // errno, ENOENT, EEXIST
#include <fstream>


#if defined(_WIN32)
#include <direct.h>   // _mkdir
#endif

bool isDirExist(const std::string& path)
{
#if defined(_WIN32)
    struct _stat info;
    if (_stat(path.c_str(), &info) != 0)
    {
        return false;
    }
    return (info.st_mode & _S_IFDIR) != 0;
#else
    struct stat info{};
    if (stat(path.c_str(), &info) != 0)
    {
        return false;
    }
    return (info.st_mode & S_IFDIR) != 0;
#endif
}

bool makePath(const std::string& path)
{
#if defined(_WIN32)
    int ret = _mkdir(path.c_str());
#else
    mode_t mode = 0755;
    int ret = mkdir(path.c_str(), mode);
#endif
    if (ret == 0)
        return true;

    switch (errno)
    {
        case ENOENT:
            // parent didn't exist, try to create it
        {
            int pos = path.find_last_of('/');
            if (pos == std::string::npos)
#if defined(_WIN32)
                pos = path.find_last_of('\\');
            if (pos == std::string::npos)
#endif
                return false;
            if (!makePath( path.substr(0, pos)))
                return false;
        }
            // now, try to create again
#if defined(_WIN32)
            return 0 == _mkdir(path.c_str());
#else
            return 0 == mkdir(path.c_str(), mode);
#endif

        case EEXIST:
            // done!
            return isDirExist(path);

        default:
            return false;
    }
}

int main(int argc, char** argv)
{
    if(argc == 4 && strcmp(argv[1], "create" ) == 0 ){
        try {
            makePath("files");
#if defined(_WIN32)
            std::string fileNameArgv = argv[2];
            std::string fileNameFiles = "files/";
            std::string fileNameDotTxt = ".txt";
            std::string allPath = fileNameFiles.append(fileNameArgv).append(fileNameDotTxt);
            std::ofstream MyFile(allPath);
            MyFile << "Hello from " << argv[3];
            MyFile.close();
#else
            std::string fileNameArgv = argv[2];
            std::string fileNameFiles = "files/";
            std::string fileNameDotTxt = ".txt";
            std::string allPath = fileNameFiles.append(fileNameArgv).append(fileNameDotTxt);
            std::ofstream MyFile(allPath);
            MyFile << "Hello from " << argv[3];
            MyFile.close();
#endif
        } catch (const std::exception &e){
            std::cout << e.what() << std::endl;
        }
    }
    else if(argc == 3 && strcmp(argv[1], "read" ) == 0 ){
        try{
#if defined(_WIN32)
            std::string fileNameArgv = argv[2];
            std::string content[3];
            std::string fileNameFiles = "files/";
            std::string fileNameDotTxt = ".txt";
            std::string allPath = fileNameFiles.append(fileNameArgv).append(fileNameDotTxt);
            std::ifstream inFile;
            inFile.open(allPath);
            inFile >> content[0] >> content[1] >> content[2];
            std::cout << content[0] << " " << content[1] << " " << content[2] << " " << std::endl;
#else
            std::string fileNameArgv = argv[2];
            std::string content[argc];
            std::string fileNameFiles = "files/";
            std::string fileNameDotTxt = ".txt";
            std::string allPath = fileNameFiles.append(fileNameArgv).append(fileNameDotTxt);
            std::ifstream inFile;
            inFile.open(allPath);
            inFile >> content[0] >> content[1] >> content[2];
            std::cout << content[0] << " " << content[1] << " " << content[2] << " " << std::endl;
#endif
        } catch (const std::exception &e){
            std::cout << e.what() << std::endl;
        }
    }
    else{
        std::cout<< "ERROR" << std::endl;
    }
    return 0;
}


//If user passed "create" argument
//		Create (or overwrite) a file named *argument2.txt*  with the text "Hello from *argument3*" in a folder named "files" under the current working directory
//else if user passed "read" argument
//		read a file named* argument2* from a folder named "files" under the current working directory and print it to the console

//Execution example (assuming working directory c:\code): question04.exe create test1 Nir - should create the file c:\code\files\test1.txt with the content "Hello from Nir"
//Execution example (assuming working directory c:\code): question04.exe read test1  - should print "Hello from Nir" in the console (assuming the previous command was executed)
