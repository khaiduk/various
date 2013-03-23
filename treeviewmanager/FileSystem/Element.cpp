/**
///\file Element.cpp
///\brief definicje metod klasy Element
///\author Chodorek Damian
///\date 14.06.2012
*/
///////////////////////////////////////////////////////////////////////////////////



#include "Element.h"
#include <sys/stat.h>
#include <boost/filesystem.hpp>
#include <sstream>


void FileSystem::Element::setPath(const FileSystem::Path& p)
{
    path=p;
}

FileSystem::Element::operator const FileSystem::Path&() const
{
    return path;
}



const FileSystem::Path& FileSystem::Element::getPath() const
{
    return path;
}

FileSystem::Path FileSystem::Element::getPath()
{
    return path;
}

string FileSystem::Element::getName() const
{
    string str=path;

    //ze œcie¿ki usuwa wszysztko oprócz liœcia (ostatniego wêz³a), który jest nazw¹

    for(int i=(str.length()-1); i>=0; --i)
    {
        if(str[i]=='/' || str[i]=='\\')
        {
            str.erase(i ,str.length());

        }else break;
    }

    for(int i=(str.length()-1); i>=0; --i)
    {
        if(str[i]=='\\' || str[i]=='/')
        {
            str.erase(0, i+1);
            break;
        }
    }

    return str;
}


FileSystem::Element::Perms FileSystem::Element::permissions() const
{
    if(!FileSystem::Globals::exists(path))
    {
        FileSystem::Element::Perms perm;
        perm.owner=FileSystem::Element::none;
        perm.group=FileSystem::Element::none;
        perm.others=FileSystem::Element::none;
        return perm;
    }

    struct stat sb;
    stat(path.getPath().c_str(), &sb);
    unsigned long p=sb.st_mode;
    stringstream tmp;
    tmp<<p;
    string str;
    tmp>>str;
    FileSystem::Element::Perms perm;


    if(str[2]=='1')
        perm.owner=FileSystem::Element::execute;
    else if(str[2]=='2')
        perm.owner=FileSystem::Element::write;
    else if(str[2]=='3')
        perm.owner=FileSystem::Element::writeExecute;
    else if(str[2]=='4')
        perm.owner=FileSystem::Element::read;
    else if(str[2]=='5')
        perm.owner=FileSystem::Element::readExecute;
    else if(str[2]=='6')
        perm.owner=FileSystem::Element::readWrite;
    else if(str[2]=='7')
        perm.owner=FileSystem::Element::all;
    else perm.owner=FileSystem::Element::none;


    if(str[3]=='1')
        perm.group=FileSystem::Element::execute;
    else if(str[3]=='2')
        perm.group=FileSystem::Element::write;
    else if(str[3]=='3')
        perm.group=FileSystem::Element::writeExecute;
    else if(str[3]=='4')
        perm.group=FileSystem::Element::read;
    else if(str[3]=='5')
        perm.group=FileSystem::Element::readExecute;
    else if(str[3]=='6')
        perm.group=FileSystem::Element::readWrite;
    else if(str[3]=='7')
        perm.group=FileSystem::Element::all;
    else perm.group=FileSystem::Element::none;

    if(str[4]=='1')
        perm.others=FileSystem::Element::execute;
    else if(str[4]=='2')
        perm.others=FileSystem::Element::write;
    else if(str[4]=='3')
        perm.others=FileSystem::Element::writeExecute;
    else if(str[4]=='4')
        perm.others=FileSystem::Element::read;
    else if(str[4]=='5')
        perm.others=FileSystem::Element::readExecute;
    else if(str[4]=='6')
        perm.others=FileSystem::Element::readWrite;
    else if(str[4]=='7')
        perm.others=FileSystem::Element::all;
    else perm.others=FileSystem::Element::none;


    return perm;
}

const char* FileSystem::Element::permissionsStr() const
{
    if(!FileSystem::Globals::exists(path))
    {
        return "---------";
    }

    struct stat sb;
    stat(path.getPath().c_str(), &sb);
    unsigned long p=sb.st_mode;
    stringstream tmp;
    tmp<<p;
    string str;
    tmp>>str;
    string perm="";


    if(str[2]=='1')
        perm+="--x";
    else if(str[2]=='2')
        perm+="-w-";
    else if(str[2]=='3')
        perm+="-wx";
    else if(str[2]=='4')
        perm+="r--";
    else if(str[2]=='5')
        perm+="r-x";
    else if(str[2]=='6')
        perm+="rw-";
    else if(str[2]=='7')
        perm+="rwx";
    else perm+="---";


    if(str[3]=='1')
        perm+="--x";
    else if(str[3]=='2')
        perm+="-w-";
    else if(str[3]=='3')
        perm+="-wx";
    else if(str[3]=='4')
        perm+="r--";
    else if(str[3]=='5')
        perm+="r-x";
    else if(str[3]=='6')
        perm+="rw-";
    else if(str[3]=='7')
        perm+="rwx";
    else perm+="---";

    if(str[4]=='1')
        perm+="--x";
    else if(str[4]=='2')
        perm+="-w-";
    else if(str[4]=='3')
        perm+="-wx";
    else if(str[4]=='4')
        perm+="r--";
    else if(str[4]=='5')
        perm+="r-x";
    else if(str[4]=='6')
        perm+="rw-";
    else if(str[4]=='7')
        perm+="rwx";
    else perm+="---";


    return perm.c_str();
}

void FileSystem::Element::remove()
{
    FileSystem::Globals::remove(path);
}

void FileSystem::Element::rename(const FileSystem::Path& p)
{
    FileSystem::Globals::rename(path, p);
}

void FileSystem::Element::rename(const char* c)
{
    FileSystem::Globals::rename(path, c);
}

void FileSystem::Element::move(const FileSystem::Path& dokad, FileSystem::Globals::copy_move_option option)
{
    FileSystem::Globals::move(path, dokad, option);
}

FileSystem::Globals::type FileSystem::Element::whatIs() const
{
    return FileSystem::Globals::whatIs(path);
}


void FileSystem::Element::copy(const Path& dokad, Globals::copy_move_option option) const
{
    FileSystem::Globals::copy(this->getPath(), dokad, option);
}

FileSystem::Path FileSystem::Element::parent() const
{
    if(!FileSystem::Globals::exists(path)) return FileSystem::Path(" ");
    try{
        string str=(boost::filesystem::canonical((boost::filesystem::path(path.getPath()).parent_path())).string());
        return FileSystem::Path(str);
    }catch(...)
    {
        return FileSystem::Path(" ");
    }
}


const char* FileSystem::Element::parentName() const
{
    if(!FileSystem::Globals::exists(path)) return NULL;
    try{
        string str=(boost::filesystem::canonical((boost::filesystem::path(path.getPath()).parent_path())).string());

        for(int i=(str.length()-1); i>=0; --i)
        {
            if(str[i]=='/' || str[i]=='\\')
            {
                str.erase(i ,str.length());

            }else break;
        }

        for(int i=(str.length()-1); i>=0; --i)
        {
            if(str[i]=='\\' || str[i]=='/')
            {
                str.erase(0, i+1);
                break;
            }
        }

        return str.c_str();

    }catch(...)
    {
        return NULL;
    }
}

uintmax_t FileSystem::Element::size() const
{
    return FileSystem::Globals::size(path);
}



bool FileSystem::Element::exists() const
{
    return FileSystem::Globals::exists(path);
}


int FileSystem::Element::positionTo(const FileSystem::Path& p) const
{
    try{
    return FileSystem::Globals::positionTo(path, p);
    }catch(...)
    {
        return 0;
    }
}


FileSystem::Path FileSystem::Element::rootDirectory() const
{
    return FileSystem::Globals::rootDirectory(path);
}


