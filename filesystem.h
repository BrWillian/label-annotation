#ifndef FILESYSTEM_H
#define FILESYSTEM_H
#include <experimental/filesystem>
#include <vector>

using namespace std;
namespace fs = experimental::filesystem;

class filesystem
{
private:
    vector<string>imgs;
public:
    filesystem();
    void List_dir(string dir);
    vector<string> GetImgs();
};

#endif // FILESYSTEM_H
