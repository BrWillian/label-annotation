#include <filesys.h>
#include <experimental/filesystem>
#include <iostream>
#include <sstream>

namespace fs = std::experimental::filesystem;

filesys::filesys()
{

}
void filesys::listDir(string dir)
{
    imgs.clear();
    for (const auto & directory: fs::directory_iterator(dir))
    {
        if(directory.path().extension() == ".png" || directory.path().extension() == ".jpeg" || directory.path().extension() == ".jpg")
        {
            imgs.push_back(directory.path());
        }
    }
}
vector<string> filesys::getImgs()
{
    return imgs;
}
void filesys::makeLabels(string labels)
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
void filesys::loadLabels()
{
    string line;
    ifstream file("data/classes.txt");
    if(file.is_open())
    {
        labels.clear();
        while(!(file.eof()))
        {
            getline (file,line);
            if(line != "")
                labels.push_back(line);
        }
    }
    file.close();
}
vector<string> filesys::getLabels()
{
    return labels;
}
void filesys::writeAnnotation(string dir, string archiveName, string annotation)
{
    ofstream outfile;
    outfile.open(dir+"/"+archiveName+".txt", ios_base::app);

    if(outfile.is_open() && outfile.good())
    {
        outfile << annotation;
        outfile.close();
    }

}
