#include <filesystem.h>
#include <iostream>

namespace fs = experimental::filesystem;


filesystem::filesystem()
{

}
void filesystem::List_dir(string dir)
{
    for (const auto & directory: fs::directory_iterator(dir))
    {
        if(directory.path().extension() == ".jpeg")
        {
            imgs.push_back(directory.path());
        }
    }
}
vector<string> filesystem::GetImgs()
{
    return imgs;
}
