#include <filesys.h>
#include <sstream>
#include <QDir>

filesys::filesys()
{

}
void filesys::listDir(string path)
{
    imgs.clear();
    QStringList nameFilter;
    nameFilter << "*.png" << "*.jpg" << "*.gif" << "*.jpeg";
    QDir dir(QString::fromStdString(path));
    dir.setSorting(QDir::Name);
    dir.setFilter(QDir::NoDotAndDotDot | QDir::Files | QDir::Dirs);
    dir.setNameFilters(nameFilter);

    foreach(const QFileInfo& fi, dir.entryList())
    {
        QString strtmp = QString::fromStdString(path)+QDir::separator()+fi.fileName();
        imgs.push_back(strtmp.toStdString());
    }

}
vector<string> filesys::getImgs()
{
    return imgs;
}
void filesys::makeLabels(string labels)
{
    QDir dir;

    if(!(dir.exists("data")))
    {
        dir.mkdir("data");
    }

    ofstream outfile;

    QString strtmp = QString("data")+QDir::separator()+QString("classes.txt");
    outfile.open(strtmp.toStdString());

    if(outfile.is_open() && outfile.good())
    {
        outfile << labels;
        outfile.close();
    }

}
void filesys::loadLabels()
{
    string line;
    QString strtmp = QString("data")+QDir::separator()+QString("classes.txt");
    ifstream file(strtmp.toStdString());
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
    QString strtmp = QString::fromStdString(dir)+QDir::separator()+QString::fromStdString(archiveName)+QString(".txt");
    outfile.open(strtmp.toStdString(), ios_base::app);

    if(outfile.is_open() && outfile.good())
    {
        outfile << annotation;
        outfile.close();
    }
}
std::string filesys::returnStem(string str)
{
    const size_t last_slash_idx = str.find_last_of("\\/");
    if (std::string::npos != last_slash_idx)
    {
        str.erase(0, last_slash_idx + 1);
    }

    const size_t period_idx = str.rfind('.');
    if (std::string::npos != period_idx)
    {
        str.erase(period_idx);
    }
    return str;
}
void filesys::removeFile(string nameFile)
{
    try{
        QDir dir;
        dir.remove(QString::fromStdString(nameFile));
    }
    catch(int err){

    }

}
