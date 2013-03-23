/**
///\file File.cpp
///\brief definicje metod klasy File
///\author Chodorek Damian
///\date 14.06.2012
*/
///////////////////////////////////////////////////////////////////////////////////

#include "File.h"
#include <boost/filesystem.hpp>
#include<cstdlib>

bool FileSystem::File::execute() const
{
    if(!FileSystem::Globals::exists(path)) return false;

    if(this->whatIs()==FileSystem::Globals::file)
    {
        system(path);
        return true;
    }else return false;
}

const char* FileSystem::File::extension() const
{
    if(this->whatIs()!=FileSystem::Globals::file) return NULL;

    string str=this->getName();

    unsigned int i=0;
    while(i<str.length())
    {
        if(str[i]=='.')
        {
            str.erase(0, i);
        }
        ++i;
    }

    return str.c_str();
}


FileSystem::File::File(const FileSystem::Path& p)
{
    path=p;
}

FileSystem::File::operator FileSystem::Path() const
{
    return path;
}
