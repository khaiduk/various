/**
///\file Directory.cpp
///\brief definicje metod klasy Directory
///\author Chodorek Damian
///\date 14.06.2012
*/
///////////////////////////////////////////////////////////////////////////////////

#include "Directory.h"
#include <boost/filesystem.hpp>

vector<FileSystem::Element> FileSystem::Directory::content() const
{
    vector<FileSystem::Element> vect=vector<FileSystem::Element>();
    try
    {
           if(!(this->exists()))
           {
               return vect;
           }

           boost::filesystem::directory_iterator iter(path.getPath()+"\\");

            while(iter!=boost::filesystem::directory_iterator())
            {
                try
                {
                    string tmp=boost::filesystem::canonical(((*iter).path())).string();

                    if(FileSystem::Globals::whatIs(FileSystem::Path(tmp.c_str()))==FileSystem::Globals::file)
                    {
                        FileSystem::Element nowy=(FileSystem::File(tmp));
                        vect.push_back(nowy);

                    }else if(FileSystem::Globals::whatIs(FileSystem::Path(tmp.c_str()))==FileSystem::Globals::dir)
                    {
                        FileSystem::Element nowy=(FileSystem::File(tmp));
                        vect.push_back(nowy);
                    }
                }catch(...)
                {

                }

                ++iter;
            }
    }

    catch(...)
    {
        return vect;
    }
    return vect;
}


FileSystem::Directory::Directory(const Path& p)
{
    path=p;
}

FileSystem::Directory::operator FileSystem::Path() const
{
    return path;
}
