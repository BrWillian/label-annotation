#include <filesystem.h>
#include <experimental/filesystem>
#include <iostream>

namespace fs = std::experimental::filesystem;

filesystem::filesystem()
{

}
void filesystem::listDir(string dir)
{
    for (const auto & directory: fs::directory_iterator(dir))
    {
        if(directory.path().extension() == ".png")
        {
            imgs.push_back(directory.path());
        }
    }
}
vector<string> filesystem::getImgs()
{
    return imgs;
}
void filesystem::makeLabels(string labels)
{
    if(!(fs::is_directory("data")))
    {
        fs::create_directory("data");
    }

    ofstream outfile;

    outfile.open("data/classes.txt");

    if(outfile.is_open() && outfile.good())
    {
        outfile << labels;
        outfile.close();
    }

}
void filesystem::loadLabels()
{
    string line;
    ifstream file("data/classes.txt");
    if(file.is_open())
    {
        labels.clear();
        while(!(file.eof()))
        {
            getline (file,line);
            labels.push_back(line);
        }
    }
    file.close();
}
vector<string> filesystem::getLabels()
{
    return labels;
}
