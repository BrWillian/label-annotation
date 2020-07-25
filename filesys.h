#ifndef FILESYS_H
#define FILESYS_H
#include <fstream>
#include <vector>

using namespace std;

class filesys
{
private:
    vector<string>imgs;
    vector<string>labels;
    vector<string>imgs_stem;
public:
    filesys();
    void listDir(string dir);
    vector<string> getImgs();
    vector<string> getLabels();
    static void makeLabels(string labels);
    void loadLabels();
    void writeAnnotation(string dir, string archiveName, string annotation);
    std::string returnStem(string str);
    void removeFile(string nameFile);
};

#endif // FILESYS_H
