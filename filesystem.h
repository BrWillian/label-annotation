#ifndef FILESYSTEM_H
#define FILESYSTEM_H
#include <fstream>
#include <vector>

using namespace std;

class filesystem
{
private:
    vector<string>imgs;
    vector<string>labels;
public:
    filesystem();
    void listDir(string dir);
    vector<string> getImgs();
    vector<string> getLabels();
    static void makeLabels(string labels);
    void loadLabels();
};

#endif // FILESYSTEM_H
